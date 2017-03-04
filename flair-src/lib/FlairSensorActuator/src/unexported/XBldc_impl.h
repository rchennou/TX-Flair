// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/11/13
//  filename:   XBldc_impl.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs i2c Xufo
//
//
/*********************************************************************/

#ifndef XBLDC_IMPL_H
#define XBLDC_IMPL_H

#include <IODevice.h>
#include <stdint.h>

namespace flair {
namespace core {
class I2cPort;
}
namespace actuator {
class XBldc;
}
}

class XBldc_impl {

public:
  XBldc_impl(flair::actuator::XBldc *self, flair::core::I2cPort *i2cport);
  ~XBldc_impl();
  void UpdateFrom(flair::core::io_data *data);
  void SetMotors(float *value);

private:
  uint8_t Sat(float value, uint8_t min, uint8_t max);
  // void StartTest(uint8_t moteur);
  void ChangeDirection(uint8_t moteur);
  void ChangeAdress(uint8_t old_add, uint8_t new_add);
  flair::actuator::XBldc *self;
  flair::core::I2cPort *i2cport;
};

#endif // XBLDC_IMPL_H
