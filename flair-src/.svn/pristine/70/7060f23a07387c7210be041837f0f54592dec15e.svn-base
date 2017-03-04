// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/15
//  filename:   Man.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe chargeant un personnage
//
/*********************************************************************/
#ifdef GL

#include "Man.h"
#include "Gui.h"
#include "Simulator.h"
#include "Simulator_impl.h"
#include "Euler.h"
#include <ISceneManager.h>
#include <IAnimatedMeshSceneNode.h>
#include <Tab.h>
#include <DoubleSpinBox.h>
#include "FollowMeCamera.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace simulator {

Man::Man(const Simulator *parent, std::string name) : Model(parent, name) {
  node = getGui()->getSceneManager()->addAnimatedMeshSceneNode(
      getGui()->getMesh("ninja.b3d"), getSceneNode(), -1, vector3df(0, 0, 0),
      vector3df(90, 0, 90), vector3df(10, 10, 10));

  node->setFrameLoop(0, 13);
  node->setAnimationSpeed(0);
  node->getMaterial(0).NormalizeNormals = true;
  node->getMaterial(0).Lighting = false;

  getFollowMeCamera()->setPositionOffset(vector3df(0, 0, -1));
  getFollowMeCamera()->setTargetOffset(vector3df(0, 0, -1));

  setTriangleSelector(
      getGui()->getSceneManager()->createTriangleSelector(node));
  Box()->addInternalBox(node->getTransformedBoundingBox());

  Tab *setup_tab = new Tab(GetTabWidget(), "model");
  t_speed = new DoubleSpinBox(setup_tab->NewRow(), "translational speed (m/s):",
                              0, 5, 0.1);
  r_speed = new DoubleSpinBox(setup_tab->NewRow(), "rotational speed (deg/s):",
                              0, 180, 10);
}

Man::~Man() {}

void Man::CalcModel(void) {
  // compute quaternion from W
  // Quaternion derivative: dQ = 0.5*(Q*Qw)
  Quaternion dQ = state[-1].Quat.GetDerivative(state[0].W);

  // Quaternion integration
  state[0].Quat = state[-1].Quat + dQ * dT();
  state[0].Quat.Normalize();

  Vector3D dir = state[0].Vel;
  dir.Rotate(state[0].Quat);
  state[0].Pos = state[-1].Pos + dT() * dir;
}

bool Man::OnEvent(const SEvent &event) {
  if (event.EventType != EET_KEY_INPUT_EVENT)
    return false;

  if (event.KeyInput.PressedDown == false) {
    state[0].Vel.x = 0;
    state[0].W.z = 0;
    node->setAnimationSpeed(0);
  } else {
    switch (event.KeyInput.Key) {
    case KEY_UP:
      state[0].Vel.x = t_speed->Value();
      node->setAnimationSpeed(t_speed->Value() * 10.f);
      break;
    case KEY_DOWN:
      state[0].Vel.x = -t_speed->Value();
      node->setAnimationSpeed(-t_speed->Value() * 10.f);
      break;
    case KEY_LEFT:
      state[0].W.z = -Euler::ToRadian(r_speed->Value());
      node->setAnimationSpeed(r_speed->Value() * .15f);
      break;
    case KEY_RIGHT:
      state[0].W.z = Euler::ToRadian(r_speed->Value());
      node->setAnimationSpeed(-r_speed->Value() * .15f);
      break;
    default:
      return false;
      break;
    }
  }

  return true;
}

size_t Man::dbtSize(void) const { return 6 * sizeof(float); }

void Man::WritedbtBuf(char *dbtbuf) { /*
                                         float *buf=(float*)dbtbuf;
                                         vector3df vect=node->getPosition();
                                         memcpy(buf,&vect.X,sizeof(float));
                                         buf++;
                                         memcpy(buf,&vect.Y,sizeof(float));
                                         buf++;
                                         memcpy(buf,&vect.Z,sizeof(float));
                                         buf++;
                                         vect=node->getRotation();
                                         memcpy(buf,&vect.X,sizeof(float));
                                         buf++;
                                         memcpy(buf,&vect.Y,sizeof(float));
                                         buf++;
                                         memcpy(buf,&vect.Z,sizeof(float));
                                         buf++;*/
}

void Man::ReaddbtBuf(char *dbtbuf) { /*
                                        float *buf=(float*)dbtbuf;
                                        vector3df vect;
                                        memcpy(&vect.X,buf,sizeof(float));
                                        buf++;
                                        memcpy(&vect.Y,buf,sizeof(float));
                                        buf++;
                                        memcpy(&vect.Z,buf,sizeof(float));
                                        buf++;
                                        node->setPosition(vect);
                                        memcpy(&vect.X,buf,sizeof(float));
                                        buf++;
                                        memcpy(&vect.Y,buf,sizeof(float));
                                        buf++;
                                        memcpy(&vect.Z,buf,sizeof(float));
                                        buf++;
                                        node->setRotation(vect);
                                        node->setAnimationSpeed(2.f);*/
}

} // end namespace simulator
} // end namespace flair
#endif // GL
