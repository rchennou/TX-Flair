// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/02/08
//  filename:   HdsX8.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a HDS X8 uav
//
//
/*********************************************************************/

#include "HdsX8.h"
#include <FrameworkManager.h>
#include <RTDM_I2cPort.h>
#include <RTDM_SerialPort.h>
#include <Srf08.h>
#include <Gx3_25_ahrs.h>
#include <BlCtrlV2.h>
#include <X4X8Multiplex.h>
#include <Ps3Eye.h>

using std::string;
using namespace flair::core;
using namespace flair::sensor;
using namespace flair::filter;
using namespace flair::actuator;

namespace flair {
namespace meta {

HdsX8::HdsX8(FrameworkManager *parent, string uav_name,
             filter::UavMultiplex *multiplex)
    : Uav(parent, uav_name, multiplex) {
  RTDM_I2cPort *i2cport = new RTDM_I2cPort(parent, "rtdm_i2c", "rti2c3");
  RTDM_SerialPort *imu_port = new RTDM_SerialPort(parent, "imu_port", "rtser1");

  if (multiplex == NULL)
    SetMultiplex(new X4X8Multiplex(parent, "motors", X4X8Multiplex::X8));

  SetBldc(new BlCtrlV2(GetUavMultiplex(), GetUavMultiplex()->GetLayout(),
                       "motors", GetUavMultiplex()->MotorsCount(), i2cport));
  SetUsRangeFinder(new Srf08(parent, "SRF08", i2cport, 0x70, 60));
  SetAhrs(new Gx3_25_ahrs(parent, "imu", imu_port,
                          Gx3_25_imu::AccelerationAngularRateAndOrientationMatrix, 70));
  SetBatteryMonitor(((BlCtrlV2 *)GetBldc())->GetBatteryMonitor());

  /*
          if(VRPNType==Auto || VRPNType==AutoSerialPort)
          {
              RTDM_SerialPort* vrpn_port=new
     RTDM_SerialPort(parent,"vrpn_port","rtser3");

              vrpnclient=new VrpnClient(parent,"vrpn",vrpn_port,10000,80);
              uav_vrpn=new
     MetaVrpnObject(vrpnclient,uav_name,VRPNSerialObjectId);
          }
  */
  SetVerticalCamera(new Ps3Eye(parent, "camv", 0, 50));
}

HdsX8::~HdsX8() {}

void HdsX8::StartSensors(void) {
  ((Gx3_25_ahrs *)GetAhrs())->Start();
  ((Srf08 *)GetUsRangeFinder())->Start();
  ((Ps3Eye *)GetVerticalCamera())->Start();
  Uav::StartSensors();
}

} // end namespace meta
} // end namespace flair
