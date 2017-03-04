// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file X4X8Multiplex_impl.h
 * \brief Class defining X4 and X8 multiplexing
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/04/10
 * \version 4.0
 */

#ifndef X4X8MULTIPLEX_IMPL_H
#define X4X8MULTIPLEX_IMPL_H

#include <string>

namespace flair {
namespace core {
class cvmatrix;
class io_data;
}
namespace gui {
class DataPlot1D;
class ComboBox;
}
namespace filter {
class X4X8Multiplex;
}
}

/*! \class X4X8Multiplex_impl
*
* \brief Class defining X4 and X8 multiplexing
*/
class X4X8Multiplex_impl {
public:
  X4X8Multiplex_impl(flair::filter::X4X8Multiplex *self, int nb_mot);
  ~X4X8Multiplex_impl();
  void UseDefaultPlot(void);
  void UpdateFrom(const flair::core::io_data *data);
  int nb_mot;
  std::string MotorName(int index);

private:
  flair::core::cvmatrix *output;
  flair::gui::ComboBox *pas;
  flair::gui::DataPlot1D *plots[4];
  flair::filter::X4X8Multiplex *self;
  float Set(float trim, float u);
};

#endif // X4X8MULTIPLEX_IMPL_H
