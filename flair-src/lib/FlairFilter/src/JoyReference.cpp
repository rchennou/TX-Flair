// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/29
//  filename:   JoyReference.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    generation de consignes a partir joystick
//
//
/*********************************************************************/

#include "JoyReference.h"
#include "JoyReference_impl.h"
#include <Layout.h>
#include <LayoutPosition.h>
#include <cvmatrix.h>
#include <AhrsData.h>
#include <Euler.h>
#include <Quaternion.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

JoyReference::JoyReference(const LayoutPosition *position, string name)
    : IODevice(position->getLayout(), name) {
  pimpl_ = new JoyReference_impl(this, position, name);
  AddDataToLog(pimpl_->output);
  AddDataToLog(pimpl_->ahrsData);
}

JoyReference::~JoyReference(void) { delete pimpl_; }

AhrsData *JoyReference::GetReferenceOrientation(void) const {
  return pimpl_->ahrsData;
}

void JoyReference::SetRollAxis(float value) { pimpl_->SetRollAxis(value); }

void JoyReference::SetPitchAxis(float value) { pimpl_->SetPitchAxis(value); }

void JoyReference::SetYawAxis(float value) { pimpl_->SetYawAxis(value); }

void JoyReference::SetAltitudeAxis(float value) {
  pimpl_->SetAltitudeAxis(value);
}

void JoyReference::RollTrimUp(void) { pimpl_->RollTrimUp(); }

void JoyReference::RollTrimDown(void) { pimpl_->RollTrimDown(); }

void JoyReference::PitchTrimUp(void) { pimpl_->PitchTrimUp(); }

void JoyReference::PitchTrimDown(void) { pimpl_->PitchTrimDown(); }

void JoyReference::SetYawRef(float value) { pimpl_->SetYawRef(value); }

void JoyReference::SetYawRef(core::Quaternion const &value) {
  Euler euler;
  value.ToEuler(euler);
  pimpl_->SetYawRef(euler.yaw);
}
void JoyReference::SetZRef(float value) { pimpl_->SetZRef(value); }

float JoyReference::ZRef(void) const { return pimpl_->ZRef(); }

float JoyReference::DzRef(void) const { return pimpl_->dZRef(); }

float JoyReference::RollTrim(void) const { return pimpl_->RollTrim(); }

float JoyReference::PitchTrim(void) const { return pimpl_->PitchTrim(); }

void JoyReference::Update(Time time) {
  pimpl_->Update(time);
  ProcessUpdate(pimpl_->output);
}

void JoyReference::UpdateFrom(const io_data *data) {
  pimpl_->UpdateFrom(data);
  ProcessUpdate(pimpl_->output);
}

} // end namespace sensor
} // end namespace flair
