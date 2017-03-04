// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/09/13
//  filename:   BlCtrlV2.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs i2c
//
//
/*********************************************************************/

#include "BlCtrlV2.h"
#include "BlCtrlV2_impl.h"
#include "BatteryMonitor.h"
#include <GroupBox.h>
#include <Layout.h>
#include <DoubleSpinBox.h>
#include <SpinBox.h>
#include <ComboBox.h>
#include <PushButton.h>

using std::string;
using namespace flair::core;
using namespace flair::sensor;
using namespace flair::gui;

namespace flair {
namespace actuator {

BlCtrlV2::BlCtrlV2(const IODevice *parent, Layout *layout, string name,
                   uint8_t motors_count, I2cPort *i2cport)
    : Bldc(parent, layout, name, motors_count) {
  pimpl_ = new BlCtrlV2_impl(this, layout, i2cport);
}

BlCtrlV2::~BlCtrlV2() { delete pimpl_; }

BatteryMonitor *BlCtrlV2::GetBatteryMonitor(void) const {
  return pimpl_->battery;
}

void BlCtrlV2::SetMotors(float *values) { pimpl_->SetMotors(values); }

} // end namespace actuator
} // end namespace flair
