// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/08/19
//  filename:   Gx3_25_imu.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant la centrale 3dmgx3-25
//
//
/*********************************************************************/

#include "Gx3_25_imu.h"
#include <FrameworkManager.h>
#include "Gx3_25_imu_impl.h"
#include <GroupBox.h>
#include <ImuData.h>

using std::string;
using namespace flair::core;

namespace flair {
namespace sensor {

Gx3_25_imu::Gx3_25_imu(const FrameworkManager *parent, string name,
                       SerialPort *serialport, Command_t command,
                       uint8_t priority)
    : Imu(parent, name), Thread(parent, name, priority) {
  pimpl_ = new Gx3_25_imu_impl(this, name, serialport, command, GetGroupBox());

  if (command == EulerAnglesAndAngularRates) {
    Printf("Gx3_25_imu enabling EulerAnglesAndAngularRates\n");
  } else if (command == AccelerationAngularRateAndOrientationMatrix) {
    Printf("Gx3_25_imu enabling AccelerationAngularRateAndOrientationMatrix\n");
  } else if (command == Quaternion) {
    Printf("Gx3_25_imu enabling Quaternion\n");
  } else {
    Thread::Err("command not supported (%i)\n", command);
  }
  // AddDataToLog(imudata);
}

Gx3_25_imu::~Gx3_25_imu() {
  SafeStop();
  Join();
  delete pimpl_;
}

void Gx3_25_imu::Run(void) { pimpl_->Run(); }

} // end namespace sensor
} // end namespace flair
