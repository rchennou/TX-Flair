// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/11/14
//  filename:   Bldc_impl.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Virtual class for brushless drivers
//
//
/*********************************************************************/

#ifndef BLDC_IMPL_H
#define BLDC_IMPL_H

#include <IODevice.h>
#include <stdint.h>

namespace flair {
namespace gui {
class DoubleSpinBox;
class Layout;
class Label;
class DataPlot1D;
class TabWidget;
class PushButton;
}
namespace actuator {
class Bldc;
}
}

class Bldc_impl {
public:
  Bldc_impl(flair::actuator::Bldc *self, flair::gui::Layout *layout,
            std::string name, uint8_t motors_count);
  Bldc_impl(flair::actuator::Bldc *self, uint8_t motors_count); // simulation
  ~Bldc_impl();
  void UpdateFrom(const flair::core::io_data *data);
  void LockUserInterface(void) const;
  void UnlockUserInterface(void) const;
  bool are_enabled;
  float *power;
  void UseDefaultPlot(flair::gui::TabWidget *tab);
  uint8_t motors_count;
  flair::gui::Layout *layout;

private:
  float *values;
  float Sat(float value);
  flair::actuator::Bldc *self;
  flair::gui::DoubleSpinBox *min_value, *max_value, *test_value;
  flair::gui::Label *flight_time;
  flair::gui::DataPlot1D *plots;
  flair::core::Time flight_start_time;
  flair::gui::PushButton **button_test;
  int time_sec;
  bool is_running;
  flair::core::Time test_start_time;
  int tested_motor; //=-1 if no motor is tested
};

#endif // BLDC_IMPL_H
