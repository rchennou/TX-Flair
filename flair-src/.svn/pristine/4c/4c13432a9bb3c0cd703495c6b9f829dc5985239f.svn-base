// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/06/15
//  filename:   AfroBldc_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs i2c
//
//
/*********************************************************************/
#include "AfroBldc_impl.h"
#include "AfroBldc.h"
#include "Bldc_impl.h"
#include "I2cPort.h"
#include <Layout.h>
#include <SpinBox.h>
#include <Label.h>
#include <cvmatrix.h>
#include <string.h>

#define BASE_ADDRESS 0x29
#define MAX_VALUE 2047

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;
using namespace flair::actuator;

AfroBldc_impl::AfroBldc_impl(AfroBldc *self, Layout *layout, I2cPort *i2cport) {
  this->self = self;
  this->i2cport = i2cport;
  nb_mot = self->MotorsCount();
}

AfroBldc_impl::~AfroBldc_impl() {}

void AfroBldc_impl::SetMotors(float *value) {
  uint16_t tosend_value[nb_mot];

  for (int i = 0; i < nb_mot; i++)
    tosend_value[i] = (uint16_t)(MAX_VALUE * value[i]);

  i2cport->GetMutex();

  for (int i = 0; i < nb_mot; i++) {
    i2cport->SetSlave(BASE_ADDRESS + i);
    WriteValue(tosend_value[i]);
  }
  i2cport->ReleaseMutex();
}

// I2cPort mutex must be taken before calling this function
void AfroBldc_impl::WriteValue(uint16_t value) {
  uint8_t tx[2];
  ssize_t written;

  tx[0] = (uint8_t)(value >> 3); // msb
  tx[1] = (value & 0x07);        // lsb
  written = i2cport->Write(tx, 2);
  if (written < 0) {
    self->Err("rt_dev_write error (%s)\n", strerror(-written));
  } else if (written != sizeof(tx)) {
    self->Err("rt_dev_write error %i/%i\n", written, sizeof(tx));
  }
}
