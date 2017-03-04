// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/06/15
//  filename:   AfroBldc_impl.h
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

#ifndef AFROBLDC_IMPL_H
#define AFROBLDC_IMPL_H

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
class AfroBldc;
}
namespace sensor {
class BatteryMonitor;
}
}

class AfroBldc_impl {
public:
  AfroBldc_impl(flair::actuator::AfroBldc *self, flair::gui::Layout *layout,
                flair::core::I2cPort *i2cport);
  ~AfroBldc_impl();
  void SetMotors(float *value);

private:
  void WriteValue(uint16_t value); // I2cPort mutex must be taken before calling
                                   // this function
  int nb_mot;
  flair::core::I2cPort *i2cport;
  flair::actuator::AfroBldc *self;
};

#endif // AFROBLDC_IMPL_H
