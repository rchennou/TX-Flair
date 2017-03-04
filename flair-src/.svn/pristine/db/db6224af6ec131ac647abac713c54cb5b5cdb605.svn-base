// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file LowPassFilter_impl.h
 * \brief Classe permettant le calcul d'un filtre passe bas
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef LOWPASSFILTER_FILTER_IMPL_H
#define LOWPASSFILTER_FILTER_IMPL_H

#include <IODevice.h>

namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class LayoutPosition;
class SpinBox;
class DoubleSpinBox;
}
namespace filter {
class LowPassFilter;
}
}

class LowPassFilter_impl {

public:
  LowPassFilter_impl(const flair::filter::LowPassFilter *self,
                     const flair::gui::LayoutPosition *position,
                     std::string name,
                     const flair::core::cvmatrix *init_value = NULL);
  ~LowPassFilter_impl();
  void UpdateFrom(const flair::core::io_data *data);
  flair::core::cvmatrix *output;

private:
  flair::core::Time previous_time;
  bool first_update;
  flair::core::cvmatrix *prev_value;
  flair::gui::DoubleSpinBox *freq, *T;
};

#endif // LOWPASSFILTER_FILTER_IMPL_H
