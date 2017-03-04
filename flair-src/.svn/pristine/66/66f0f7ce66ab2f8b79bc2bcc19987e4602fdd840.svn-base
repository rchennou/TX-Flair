// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Pid_impl.h
 * \brief Classe permettant le calcul d'un Pid
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef PID_IMPL_H
#define PID_IMPL_H

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
class Pid;
}
}

/*! \class Pid_impl
* \brief Class defining a PID
*/

class Pid_impl {
public:
  Pid_impl(flair::filter::Pid *self, const flair::gui::LayoutPosition *position,
           std::string name);
  ~Pid_impl();
  void UseDefaultPlot(const flair::gui::LayoutPosition *position);
  void UpdateFrom(const flair::core::io_data *data);
  float i;
  bool first_update;

private:
  flair::filter::Pid *self;
  flair::core::Time previous_time;

  // matrix
  flair::core::cvmatrix *state;

  flair::gui::DoubleSpinBox *T, *kp, *ki, *kd, *sat, *sati;
};

#endif // PID_IMPL_H
