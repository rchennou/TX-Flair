// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Ahrs_impl.h
 * \brief Virtual class for Ahrs_impl
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/14
 * \version 4.0
 */

#ifndef AHRS_IMPL_H
#define AHRS_IMPL_H

#include <DataPlot.h>

namespace flair {
namespace core {
class AhrsData;
}
namespace gui {
class Tab;
class DataPlot1D;
}
namespace filter {
class Ahrs;
}
}

/*! \class Ahrs_impl
* \brief Abstract class for Ahrs_impl
*
* Use this class to define a custom Ahrs_impl. \n
*
*/

class Ahrs_impl {
public:
  Ahrs_impl(flair::filter::Ahrs *self);
  ~Ahrs_impl();
  void UseDefaultPlot(void);
  void AddPlot(const flair::core::AhrsData *ahrsData,
               flair::gui::DataPlot::Color_t color);
  flair::gui::DataPlot1D *rollPlot, *pitchPlot, *yawPlot;
  flair::gui::DataPlot1D *wXPlot, *wYPlot, *wZPlot;
  flair::gui::DataPlot1D *q0Plot, *q1Plot, *q2Plot, *q3Plot;
  flair::core::AhrsData *ahrsData;

private:
  flair::gui::Tab *eulerTab, *quaternionTab;
  flair::filter::Ahrs *self;
};

#endif // AHRS_IMPL_H
