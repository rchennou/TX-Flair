// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/29
//  filename:   JoyReference_impl.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    generation de consignes a partir joystick
//
//
/*********************************************************************/

#ifndef JOYREFERENCE_IMPL_H
#define JOYREFERENCE_IMPL_H

#include <stdint.h>
#include <Object.h>
#include <Quaternion.h>

namespace flair {
namespace core {
class cvmatrix;
class io_data;
class AhrsData;
}
namespace gui {
class LayoutPosition;
class GroupBox;
class DoubleSpinBox;
class SpinBox;
class Label;
class PushButton;
}
namespace filter {
class JoyReference;
}
}

class JoyReference_impl {

public:
  JoyReference_impl(flair::filter::JoyReference *self,
                    const flair::gui::LayoutPosition *position,
                    std::string name);
  ~JoyReference_impl();
  void SetRollAxis(float value);
  void SetPitchAxis(float value);
  void SetYawAxis(float value);
  void SetAltitudeAxis(float value);
  float ZRef(void) const;
  float dZRef(void) const;
  float RollTrim(void) const;
  float PitchTrim(void) const;
  void SetYawRef(float value);
  void SetZRef(float value);
  void RollTrimUp(void);
  void RollTrimDown(void);
  void PitchTrimUp(void);
  void PitchTrimDown(void);
  void Update(flair::core::Time time);
  void UpdateFrom(const flair::core::io_data *data);
  flair::core::cvmatrix *output;
  flair::core::AhrsData *ahrsData;

private:
  flair::core::cvmatrix *input;

  flair::gui::GroupBox *reglages_groupbox;
  flair::gui::DoubleSpinBox *deb_roll, *deb_pitch, *deb_wz, *deb_dz;
  flair::gui::DoubleSpinBox *trim;
  flair::gui::Label *label_roll, *label_pitch;
  flair::gui::PushButton *button_roll, *button_pitch;

  float z_ref;
  flair::core::Quaternion q_z = flair::core::Quaternion(1, 0, 0, 0);
  float trim_roll, trim_pitch;
  flair::core::Time previous_time;

  flair::filter::JoyReference *self;
};

#endif // JOYREFERENCE_IMPL_H
