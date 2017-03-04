// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/08/19
//  filename:   Gx3_25_imu_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant la centrale 3dmgx3-25
//
//
/*********************************************************************/

#include "Gx3_25_imu_impl.h"
#include <FrameworkManager.h>
#include <SerialPort.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <CheckBox.h>
#include <PushButton.h>
#include <Label.h>
#include <ImuData.h>
#include <AhrsData.h>
#include <Euler.h>
#include <Vector3D.h>
#include <RotationMatrix.h>

#include <math.h>
#include <string.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;

Gx3_25_imu_impl::Gx3_25_imu_impl(Gx3_25_imu *self, string name,
                                 SerialPort *serialport,
                                 Gx3_25_imu::Command_t command,
                                 GroupBox *setupgroupbox) {
  int err = 0;

  this->self = self;
  this->command = (uint8_t)command;
  this->setupgroupbox = setupgroupbox;
  this->serialport = serialport;

  ahrsData = new AhrsData((Imu *)self);

  // station sol
  button_bias = new PushButton(setupgroupbox->NewRow(), "gyros bias");
  data_rate =
      new SpinBox(setupgroupbox->NewRow(), "data rate (Hz):", 1, 500, 1, 200);
  data_rate_label = new Label(setupgroupbox->LastRowLastCol(), "data_rate");
  gyro_acc_size = new SpinBox(setupgroupbox->NewRow(),
                              "gyro and acc filter win size:", 1, 32, 1, 15);
  mag_size = new SpinBox(setupgroupbox->LastRowLastCol(),
                         "mag filter win size:", 1, 32, 1, 17);
  up_comp = new SpinBox(setupgroupbox->NewRow(), "up compensation (s):", 1,
                        1000, 1, 10);
  north_comp = new SpinBox(setupgroupbox->LastRowLastCol(),
                           "north compensation (s):", 1, 1000, 1, 10);
  coning =
      new CheckBox(setupgroupbox->NewRow(), "enable Coning&Sculling:", true);
  disable_magn = new CheckBox(setupgroupbox->LastRowLastCol(),
                              "disable magnetometer:", true);
  disable_north_comp = new CheckBox(
      setupgroupbox->NewRow(), "disable magnetic north compensation:", false);
  disable_grav_comp = new CheckBox(setupgroupbox->NewRow(),
                                   "disable gravity compensation:", false);
}

Gx3_25_imu_impl::~Gx3_25_imu_impl() {}

