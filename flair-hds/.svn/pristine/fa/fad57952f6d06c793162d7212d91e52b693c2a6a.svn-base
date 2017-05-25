// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/07/25
//  filename:   Bebop.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a bebop uav
//
//
/*********************************************************************/

#include "Bebop.h"
#include <FrameworkManager.h>
#include "BebopBldc.h"
#include "BebopUs.h"
#include <Unix_I2cPort.h>
#include <X4X8Multiplex.h>
#include <AhrsComplementaryFilter.h>
#include <BebopImu.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;
using namespace flair::filter;
using namespace flair::actuator;

namespace flair {
namespace meta {

Bebop::Bebop(string uav_name,
             filter::UavMultiplex *multiplex)
    : Uav(uav_name, multiplex) {
  Unix_I2cPort *bldcPort = new Unix_I2cPort(getFrameworkManager(), "bldc_port", "/dev/i2c-1");

  if (multiplex == NULL)
    SetMultiplex(new X4X8Multiplex("x4-multiplex", X4X8Multiplex::X4));

  SetBldc(new BebopBldc(GetUavMultiplex(), GetUavMultiplex()->GetLayout(),
                        "bebop-bldc", bldcPort));
  SetUsRangeFinder(new BebopUs("bebop-us", 50));
  
  Unix_I2cPort *imuPort = new Unix_I2cPort(getFrameworkManager(), "imu_port", "/dev/i2c-2");
  
  BebopImu* imu=new BebopImu("bebop-imu",imuPort,90);
  SetAhrs(new AhrsComplementaryFilter(imu,"bebop-ahrs"));
  //SetVerticalCamera(new BebopCamV(parent,"camv",50));

  SetBatteryMonitor(((BebopBldc*)GetBldc())->GetBatteryMonitor());
}

Bebop::~Bebop() {}

void Bebop::StartSensors(void) {
  ((BebopUs*)GetUsRangeFinder())->Start();
  ((BebopImu*)(GetAhrs()->GetImu()))->Start();
 
}

} // end namespace meta
} // end namespace flair
