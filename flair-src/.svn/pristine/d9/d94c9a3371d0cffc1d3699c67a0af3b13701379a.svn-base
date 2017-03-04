// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/09/13
//  filename:   BlCtrlV2_impl.cpp
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
#include "BlCtrlV2_impl.h"
#include "BlCtrlV2.h"
#include "Bldc_impl.h"
#include "BatteryMonitor.h"
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

BlCtrlV2_impl::BlCtrlV2_impl(BlCtrlV2 *self, Layout *layout, I2cPort *i2cport) {
  this->self = self;
  this->i2cport = i2cport;
  last_voltage_time = 0;

  DetectMotors();
  // if(nb_mot!=self->MotorsCount()) self->Err("motors count different from
  // multiplex count\n");

  // BatteryMonitor
  battery = new BatteryMonitor(layout->NewRow(), "battery");

  // user interface
  GroupBox *setupgroupbox = new GroupBox(layout->NewRow(), "Motors");
  poles = new SpinBox(setupgroupbox->NewRow(), "nb poles:", 0, 255, 1, 14);
}

BlCtrlV2_impl::~BlCtrlV2_impl() {}

void BlCtrlV2_impl::SetMotors(float *value) {
  uint16_t tosend_value[nb_mot];
  // stocke dans une variable pour garder le moins longtemps l'i2c (pour ne pas
  // bloquer sur le mutex de l'output)
  float speeds[nb_mot];
  float currents[nb_mot];

  for (int i = 0; i < nb_mot; i++)
    tosend_value[i] = (uint16_t)(MAX_VALUE * value[i]);

  i2cport->GetMutex();

  for (int i = 0; i < nb_mot; i++) {
    i2cport->SetSlave(BASE_ADDRESS + i);
    WriteValue(tosend_value[i]);
  }

  for (int i = 0; i < nb_mot; i++) {
    i2cport->SetSlave(BASE_ADDRESS + i);

    if (i == 0 && GetTime() > (last_voltage_time + 5 * (Time)1000000000)) {
      // toute les 5 secondes sur moteur 0
      float voltage;
      GetCurrentSpeedAndVoltage(currents[i], speeds[i], voltage);
      battery->SetBatteryValue(voltage);
      last_voltage_time = GetTime();
    } else {
      GetCurrentAndSpeed(currents[i], speeds[i]);
    }
  }
  // printf("%f %f %f %f\n",speeds[0],speeds[1],speeds[2],speeds[3]);
  /*
      if(GetTime()>(last_voltage_time+5*(Time)1000000000))//toute les 5 secondes
      {
          i2cport->SetSlave(BASE_ADDRESS);
          battery->SetBatteryValue(ReadVoltage());
          last_voltage_time=GetTime();
      }
  */
  i2cport->ReleaseMutex();

  // on prend une fois pour toute le mutex et on fait des accès directs
  cvmatrix *output = self->output;
  output->GetMutex();
  for (int i = 0; i < nb_mot; i++)
    output->SetValueNoMutex(i, 0, speeds[i]);
  for (int i = 0; i < nb_mot; i++)
    output->SetValueNoMutex(i, 1, currents[i]);
  output->ReleaseMutex();
}

// I2cPort mutex must be taken before calling this function
void BlCtrlV2_impl::WriteValue(uint16_t value) {
  uint8_t tx[2];
  ssize_t written;

  tx[0] = (uint8_t)(value >> 3); // msb
  tx[1] = (value & 0x07);
  ; //+16+8; //pour recuperer la vitesse en premier
  written = i2cport->Write(tx, 2);
  if (written < 0) {
    self->Err("rt_dev_write error (%s)\n", strerror(-written));
  } else if (written != sizeof(tx)) {
    self->Err("rt_dev_write error %i/%i\n", written, sizeof(tx));
  }
}

// I2cPort mutex must be taken before calling this function
void BlCtrlV2_impl::GetCurrentAndSpeed(float &current, float &speed) {
  ssize_t read;
  uint8_t value[4];
  read = i2cport->Read(value, sizeof(value));

  if (read < 0) {
    self->Err("rt_dev_read error (%s)\n", strerror(-read));
    speed = -1;
    current = -1;
  } else if (read != sizeof(value)) {
    self->Err("rt_dev_read error %i/%i\n", read, sizeof(value));
    speed = -1;
    current = -1;
  } else {
    current = value[0] / 10.;
    speed = value[3] * 780. / poles->Value();
  }
}

// I2cPort mutex must be taken before calling this function
void BlCtrlV2_impl::GetCurrentSpeedAndVoltage(float &current, float &speed,
                                              float &voltage) {
  ssize_t read;
  uint8_t value[6];
  read = i2cport->Read(value, sizeof(value));

  if (read < 0) {
    self->Err("rt_dev_read error (%s)\n", strerror(-read));
    speed = -1;
    voltage = -1;
    current = -1;
  } else if (read != sizeof(value)) {
    self->Err("rt_dev_read error %i/%i\n", read, sizeof(value));
    speed = -1;
    voltage = -1;
    current = -1;
  } else {
    current = value[0] / 10.;
    voltage = value[5] / 10.;
    speed = value[3] * 780. / poles->Value();
  }
}

void BlCtrlV2_impl::DetectMotors(void) {
  int nb = 0;
  ssize_t read, nb_write;
  uint8_t value[3];
  uint8_t tx[2];

  i2cport->GetMutex();

  for (int i = 0; i < MAX_MOTORS; i++) {
    // printf("test %i\n",i);
    i2cport->SetSlave(BASE_ADDRESS + i);
    tx[0] = 0;
    tx[1] = 16 + 8; // 16+8 pour recuperer la vitesse

    nb_write = i2cport->Write(tx, 2);

    if (nb_write != sizeof(tx)) {
      continue;
    }
    nb++;
  }

  for (int i = 0; i < MAX_MOTORS; i++) {
    i2cport->SetSlave(BASE_ADDRESS + i);
    read = i2cport->Read(value, 3);

    if (read != sizeof(value)) {
      continue;
    }
  }

  i2cport->ReleaseMutex();

  Printf("BlCtrlV2: Dectected motors: %i\n", nb);
  if (nb == 4) {
    Printf("BlCtrlV2: Configuration X4\n");
  } else if (nb == 8) {
    Printf("BlCtrlV2: Configuration X8\n");
  } else {
    // self->Err("Error, configuration not supported (%i/%i)\n",nb,MAX_MOTORS);
  }

  nb_mot = nb;
}