void Gx3_25_imu_impl::Run(void) {
  Time imuTime;
  ImuData *imuData;
  self->GetDatas(&imuData);

  self->WarnUponSwitches(true);

  // reset IMU to be sure it is at 115200
  Printf("Gx3_25_imu::Reset IMU at 921600\n");
  serialport->SetBaudrate(921600);
  DeviceReset();
  self->Thread::SleepMS(100);
  serialport->FlushInput();
  serialport->SetBaudrate(115200);

  SetBaudrate(921600);
  Printf("Gx3_25_imu firmware number: %i\n", FirmwareNumber());
  PrintModelInfo();
  SamplingSettings();
  GyrosBias();
  // RealignUpNorth(true,true);

  // on provoque les 9 ValueChanged
  for (int i = 0; i < 9; i++) {
    if (data_rate->ValueChanged() == true ||
        disable_magn->ValueChanged() == true ||
        disable_north_comp->ValueChanged() == true ||
        disable_grav_comp->ValueChanged() == true ||
        coning->ValueChanged() == true ||
        gyro_acc_size->ValueChanged() == true ||
        mag_size->ValueChanged() == true || up_comp->ValueChanged() == true ||
        north_comp->ValueChanged() == true) {
      if (setupgroupbox->isEnabled() == true)
        SamplingSettings();
    }
  }

  // periode a passer en argument (reglable)
  // ou plutot laisser la periode geree par le centrale (polling)
  // self->SetPeriodMS(2);
  SetContinuousMode(command);

  while (!self->ToBeStopped()) {
    if (command == Gx3_25_imu::EulerAnglesAndAngularRates) {
      uint8_t response[31] = {0};
      uint8_t *buf = &response[1];
      GetData(response, sizeof(response), &imuTime);

      Euler eulerAngles;
      eulerAngles.roll = Dequeue(&buf);
      eulerAngles.pitch = Dequeue(&buf);
      eulerAngles.yaw = Dequeue(&buf);

      Vector3D filteredAngRates;
      filteredAngRates.x = Dequeue(&buf);
      filteredAngRates.y = Dequeue(&buf);
      filteredAngRates.z = Dequeue(&buf);

      ahrsData->SetQuaternionAndAngularRates(eulerAngles.ToQuaternion(),
                                             filteredAngRates);
    } else if (command ==
               Gx3_25_imu::AccelerationAngularRateAndOrientationMatrix) {
      uint8_t response[67] = {0};
      uint8_t *buf = &response[1];
      GetData(response, sizeof(response), &imuTime);

      Vector3D rawAcc;
      rawAcc.x = 9.80665 * Dequeue(&buf);
      rawAcc.y = 9.80665 * Dequeue(&buf);
      rawAcc.z = 9.80665 * Dequeue(&buf);

      Vector3D filteredAngRates;
      filteredAngRates.x = Dequeue(&buf);
      filteredAngRates.y = Dequeue(&buf);
      filteredAngRates.z = Dequeue(&buf);

      RotationMatrix matrix;
      matrix(0, 0) = Dequeue(&buf);
      matrix(0, 1) = Dequeue(&buf);
      matrix(0, 2) = Dequeue(&buf);
      matrix(1, 0) = Dequeue(&buf);
      matrix(1, 1) = Dequeue(&buf);
      matrix(1, 2) = Dequeue(&buf);
      matrix(2, 0) = Dequeue(&buf);
      matrix(2, 1) = Dequeue(&buf);
      matrix(2, 2) = Dequeue(&buf);

      ahrsData->SetQuaternionAndAngularRates(matrix.ToQuaternion(),
                                             filteredAngRates);
      imuData->SetRawAcc(rawAcc);
    } else if (command == Gx3_25_imu::Quaternion) {
      uint8_t response[23] = {0};
      uint8_t *buf = &response[1];
      GetData(response, sizeof(response), &imuTime);

      Quaternion quaternion;
      quaternion.q0 = Dequeue(&buf);
      quaternion.q1 = Dequeue(&buf);
      quaternion.q2 = Dequeue(&buf);
      quaternion.q3 = Dequeue(&buf);

      Vector3D filteredAngRates;
      filteredAngRates.x = 0;
      filteredAngRates.y = 0;
      filteredAngRates.z = 0;

      ahrsData->SetQuaternionAndAngularRates(quaternion,
                                             filteredAngRates);
    }

    // change settings as soon as possible
    // we assume that new imu datas will not come so fast
    // so newt message from imu is an ack from the change settings
    if (button_bias->Clicked() == true)
      GyrosBias();

    if (data_rate->ValueChanged() == true ||
        disable_magn->ValueChanged() == true ||
        disable_north_comp->ValueChanged() == true ||
        disable_grav_comp->ValueChanged() == true ||
        coning->ValueChanged() == true ||
        gyro_acc_size->ValueChanged() == true ||
        mag_size->ValueChanged() == true || up_comp->ValueChanged() == true ||
        north_comp->ValueChanged() == true) {
      if (setupgroupbox->isEnabled() == true)
        SamplingSettings();
    }

    imuData->SetDataTime(imuTime);
    ahrsData->SetDataTime(imuTime);
    self->UpdateImu();
    self->ProcessUpdate(ahrsData);
  }
  SetContinuousMode(0);
  SetBaudrate(115200);

  self->WarnUponSwitches(false);
}

void Gx3_25_imu_impl::GetData(uint8_t *buf, ssize_t buf_size, Time *time) {
  ssize_t read = 0;
  ssize_t written = 0;
  /*
      written = serialport->Write(&command, sizeof(command));
      if(written<0)
      {
          self->Thread::Err("Write error (%s)\n",strerror(-written));
      }
      else if (written != sizeof(command))
      {
          self->Thread::Err("Write error %i/%i\n",written,sizeof(command));
      }
  */
  read = serialport->Read(buf, buf_size);
  *time = GetTime();
  if (read < 0) {
    self->Thread::Err("Read error (%s)\n", strerror(-read));
  } else if (read != buf_size) {
    self->Thread::Err("Read error %i/%i\n", read, buf_size);
  }

  if (CalcChecksum(buf, buf_size) == false) {
    self->Thread::Err("wrong checksum\n");
    return;
  }
}

