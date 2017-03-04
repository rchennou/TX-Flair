// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/03/06
//  filename:   SimuCamera.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for a simulation camera
//
//
/*********************************************************************/

#include "SimuCamera.h"
#include <FrameworkManager.h>
#include <SpinBox.h>
#include <GroupBox.h>
#include <cvimage.h>
#include <SharedMem.h>
#include <sstream>

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

SimuCamera::SimuCamera(const FrameworkManager *parent, string name,
                       uint16_t width, uint16_t height, uint8_t channels,
                       uint32_t dev_id, uint8_t priority)
    : Thread(parent, name, priority),
      Camera(parent, name, width, height, cvimage::Type::Format::BGR) {
  data_rate =
      new SpinBox(GetGroupBox()->NewRow(), "data rate", " Hz", 1, 100, 1, 50);

  buf_size = width * height * channels;

  img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
  output->img->imageData = img->imageData;

  ostringstream dev_name;
  dev_name << "simu_cam_" << dev_id;
  shmem = new SharedMem((Thread *)this, dev_name.str().c_str(), buf_size);
}

SimuCamera::SimuCamera(const IODevice *parent, string name, uint16_t width,
                       uint16_t height, uint8_t channels, uint32_t dev_id)
    : Thread(parent, name, 0), Camera(parent, name) {
  data_rate = NULL;

  ostringstream dev_name;
  dev_name << "simu_cam_" << dev_id;
  shmem = new SharedMem((Thread *)this, dev_name.str().c_str(),
                        width * height * channels);
}

SimuCamera::~SimuCamera() {
  SafeStop();
  Join();
}

void SimuCamera::Run(void) {
  if (data_rate == NULL) {
    Thread::Err("not applicable for simulation part.\n");
    return;
  }

  SetPeriodUS((uint32_t)(1000000. / data_rate->Value()));

  while (!ToBeStopped()) {
    WaitPeriod();

    if (data_rate->ValueChanged() == true) {
      SetPeriodUS((uint32_t)(1000000. / data_rate->Value()));
    }

    output->GetMutex();
    shmem->Read((char *)img->imageData, buf_size); // remplacer copie par
                                                   // échange de pointeur sur
                                                   // double buffering
    output->ReleaseMutex();

    output->SetDataTime(GetTime());

    ProcessUpdate(output);
  }
}

} // end namespace sensor
} // end namespace flair
