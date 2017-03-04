// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/14
//  filename:   MetaDualShock3_impl.cpp
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

#include "MetaDualShock3_impl.h"
#include "MetaDualShock3.h"
#include <JoyReference.h>
#include <Tab.h>
#include <cvmatrix.h>
#include <FrameworkManager.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;
using namespace flair::meta;

MetaDualShock3_impl::MetaDualShock3_impl(MetaDualShock3 *self, string name) {
  joy_ref=new JoyReference(self->controller->GetTab()->NewRow(),"consignes joy");
  this->self = self;
  joy_init = false;
  wasRollTrimUpButtonPressed = false;
  wasRollTrimDownButtonPressed = false;
  wasPitchTrimUpButtonPressed = false;
  wasPitchTrimDownButtonPressed = false;
}

MetaDualShock3_impl::~MetaDualShock3_impl() {}

// receives updates from the controler
void MetaDualShock3_impl::UpdateFrom(const io_data *data) {
  cvmatrix *input = (cvmatrix *)data;

  // on prend une fois pour toute le mutex et on fait des accès directs
  input->GetMutex();

  // up
  if (self->controller->IsButtonPressed(12)) {
    if (!wasPitchTrimDownButtonPressed) {
      joy_ref->PitchTrimDown();
      wasPitchTrimDownButtonPressed = true;
    }
  } else {
    wasPitchTrimDownButtonPressed = false;
  }

  // down
  if (self->controller->IsButtonPressed(13)) {
    if (!wasPitchTrimUpButtonPressed) {
      joy_ref->PitchTrimUp();
      wasPitchTrimUpButtonPressed = true;
    }
  } else {
    wasPitchTrimUpButtonPressed = false;
  }

  // right
  if (self->controller->IsButtonPressed(15)) {
    if (!wasRollTrimUpButtonPressed) {
      joy_ref->RollTrimUp();
      wasRollTrimUpButtonPressed = true;
    }
  } else {
    wasRollTrimUpButtonPressed = false;
  }

  // left
  if (self->controller->IsButtonPressed(14)) {
    if (!wasRollTrimDownButtonPressed) {
      joy_ref->RollTrimDown();
      wasRollTrimDownButtonPressed = true;
    }
  } else {
    wasRollTrimDownButtonPressed = false;
  }

  if (!getFrameworkManager()->ConnectionLost()) {
    input->GetMutex();
    joy_ref->SetRollAxis(input->ValueNoMutex(0, 0));
    joy_ref->SetPitchAxis(input->ValueNoMutex(1, 0));
    joy_ref->SetYawAxis(input->ValueNoMutex(2, 0));
    joy_ref->SetAltitudeAxis(input->ValueNoMutex(3, 0));
    input->ReleaseMutex();
  } else {
    joy_ref->SetRollAxis(0);
    joy_ref->SetPitchAxis(0);
    joy_ref->SetYawAxis(0);
    joy_ref->SetAltitudeAxis(0);
  }
  input->ReleaseMutex();

  joy_ref->Update(data->DataTime());

  if (!joy_init) {
    self->controller->FlashLed(1, 10, 10);
    joy_init = true;
  }
}