float Gx3_25_imu_impl::Dequeue(uint8_t **buf) {
  union float_4uint8 {
    float f;
    uint8_t b[4];
  } float_value;

  float_value.b[0] = (*buf)[3];
  float_value.b[1] = (*buf)[2];
  float_value.b[2] = (*buf)[1];
  float_value.b[3] = (*buf)[0];
  (*buf) += sizeof(float);

  return float_value.f;
}

void Gx3_25_imu_impl::GyrosBias(void) {
  if (setupgroupbox->isEnabled() == true) { // devrait toujours etre bon
    uint8_t response[19] = {0};
    uint8_t command[5];
    ssize_t read = 0;
    ssize_t written = 0;

    Printf("Gx3_25_imu::gyros_bias: %s\n",
           self->IODevice::ObjectName().c_str());

    command[0] = 0xcd; // entete
    command[1] = 0xc1; // confirm
    command[2] = 0x29; // confirm
    command[3] = 0x27; // time MSB en us
    command[4] = 0x10; // time LSB en us

    written = serialport->Write(&command, sizeof(command));
    if (written < 0) {
      self->Thread::Err("Write error (%s)\n", strerror(-written));
    } else if (written != sizeof(command)) {
      self->Thread::Err("Write error %i/%i\n", written, sizeof(command));
    }

    self->SleepUS(1.1 * (command[3] * 256 +
                         command[4])); // on fait un sleep un peu plus grand

    read = serialport->Read(&response[0], sizeof(response));
    if (read < 0) {
      self->Thread::Err("Read error (%s)\n", strerror(-read));
    } else if (read != sizeof(response)) {
      self->Thread::Err("Read error %i/%i\n", read, sizeof(response));
    }

    if (CalcChecksum(response, sizeof(response)) == false) {
      self->Thread::Err("wrong checksum\n");
      // return -1;
    }

    Printf("Gx3_25_imu::gyros_bias: %s ok\n",
           self->IODevice::ObjectName().c_str());

  } else {
    self->Thread::Err("error locked\n");
  }
}

void Gx3_25_imu_impl::SetContinuousMode(uint8_t continuous_command) {
  uint8_t response[8] = {0};
  uint8_t command[4];
  ssize_t read = 0;
  ssize_t written = 0;

  command[0] = 0xc4; // entete
  command[1] = 0xc1; // confirm
  command[2] = 0x29; // confirm
  command[3] = continuous_command;

  written = serialport->Write(command, sizeof(command));
  if (written < 0) {
    self->Thread::Err("Write error (%s)\n", strerror(-written));
  } else if (written != sizeof(command)) {
    self->Thread::Err("Write error %i/%i\n", written, sizeof(command));
  }

  read = serialport->Read(response, sizeof(response));
  if (read < 0) {
    self->Thread::Err("Read error (%s)\n", strerror(-read));
  } else if (read != sizeof(response)) {
    self->Thread::Err("Read error %i/%i\n", read, sizeof(response));
  }

  if (CalcChecksum(response, sizeof(response)) == false) {
    self->Thread::Err("wrong checksum\n", self->IODevice::ObjectName().c_str());
  }
}

