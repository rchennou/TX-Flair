// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/08/23
//  filename:   Mb800.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant le recepteur gps mb800
//
//
/*********************************************************************/

#include "Mb800.h"
#include <SerialPort.h>
#include <FrameworkManager.h>
#include <string.h>

using std::string;
using namespace flair::core;

namespace flair {
namespace sensor {

Mb800::Mb800(const FrameworkManager *parent, string name,
             SerialPort *serialport, NmeaGps::NMEAFlags_t NMEAFlags,
             uint8_t priority)
    : NmeaGps(parent, name, NMEAFlags), Thread(parent, name, priority) {
  this->serialport = serialport;
  serialport->SetRxTimeout(100000000);
}

Mb800::~Mb800() {
  SafeStop();
  Join();
}

void Mb800::Run(void) {
  /** Debut init **/
  char response[200] = {0};
  int size,written;

  /** Fin init **/

  /** Debut config **/
  char to_send[] = "$PASHS,NME,ALL,A,OFF\r\n";
  written=serialport->Write(to_send, sizeof(to_send));
  if (written< 0) {
      Thread::Err("erreur Write (%s)\n", strerror(-written));
  }

  {
    char to_send[] = "$PASHS,CPD,AFP,95.0\r\n";
    written=serialport->Write(to_send, sizeof(to_send));
    if (written< 0) {
      Thread::Err("erreur Write (%s)\n", strerror(-written));
    }
  }
  {
    char to_send[] = "$PASHS,DIF,PRT,C,RT3\r\n";
    written=serialport->Write(to_send, sizeof(to_send));
    if (written< 0) {
      Thread::Err("erreur Write (%s)\n", strerror(-written));
    }
  }

  if ((NMEAFlags & GGA) != 0) {
    char to_send[] = "$PASHS,NME,GGA,A,ON,0.05\r\n";
    written = serialport->Write(to_send, sizeof(to_send));
    if (written< 0) {
      Thread::Err("erreur Write (%s)\n", strerror(-written));
    }
  }
  if ((NMEAFlags & VTG) != 0) {
    char to_send[] = "$PASHS,NME,VTG,A,ON,0.05\r\n";
    written = serialport->Write(to_send, sizeof(to_send));
    if (written< 0) {
      Thread::Err("erreur Write (%s)\n", strerror(-written));
    }
  }
  if ((NMEAFlags & GST) != 0) {
    char to_send[] = "$PASHS,NME,GST,A,ON,0.05\r\n";
    written = serialport->Write(to_send, sizeof(to_send));
    if (written< 0) {
      Thread::Err("erreur Write (%s)\n", strerror(-written));
    }
  }

  Sync();

  /** Fin config **/

  /** Debut running loop **/
  WarnUponSwitches(true);

  while (!ToBeStopped()) {
    SleepMS(10);
    size = 0;
    while (!ToBeStopped()) {
      ssize_t read = serialport->Read(&response[size], 1);
      if (read < 0) {
        Thread::Err("erreur Read (%s)\n", strerror(-read));
      }

      if (response[size] == 0x0a)
        break;
      size++;
    }
    size++;
    parseFrame(response, size);
  }
  /** fin running loop **/
  WarnUponSwitches(false);
}

void Mb800::Sync(void) {
  char data = 0;
  ssize_t read = 0;

  // attente fin trame
  while (data != 0x0a && !ToBeStopped()) {
    read = serialport->Read(&data, 1);
    SleepMS(10);

    if (read < 0) {
      Thread::Err("erreur Read (%s)\n", strerror(-read));
    }
  }
}

} // end namespace sensor
} // end namespace framewor
