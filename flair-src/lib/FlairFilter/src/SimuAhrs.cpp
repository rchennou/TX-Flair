// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/07
//  filename:   SimuAhrs.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for a simulation ahrs
//
//
/*********************************************************************/

#include "SimuAhrs.h"
#include "SimuImu.h"
#include <FrameworkManager.h>
#include <AhrsData.h>

using std::string;
using namespace flair::core;
using namespace flair::sensor;

namespace flair {
namespace filter {

SimuAhrs::SimuAhrs(const FrameworkManager *parent, string name, uint32_t dev_id,
                   uint8_t priority)
    : Ahrs(new SimuImu(parent, name, dev_id, priority), name) {}

SimuAhrs::~SimuAhrs() {}

void SimuAhrs::Start(void) { ((SimuImu *)GetImu())->Start(); }

// datas from SimuImu are AhrsData!
void SimuAhrs::UpdateFrom(const io_data *data) {
  AhrsData *input = (AhrsData *)data;
  AhrsData *output;
  GetDatas(&output);

  Quaternion quaternion;
  Vector3D filteredAngRates;
  input->GetQuaternionAndAngularRates(quaternion, filteredAngRates);
  output->SetQuaternionAndAngularRates(quaternion, filteredAngRates);
  output->SetDataTime(input->DataTime());

  ProcessUpdate(output);
}

} // end namespace filter
} // end namespace flair
