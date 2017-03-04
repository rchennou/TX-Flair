// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/29
//  filename:   BlCtrlV2_x4_speed.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs i2c, controle en vitesse
//
//
/*********************************************************************/

#ifndef BLCTRLV2_X4_SPEED_H
#define BLCTRLV2_X4_SPEED_H

#include <IODevice.h>
#include <Thread.h>

namespace flair {
namespace core {
class cvmatrix;
class FrameworkManager;
class I2cPort;
}
namespace gui {
class TabWidget;
class Tab;
class SpinBox;
class DoubleSpinBox;
class ComboBox;
class PushButton;
class GroupBox;
}
}

namespace flair {
namespace actuator {
class BlCtrlV2_x4_speed : public core::Thread, public core::IODevice {

public:
  BlCtrlV2_x4_speed(core::FrameworkManager *parent, std::string name,
                    core::I2cPort *i2cport, uint8_t base_address,
                    uint8_t priority);
  ~BlCtrlV2_x4_speed();
  void UseDefaultPlot(void);
  void LockUserInterface(void);
  void UnlockUserInterface(void);
  void SetEnabled(bool status);
  void SetUroll(float value);
  void SetUpitch(float value);
  void SetUyaw(float value);
  void SetUgaz(float value);
  void SetRollTrim(float value);
  void SetPitchTrim(float value);
  void SetYawTrim(float value);
  void SetGazTrim(float value);
  float TrimValue(void);
  int StartValue(void);

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(core::io_data *data){};
  void WriteValue(uint16_t value);
  float GetSpeed(void);
  void StartTest(void);
  void StopTest(void);
  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);
  void Update(void);
  gui::Tab *main_tab;
  gui::TabWidget *tab;
  gui::GroupBox *reglages_groupbox;
  gui::SpinBox *min, *max, *test;
  gui::PushButton *button_avg, *button_avd, *button_arg, *button_ard;
  gui::ComboBox *av_g, *av_d, *ar_g, *ar_d, *pas;
  gui::DoubleSpinBox *trim, *kp, *ki;
  gui::SpinBox *start_value, *poles;
  core::Time start_time, flight_start_time;
  int time_sec;
  float speed_av_g, speed_av_d, speed_ar_g, speed_ar_d;
  float int_av_g, int_av_d, int_ar_g, int_ar_d;

  // matrix
  core::cvmatrix *input;
  core::cvmatrix *output;

  int tested_motor;
  core::I2cPort *i2cport;
  uint8_t slave_address;

  bool enabled;

  uint16_t SatPWM(float vel_cons, uint16_t min, uint16_t max);
};
} // end namespace actuator
} // end namespace flair
#endif // BLCTRLV2_X4_SPEED_H
