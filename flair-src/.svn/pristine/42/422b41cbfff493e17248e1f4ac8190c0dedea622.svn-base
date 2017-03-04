// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file NestedSat.h
 * \brief Classe permettant le calcul d'un Pid avec saturations
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/15
 * \version 4.0
 */

#ifndef NESTEDSAT_IMPL_H
#define NESTEDSAT_IMPL_H

#include <Object.h>

namespace flair {
namespace core {
class cvmatrix;
class io_data;
}
namespace gui {
class Layout;
class LayoutPosition;
class DoubleSpinBox;
class DataPlot1D;
}
namespace filter {
class NestedSat;
}
}

/*! \class NestedSat
* \brief Classe permettant le calcul d'un Pid avec saturations
*/
class NestedSat_impl {
public:
  NestedSat_impl(flair::filter::NestedSat *self,
                 const flair::gui::LayoutPosition *position, std::string name);
  ~NestedSat_impl();
  float Value(void);
  void UseDefaultPlot(const flair::gui::Layout *layout, int row, int col);
  void UpdateFrom(const flair::core::io_data *data);
  void ConvertSatFromDegToRad(void);
  float k;

private:
  flair::filter::NestedSat *self;
  flair::gui::DoubleSpinBox *kp, *kd, *sat, *dsat, *usat;
  flair::gui::DataPlot1D *plot;
  float Sat(float value, float borne);
};

#endif // NESTEDSAT_IMPL_H
