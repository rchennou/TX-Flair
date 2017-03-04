// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   Model_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un modele a simuler
//
/*********************************************************************/

#include "Model.h"
#include "Model_impl.h"
#include "Simulator.h"
#include "TabWidget.h"
#include "Tab.h"
#include "DoubleSpinBox.h"
#include "Vector3DSpinBox.h"
#include "SpinBox.h"
#include "CheckBox.h"
#include "cvmatrix.h"
#include "Euler.h"
#include <math.h>

#ifdef GL
#include "ConditionVariable.h"
#include "Gui.h"
#include "Gui_impl.h"
#include <ISceneManager.h>
#include <ISceneNodeAnimatorCollisionResponse.h>
#include <IMetaTriangleSelector.h>
#include <IVideoDriver.h>
#include <ICameraSceneNode.h>
#include "FollowMeCamera.h"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace io;
#endif

using namespace flair::core;
using namespace flair::gui;
using namespace flair::simulator;

#ifdef GL
Model_impl::Model_impl(Model *self, std::string name,
                       ISceneManager *scenemanager, vrpn_Connection_IP *vrpn)
    : ISceneNode(scenemanager->getRootSceneNode(), scenemanager, -1),
      Thread(self, name, 50), vrpn_Tracker(name.c_str(), vrpn)

#else
Model_impl::Model_impl(Model *self, std::string name, vrpn_Connection_IP *vrpn)
    : Thread(self, name, 50), vrpn_Tracker(name.c_str(), vrpn)
#endif
{
  this->self = self;

#ifdef GL
  // for sync with gui
  cond = new ConditionVariable(this, name);
  sync_count = 0;

  // collisions
  collision_mutex = new Mutex(this);
  collision_occured = false;

  // selector for collisions
  selector = getSceneManager()->createTriangleSelectorFromBoundingBox(this);
  setTriangleSelector(selector);
  meta_selector = getSceneManager()->createMetaTriangleSelector();

  anim = getSceneManager()->createCollisionResponseAnimator(
      meta_selector, this, vector3df(1, 1, 1), vector3df(0, 0, 0),
      vector3df(0, 0, 0));
  addAnimator(anim);

  // camera
  camera = new FollowMeCamera(this,name);

  position_init = false;
#endif

  // init user interface
  Tab *tab = new Tab(getSimulator()->GetTabWidget(), ObjectName());
  tabwidget = new TabWidget(tab->NewRow(), "tabs");
  Tab *sampl = new Tab(tabwidget, "sampling");
  dT = new DoubleSpinBox(sampl->NewRow(), "Tech (s):", 0.001, 1, 0.001, 3);
  Tab *layout = new Tab(tabwidget, "optitrack");
  enable_opti = new CheckBox(layout->NewRow(), "enabled");
  Tab *init = new Tab(tabwidget, "init");
  pos_init = new Vector3DSpinBox(init->NewRow(), "position", -50, 50, 1);
  yaw_init = new SpinBox(init->NewRow(), "yaw (deg):", -180, 180, 10);

  // modele
  states_mutex = new Mutex(this);
  self->state[0].Pos = pos_init->Value();
  self->state[0].Vel.x = 0;
  self->state[0].Vel.y = 0;
  self->state[0].Vel.z = 0;
  self->state[0].Quat = ComputeInitRotation(Quaternion(1, 0, 0, 0));
  self->state[0].W.x = 0;
  self->state[0].W.y = 0;
  self->state[0].W.z = 0;

  self->state[-1] = self->state[0];
  self->state[-2] = self->state[0];

  cvmatrix_descriptor *desc = new cvmatrix_descriptor(13, 1);
  desc->SetElementName(0, 0, "q0");
  desc->SetElementName(1, 0, "q1");
  desc->SetElementName(2, 0, "q2");
  desc->SetElementName(3, 0, "q3");
  desc->SetElementName(4, 0, "x");
  desc->SetElementName(5, 0, "y");
  desc->SetElementName(6, 0, "z");
  desc->SetElementName(7, 0, "wx");
  desc->SetElementName(8, 0, "wy");
  desc->SetElementName(9, 0, "wz");
  desc->SetElementName(10, 0, "vx");
  desc->SetElementName(11, 0, "vy");
  desc->SetElementName(12, 0, "vz");
  output = new cvmatrix(this, desc, floatType, "state");

  self->AddDataToLog(output);
}

Model_impl::~Model_impl() {
  SafeStop();
  Join();
#ifdef GL
  remove(); // remove ISceneNode
#endif
}

Quaternion Model_impl::ComputeInitRotation(Quaternion quat_in) {
  Quaternion yaw_rot_quat;
  Euler yaw_rot_euler(0, 0, Euler::ToRadian(yaw_init->Value()));
  yaw_rot_euler.ToQuaternion(yaw_rot_quat);
  return yaw_rot_quat * quat_in;
}

void Model_impl::mainloop(void) {
  if (enable_opti->Value() == false)
    return;
  vrpn_gettimeofday(&_timestamp, NULL);
  vrpn_Tracker::timestamp = _timestamp;

  // change to vrpn reference
  states_mutex->GetMutex();
  Quaternion quat = getSimulator()->ToVRPNReference(self->state[0].Quat);
  Vector3D position = getSimulator()->ToVRPNReference(self->state[0].Pos);
  states_mutex->ReleaseMutex();

  pos[0] = position.x;
  pos[1] = position.y;
  pos[2] = position.z;
  // warning: d_quat is defined as (qx,qy,qz,qw), which is different from
  // flair::core::Quaternion
  d_quat[0] = quat.q1;
  d_quat[1] = quat.q2;
  d_quat[2] = quat.q3;
  d_quat[3] = quat.q0;

  char msgbuf[1000];

  d_sensor = 0;

  int len = vrpn_Tracker::encode_to(msgbuf);

  if (d_connection->pack_message(len, _timestamp, position_m_id, d_sender_id,
                                 msgbuf, vrpn_CONNECTION_LOW_LATENCY)) {
    fprintf(stderr, "can't write message: tossing\n");
  }

  server_mainloop();
}

