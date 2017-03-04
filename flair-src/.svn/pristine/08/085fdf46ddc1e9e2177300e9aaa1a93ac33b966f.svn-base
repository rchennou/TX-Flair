// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file TrajectoryGenerator1D_impl.h
 * \brief Class generating a trajectory in 1D
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef TRAJECTORYGENERATOR1D_IMPL_H
#define TRAJECTORYGENERATOR1D_IMPL_H

namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class LayoutPosition;
class DoubleSpinBox;
}
}

/*! \class TrajectoryGenerator1D_impl
* \brief Class generating a trajectory in 1D
*/
class TrajectoryGenerator1D_impl {

public:
  TrajectoryGenerator1D_impl(flair::filter::TrajectoryGenerator1D *self,
                             const flair::gui::LayoutPosition *position,
                             std::string name, std::string unit);
  ~TrajectoryGenerator1D_impl();
  void Update(flair::core::Time time);
  void StartTraj(float start_pos, float end_pos);
  void StopTraj(void);
  void Reset(void);
  flair::core::cvmatrix *output;
  float pos_off, vel_off;
  bool is_finished, is_started;

private:
  float end_position;
  float pos, v, acc;
  flair::core::Time previous_time;
  bool first_update;
  flair::gui::DoubleSpinBox *T, *max_veloctity, *acceleration;
};

#endif // TRAJECTORYGENERATOR1D_IMPL_H
