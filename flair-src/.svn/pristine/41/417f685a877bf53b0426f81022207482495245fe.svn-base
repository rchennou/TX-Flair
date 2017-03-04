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
//  purpose:    Class for VRPN object
//
//
/*********************************************************************/

#include "VrpnObject.h"
#include "VrpnObject_impl.h"
#include "VrpnClient.h"
#include <string.h>

#include <cvmatrix.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

VrpnObject::VrpnObject(const VrpnClient *parent, string name,
                       const TabWidget *tab)
    : IODevice(parent, name) {
  pimpl_ = new VrpnObject_impl(this, parent, name, -1, tab);
  AddDataToLog(pimpl_->output);
}

VrpnObject::VrpnObject(const VrpnClient *parent, string name, uint8_t id,
                       const TabWidget *tab)
    : IODevice(parent, name) {
  Warn("Creation of object %s with id %i\n", name.c_str(), id);
  pimpl_ = new VrpnObject_impl(this, parent, name, id, tab);
  AddDataToLog(pimpl_->output);
}

VrpnObject::~VrpnObject(void) { delete pimpl_; }

cvmatrix *VrpnObject::Output(void) const { return pimpl_->output; }

cvmatrix *VrpnObject::State(void) const { return pimpl_->state; }

Tab *VrpnObject::GetPlotTab(void) const { return pimpl_->plot_tab; }

DataPlot1D *VrpnObject::xPlot(void) const { return pimpl_->x_plot; }

DataPlot1D *VrpnObject::yPlot(void) const { return pimpl_->y_plot; }

DataPlot1D *VrpnObject::zPlot(void) const { return pimpl_->z_plot; }

Time VrpnObject::GetLastPacketTime(void) const {
  return pimpl_->output->DataTime();
}

bool VrpnObject::IsTracked(unsigned int timeout_ms) const {
  return pimpl_->IsTracked(timeout_ms);
}

void VrpnObject::GetEuler(Euler &euler) const { pimpl_->GetEuler(euler); }

void VrpnObject::GetQuaternion(Quaternion &quaternion) const {
  pimpl_->GetQuaternion(quaternion);
}

void VrpnObject::GetPosition(Vector3D &point) const {
  pimpl_->GetPosition(point);
}

void VrpnObject::mainloop(void) { pimpl_->mainloop(); }

} // end namespace sensor
} // end namespace flair
