// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/07
//  filename:   SimuImu.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for a simulation imu
//
//
/*********************************************************************/

#include "SimuImu.h"
#include <FrameworkManager.h>
#include <ImuData.h>
#include <SpinBox.h>
#include <GroupBox.h>
#include <cvmatrix.h>
#include <SharedMem.h>
#include <AhrsData.h>
#include <sstream>

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

SimuImu::SimuImu(const FrameworkManager *parent, string name, uint32_t dev_id,
                 uint8_t priority)
    : Imu(parent, name), Thread(parent, name, priority) {
  dataRate =
      new SpinBox(GetGroupBox()->NewRow(), "data rate", " Hz", 1, 500, 1, 200);
  ahrsData = new AhrsData((Imu *)this);

  ostringstream dev_name;
  dev_name << "simu_imu_" << dev_id;
  shmem = new SharedMem((Thread *)this, dev_name.str().c_str(),
                        sizeof(imu_states_t));
}

SimuImu::SimuImu(const IODevice *parent, string name, uint32_t dev_id)
    : Imu(parent, name), Thread(parent, name, 0) {
  dataRate = NULL;

  ostringstream dev_name;
  dev_name << "simu_imu_" << dev_id;
  shmem = new SharedMem((Thread *)this, dev_name.str().c_str(),
                        sizeof(imu_states_t));
}

SimuImu::~SimuImu() {
  SafeStop();
  Join();
}

void SimuImu::UpdateFrom(const io_data *data) {
  if (data != NULL) {
    cvmatrix *input = (cvmatrix *)data;
    imu_states_t state;

    input->GetMutex();
    state.q0 = input->ValueNoMutex(0, 0);
    state.q1 = input->ValueNoMutex(1, 0);
    state.q2 = input->ValueNoMutex(2, 0);
    state.q3 = input->ValueNoMutex(3, 0);
    state.wx = input->ValueNoMutex(7, 0);
    state.wy = input->ValueNoMutex(8, 0);
    state.wz = input->ValueNoMutex(9, 0);
    input->ReleaseMutex();

    shmem->Write((char *)&state, sizeof(imu_states_t));
  }
}

void SimuImu::Run(void) {
  imu_states_t state;
  ImuData *imuData;
  GetDatas(&imuData);

  if (dataRate == NULL) {
    Thread::Err("not applicable for simulation part.\n");
    return;
  }

  SetPeriodUS((uint32_t)(1000000. / dataRate->Value()));

  while (!ToBeStopped()) {
    WaitPeriod();

    if (dataRate->ValueChanged() == true) {
      SetPeriodUS((uint32_t)(1000000. / dataRate->Value()));
    }

    shmem->Read((char *)&state, sizeof(imu_states_t));
    ahrsData->SetQuaternionAndAngularRates(
        Quaternion(state.q0, state.q1, state.q2, state.q3),
        Vector3D(state.wx, state.wy, state.wz));

    imuData->SetDataTime(GetTime());
    ahrsData->SetDataTime(GetTime());

    UpdateImu();
    ProcessUpdate(ahrsData);
  }
}

} // end namespace sensor
} // end namespace flair
