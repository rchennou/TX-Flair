// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file EulerDerivative.h
 * \brief Classe permettant le calcul d'une derivee d'Euler
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef EULERDERIVATIVE_IMPL_H
#define EULERDERIVATIVE_IMPL_H

#include <IODevice.h>

namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class LayoutPosition;
class DoubleSpinBox;
}
namespace filter {
class EulerDerivative;
}
}

/*! \class EulerDerivative
* \brief Classe permettant le calcul d'une derivee d'Euler
*/

class EulerDerivative_impl {
public:
  EulerDerivative_impl(flair::filter::EulerDerivative *self,
                       const flair::gui::LayoutPosition *position,
                       std::string name,
                       const flair::core::cvmatrix *init_value = NULL);
  ~EulerDerivative_impl();
  void UpdateFrom(const flair::core::io_data *data);
  flair::core::cvmatrix *output;

private:
  flair::gui::DoubleSpinBox *T;
  flair::core::Time previous_time;
  bool first_update;
  flair::core::cvmatrix *prev_value;
};

#endif // EULERDERIVATIVE_IMPL_H
