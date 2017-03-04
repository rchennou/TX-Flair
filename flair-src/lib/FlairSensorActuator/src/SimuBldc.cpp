// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/07
//  filename:   SimuBldc.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for a simulation bldc
//
//
/*********************************************************************/
#include "SimuBldc.h"
#include <FrameworkManager.h>
#include <GridLayout.h>
#include <DoubleSpinBox.h>
#include <GroupBox.h>
#include <SharedMem.h>
#include <cvmatrix.h>
#include <sstream>

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace actuator {

SimuBldc::SimuBldc(const IODevice *parent, Layout *layout, string name,
                   uint8_t motors_count, uint32_t dev_id)
    : Bldc(parent, layout, name, motors_count) {
  ostringstream dev_name;
  dev_name << "simu_bldc_" << dev_id;
  shmem =
      new SharedMem(this, dev_name.str().c_str(), motors_count * sizeof(float));

  GroupBox *groupbox = new GroupBox(layout->NewRow(), "simubldc");
  k = new DoubleSpinBox(groupbox->NewRow(), "k driver:", 0, 10000, 1);
}

SimuBldc::SimuBldc(const Object *parent, string name, uint8_t motors_count,
                   uint32_t dev_id)
    : Bldc(parent, name, motors_count) {
  ostringstream dev_name;
  dev_name << "simu_bldc_" << dev_id;
  shmem =
      new SharedMem(this, dev_name.str().c_str(), motors_count * sizeof(float));

  // reset values
  float values[motors_count];
  for (int i = 0; i < motors_count; i++)
    values[i] = 0;

  shmem->Write((char *)&values, motors_count * sizeof(float));
}

SimuBldc::~SimuBldc() {}

void SimuBldc::SetMotors(float *value) {
  float values[MotorsCount()];

  for (int i = 0; i < MotorsCount(); i++)
    values[i] = k->Value() * value[i];

  shmem->Write((char *)&values, MotorsCount() * sizeof(float));

  // on prend une fois pour toute le mutex et on fait des accès directs
  output->GetMutex();
  for (int i = 0; i < MotorsCount(); i++)
    output->SetValueNoMutex(i, 0, values[i]);
  output->ReleaseMutex();
}

void SimuBldc::GetSpeeds(float *value) const {
  float values[MotorsCount()];
  shmem->Read((char *)&values, MotorsCount() * sizeof(float));

  for (int i = 0; i < MotorsCount(); i++)
    value[i] = values[i];
}

} // end namespace sensor
} // end namespace flair
