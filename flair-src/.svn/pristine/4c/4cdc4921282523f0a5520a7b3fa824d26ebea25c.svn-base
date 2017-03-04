// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/09/13
//  filename:   BlCtrlV2_impl.h
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

#ifndef BLCTRLV2_IMPL_H
#define BLCTRLV2_IMPL_H

#include <stdint.h>
#include <Object.h>

#define MAX_MOTORS 8

namespace flair {
namespace core {
class I2cPort;
}
namespace gui {
class SpinBox;
class GroupBox;
class Layout;
}
namespace actuator {
class BlCtrlV2;
}
namespace sensor {
class BatteryMonitor;
}
}

class BlCtrlV2_impl {
public:
  BlCtrlV2_impl(flair::actuator::BlCtrlV2 *self, flair::gui::Layout *layout,
                flair::core::I2cPort *i2cport);
  ~BlCtrlV2_impl();
  void SetMotors(float *value);
  flair::sensor::BatteryMonitor *battery;
  flair::gui::SpinBox *poles;

private:
  void WriteValue(uint16_t value); // I2cPort mutex must be taken before calling
                                   // this function
  void DetectMotors(void);
  void GetCurrentSpeedAndVoltage(float &current, float &speed,
                                 float &voltage); // I2cPort mutex must be taken
                                                  // before calling this
                                                  // function
  void GetCurrentAndSpeed(
      float &current,
      float &speed); // I2cPort mutex must be taken before calling this function
  flair::core::Time last_voltage_time;
  int nb_mot;
  flair::core::I2cPort *i2cport;
  flair::actuator::BlCtrlV2 *self;
};

#endif // BLCTRLV2_IMPL_H
