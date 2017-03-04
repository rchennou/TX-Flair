// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/14
//  filename:   MetaDualShock3.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant la manette DualShock3 et les consignes joystick
//
//
/*********************************************************************/

#include "MetaDualShock3.h"
#include "MetaDualShock3_impl.h"
#include "TargetController.h"
#include "JoyReference.h"
#include <Tab.h>
#include <FrameworkManager.h>
#include <cvmatrix.h>
#include <Ahrs.h>
#include <AhrsData.h>
#include <DataPlot1D.h>

using std::string;
using namespace flair::core;
using namespace flair::filter;
using namespace flair::gui;
using namespace flair::sensor;

namespace flair {
namespace meta {

MetaDualShock3::MetaDualShock3(FrameworkManager *parent, string name,
                               TargetController *controller)
    : controller(controller),IODevice((IODevice*)controller, name) {
  pimpl_ = new MetaDualShock3_impl(this, name);
  parent->AddDeviceToLog(pimpl_->joy_ref);
  controller->Start();
}

MetaDualShock3::~MetaDualShock3() { delete pimpl_; }

AhrsData *MetaDualShock3::GetReferenceOrientation(void) const {
  return pimpl_->joy_ref->GetReferenceOrientation();
}

void MetaDualShock3::ErrorNotify(void) {
    controller->FlashLed(4,10,0);
    controller->Rumble(0xff,20,0,0);
}

void MetaDualShock3::Rumble(uint8_t left_force,uint8_t left_timeout,uint8_t right_force,uint8_t right_timeout) {
    controller->Rumble(left_force,left_timeout,right_force,right_timeout);
}

void MetaDualShock3::SetLedON(unsigned int ledId) {
    controller->SetLedOn(ledId);
}

void MetaDualShock3::SetLedOFF(unsigned int ledId) {
    controller->SetLedOff(ledId);
}

void MetaDualShock3::FlashLed(unsigned int ledId,uint8_t on_timeout,uint8_t off_timeout) {
    controller->FlashLed(ledId,on_timeout,off_timeout);
}

float MetaDualShock3::ZRef(void) const { return pimpl_->joy_ref->ZRef(); }

float MetaDualShock3::DzRef(void) const { return pimpl_->joy_ref->DzRef(); }

void MetaDualShock3::SetYawRef(float value) {
  pimpl_->joy_ref->SetYawRef(value);
}

void MetaDualShock3::SetYawRef(Quaternion const &value) {
  pimpl_->joy_ref->SetYawRef(value);
}

void MetaDualShock3::SetZRef(float value) { pimpl_->joy_ref->SetZRef(value); }

float MetaDualShock3::RollTrim(void) const {
  return pimpl_->joy_ref->RollTrim();
}

float MetaDualShock3::PitchTrim(void) const {
    return pimpl_->joy_ref->PitchTrim();
}

void MetaDualShock3::UpdateFrom(const flair::core::io_data *data) {
    pimpl_->UpdateFrom(data);
}

} // end namespace meta
} // end namespace flair
