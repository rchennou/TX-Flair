// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/03
//  filename:   VrpnObject.cpp
//
//  author:     César Richard, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet vrpn
//
//
/*********************************************************************/
#include "VrpnObject_impl.h"
#include "VrpnObject.h"
#include "VrpnClient.h"
#include "VrpnClient_impl.h"
#include <vrpn_Tracker.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <vrpn_Connection.h>
#include <cvmatrix.h>
#include <Tab.h>
#include <TabWidget.h>
#include <DataPlot1D.h>
#include <OneAxisRotation.h>
#include <Vector3D.h>
#include <Euler.h>
#include <math.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;

VrpnObject_impl::VrpnObject_impl(VrpnObject *self, const VrpnClient *parent,
                                 string name, int id, const TabWidget *tab) {
  this->parent = parent;
  this->self = self;

  if (id == -1 && parent->UseXbee()) {
    self->Err("erreur aucun identifiant specifie pour la connexion Xbee\n");
  }
  if (id != -1 && !parent->UseXbee()) {
    self->Warn(
        "identifiant pour la connexion Xbee ignore car pas en mode Xbee\n");
  }

  if (parent->UseXbee()) {
    parent->pimpl_->AddTrackable(this, id);
    tracker = NULL;
  } else {
    parent->pimpl_->AddTrackable(self);
    tracker = new vrpn_Tracker_Remote(name.c_str(), parent->pimpl_->connection);
    tracker->register_change_handler(this, handle_pos);
    tracker->shutup = true;
  }

  // state
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(6, 1);
  desc->SetElementName(0, 0, "roll");
  desc->SetElementName(1, 0, "pitch");
  desc->SetElementName(2, 0, "yaw");
  desc->SetElementName(3, 0, "x");
  desc->SetElementName(4, 0, "y");
  desc->SetElementName(5, 0, "z");
  output = new cvmatrix(self, desc, floatType);

  desc = new cvmatrix_descriptor(3, 1);
  desc->SetElementName(0, 0, "roll");
  desc->SetElementName(1, 0, "pitch");
  desc->SetElementName(2, 0, "yaw");
  state = new cvmatrix(self, desc, floatType);

  // ui
  plot_tab = new Tab(tab, "Mesures " + name);
  x_plot = new DataPlot1D(plot_tab->NewRow(), "x", -10, 10);
  x_plot->AddCurve(output->Element(3));
  y_plot = new DataPlot1D(plot_tab->LastRowLastCol(), "y", -10, 10);
  y_plot->AddCurve(output->Element(4));
  z_plot = new DataPlot1D(plot_tab->LastRowLastCol(), "z", -2, 0);
  z_plot->AddCurve(output->Element(5));
}

VrpnObject_impl::~VrpnObject_impl(void) {
  if (tracker != NULL) // normal
  {
    parent->pimpl_->RemoveTrackable(self);
    tracker->unregister_change_handler(this, handle_pos);
    delete tracker;
  } else // xbee
  {
    parent->pimpl_->RemoveTrackable(this);
  }
  delete plot_tab;
}

void VrpnObject_impl::mainloop(void) { tracker->mainloop(); }

bool VrpnObject_impl::IsTracked(unsigned int timeout_ms) {
  output->GetMutex();
  Time a = GetTime();
  Time dt = a - output->DataTime();
  output->ReleaseMutex();

  if (dt > (Time)(timeout_ms * 1000000)) {
    // self->Printf("%lld %lld %lld
    // %lld\n",a,output->DataTime(),dt,(Time)(timeout_ms*1000000));
    return false;
  } else {
    return true;
  }
}

void VrpnObject_impl::GetEuler(Euler &euler) {
  output->GetMutex();
  euler.roll = output->ValueNoMutex(0, 0);
  euler.pitch = output->ValueNoMutex(1, 0);
  euler.yaw = output->ValueNoMutex(2, 0);
  output->ReleaseMutex();
}

void VrpnObject_impl::GetQuaternion(Quaternion &quaternion) {
  output->GetMutex();
  quaternion.q0 = this->quaternion.q0;
  quaternion.q1 = this->quaternion.q1;
  quaternion.q2 = this->quaternion.q2;
  quaternion.q3 = this->quaternion.q3;
  output->ReleaseMutex();
}

void VrpnObject_impl::GetPosition(Vector3D &point) {
  output->GetMutex();
  point.x = output->ValueNoMutex(3, 0);
  point.y = output->ValueNoMutex(4, 0);
  point.z = output->ValueNoMutex(5, 0);
  output->ReleaseMutex();
}

void VRPN_CALLBACK
VrpnObject_impl::handle_pos(void *userdata, const vrpn_TRACKERCB t) {
  bool is_nan = false;
  VrpnObject_impl *caller = reinterpret_cast<VrpnObject_impl *>(userdata);
  Time time = GetTime();

  // check if something is nan
  for (int i = 0; i < 3; i++) {
    if (isnan(t.pos[i]) == true)
      is_nan = true;
  }
  for (int i = 0; i < 4; i++) {
    if (isnan(t.quat[i]) == true)
      is_nan = true;
  }
  if (is_nan == true) {
    caller->self->Warn("data is nan, skipping it (time %lld)\n", time);
    return;
  }

  // on prend une fois pour toute le mutex et on fait des accès directs
  caller->output->GetMutex();

  // warning: t.quat is defined as (qx,qy,qz,qw), which is different from
  // flair::core::Quaternion
  caller->quaternion.q0 = t.quat[3];
  caller->quaternion.q1 = t.quat[0];
  caller->quaternion.q2 = t.quat[1];
  caller->quaternion.q3 = t.quat[2];
  Vector3D pos((float)t.pos[0], (float)t.pos[1], (float)t.pos[2]);

  // on effectue les rotation
  caller->parent->pimpl_->ComputeRotations(pos);
  caller->parent->pimpl_->ComputeRotations(caller->quaternion);

  Euler euler;
  caller->quaternion.ToEuler(euler);
  caller->output->SetValueNoMutex(0, 0, euler.roll);
  caller->output->SetValueNoMutex(1, 0, euler.pitch);
  caller->output->SetValueNoMutex(2, 0, euler.yaw);
  caller->output->SetValueNoMutex(3, 0, pos.x);
  caller->output->SetValueNoMutex(4, 0, pos.y);
  caller->output->SetValueNoMutex(5, 0, pos.z);

  caller->output->SetDataTime(time);
  caller->output->ReleaseMutex();

  caller->state->GetMutex();
  caller->state->SetValueNoMutex(0, 0, Euler::ToDegree(euler.roll));
  caller->state->SetValueNoMutex(1, 0, Euler::ToDegree(euler.pitch));
  caller->state->SetValueNoMutex(2, 0, Euler::ToDegree(euler.yaw));
  caller->state->ReleaseMutex();

  caller->self->ProcessUpdate(caller->output);
}
