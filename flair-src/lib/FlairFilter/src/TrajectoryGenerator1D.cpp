// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   TrajectoryGenerator1D.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class generating a trajectory in 1D
//
//
/*********************************************************************/

#include "TrajectoryGenerator1D.h"
#include "TrajectoryGenerator1D_impl.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <LayoutPosition.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

TrajectoryGenerator1D::TrajectoryGenerator1D(const LayoutPosition *position,
                                             string name, string unit)
    : IODevice(position->getLayout(), name) {
  pimpl_ = new TrajectoryGenerator1D_impl(this, position, name, unit);
  AddDataToLog(pimpl_->output);
}

TrajectoryGenerator1D::~TrajectoryGenerator1D() { delete pimpl_; }

cvmatrix *TrajectoryGenerator1D::Matrix(void) const { return pimpl_->output; }

void TrajectoryGenerator1D::StartTraj(float start_pos, float end_pos) {
  pimpl_->StartTraj(start_pos, end_pos);
}

// revoir l'interet du stop?
void TrajectoryGenerator1D::StopTraj(void) { pimpl_->StopTraj(); }

bool TrajectoryGenerator1D::IsRunning(void) const {
  if (pimpl_->is_started == true) {
    if (pimpl_->is_finished == true) {
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

float TrajectoryGenerator1D::Position(void) const {
  return pimpl_->output->Value(0, 0);
}

void TrajectoryGenerator1D::Reset(void) {
  if (IsRunning() == false) {
    pimpl_->Reset();
  } else {
    Err("impossible while running\n");
  }
}

void TrajectoryGenerator1D::SetPositionOffset(float value) {
  pimpl_->pos_off = value;
}

float TrajectoryGenerator1D::Speed(void) const {
  return pimpl_->output->Value(1, 0);
}

void TrajectoryGenerator1D::SetSpeedOffset(float value) {
  pimpl_->vel_off = value;
}

void TrajectoryGenerator1D::Update(Time time) {
  pimpl_->Update(time);
  ProcessUpdate(pimpl_->output);
}

} // end namespace filter
} // end namespace flair
