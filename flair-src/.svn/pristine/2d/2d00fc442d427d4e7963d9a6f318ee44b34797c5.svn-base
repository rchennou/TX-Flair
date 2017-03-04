// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/01/16
//  filename:   Gx3_25_ahrs.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class for 3dmgx3-25 ahrs
//
//
/*********************************************************************/

#include "Gx3_25_ahrs.h"
#include <FrameworkManager.h>
#include <AhrsData.h>
#include <OneAxisRotation.h>

using std::string;
using namespace flair::core;
using namespace flair::sensor;

namespace flair {
namespace filter {

Gx3_25_ahrs::Gx3_25_ahrs(const FrameworkManager *parent, string name,
                         SerialPort *serialport, Gx3_25_imu::Command_t command,
                         uint8_t priority)
    : Ahrs(new Gx3_25_imu(parent, name, serialport, command, priority), name) {}

Gx3_25_ahrs::~Gx3_25_ahrs() {}

void Gx3_25_ahrs::Start(void) { ((Gx3_25_imu *)GetImu())->Start(); }

// datas from Gx3_25_imu are AhrsData!
void Gx3_25_ahrs::UpdateFrom(const io_data *data) {
  AhrsData *input = (AhrsData *)data;
  AhrsData *output;
  GetDatas(&output);

  Quaternion quaternion;
  Vector3D filteredAngRates;
  input->GetQuaternionAndAngularRates(quaternion, filteredAngRates);
  GetImu()->GetOneAxisRotation()->ComputeRotation(quaternion);
  GetImu()->GetOneAxisRotation()->ComputeRotation(filteredAngRates);
  output->SetQuaternionAndAngularRates(quaternion, filteredAngRates);
  output->SetDataTime(input->DataTime());

  ProcessUpdate(output);
}

} // end namespace filter
} // end namespace flair
