// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/11/14
//  filename:   Bldc.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Virtual class for brushless drivers
//
//
/*********************************************************************/

#include "Bldc.h"
#include "Bldc_impl.h"
#include <cvmatrix.h>
#include <DoubleSpinBox.h>
#include <sstream>
#include "compile_info.h"

//todo: put it on seprate file, but not possible with static lib?
static void constructor() __attribute__((constructor));

void constructor() {
  compile_info("FlairSensorActuator");
}

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace actuator {

Bldc::Bldc(const IODevice *parent, Layout *layout, string name,
           uint8_t motors_count)
    : IODevice(parent, name) {
  pimpl_ = new Bldc_impl(this, layout, name, motors_count);

  cvmatrix_descriptor *desc = new cvmatrix_descriptor(motors_count, 2);
  for (int i = 0; i < motors_count; i++) {
    ostringstream speed, current;
    speed << "speed_" << i;
    desc->SetElementName(i, 0, speed.str());

    current << "current_" << i;
    desc->SetElementName(i, 1, current.str());
  }

  output = new cvmatrix(this, desc, floatType);
  AddDataToLog(output);
}

Bldc::Bldc(const Object *parent, string name, uint8_t motors_count)
    : IODevice(parent, name) {
  pimpl_ = new Bldc_impl(this, motors_count);
}

Bldc::~Bldc() { delete pimpl_; }

void Bldc::UpdateFrom(const io_data *data) { pimpl_->UpdateFrom(data); }

void Bldc::LockUserInterface(void) const { pimpl_->LockUserInterface(); }

void Bldc::UnlockUserInterface(void) const { pimpl_->UnlockUserInterface(); }

Layout *Bldc::GetLayout(void) const { return (Layout *)pimpl_->layout; }

void Bldc::UseDefaultPlot(TabWidget *tabwidget) {
  pimpl_->UseDefaultPlot(tabwidget);
}

uint8_t Bldc::MotorsCount(void) const { return pimpl_->motors_count; }

cvmatrix *Bldc::Output(void) const { return output; }

bool Bldc::AreEnabled(void) const { return pimpl_->are_enabled; }

void Bldc::SetEnabled(bool status) {
  if (pimpl_->are_enabled != status) {
    pimpl_->are_enabled = status;
    if (pimpl_->are_enabled) {
      LockUserInterface();
    } else {
      UnlockUserInterface();
    }
  }
}

void Bldc::SetPower(int motor_id, float value) {
  // use output mutex to avoid making a new mutex
  output->GetMutex();
  pimpl_->power[motor_id] = value;
  output->ReleaseMutex();
}

} // end namespace sensor
} // end namespace flair
