// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/08
//  filename:   TrajectoryGenerator2DSquare.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class generating a circle trajectory in 2D
//
//
/*********************************************************************/

#include "TrajectoryGenerator2DSquare.h"
#include "TrajectoryGenerator2DSquare_impl.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <LayoutPosition.h>
#include <Vector2D.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

TrajectoryGenerator2DSquare::TrajectoryGenerator2DSquare(
    const LayoutPosition *position, string name)
    : IODevice(position->getLayout(), name) {
  pimpl_ = new TrajectoryGenerator2DSquare_impl(this, position, name);
  AddDataToLog(pimpl_->output);
}

TrajectoryGenerator2DSquare::~TrajectoryGenerator2DSquare() { delete pimpl_; }

bool TrajectoryGenerator2DSquare::IsRunning(void) const {
  return pimpl_->is_running;
}

cvmatrix *TrajectoryGenerator2DSquare::Matrix(void) const {
  return pimpl_->output;
}

void TrajectoryGenerator2DSquare::StartTraj(const Vector2D &start_pos,
                                            float nb_lap) {
  pimpl_->StartTraj(start_pos, nb_lap);
}

void TrajectoryGenerator2DSquare::StopTraj(void) { pimpl_->is_running = false; }

void TrajectoryGenerator2DSquare::GetPosition(Vector2D &point) const {
  point.x = pimpl_->output->Value(0, 0);
  point.y = pimpl_->output->Value(0, 1);
}

void TrajectoryGenerator2DSquare::SetCenter(const Vector2D &value) {
  pimpl_->pos_off = value;
}

void TrajectoryGenerator2DSquare::GetSpeed(Vector2D &point) const {
  point.x = pimpl_->output->Value(1, 0);
  point.y = pimpl_->output->Value(1, 1);
}

void TrajectoryGenerator2DSquare::SetCenterSpeed(const Vector2D &value) {
  pimpl_->vel_off = value;
}

void TrajectoryGenerator2DSquare::Update(Time time) {
  pimpl_->Update(time);
  ProcessUpdate(pimpl_->output);
}

} // end namespace filter
} // end namespace flair