void Gx3_25_imu_impl::SamplingSettings(void) {
  uint8_t response[19] = {0};
  uint8_t command[20];
  uint8_t result;
  ssize_t read = 0;
  ssize_t written = 0;

  uint16_t rate = 1000 / data_rate->Value();

  command[0] = 0xdb;               // entete
  command[1] = 0xa8;               // confirm
  command[2] = 0xb9;               // confirm
  command[3] = 1;                  // change values
  command[4] = (rate >> 8) & 0xff; // data rate MSB
  command[5] = rate & 0xff;        // data rate LSB
  result = 0;
  if (disable_magn->IsChecked() == true) result |= 0x01;
  if (disable_north_comp->IsChecked() == true) result |= 0x04;
  if (disable_grav_comp->IsChecked() == true) result |= 0x08;
  if (this->command == Gx3_25_imu::Quaternion) result |= 0x10;//enable quaternion
  command[6] = result;

  result = 0x01; // Calculate orientation
  if (coning->IsChecked() == true)
    result |= 0x02;

  command[7] = result;
  command[8] = gyro_acc_size->Value();             // gyro acc filter window
  command[9] = mag_size->Value();                  // mag filter window
  command[10] = (up_comp->Value() >> 8) & 0xff;    // up comp MSB
  command[11] = up_comp->Value() & 0xff;           // up comp LSB
  command[12] = (north_comp->Value() >> 8) & 0xff; // north comp MSB
  command[13] = north_comp->Value() & 0xff;        // north comp LSB
  command[14] = 0;                                 // reserved
  command[15] = 0;                                 // reserved
  command[16] = 0;                                 // reserved
  command[17] = 0;                                 // reserved
  command[18] = 0;                                 // reserved
  command[19] = 0;                                 // reserved

  written = serialport->Write(&command, sizeof(command));
  if (written < 0) {
    self->Thread::Err("Write error (%s)\n", strerror(-written));
  } else if (written != sizeof(command)) {
    self->Thread::Err("Write error %i/%i\n", written, sizeof(command));
  }

  read = serialport->Read(&response[0], sizeof(response));
  if (read < 0) {
    self->Thread::Err("Read error (%s)\n", strerror(-read));
  } else if (read != sizeof(response)) {
    self->Thread::Err("Read error %i/%i\n", read, sizeof(response));
  }

  if (CalcChecksum(response, sizeof(response)) == false) {
    self->Thread::Err("wrong checksum\n", self->IODevice::ObjectName().c_str());
  } else {
    data_rate_label->SetText("real: %.2fHz", 1000. / rate);
  }
}

void Gx3_25_imu_impl::SetBaudrate(int value) {
  uint8_t response[10] = {0};
  uint8_t command[11];
  ssize_t read = 0;
  ssize_t written = 0;

  union int32_4uint8 {
    int32_t i;
    uint8_t b[4];
  } baudrate_value;

  baudrate_value.i = value;
  Printf("Gx3_25_imu::SetBaudrate: %s ->%i\n",
         self->IODevice::ObjectName().c_str(), baudrate_value.i);

  command[0] = 0xd9; // entete
  command[1] = 0xc3; // confirm
  command[2] = 0x55; // confirm
  command[3] = 1;    // primary uart
  command[4] = 1;    // chgt temporaire
  command[5] = baudrate_value.b[3];
  command[6] = baudrate_value.b[2];
  command[7] = baudrate_value.b[1];
  command[8] = baudrate_value.b[0];
  command[9] = 2;  // uart enabled
  command[10] = 0; // reserved

  written = serialport->Write(&command, sizeof(command));
  if (written < 0) {
    self->Thread::Err("Write error (%s)\n", strerror(-written));
  } else if (written != sizeof(command)) {
    self->Thread::Err("Write error %i/%i\n", written, sizeof(command));
  }

  read = serialport->Read(&response[0], sizeof(response));
  if (read < 0) {
    self->Thread::Err("Read error (%s)\n", strerror(-read));
  } else if (read != sizeof(response)) {
    self->Thread::Err("Read error %i/%i\n", read, sizeof(response));
  }

  if (CalcChecksum(response, sizeof(response)) == false) {
    self->Thread::Err("wrong checksum\n");
    return;
  }

  serialport->SetBaudrate(value);
}

int Gx3_25_imu_impl::FirmwareNumber(void) {
  uint8_t response[7] = {0};
  uint8_t command;
  ssize_t read = 0;
  ssize_t written = 0;
  union int32_4uint8 {
    int32_t i;
    uint8_t b[4];
  } value;

  command = 0xe9; // entete

  written = serialport->Write(&command, sizeof(command));
  if (written < 0) {
    self->Thread::Err("Write error (%s)\n", strerror(-written));
  } else if (written != sizeof(command)) {
    self->Thread::Err("Write error %i/%i\n", written, sizeof(command));
  }

  read = serialport->Read(&response[0], sizeof(response));
  if (read < 0) {
    self->Thread::Err("Read error (%s)\n", strerror(-read));
  } else if (read != sizeof(response)) {
    self->Thread::Err("Read error %i/%i\n", read, sizeof(response));
  }

  if (CalcChecksum(response, sizeof(response)) == false) {
    self->Thread::Err("wrong checksum\n");
    return -1;
  }

  value.b[3] = response[1];
  value.b[2] = response[2];
  value.b[1] = response[3];
  value.b[0] = response[4];

  return value.i;
}

