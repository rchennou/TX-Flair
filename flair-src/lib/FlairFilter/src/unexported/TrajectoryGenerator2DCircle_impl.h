// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file TrajectoryGenerator2DCircle_impl.h
 * \brief Class generating a circle trajectory in 2D
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/08
 * \version 4.0
 */

#ifndef TRAJECTORYGENERATOR2DCIRCLE_IMPL_H
#define TRAJECTORYGENERATOR2DCIRCLE_IMPL_H

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
class TrajectoryGenerator2DCircle;
}
}

/*! \class TrajectoryGenerator2DCircle_impl
* \brief Class generating a circle trajectory in 2D
*/

class TrajectoryGenerator2DCircle_impl {

public:
  TrajectoryGenerator2DCircle_impl(
      flair::filter::TrajectoryGenerator2DCircle *self,
      const flair::gui::LayoutPosition *position, std::string name);
  ~TrajectoryGenerator2DCircle_impl();
  void Update(flair::core::Time time);
  void StartTraj(const flair::core::Vector2D &start_pos, float nb_lap);
  void FinishTraj(void);
  bool is_running;
  flair::core::cvmatrix *output;
  flair::core::Vector2D pos_off, vel_off;

private:
  flair::core::Time previous_time;
  float CurrentTime, FinishTime;
  bool first_update, is_finishing;
  flair::core::Vector2D pos;
  float angle_off;
  flair::gui::DoubleSpinBox *T, *veloctity, *acceleration, *rayon;
  float nb_lap;
};

#endif // TRAJECTORYGENERATOR2DCIRCLE_IMPL_H
