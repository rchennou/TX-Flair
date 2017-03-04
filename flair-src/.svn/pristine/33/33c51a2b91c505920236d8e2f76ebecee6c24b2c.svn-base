// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/07
//  filename:   SimuUs.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for a simulation us
//
//
/*********************************************************************/
#include "SimuUs.h"
#include <FrameworkManager.h>
#include <ImuData.h>
#include <SpinBox.h>
#include <GroupBox.h>
#include <cvmatrix.h>
#include <SharedMem.h>
#include <sstream>

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

SimuUs::SimuUs(const FrameworkManager *parent, string name, uint32_t dev_id,
               uint8_t priority)
    : Thread(parent, name, priority), UsRangeFinder(parent, name) {
  data_rate =
      new SpinBox(GetGroupBox()->NewRow(), "data rate", " Hz", 1, 500, 1, 50);

  ostringstream dev_name;
  dev_name << "simu_us_" << dev_id;
  shmem = new SharedMem((Thread *)this, dev_name.str().c_str(), sizeof(float));
}

SimuUs::SimuUs(const IODevice *parent, string name, uint32_t dev_id)
    : Thread(parent, name, 0), UsRangeFinder(parent, name) {
  data_rate = NULL;

  ostringstream dev_name;
  dev_name << "simu_us_" << dev_id;
  shmem = new SharedMem((Thread *)this, dev_name.str().c_str(), sizeof(float));
}

SimuUs::~SimuUs() {
  SafeStop();
  Join();
}

void SimuUs::Run(void) {
  float z;

  if (data_rate == NULL) {
    Thread::Err("not applicable for simulation part.\n");
    return;
  }

  SetPeriodUS((uint32_t)(1000000. / data_rate->Value()));

  while (!ToBeStopped()) {
    WaitPeriod();

    shmem->Read((char *)&z, sizeof(float));

    if (data_rate->ValueChanged() == true) {
      SetPeriodUS((uint32_t)(1000000. / data_rate->Value()));
    }

    output->SetValue(0, 0, z);
    output->SetDataTime(GetTime());
    ProcessUpdate(output);
  }
}

} // end namespace sensor
} // end namespace flair
