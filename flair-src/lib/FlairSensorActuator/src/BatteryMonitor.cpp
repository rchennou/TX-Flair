// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/24
//  filename:   BatteryMonitor.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for battery monitor
//
//
/*********************************************************************/

#include "BatteryMonitor.h"
#include <Layout.h>
#include <Label.h>
#include <DoubleSpinBox.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

BatteryMonitor::BatteryMonitor(const gui::LayoutPosition *position, string name)
    : GroupBox(position, name) {
  battery = new Label(this->NewRow(), "battery");
  battery_thresh = new DoubleSpinBox(this->LastRowLastCol(), "threshold", " V",
                                     0, 24, .1, 1);
}

BatteryMonitor::~BatteryMonitor() {}

float BatteryMonitor::GetVoltage(void) const { return batteryvalue; }

bool BatteryMonitor::IsBatteryLow(void) const {
  if (batteryvalue < battery_thresh->Value())
    return true;
  else
    return false;
}

void BatteryMonitor::SetBatteryValue(float value) {
  batteryvalue = value;
  if (value > 0) {
    battery->SetText("battery: %.1fV", value);
  } else {
    battery->SetText("battery: unreadable");
  }
}

} // end namespace sensor
} // end namespace flair
