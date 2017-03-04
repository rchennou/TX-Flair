// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Gx3_25_imu_impl.h
 * \brief Classe intégrant la centrale 3dmgx3-25
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/08/19
 * \version 4.0
 */

#ifndef GX3_25_IMU_IMPL_H
#define GX3_25_IMU_IMPL_H

#include "Gx3_25_imu.h"
#include <unistd.h> //ssize_t

namespace flair {
namespace core {
class FrameworkManager;
class SerialPort;
class AhrsData;
}
namespace gui {
class SpinBox;
class CheckBox;
class PushButton;
class Label;
}
}

/*! \class Gx3_25_imu_impl
*
* \brief Classe intégrant la centrale 3dmgx3-25
*/

class Gx3_25_imu_impl {

public:
  Gx3_25_imu_impl(flair::sensor::Gx3_25_imu *self, std::string name,
                  flair::core::SerialPort *serialport,
                  flair::sensor::Gx3_25_imu::Command_t command,
                  flair::gui::GroupBox *setupgroupbox);
  ~Gx3_25_imu_impl();
  void Run(void);

private:
  void DeviceReset(void);
  void GetData(uint8_t *buf, ssize_t buf_size, flair::core::Time *time);
  float Dequeue(uint8_t **buf);
  void GyrosBias(void);
  void SamplingSettings(void);
  void SetBaudrate(int value);
  bool CalcChecksum(uint8_t *buf, int size);
  int FirmwareNumber(void);
  void PrintModelInfo(void);
  void RealignUpNorth(bool realign_up, bool realign_north);

  void SetContinuousMode(uint8_t continuous_command);

  flair::gui::GroupBox *setupgroupbox;
  flair::gui::SpinBox *data_rate, *gyro_acc_size, *mag_size, *up_comp,
      *north_comp;
  flair::gui::CheckBox *coning, *disable_magn, *disable_north_comp,
      *disable_grav_comp;
  flair::gui::PushButton *button_bias;
  flair::gui::Label *data_rate_label;

  flair::core::SerialPort *serialport;
  uint8_t command;
  flair::sensor::Gx3_25_imu *self;
  flair::core::AhrsData *ahrsData;
};

#endif // GX3_25_IMU_IMPL_H
