// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/08/23
//  filename:   Novatel.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant le recepteur gps Novatel
//
//
/*********************************************************************/

#include "Novatel.h"
#include <SerialPort.h>
#include <FrameworkManager.h>
#include <string.h>

using std::string;
using namespace flair::core;

namespace flair {
namespace sensor {

Novatel::Novatel(const FrameworkManager *parent, string name,
                 SerialPort *serialport, NmeaGps::NMEAFlags_t NMEAFlags,
                 uint8_t priority)
    : NmeaGps(parent, name, NMEAFlags), Thread(parent, name, priority) {
  this->serialport = serialport;
}

Novatel::~Novatel() {
  SafeStop();
  Join();
}

void Novatel::Run(void) {
  char response[200] = {0};
  int size;
  ssize_t written;

  WarnUponSwitches(true);

  char to_send[] = "log gpggalong ontime 0.05\n";
  written = serialport->Write(to_send, sizeof(to_send));
  if (written < 0) {
    Thread::Err("erreur write (%s)\n", strerror(-written));
  }
  char to_send2[] = "log gpvtg ontime 0.05\n";
  written = serialport->Write(to_send2, sizeof(to_send2));
  if (written < 0) {
    Thread::Err("erreur write (%s)\n", strerror(-written));
  }

  Sync();

  while (!ToBeStopped()) {
    size = 0;
    while (1) {
      // ssize_t read = rt_dev_read(uart_fd, &response[size],1);
      ssize_t Read = serialport->Read(&response[size], 1);
      if (Read < 0) {
        Thread::Err("erreur Read (%s)\n", strerror(-Read));
      }
      if (response[size] == 0x0a)
        break;
      size++;
    }
    size++;
    parseFrame(response, size);
  }

  WarnUponSwitches(false);
}

void Novatel::Sync(void) {
  char data = 0;
  ssize_t Read = 0;

  // attente fin trame
  while (data != 0x0a) {
    Read = serialport->Read(&data, 1);
    if (Read < 0) {
      Thread::Err("erreur Read (%s)\n", strerror(-Read));
    }
  }
}

} // end namespace sensor
} // end namespace framewor