#ifdef GL
ITriangleSelector *Model_impl::TriangleSelector(void) { return selector; }

IMetaTriangleSelector *Model_impl::MetaTriangleSelector(void) {
  return meta_selector;
}

void Model_impl::UpdatePos(void) {
  vector3df nodePosition;
  Quaternion nodeOrientation;
  Euler euler;

  states_mutex->GetMutex();
  nodePosition = ToIrrlichtCoordinates(self->state[0].Pos);
  nodeOrientation = ToIrrlichtOrientation(self->state[0].Quat);
  states_mutex->ReleaseMutex();

  setPosition(nodePosition);

  nodeOrientation.ToEuler(euler);
  ISceneNode::setRotation(Euler::ToDegree(1) *
                          vector3df(euler.roll, euler.pitch, euler.yaw));

  if (position_init == false) {
    anim->setTargetNode(this); // a faire pour se teleporter sans les collisions
    position_init = true;
  }

  self->AnimateModel();
}

void Model_impl::CheckCollision(void) {
  // TODO: setEllipsoidRadius should be called in Model::setScale
  // but we need to call recalculateBoundingBox
  anim->setEllipsoidRadius(getTransformedBoundingBox().getExtent());

  if (anim->collisionOccurred() == true) {
    vector3df pos;
    vector3df pos_rel;
    vector3df nodePosition;
    pos = anim->getCollisionPoint();
    nodePosition = getPosition();
    pos_rel = pos - nodePosition;
    // printf("collision %f %f %f\n",pos.X,pos.Y,pos.Z);
    // printf("drone %f %f %f\n",nodePosition.X,nodePosition.Y,nodePosition.Z);
    // printf("rel %f %f %f\n",pos_rel.X,pos_rel.Z,pos_rel.Y);

    collision_mutex->GetMutex();
    collision_occured = true;
    collision_point = ToSimulatorCoordinates(nodePosition);
    collision_mutex->ReleaseMutex();
  }
}

void Model_impl::CollisionHandler(void) {
  collision_mutex->GetMutex();
  if (collision_occured == true) {
    collision_occured = false;
    states_mutex->GetMutex();
    self->state[0].Pos = collision_point;
    self->state[-1].Pos = self->state[0].Pos;
    self->state[-2].Pos = self->state[0].Pos;
    states_mutex->ReleaseMutex();
  }
  collision_mutex->ReleaseMutex();
}

void Model_impl::OnRegisterSceneNode(void) {
  if (IsVisible)
    SceneManager->registerNodeForRendering(this);

  ISceneNode::OnRegisterSceneNode();
}

void Model_impl::render(void) {
  IVideoDriver *driver = SceneManager->getVideoDriver();
  driver->setTransform(ETS_WORLD, AbsoluteTransformation);
}

// le premier arrive attend l'autre
void Model_impl::SynchronizationPoint() {
  cond->GetMutex();
  sync_count++;

  if (sync_count < 2) {
    cond->CondWait();
  } else {
    cond->CondSignal();
  }

  cond->ReleaseMutex();
}
#endif // GL

void Model_impl::Run(void) {
  // Ask Xenomai to warn us upon switches to secondary mode.
  WarnUponSwitches(true);

#ifdef GL
  // synchronize with gui
  SynchronizationPoint();
#endif

  SetPeriodMS(dT->Value() * 1000.);

  while (!ToBeStopped()) {
    if (dT->ValueChanged())
      SetPeriodMS(dT->Value() * 1000.);
    WaitPeriod();

#ifdef GL
    CollisionHandler();
#endif
    states_mutex->GetMutex();
    self->CalcModel();

    output->GetMutex();
    output->SetValueNoMutex(0, 0, self->state[0].Quat.q0);
    output->SetValueNoMutex(1, 0, self->state[0].Quat.q1);
    output->SetValueNoMutex(2, 0, self->state[0].Quat.q2);
    output->SetValueNoMutex(3, 0, self->state[0].Quat.q3);
    output->SetValueNoMutex(4, 0, self->state[0].Pos.x);
    output->SetValueNoMutex(5, 0, self->state[0].Pos.y);
    output->SetValueNoMutex(6, 0, self->state[0].Pos.z);
    output->SetValueNoMutex(7, 0, self->state[0].W.x);
    output->SetValueNoMutex(8, 0, self->state[0].W.y);
    output->SetValueNoMutex(9, 0, self->state[0].W.z);
    output->SetValueNoMutex(10, 0, self->state[0].Vel.x);
    output->SetValueNoMutex(11, 0, self->state[0].Vel.y);
    output->SetValueNoMutex(12, 0, self->state[0].Vel.z);
    output->ReleaseMutex();
    output->SetDataTime(GetTime());

    self->state.Update();

    if (pos_init->ValueChanged() || yaw_init->ValueChanged()) {
      self->state[-1].Quat = ComputeInitRotation(Quaternion(1, 0, 0, 0));
      self->state[-2].Quat = ComputeInitRotation(Quaternion(1, 0, 0, 0));
      self->state[-1].Pos = pos_init->Value();
      self->state[-2].Pos = self->state[-1].Pos;
#ifdef GL
      position_init = false;
#endif
    }

    states_mutex->ReleaseMutex();

    self->ProcessUpdate(output);
  }

  WarnUponSwitches(false);
}
