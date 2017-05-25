// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/12/19
//  filename:   BebopBldc.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs ardrone
//
//
/*********************************************************************/

#include "BebopBldc.h"
#include <I2cPort.h>
#include <BatteryMonitor.h>
#include <cvmatrix.h>
#include <string.h>
#include <asm/byteorder.h>

#define SLAVE_ADDRESS 0x08

// motor commands
#define START_MOTORS 0x40
#define STOP_MOTORS 0x60
#define SET_REF_SPEED 0x02
#define GET_DATAS 0x20
#define GET_INFO 0xA0
#define CLEAR_ERROR 0x80

#define MAX_SPEED 15500

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::actuator;
using namespace flair::sensor;

namespace flair {
namespace actuator {

BebopBldc::BebopBldc(const IODevice *parent, Layout *layout, string name,
                     I2cPort *inI2cPort)
    : Bldc(parent, layout, name, 4) {
  i2cPort = inI2cPort;
  
   // BatteryMonitor
  battery = new BatteryMonitor(layout->NewRow(), "battery");

  PrintInfo();
  areMotorsStarted = false;
  areMotorsSpinning = false;
  last_voltage_time = 0;
  
  SetIsReady(true);
}

BebopBldc::~BebopBldc() { StopMotors(); }

BatteryMonitor *BebopBldc::GetBatteryMonitor(void) const {
  return battery;
}

void BebopBldc::SetMotors(float *value) {
  bool needToStart = false;

  for (int i = 0; i < MotorsCount(); i++) {
    if (value[i] != 0)
      needToStart = true;
  }

  if (!areMotorsStarted && needToStart) {
    StartMotors();
  } else if (areMotorsStarted && !needToStart) {
    StopMotors();
    ClearError();
  } else if (areMotorsStarted) {

    if (areMotorsSpinning) {

      typedef struct speedStruct_t {
        uint8_t command;
        uint16_t refSpeed[4];
        uint8_t reserved;
        uint8_t checksum;
      } __attribute__((packed)) speedStruct_t;
      speedStruct_t speedStruct;

      speedStruct.command = SET_REF_SPEED;
      for (int i = 0; i < 4; i++) {
        speedStruct.refSpeed[i] = __cpu_to_be16(MAX_SPEED * value[i]);
        //Printf("%i ",256*(speedStruct.refSpeed[i]&0xff) + (speedStruct.refSpeed[i]>>8));
      }
      //Printf("\n");
      speedStruct.reserved = 0;
      speedStruct.checksum = CalcChecksum((uint8_t *)&speedStruct, sizeof(speedStruct) - 1);

      i2cPort->GetMutex();
      i2cPort->SetSlave(SLAVE_ADDRESS);
      ssize_t written = i2cPort->Write(&speedStruct, sizeof(speedStruct));
      i2cPort->ReleaseMutex();

      if (written < 0) {
        Err("error write i2c (%s)\n", strerror(-written));
      } else if (written != sizeof(speedStruct)) {
        Err("error write i2c %i/%i\n", written), sizeof(speedStruct);
      }
    }
  }
  datasStruct_t datasStruct;
  if(GetDatas(datasStruct)) {
    if (GetTime() > (last_voltage_time + 5 * (Time)1000000000)) {
      // toute les 5 secondes
      battery->SetBatteryValue(datasStruct.batteryVoltage/1000.);
      last_voltage_time = GetTime();
    }
    
     // on prend une fois pour toute le mutex et on fait des accès directs
    output->GetMutex();
    for (int i = 0; i < 4; i++) output->SetValueNoMutex(i, 0, datasStruct.speed[i]);
    output->ReleaseMutex();
  }
}

void BebopBldc::ClearError(void) {
  uint8_t tx = CLEAR_ERROR;
  //Printf("ClearError \n");
  i2cPort->GetMutex();
  i2cPort->SetSlave(SLAVE_ADDRESS);
  ssize_t written = i2cPort->Write(&tx, sizeof(tx));
  i2cPort->ReleaseMutex();

  if (written < 0) {
    Err("error write i2c (%s)\n", strerror(-written));
  } else if (written != sizeof(tx)) {
    Err("error write i2c %i/%i\n", written), sizeof(tx);
  } else {
    areMotorsStarted = false;
  }
}

void BebopBldc::PrintInfo(void) {

  typedef struct infoStruct_t {
    uint8_t version_major;
    uint8_t version_minor;
    uint8_t type;
    uint8_t numberOfMotors;
    uint16_t numberOfFlights;
    uint16_t timeLastFlight;
    uint32_t fulltFlighttime;
    uint8_t lastErrorCode;
  } __attribute__((packed)) infoStruct_t;
  infoStruct_t infoStruct;

  uint8_t tx = GET_INFO;

  i2cPort->GetMutex();
  i2cPort->SetSlave(SLAVE_ADDRESS);
  ssize_t written = i2cPort->Write(&tx, sizeof(tx));

  if (written < 0) {
    Err("error write i2c (%s)\n", strerror(-written));
    i2cPort->ReleaseMutex();
    return;
  } else if (written != sizeof(tx)) {
    Err("error write i2c %i/%i\n", written, sizeof(tx));
    i2cPort->ReleaseMutex();
    return;
  } else {
    ssize_t read = i2cPort->Read(&infoStruct, sizeof(infoStruct));
    i2cPort->ReleaseMutex();

    if (read < 0) {
      Err("error read i2c (%s)\n", strerror(-read));
    } else if (read != sizeof(infoStruct)) {
      Err("error read i2c %i/%i\n", read, sizeof(infoStruct));
    } else { /*
       Printf("%i %i %i %i %i %i %u
       %i\n",infoStruct.version_major,infoStruct.version_minor,infoStruct.type,
                                         infoStruct.numberOfMotors,
                                         __be16_to_cpu(infoStruct.numberOfFlights),__be16_to_cpu(infoStruct.timeLastFlight),
                                         __be32_to_cpu(infoStruct.fulltFlighttime),infoStruct.lastErrorCode);*/
      Printf("Bebop: %i flights, %is time last flight, %us total flight time\n",
             __be16_to_cpu(infoStruct.numberOfFlights),
             __be16_to_cpu(infoStruct.timeLastFlight),
             __be32_to_cpu(infoStruct.fulltFlighttime));
    }
  }
}

bool BebopBldc::GetDatas(datasStruct_t& outDatasStruct) {
  
  datasStruct_t datasStructBigEndian;

  uint8_t tx = GET_DATAS;

  i2cPort->GetMutex();
  i2cPort->SetSlave(SLAVE_ADDRESS);
  ssize_t written = i2cPort->Write(&tx, sizeof(tx));

  if (written < 0) {
    Err("error write i2c (%s)\n", strerror(-written));
    i2cPort->ReleaseMutex();
    return false;
  } else if (written != sizeof(tx)) {
    Err("error write i2c %i/%i\n", written, sizeof(tx));
    i2cPort->ReleaseMutex();
    return false;
  } else {
    ssize_t read = i2cPort->Read(&datasStructBigEndian, sizeof(datasStruct_t));
    i2cPort->ReleaseMutex();

    if (read < 0) {
      Err("error read i2c (%s)\n", strerror(-read));
    } else if (read != sizeof(datasStruct_t)) {
      Err("error read i2c %i/%i\n", read, sizeof(datasStruct_t));
    } else {
      if (datasStructBigEndian.checksum !=
          CalcChecksum((uint8_t *)&datasStructBigEndian, sizeof(datasStruct_t) - 1)) {
        Err("checksum error\n");
      } else {
         for(int i=0;i<4;i++) {
           //remove saturation information
           outDatasStruct.speed[i]=__be16_to_cpu(datasStructBigEndian.speed[i]);
          // Printf("%i ",outDatasStruct.speed[i]);
         }
         outDatasStruct.batteryVoltage=__be16_to_cpu(datasStructBigEndian.batteryVoltage);
         outDatasStruct.status=datasStructBigEndian.status;
        outDatasStruct.errorNumber=datasStructBigEndian.errorNumber;
        outDatasStruct.faultMotors=datasStructBigEndian.faultMotors;
        outDatasStruct.temperature=datasStructBigEndian.temperature;
        outDatasStruct.checksum=datasStructBigEndian.checksum;
    
        /* Printf("%i %x %i %i %i\n",
         outDatasStruct.batteryVoltage,outDatasStruct.status,outDatasStruct.errorNumber,
                                           outDatasStruct.faultMotors,outDatasStruct.temperature);*/
        if ((outDatasStruct.status & 0x0f) == 0x04) {
          areMotorsSpinning = true;
        } else {
          areMotorsSpinning = false;
        }
      }
    }
    return true;
  }
}

uint8_t BebopBldc::CalcChecksum(uint8_t *buf, uint8_t bufSize) {
  uint8_t checksum = 0;
  for (int i = 0; i < bufSize; i++) {
    checksum = checksum ^ buf[i];
  }

  return checksum;
}

void BebopBldc::StartMotors(void) {
  uint8_t tx[2];

  tx[0] = START_MOTORS;
  //tx[1] = 0b00000101;//bebop1
  tx[1] = 0b00001010;//bebop2
  //Printf("start motors\n");
  i2cPort->GetMutex();
  i2cPort->SetSlave(SLAVE_ADDRESS);
  ssize_t written = i2cPort->Write(tx, sizeof(tx));
  i2cPort->ReleaseMutex();

  if (written < 0) {
    Err("error write i2c (%s)\n", strerror(-written));
  } else if (written != sizeof(tx)) {
    Err("error write i2c %i/%i\n", written, sizeof(tx));
  } else {
    areMotorsStarted = true;
    areMotorsSpinning = false;
  }
}

void BebopBldc::StopMotors(void) {
  uint8_t tx = STOP_MOTORS;
  //Printf("stop motors\n");
  i2cPort->GetMutex();
  i2cPort->SetSlave(SLAVE_ADDRESS);
  ssize_t written = i2cPort->Write(&tx, sizeof(tx));
  i2cPort->ReleaseMutex();

  if (written < 0) {
    Err("error write i2c (%s)\n", strerror(-written));
  } else if (written != sizeof(tx)) {
    Err("error write i2c %i/%i\n", written), sizeof(tx);
  } else {
    areMotorsStarted = false;
    areMotorsSpinning = false;
  }
}

} // end namespace actuator
} // end namespace flair
