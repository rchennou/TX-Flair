// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   Srf08.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for ultra sonic SRF08
//
//
/*********************************************************************/

#include "Srf08.h"
#include <I2cPort.h>
#include <FrameworkManager.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <cvmatrix.h>
#include <string.h>
#include <errno.h>
#include <math.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

Srf08::Srf08(const FrameworkManager *parent, string name, I2cPort *i2cport,
             uint16_t address, uint8_t priority)
    : Thread(parent, name, priority), UsRangeFinder(parent, name) {
  is_init = false;

  // default values
  // range 46*43+43=2021mm max (2m)
  // 7:gain=118
  // range=46;
  // gain=7;

  this->i2cport = i2cport;
  this->address = address;

  // station sol
  gain = new SpinBox(GetGroupBox()->NewRow(), "gain:", 0, 255, 1, 8);
  range = new SpinBox(GetGroupBox()->LastRowLastCol(), "range:", 0, 255, 1, 46);

  SetRange();
  SetMaxGain();
}

Srf08::~Srf08() {
  SafeStop();
  Join();
}

void Srf08::Run(void) {
  WarnUponSwitches(true);

  // init srf
  SendEcho();

  SetPeriodMS(20);

  while (!ToBeStopped()) {
    WaitPeriod();

    if (range->ValueChanged() == true)
      SetRange();
    if (gain->ValueChanged() == true)
      SetMaxGain();

    GetEcho();
    SendEcho();
  }

  WarnUponSwitches(false);
}

void Srf08::SendEcho(void) {
  ssize_t written;
  uint8_t tx[2];

  tx[0] = 0;  // command register
  tx[1] = 82; // ranging mode in usec

  i2cport->GetMutex();

  i2cport->SetSlave(address);
  written = i2cport->Write(tx, 2);
  echo_time = GetTime();

  i2cport->ReleaseMutex();

  if (written < 0) {
    Thread::Err("error write i2c (%s)\n", strerror(-written));
  } else if (written != 2) {
    Thread::Err("error write i2c %i/2\n", written);
  }
}

void Srf08::GetEcho(void) {
  float z = 0;
  ssize_t written, read;
  uint8_t tx, rx[2];
  tx = 2;
  uint8_t nb_err = 0;

  // si l'us est bloqué, on attend 1ms de plus
  while (1) {
    i2cport->GetMutex();
    i2cport->SetSlave(address);
    written = i2cport->Write(&tx, 1);

    if (written < 0) {
      i2cport->ReleaseMutex();
      Thread::Err("error write i2c (%s)\n", strerror(-written));
      nb_err++;
      if (nb_err == 20) {
        Thread::Err("error write i2c (%s), too many errors\n",
                    strerror(-written));
        return;
      }
      SleepMS(1);
    } else {
      read = i2cport->Read(rx, 2);
      i2cport->ReleaseMutex();
      // rt_printf("%i %i\n",rx[0],rx[1]);
      if (read < 0) {
        if (read != -ETIMEDOUT)
          Thread::Err("error read i2c (%s) %i\n", strerror(-read), read);
        nb_err++;
        if (nb_err == 20) {
          Thread::Err("error read i2c (%s), too many errors\n",
                      strerror(-written));
          return;
        }
        SleepMS(1);
      } else if (read != 2) {
        Thread::Err("error read i2c %i/2\n", read);
        return;
      } else if (read == 2) {
        break;
      }
    }
  }

  // if(z!=-1)
  // revoir ce filtrage!!!
  {
    z = 0.000001 * (float)(rx[0] * 256 + rx[1]) * 344 /
        2; // d=v*t; v=344m/s, t=t usec/2 (aller retour)
    // if(z>1) rt_printf("%i %i %f\n",rx[0],rx[1],z);
    // on ne permet pas 2 mesures consecutives + grandes de 10cm
    if (fabs(z - z_1) > 0.5 && is_init == true) {
      Printf("z %f (anc %f) %lld\n", z, z_1, echo_time);
      Printf("a revoir on suppose le sol plan\n");
      z = z_1 + (z_1 - z_2); // on suppose que l'on continue a la meme vitesse
    }
    output->SetValue(0, 0, z);
    output->SetDataTime(echo_time + (rx[0] * 256 + rx[1]) * 1000);
    ProcessUpdate(output);
    z_2 = z_1;
    z_1 = z;
    is_init = true;
  }
}

void Srf08::SetRange(void) {
  ssize_t written;
  uint8_t tx[2];

  tx[0] = 2;              // range register
  tx[1] = range->Value(); // range*43+43=dist max en mm

  i2cport->GetMutex();

  i2cport->SetSlave(address);
  written = i2cport->Write(tx, 2);

  i2cport->ReleaseMutex();

  if (written < 0) {
    Thread::Err("error write i2c (%s)\n", strerror(-written));
  } else if (written != 2) {
    Thread::Err("error write i2c %i/2\n", written);
  }
}

void Srf08::SetMaxGain(void) {
  ssize_t written;
  uint8_t tx[2];

  // rt_printf("Srf08::SetMaxGain: %s
  // ->%i\n",IODevice::ObjectName().c_str(),gain->Value());

  tx[0] = 1; // max gain register
  tx[1] = gain->Value();

  i2cport->GetMutex();

  i2cport->SetSlave(address);
  written = i2cport->Write(tx, 2);

  i2cport->ReleaseMutex();

  if (written < 0) {
    Thread::Err("error write i2c (%s)\n", strerror(-written));
  } else if (written != 2) {
    Thread::Err("error write i2c %i/2\n", written);
  }
}

} // end namespace sensor
} // end namespace flair
