// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/29
//  filename:   JoyReference_impl.cpp
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

#include "JoyReference_impl.h"
#include "JoyReference.h"
#include <AhrsData.h>
#include <Euler.h>
#include <cvmatrix.h>
#include <Layout.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <SpinBox.h>
#include <Label.h>
#include <PushButton.h>
#include <math.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

JoyReference_impl::JoyReference_impl(JoyReference *inSelf,
                                     const LayoutPosition *position,
                                     string name)
    : self(inSelf) {

  ahrsData = new AhrsData(self);
  input = new cvmatrix(self, 4, 1, floatType, name);

  cvmatrix_descriptor *desc = new cvmatrix_descriptor(4, 1);
  desc->SetElementName(0, 0, "z");
  ;
  desc->SetElementName(1, 0, "dz");
  desc->SetElementName(2, 0, "trim_roll");
  desc->SetElementName(3, 0, "trim_pitch");
  output = new cvmatrix(self, desc, floatType, name);

  reglages_groupbox = new GroupBox(position, name);
  deb_roll = new DoubleSpinBox(reglages_groupbox->NewRow(), "debattement roll",
                               " deg", -45, 45, 1, 0);
  deb_pitch = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),
                                "debattement pitch", " deg", -45, 45, 1, 0);
  deb_wz = new DoubleSpinBox(reglages_groupbox->NewRow(), "debattement wz",
                             " deg/s", -180, 180, 1, 0);
  deb_dz = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),
                             "debattement dz", " m/s", -2, 2, 0.1, 1);
  trim = new DoubleSpinBox(reglages_groupbox->NewRow(), "trim", -1, 1, 0.01);
  label_roll = new Label(reglages_groupbox->NewRow(), "trim roll");
  button_roll =
      new PushButton(reglages_groupbox->LastRowLastCol(), "reset roll trim");
  label_pitch = new Label(reglages_groupbox->NewRow(), "trim pitch");
  button_pitch =
      new PushButton(reglages_groupbox->LastRowLastCol(), "reset pitch trim");

  z_ref = 0;
  previous_time = 0;
  trim_roll = 0;
  trim_pitch = 0;

  label_roll->SetText("trim roll: %.2f", trim_roll);
  label_pitch->SetText("trim pitch: %.2f", trim_pitch);
}

JoyReference_impl::~JoyReference_impl(void) {}

void JoyReference_impl::SetRollAxis(float value) {
  input->SetValue(0, 0, value);
}

void JoyReference_impl::SetPitchAxis(float value) {
  input->SetValue(1, 0, value);
}

void JoyReference_impl::SetYawAxis(float value) {
  input->SetValue(2, 0, value);
}

void JoyReference_impl::SetAltitudeAxis(float value) {
  input->SetValue(3, 0, value);
}

void JoyReference_impl::RollTrimUp(void) {
  trim_roll += trim->Value();
  output->SetValue(2, 0, trim_roll);
  label_roll->SetText("trim roll: %.2f", trim_roll);
}

void JoyReference_impl::RollTrimDown(void) {
  trim_roll -= trim->Value();
  output->SetValue(2, 0, trim_roll);
  label_roll->SetText("trim roll: %.2f", trim_roll);
}

void JoyReference_impl::PitchTrimUp(void) {
  trim_pitch += trim->Value();
  output->SetValue(3, 0, trim_pitch);
  label_pitch->SetText("trim pitch: %.2f", trim_pitch);
}

void JoyReference_impl::PitchTrimDown(void) {
  trim_pitch -= trim->Value();
  output->SetValue(3, 0, trim_pitch);
  label_pitch->SetText("trim pitch: %.2f", trim_pitch);
}

void JoyReference_impl::SetYawRef(float value) {
  Euler ref(0, 0, value);
  input->GetMutex();
  ref.ToQuaternion(q_z);
  input->ReleaseMutex();

  Update(GetTime());
}

void JoyReference_impl::SetZRef(float value) {
  z_ref = value;
  output->SetValue(0, 0, z_ref);
}

float JoyReference_impl::ZRef(void) const { return output->Value(0, 0); }

float JoyReference_impl::dZRef(void) const { return output->Value(1, 0); }

float JoyReference_impl::RollTrim(void) const { return trim_roll; }

float JoyReference_impl::PitchTrim(void) const { return trim_pitch; }

void JoyReference_impl::Update(Time time) {
  input->SetDataTime(time);
  UpdateFrom(input);
}

void JoyReference_impl::UpdateFrom(const io_data *data) {
  cvmatrix *input = (cvmatrix *)data;

  if (previous_time == 0)
    previous_time = data->DataTime(); // pour la premiere iteration
  float delta_t = (float)(data->DataTime() - previous_time) / 1000000000.;
  previous_time = data->DataTime();

  if (button_roll->Clicked() == true) {
    trim_roll = 0;
    output->SetValue(2, 0, 0);
    label_roll->SetText("trim roll: %.2f", trim_roll);
  }
  if (button_pitch->Clicked() == true) {
    trim_pitch = 0;
    output->SetValue(3, 0, 0);
    label_pitch->SetText("trim pitch: %.2f", trim_pitch);
  }

  // les box sont en degrés
  input->GetMutex();

  Vector3D theta_xy(
      -Euler::ToRadian(input->ValueNoMutex(0, 0) * deb_roll->Value()),
      -Euler::ToRadian(input->ValueNoMutex(1, 0) * deb_pitch->Value()), 0);
  Vector3D e_bar = theta_xy;
  e_bar.Normalize();
  Quaternion q_xy(cos(theta_xy.GetNorm() / 2.0f),
                  e_bar.x * sin(theta_xy.GetNorm() / 2.0f),
                  e_bar.y * sin(theta_xy.GetNorm() / 2.0f), 0);
  q_xy.Normalize();

  float wz_ref = Euler::ToRadian(input->ValueNoMutex(2, 0) * deb_wz->Value());
  Quaternion w_zd(1, 0, 0, wz_ref * delta_t / 2);
  w_zd.Normalize();
  q_z = q_z * w_zd;
  q_z.Normalize();

  Quaternion q_ref = q_z * q_xy;
  q_ref.Normalize();

  z_ref += input->ValueNoMutex(3, 0) * deb_dz->Value() * delta_t;
  float dz_ref = input->ValueNoMutex(3, 0) * deb_dz->Value();

  input->ReleaseMutex();

  ahrsData->SetQuaternionAndAngularRates(q_ref, Vector3D(0, 0, wz_ref));

  // ouput quaternion for control law
  output->GetMutex();
  output->SetValueNoMutex(0, 0, z_ref);
  output->SetValueNoMutex(1, 0, dz_ref);
  output->ReleaseMutex();

  output->SetDataTime(data->DataTime());
}
