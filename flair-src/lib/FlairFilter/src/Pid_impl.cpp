// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   Pid_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a PID
//
//
/*********************************************************************/
#include "Pid_impl.h"
#include "Pid.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <DataPlot1D.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

Pid_impl::Pid_impl(Pid *self, const LayoutPosition *position, string name) {
  i = 0;
  first_update = true;
  this->self = self;

  // init matrix
  self->input = new cvmatrix(self, 2, 1, floatType, name);

  cvmatrix_descriptor *desc = new cvmatrix_descriptor(4, 1);
  desc->SetElementName(0, 0, "p");
  desc->SetElementName(1, 0, "i");
  desc->SetElementName(2, 0, "d");
  desc->SetElementName(3, 0, "p+i+d");
  state = new cvmatrix(self, desc, floatType, name);

  GroupBox *reglages_groupbox = new GroupBox(position, name);
  T = new DoubleSpinBox(reglages_groupbox->NewRow(), "period, 0 for auto", " s",
                        0, 1, 0.01);
  kp = new DoubleSpinBox(reglages_groupbox->NewRow(), "kp:", 0, 90000000, 0.01,
                         3);
  ki = new DoubleSpinBox(reglages_groupbox->NewRow(), "ki:", 0, 90000000, 0.01,
                         3);
  sati = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(), "sat i:", 0, 1,
                           0.01);
  kd = new DoubleSpinBox(reglages_groupbox->NewRow(), "kd:", 0, 90000000, 0.01,
                         3);
  sat = new DoubleSpinBox(reglages_groupbox->NewRow(), "sat:", 0, 1, 0.1);
}

Pid_impl::~Pid_impl(void) {}

void Pid_impl::UseDefaultPlot(const LayoutPosition *position) {
  DataPlot1D *plot = new DataPlot1D(position, self->ObjectName(), -1, 1);
  plot->AddCurve(state->Element(0));
  plot->AddCurve(state->Element(1), DataPlot::Green);
  plot->AddCurve(state->Element(2), DataPlot::Blue);
  plot->AddCurve(state->Element(3), DataPlot::Black);
}

void Pid_impl::UpdateFrom(const io_data *data) {
  float p, d, total;
  float delta_t;
  cvmatrix *input = (cvmatrix *)data;

  if (T->Value() == 0) {
    delta_t = (float)(data->DataTime() - previous_time) / 1000000000.;
  } else {
    delta_t = T->Value();
  }
  if (first_update == true) {
    delta_t = 0;
    first_update = false;
  }

  input->GetMutex();
  p = kp->Value() * input->ValueNoMutex(0, 0);
  i += ki->Value() * input->ValueNoMutex(0, 0) * delta_t;
  if (i > sati->Value())
    i = sati->Value();
  if (i < -sati->Value())
    i = -sati->Value();
  d = kd->Value() * input->ValueNoMutex(1, 0);
  input->ReleaseMutex();

  total = p + i + d;
  if (total > sat->Value())
    total = sat->Value();
  if (total < -sat->Value())
    total = -sat->Value();

  state->GetMutex();
  state->SetValueNoMutex(0, 0, p);
  state->SetValueNoMutex(1, 0, i);
  state->SetValueNoMutex(2, 0, d);
  state->SetValueNoMutex(3, 0, total);
  state->ReleaseMutex();

  self->output->SetValue(0, 0, total);
  self->output->SetDataTime(data->DataTime());

  previous_time = data->DataTime();
}
