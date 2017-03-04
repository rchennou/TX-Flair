// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/03
//  filename:   X8.cpp
//
//  author:     Majd Saied, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un X8
//
/*********************************************************************/

#include "X8.h"
#include "Simulator.h"
#include <SimuBldc.h>
#include <TabWidget.h>
#include <Tab.h>
#include <DoubleSpinBox.h>
#include <GroupBox.h>
#include <math.h>
#ifdef GL
#include <ISceneManager.h>
#include "Blade.h"
#include "MeshSceneNode.h"
#include "Gui.h"
#include <Mutex.h>
#endif

#define K_MOT 0.4f    // blade animation
#define G (float)9.81 // gravity ( N/(m/s²) )

#ifdef GL
using namespace irr::video;
using namespace irr::scene;
using namespace irr::core;
#endif
using namespace flair::core;
using namespace flair::gui;
using namespace flair::actuator;

namespace flair {
namespace simulator {

X8::X8(const Simulator *parent, std::string name, int dev_id)
    : Model(parent, name) {
  Tab *setup_tab = new Tab(GetTabWidget(), "model");
  m = new DoubleSpinBox(setup_tab->NewRow(), "mass (kg):", 0, 20, 0.1);
  arm_length = new DoubleSpinBox(setup_tab->LastRowLastCol(), "arm length (m):",
                                 0, 2, 0.1);
  l_cg = new DoubleSpinBox(
      setup_tab->LastRowLastCol(), "position G (m):", -0.5, 0.5,
      0.02); // position du centre de gravité/centre de poussé
  k_mot =
      new DoubleSpinBox(setup_tab->NewRow(), "k_mot:", 0, 1, 0.001,
                        3); // vitesse rotation² (unité arbitraire) -> force (N)
  c_mot = new DoubleSpinBox(
      setup_tab->LastRowLastCol(), "c_mot:", 0, 1, 0.001,
      3); // vitesse rotation moteur -> couple (N.m/unité arbitraire)
  f_air_vert = new DoubleSpinBox(setup_tab->NewRow(), "f_air_vert:", 0, 10,
                                 1); // frottements air depl. vertical, aussi
                                     // utilisé pour les rotations ( N/(m/s) )
                                     // (du aux helices en rotation)
  f_air_lat =
      new DoubleSpinBox(setup_tab->LastRowLastCol(), "f_air_lat:", 0, 10,
                        1); // frottements air deplacements lateraux ( N/(m/s) )
  j_roll = new DoubleSpinBox(setup_tab->NewRow(), "j_roll:", 0, 1, 0.001,
                             5); // moment d'inertie d'un axe (N.m.s²/rad)
  j_pitch =
      new DoubleSpinBox(setup_tab->LastRowLastCol(), "j_pitch:", 0, 1, 0.001,
                        5); // moment d'inertie d'un axe (N.m.s²/rad)
  j_yaw = new DoubleSpinBox(setup_tab->LastRowLastCol(), "j_yaw:", 0, 1, 0.001,
                            5); // moment d'inertie d'un axe (N.m.s²/rad)
  j_r = new DoubleSpinBox(setup_tab->NewRow(), "j_r:", 0, 1,
                          0.001); // moment des helices (N.m.s²/rad)
  sigma = new DoubleSpinBox(
      setup_tab->LastRowLastCol(), "sigma:", 0, 1,
      0.1); // coefficient de perte d efficacite aerodynamique (sans unite)
  S = new DoubleSpinBox(
      setup_tab->LastRowLastCol(), "S:", 1, 2,
      0.1); // coefficient de forme des helices 1<S=1+Ss/Sprop<2 (sans unite)

  motors = new SimuBldc(this, name, 8, dev_id);
}

void X8::Draw() {
#ifdef GL

  // create unite (1m=100cm) UAV; scale will be adapted according to arm_length
  // parameter
  // note that the frame used is irrlicht one:
  // left handed, North East Up

  const IGeometryCreator *geo;
  geo = getGui()->getSceneManager()->getGeometryCreator();

  // cylinders are aligned with y axis
  red_arm = geo->createCylinderMesh(2.5, 100, 16, SColor(0, 255, 0, 0));
  black_arm = geo->createCylinderMesh(2.5, 100, 16, SColor(0, 128, 128, 128));
  motor = geo->createCylinderMesh(7.5, 15, 16); //,SColor(0, 128, 128, 128));
  // geo->drop();

  ITexture *texture = getGui()->getTexture("carbone.jpg");
  fl_arm = new MeshSceneNode(this, red_arm, vector3df(0, 0, 0),
                             vector3df(0, 0, -135));
  fr_arm = new MeshSceneNode(this, red_arm, vector3df(0, 0, 0),
                             vector3df(0, 0, -45));
  rl_arm = new MeshSceneNode(this, black_arm, vector3df(0, 0, 0),
                             vector3df(0, 0, 135), texture);
  rr_arm = new MeshSceneNode(this, black_arm, vector3df(0, 0, 0),
                             vector3df(0, 0, 45), texture);

  texture = getGui()->getTexture("metal047.jpg");
  tfl_motor = new MeshSceneNode(this, motor, vector3df(70.71, -70.71, 2.5),
                                vector3df(90, 0, 0), texture);
  tfr_motor = new MeshSceneNode(this, motor, vector3df(70.71, 70.71, 2.5),
                                vector3df(90, 0, 0), texture);
  trl_motor = new MeshSceneNode(this, motor, vector3df(-70.71, -70.71, 2.5),
                                vector3df(90, 0, 0), texture);
  trr_motor = new MeshSceneNode(this, motor, vector3df(-70.71, 70.71, 2.5),
                                vector3df(90, 0, 0), texture);

  bfl_motor = new MeshSceneNode(this, motor, vector3df(70.71, -70.71, -17.5),
                                vector3df(90, 0, 0), texture);
  bfr_motor = new MeshSceneNode(this, motor, vector3df(70.71, 70.71, -17.5),
                                vector3df(90, 0, 0), texture);
  brl_motor = new MeshSceneNode(this, motor, vector3df(-70.71, -70.71, -17.5),
                                vector3df(90, 0, 0), texture);
  brr_motor = new MeshSceneNode(this, motor, vector3df(-70.71, 70.71, -17.5),
                                vector3df(90, 0, 0), texture);

  tfl_blade = new Blade(this, vector3df(70.71, -70.71, 17.5));
  tfr_blade = new Blade(this, vector3df(70.71, 70.71, 17.5), true);
  trl_blade = new Blade(this, vector3df(-70.71, -70.71, 17.5), true);
  trr_blade = new Blade(this, vector3df(-70.71, 70.71, 17.5));

  bfl_blade = new Blade(this, vector3df(70.71, -70.71, -17.5));
  bfr_blade = new Blade(this, vector3df(70.71, 70.71, -17.5), true);
  brl_blade = new Blade(this, vector3df(-70.71, -70.71, -17.5), true);
  brr_blade = new Blade(this, vector3df(-70.71, 70.71, -17.5));

  motor_speed_mutex = new Mutex(this);
  for (int i = 0; i < 8; i++)
    motor_speed[i] = 0;
  ExtraDraw();
#endif
}

X8::~X8() {
  // les objets irrlicht seront automatiquement detruits (moteurs, helices,
  // pales) par parenté
}

#ifdef GL
void X8::AnimateModel(void) {
  motor_speed_mutex->GetMutex();
  tfl_blade->SetRotationSpeed(K_MOT * motor_speed[0]);
  tfr_blade->SetRotationSpeed(-K_MOT * motor_speed[1]);
  trl_blade->SetRotationSpeed(-K_MOT * motor_speed[2]);
  trr_blade->SetRotationSpeed(K_MOT * motor_speed[3]);

  bfl_blade->SetRotationSpeed(-K_MOT * motor_speed[4]);
  bfr_blade->SetRotationSpeed(K_MOT * motor_speed[5]);
  brl_blade->SetRotationSpeed(K_MOT * motor_speed[6]);
  brr_blade->SetRotationSpeed(-K_MOT * motor_speed[7]);
  motor_speed_mutex->ReleaseMutex();

  // adapt UAV size
  if (arm_length->ValueChanged() == true) {
    setScale(arm_length->Value());
  }
}

size_t X8::dbtSize(void) const {
  return 6 * sizeof(float) + 4 * sizeof(float); // 6ddl+4helices
}

void X8::WritedbtBuf(
    char *dbtbuf) { /*
                       float *buf=(float*)dbtbuf;
                       vector3df vect=getPosition();
                       memcpy(buf,&vect.X,sizeof(float));
                       buf++;
                       memcpy(buf,&vect.Y,sizeof(float));
                       buf++;
                       memcpy(buf,&vect.Z,sizeof(float));
                       buf++;
                       vect=getRotation();
                       memcpy(buf,&vect.X,sizeof(float));
                       buf++;
                       memcpy(buf,&vect.Y,sizeof(float));
                       buf++;
                       memcpy(buf,&vect.Z,sizeof(float));
                       buf++;
                       memcpy(buf,&motors,sizeof(rtsimu_motors));*/
}

void X8::ReaddbtBuf(
    char *dbtbuf) { /*
                       float *buf=(float*)dbtbuf;
                       vector3df vect;
                       memcpy(&vect.X,buf,sizeof(float));
                       buf++;
                       memcpy(&vect.Y,buf,sizeof(float));
                       buf++;
                       memcpy(&vect.Z,buf,sizeof(float));
                       buf++;
                       setPosition(vect);
                       memcpy(&vect.X,buf,sizeof(float));
                       buf++;
                       memcpy(&vect.Y,buf,sizeof(float));
                       buf++;
                       memcpy(&vect.Z,buf,sizeof(float));
                       buf++;
                       ((ISceneNode*)(this))->setRotation(vect);
                       memcpy(&motors,buf,sizeof(rtsimu_motors));
                       AnimateModele();*/
}
#endif // GL

// states are computed on fixed frame NED
// x north
// y east
// z down
void X8::CalcModel(void) {
  float tfl_speed, tfr_speed, trl_speed, trr_speed;
  float bfl_speed, bfr_speed, brl_speed, brr_speed;
  float u_roll, u_pitch, u_yaw, u_thrust;
  float omega;
#ifdef GL
  motor_speed_mutex->GetMutex();
#endif // GL
  motors->GetSpeeds(motor_speed);
#ifdef GL
  motor_speed_mutex->ReleaseMutex();
#endif // GL
  tfl_speed = motor_speed[0];
  tfr_speed = motor_speed[1];
  trl_speed = motor_speed[2];
  trr_speed = motor_speed[3];
  bfl_speed = motor_speed[4];
  bfr_speed = motor_speed[5];
  brl_speed = motor_speed[6];
  brr_speed = motor_speed[7];

  omega = tfl_speed + brl_speed + trr_speed + bfr_speed - bfl_speed -
          trl_speed - brr_speed - tfr_speed;

  /*
      ** ===================================================================
      **    u roll: roll torque
      **
      ** ===================================================================
      */

  u_roll = arm_length->Value() * k_mot->Value() *
           (sigma->Value() * tfl_speed * tfl_speed + bfl_speed * bfl_speed +
            sigma->Value() * trl_speed * trl_speed + brl_speed * brl_speed -
            sigma->Value() * tfr_speed * tfr_speed - bfr_speed * bfr_speed -
            sigma->Value() * trr_speed * trr_speed - brr_speed * brr_speed) *
           sqrtf(2) / 2;

  /// Classical Nonlinear model of a quadrotor ( This is the w_x angular speed
  /// of the quadri in the body frame). It is a discrete integrator
  // state[0].W.x=(dT()/j_roll->Value())*((j_yaw->Value()-j_pitch->Value())*state[-1].W.y*state[-1].W.z-j_r->Value()*state[-1].W.y*omega
  // + u_roll) +state[-1].W.x;//Osamah
  state[0].W.x =
      (dT() / j_roll->Value()) *
          ((j_pitch->Value() - j_yaw->Value()) * state[-1].W.y * state[-1].W.z -
           j_r->Value() * state[-1].W.y * omega + u_roll) +
      state[-1].W.x; // Majd

  // state[0].W.x=(dT()/j_roll->Value())*(u_roll-m->Value()*G*l_cg->Value()*sinf(state[-2].W.x)-f_air_vert->Value()*arm_length->Value()*arm_length->Value()*state[-1].W.x)+state[-1].W.x;

  /*
  ** ===================================================================
  **   u pitch : pitch torque
  **
  ** ===================================================================
  */
  u_pitch = arm_length->Value() * k_mot->Value() *
            (sigma->Value() * tfl_speed * tfl_speed + bfl_speed * bfl_speed +
             sigma->Value() * tfr_speed * tfr_speed + bfr_speed * bfr_speed -
             sigma->Value() * trl_speed * trl_speed - brl_speed * brl_speed -
             sigma->Value() * trr_speed * trr_speed - brr_speed * brr_speed) *
            sqrtf(2) / 2;

  /// Classical Nonlinear model of a quadrotor ( This is the w_y angular speed
  /// of the quadri in the body frame). It is a discrete integrator
  // state[0].W.y=(dT()/j_pitch->Value())*((j_roll->Value()-j_yaw->Value())*state[-1].W.x*state[-1].W.z-j_r->Value()*state[-1].W.x*omega
  // + u_pitch)+state[-1].W.y;//Osamah
  state[0].W.y =
      (dT() / j_pitch->Value()) *
          ((j_yaw->Value() - j_roll->Value()) * state[-1].W.x * state[-1].W.z -
           j_r->Value() * state[-1].W.x * omega + u_pitch) +
      state[-1].W.y; // Majd

  // state[0].W.y=(dT()/j_pitch->Value())*(u_pitch-m->Value()*G*l_cg->Value()*sinf(state[-2].W.y)-f_air_vert->Value()*arm_length->Value()*arm_length->Value()*state[-1].W.y)+state[-1].W.y;

  /*
  ** ===================================================================
  **    u yaw : yaw torque
  **
  ** ===================================================================
  */
  u_yaw = c_mot->Value() * (tfl_speed * tfl_speed - bfl_speed * bfl_speed +
                            trr_speed * trr_speed - brr_speed * brr_speed -
                            tfr_speed * tfr_speed + bfr_speed * bfr_speed -
                            trl_speed * trl_speed + brl_speed * brl_speed);

  /// Classical Nonlinear model of a quadrotor ( This is the w_z angular speed
  /// of the quadri in the body frame). It is a discrete integrator
  // state[0].W.z=(dT()/j_yaw->Value())* u_yaw +state[-1].W.z;//Osamah
  state[0].W.z =
      (dT() / j_yaw->Value()) * ((j_roll->Value() - j_pitch->Value()) *
                                     state[-1].W.x * state[-1].W.y +
                                 u_yaw) +
      state[-1].W.z; // Majd

  // state[0].W.z=(dT()/j_yaw->Value())*(u_yaw-f_air_lat->Value()*state[-1].W.z)+state[-1].W.z;

  // compute quaternion from W
  // Quaternion derivative: dQ = 0.5*(Q*Qw)
  Quaternion dQ = state[-1].Quat.GetDerivative(state[0].W);

  // Quaternion integration
  state[0].Quat = state[-1].Quat + dQ * dT();
  state[0].Quat.Normalize();

  // Calculation of the thrust from the reference speed of motors
  u_thrust =
      k_mot->Value() * S->Value() *
      (sigma->Value() * tfl_speed * tfl_speed +
       sigma->Value() * tfr_speed * tfr_speed +
       sigma->Value() * trl_speed * trl_speed +
       sigma->Value() * trr_speed * trr_speed + bfl_speed * bfl_speed +
       bfr_speed * bfr_speed + brl_speed * brl_speed + brr_speed * brr_speed);
  Vector3D vect(0, 0, -u_thrust);
  vect.Rotate(state[0].Quat);

  /*
      ** ===================================================================
      **     x double integrator
      **
      ** ===================================================================
      */
  state[0].Pos.x =
      (dT() * dT() / m->Value()) *
          (vect.x -
           f_air_lat->Value() * (state[-1].Pos.x - state[-2].Pos.x) / dT()) +
      2 * state[-1].Pos.x - state[-2].Pos.x;
  state[0].Vel.x = (state[0].Pos.x - state[-1].Pos.x) / dT();

  /*
      ** ===================================================================
      **     y double integrator
      **
      ** ===================================================================
      */
  state[0].Pos.y =
      (dT() * dT() / m->Value()) *
          (vect.y -
           f_air_lat->Value() * (state[-1].Pos.y - state[-2].Pos.y) / dT()) +
      2 * state[-1].Pos.y - state[-2].Pos.y;
  state[0].Vel.y = (state[0].Pos.y - state[-1].Pos.y) / dT();

  /*
  ** ===================================================================
  **     z double integrator
  **
  ** ===================================================================
  */
  state[0].Pos.z =
      (dT() * dT() / m->Value()) *
          (vect.z +
           f_air_vert->Value() * (state[-1].Pos.z - state[-2].Pos.z) / dT() +
           m->Value() * G) +
      2 * state[-1].Pos.z - state[-2].Pos.z;
  state[0].Vel.z = (state[0].Pos.z - state[-1].Pos.z) / dT();

#ifndef GL
  if (state[0].Pos.z < 0)
    state[0].Pos.z = 0;
#endif
}

} // end namespace simulator
} // end namespace flair
