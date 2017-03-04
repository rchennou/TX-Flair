// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/02/08
//  filename:   SimuX8.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a simulation x8 uav
//
//
/*********************************************************************/

#include "SimuX8.h"
#include <FrameworkManager.h>
#include <X4X8Multiplex.h>
#include <SimuImu.h>
#include <SimuAhrs.h>
#include <SimuBldc.h>
#include <SimuUs.h>
#include <SimuCamera.h>
#include <BatteryMonitor.h>
#include <Tab.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;
using namespace flair::filter;
using namespace flair::actuator;

namespace flair {
namespace meta {

SimuX8::SimuX8(FrameworkManager *parent, string uav_name, int simu_id,
               filter::UavMultiplex *multiplex)
    : Uav(parent, uav_name, multiplex) {

  if (multiplex == NULL)
    SetMultiplex(new X4X8Multiplex(parent, "motors", X4X8Multiplex::X8));

  SetBldc(new SimuBldc(GetUavMultiplex(), GetUavMultiplex()->GetLayout(),
                       "motors", GetUavMultiplex()->MotorsCount(), simu_id));
  SetUsRangeFinder(new SimuUs(parent, "us", simu_id, 60));
  SetAhrs(new SimuAhrs(parent, "imu", simu_id, 70));
  Tab *bat_tab = new Tab(parent->GetTabWidget(), "battery");
  SetBatteryMonitor(new BatteryMonitor(bat_tab->NewRow(), "battery"));
  GetBatteryMonitor()->SetBatteryValue(12);
  SetVerticalCamera(
      new SimuCamera(parent, "simu_cam_v", 320, 240, 3, simu_id, 10));
}

SimuX8::~SimuX8() {}

void SimuX8::StartSensors(void) {
  ((SimuAhrs *)GetAhrs())->Start();
  ((SimuUs *)GetUsRangeFinder())->Start();
  ((SimuCamera *)GetVerticalCamera())->Start();
  Uav::StartSensors();
}

void SimuX8::SetupVRPNAutoIP(string name) { SetupVRPN("127.0.0.1:3883", name); }

} // end namespace meta
} // end namespace flair
