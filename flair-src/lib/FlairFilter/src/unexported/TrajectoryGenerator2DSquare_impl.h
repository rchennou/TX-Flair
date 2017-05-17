// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file TrajectoryGenerator2DSquare_impl.h
 * \brief Class generating a circle trajectory in 2D
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/08
 * \version 4.0
 */

#ifndef TRAJECTORYGENERATOR2DSQUARE_IMPL_H
#define TRAJECTORYGENERATOR2DSQUARE_IMPL_H

#include <Object.h>
#include <Vector2D.h>

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
class TrajectoryGenerator2DSquare;
}
}

/*! \class TrajectoryGenerator2DSquare_impl
* \brief Class generating a circle trajectory in 2D
*/

class TrajectoryGenerator2DSquare_impl {

public:
  TrajectoryGenerator2DSquare_impl(
      flair::filter::TrajectoryGenerator2DSquare *self,
      const flair::gui::LayoutPosition *position, std::string name);
  ~TrajectoryGenerator2DSquare_impl();
  void Update(flair::core::Time time);
  void StartTraj(const flair::core::Vector2D &start_pos, float nb_lap);
  bool is_running;
  flair::core::cvmatrix *output;
  flair::core::Vector2D pos_off, vel_off;

private:
  flair::core::Time previous_time;
  float CurrentTime, FinishTime;
  bool first_update;
  flair::core::Vector2D pos, posStart;
  float angle_off;
  flair::gui::DoubleSpinBox *veloctity, *acceleration, *distance;
  float nb_lap;

  unsigned int nb;
};

#endif // TrajectoryGenerator2DSquare_IMPL_H
