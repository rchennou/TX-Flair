// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/11/13
//  filename:   XBldc_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs i2c Xufo
//
//
/*********************************************************************/

#include "XBldc_impl.h"
#include "XBldc.h"
#include <I2cPort.h>
#include <cvmatrix.h>
#include <string.h>

#define BASE_ADDRESS 0x01
#define MAX_VALUE 200

using namespace flair::core;
using namespace flair::gui;
using namespace flair::actuator;

XBldc_impl::XBldc_impl(XBldc *self, I2cPort *i2cport) {
  this->self = self;
  this->i2cport = i2cport;

  i2cport->SetTxTimeout(5000000);
}

XBldc_impl::~XBldc_impl() {}

void XBldc_impl::SetMotors(float *value) {
  uint8_t tosend_value[5];

  for (int i = 0; i < 4; i++)
    tosend_value[i] = (uint8_t)(MAX_VALUE * value[i]);

  ssize_t written;
  tosend_value[4] = 0xaa;
  for (int i = 0; i < 4; i++)
    tosend_value[4] += tosend_value[i];
  self->Err("please verify motors adresses\n");
  // todo faire la procedure changement addresse par la station sol
  /*
      i2cport->GetMutex();
      i2cport->SetSlave(BASE_ADDRESS);

      written =i2cport->Write(tosend_value, sizeof(tosend_value));
      if(written<0)
      {
          self->Err("rt_dev_write error (%s)\n",strerror(-written));
      }
      else if (written != sizeof(tosend_value))
      {
          self->Err("rt_dev_write error %i/%i\n",written,sizeof(tosend_value));
      }

      i2cport->ReleaseMutex();*/
}
/*
void XBldc_impl::StartTest(uint8_t moteur)
{
    unsigned char tx[4];
    ssize_t written;

    tx[0]=251;
    tx[1]=moteur;
    tx[2]=0;
    tx[3]=231+moteur;

    i2cport->GetMutex();
    i2cport->SetSlave(BASE_ADDRESS);

    written =i2cport->Write(tx, sizeof(tx));
    if(written<0)
    {
        self->Err("rt_dev_write error (%s)\n",strerror(-written));
    }
    else if (written != sizeof(tx))
    {
        self->Err("rt_dev_write %i/%i error\n",written,sizeof(tx));
    }

    i2cport->ReleaseMutex();
}
*/
void XBldc_impl::ChangeDirection(uint8_t moteur) {
  unsigned char tx[4];
  ssize_t written;

  tx[0] = 254;
  tx[1] = moteur;
  tx[2] = 0;
  tx[3] = 234 + moteur;

  i2cport->GetMutex();
  i2cport->SetSlave(BASE_ADDRESS);

  written = i2cport->Write(tx, sizeof(tx));
  if (written < 0) {
    self->Err("rt_dev_write (%s) error\n", strerror(-written));
  } else if (written != sizeof(tx)) {
    self->Err("rt_dev_write %i/%i error\n", written, sizeof(tx));
  }

  i2cport->ReleaseMutex();
}

void XBldc_impl::ChangeAdress(uint8_t old_add, uint8_t new_add) {
  unsigned char tx[4];
  ssize_t written;

  tx[0] = 250;
  tx[1] = old_add;
  tx[2] = new_add;
  tx[3] = 230 + old_add + new_add;

  i2cport->GetMutex();
  i2cport->SetSlave(BASE_ADDRESS);

  written = i2cport->Write(tx, sizeof(tx));
  if (written < 0) {
    self->Err("rt_dev_write error (%s)\n", strerror(-written));
  } else if (written != sizeof(tx)) {
    self->Err("rt_dev_write error %i/%i\n", written, sizeof(tx));
  }

  i2cport->ReleaseMutex();
}

uint8_t XBldc_impl::Sat(float value, uint8_t min, uint8_t max) {
  uint8_t sat_value = (uint8_t)value;

  if (value > ((float)sat_value + 0.5))
    sat_value++;

  if (value < (float)min)
    sat_value = min;
  if (value > (float)max)
    sat_value = max;

  return sat_value;
}
