// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file PidThrust_impl.h
 * \brief Classe permettant le calcul d'un Pid
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/11/07
 * \version 4.0
 */

#ifndef PIDTHRUST_IMPL_H
#define PIDTHRUST_IMPL_H

#include <Object.h>

namespace flair {
namespace core {
class cvmatrix;
class io_data;
}
namespace gui {
class LayoutPosition;
class DoubleSpinBox;
}
namespace filter {
class PidThrust;
}
}

/*! \class PidThrust_impl
* \brief Class defining a PID
*/

class PidThrust_impl {
public:
  PidThrust_impl(flair::filter::PidThrust *self,
                 const flair::gui::LayoutPosition *position, std::string name);
  ~PidThrust_impl();
  void UseDefaultPlot(const flair::gui::LayoutPosition *position);
  void UpdateFrom(const flair::core::io_data *data);
  float i, offset_g;
  flair::gui::DoubleSpinBox *offset, *pas_offset;

private:
  flair::filter::PidThrust *self;
  flair::core::Time previous_time;
  bool first_update;

  // matrix
  flair::core::cvmatrix *state;

  flair::gui::DoubleSpinBox *T, *kp, *ki, *kd, *sat, *sati;
};

#endif // PIDTHRUST_IMPL_H
