// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   TrajectoryGenerator1D_impl.cpp
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
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <cmath>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

TrajectoryGenerator1D_impl::TrajectoryGenerator1D_impl(
    TrajectoryGenerator1D *self, const LayoutPosition *position, string name,
    string unit) {
  first_update = true;
  is_started = false;

  // init UI
  GroupBox *reglages_groupbox = new GroupBox(position, name);
  T = new DoubleSpinBox(reglages_groupbox->NewRow(), "period, 0 for auto:",
                        " s", 0, 1, 0.01);
  if (unit == "") {
    max_veloctity =
        new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),
                          "velocity max (absolute):", 0., 200000, 1);
  } else {
    max_veloctity = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),
                                      "velocity max (absolute):",
                                      " " + unit + "/s", 0., 200000, 1);
  }
  if (unit == "") {
    acceleration = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),
                                     "acceleration (absolute):", 0., 10, 1, 3);
  } else {
    acceleration = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),
                                     "acceleration (absolute):",
                                     " " + unit + "/s²", 0., 200000, 1);
  }

  Reset();

  // init matrix
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(2, 1);
  desc->SetElementName(0, 0, "pos");
  desc->SetElementName(1, 0, "vel");
  output = new cvmatrix(self, desc, floatType, name);

  output->SetValue(0, 0, pos);
  output->SetValue(1, 0, v);
}

TrajectoryGenerator1D_impl::~TrajectoryGenerator1D_impl() {}

void TrajectoryGenerator1D_impl::Reset(void) {
  pos = 0;
  v = 0;
  pos_off = 0;
  vel_off = 0;
}

void TrajectoryGenerator1D_impl::StartTraj(float start_pos, float end_pos) {
  is_started = true;
  is_finished = false;
  first_update = true;

  // configure trajectory
  end_position = end_pos;
  pos = start_pos;
  acc = acceleration->Value();
  v = 0;
  if (end_position < start_pos) {
    acc = -acc;
    // max_veloctity=-max_veloctity;
  }
}

// revoir l'interet du stop?
void TrajectoryGenerator1D_impl::StopTraj(void) {
  is_started = false;
  v = 0;
  // output->SetValue(1,0,v);
}

void TrajectoryGenerator1D_impl::Update(Time time) {
  float delta_t;

  if (T->Value() == 0) {
    if (first_update == true) {
      first_update = false;
      previous_time = time;
      output->GetMutex();
      output->SetValueNoMutex(0, 0, pos + pos_off);
      output->SetValueNoMutex(1, 0, v + vel_off);
      output->ReleaseMutex();

      output->SetDataTime(time);
      return;
    } else {
      delta_t = (float)(time - previous_time) / 1000000000.;
    }
  } else {
    delta_t = T->Value();
  }
  previous_time = time;

  if (is_started == true) {
    if (is_finished == false) {
      v += acc * delta_t;
      if (fabs(v) > fabs(max_veloctity->Value())) {
        if (v > 0)
          v = max_veloctity->Value();
        else
          v = -max_veloctity->Value();
      }
      pos += v * delta_t;
      if (end_position - v * v / (2 * acc) <= pos && v >= 0)
        acc = -acc;
      if (end_position - v * v / (2 * acc) >= pos && v < 0)
        acc = -acc;
      if (pos >= end_position && v >= 0)
        is_finished = true;
      if (pos <= end_position && v < 0)
        is_finished = true;
    }
    // else
    if (is_finished == true) {
      v = 0;
      pos = end_position;
    }
  }

  // on prend une fois pour toute les mutex et on fait des accès directs
  output->GetMutex();
  output->SetValueNoMutex(0, 0, pos + pos_off);
  output->SetValueNoMutex(1, 0, v + vel_off);
  output->ReleaseMutex();

  output->SetDataTime(time);
}
