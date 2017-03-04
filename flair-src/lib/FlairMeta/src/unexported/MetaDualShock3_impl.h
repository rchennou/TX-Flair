// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file MetaDualShock3_impl.h
 * \brief Classe intégrant la manette DualShock3 et les consignes joystick
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/14
 * \version 3.4
 */

#ifndef METADUALSHOCK3_IMPL_H
#define METADUALSHOCK3_IMPL_H

#include <MetaDualShock3.h>

namespace flair {
namespace meta {
class MetaDualShock3;
}
namespace filter {
class JoyReference;
}
}

/*! \class MetaDualShock3_impl
*
* \brief Classe intégrant la manette DualShock3 et les consignes joystick
*/
class MetaDualShock3_impl {
public:
  MetaDualShock3_impl(flair::meta::MetaDualShock3 *self, std::string name);
  ~MetaDualShock3_impl();
  flair::filter::JoyReference *joy_ref;
  void UpdateFrom(const flair::core::io_data *data);

private:
  flair::meta::MetaDualShock3 *self;
  bool joy_init;
  bool wasRollTrimUpButtonPressed, wasRollTrimDownButtonPressed,
      wasPitchTrimUpButtonPressed, wasPitchTrimDownButtonPressed;
};

#endif // METADUALSHOCK3_IMPL_H