void Gx3_25_imu_impl::PrintModelInfo(void) {
  uint8_t response[20] = {0};
  uint8_t command[2];
  ssize_t read = 0;
  ssize_t written = 0;

  for (int i = 0; i < 3; i++) {
    command[0] = 0xea; // entete
    command[1] = i;    // entete

    written = serialport->Write(&command, sizeof(command));
    if (written < 0) {
      self->Thread::Err("Write error (%s)\n", strerror(-written));
    } else if (written != sizeof(command)) {
      self->Thread::Err("Write error %i/%i\n", written, sizeof(command));
    }

    read = serialport->Read(&response[0], sizeof(response));
    if (read < 0) {
      self->Thread::Err("Read error (%s)\n", strerror(-read));
    } else if (read != sizeof(response)) {
      self->Thread::Err("Read error %i/%i\n", read, sizeof(response));
    }

    if (CalcChecksum(response, sizeof(response)) == false) {
      self->Thread::Err("wrong checksum\n");
      // return -1;
    }

    char *msg = (char *)(&response[2]);
    msg[16] = 0;
    switch (i) {
    case 0:
      Printf("Gx3_25_imu model number: %s\n", msg);
      break;
    case 1:
      Printf("Gx3_25_imu serial number: %s\n", msg);
      break;
    case 2:
      Printf("Gx3_25_imu model name: %s\n", msg);
      break;
    }
  }
}

void Gx3_25_imu_impl::RealignUpNorth(bool realign_up, bool realign_north) {
  uint8_t response[7] = {0};
  uint8_t command[10];
  ssize_t read = 0;
  ssize_t written = 0;

  command[0] = 0xdd; // entete
  command[1] = 0x54; // confirm
  command[2] = 0x4c; // confirm
  command[3] = 0;    // send reply
  command[4] = 255;  // up realign
  command[5] = 1;    // north realign
  command[6] = 0;    // reserved
  command[7] = 0;    // reserved
  command[8] = 0;    // reserved
  command[9] = 0;    // reserved

  written = serialport->Write(&command, sizeof(command));
  if (written < 0) {
    self->Thread::Err("Write error (%s)\n", strerror(-written));
  } else if (written != sizeof(command)) {
    self->Thread::Err("Write error %i/%i\n", written, sizeof(command));
  }

  read = serialport->Read(&response[0], sizeof(response));
  if (read < 0) {
    self->Thread::Err("Read error(%s)\n", strerror(-read));
  } else if (read != sizeof(response)) {
    self->Thread::Err("Read error %i/%i\n", read, sizeof(response));
  }

  if (CalcChecksum(response, sizeof(response)) == false) {
    self->Thread::Err("wrong checksum\n");
  }
}

void Gx3_25_imu_impl::DeviceReset(void) {
  uint8_t command[3];
  ssize_t written = 0;

  command[0] = 0xfe; // entete
  command[1] = 0x9e; // confirm
  command[2] = 0x3a; // confirm

  written = serialport->Write(&command, sizeof(command));
  if (written < 0) {
    self->Thread::Err("Write error (%s)\n", strerror(-written));
  } else if (written != sizeof(command)) {
    self->Thread::Err("Write error %i/%i\n", written, sizeof(command));
  }
}

bool Gx3_25_imu_impl::CalcChecksum(uint8_t *buf, int size) {
  uint16_t tChksum, tResponseChksum;

  tChksum = 0;
  for (int i = 0; i < size - 2; i++)
    tChksum += buf[i];
  // Extract the big-endian checksum from reply
  tResponseChksum = 0;
  tResponseChksum = buf[size - 2] << 8;
  tResponseChksum += buf[size - 1];

  if (tChksum != tResponseChksum)
    return false;
  else
    return true;
}
