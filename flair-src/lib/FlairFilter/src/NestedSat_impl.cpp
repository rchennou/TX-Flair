// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/15
//  filename:   NestedSat_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet permettant le calcul d'un Pid avec saturations
//
//
/*********************************************************************/

#include "NestedSat_impl.h"
#include "NestedSat.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

NestedSat_impl::NestedSat_impl(NestedSat *self, const LayoutPosition *position,
                               string name) {
  this->self = self;
  k = 1;

  // init matrix
  self->input = new cvmatrix(self, 3, 1, floatType, name);

  GroupBox *reglages_groupbox = new GroupBox(position, name);
  sat =
      new DoubleSpinBox(reglages_groupbox->NewRow(), "sat ref:", 0, 9000000, 1);
  kp = new DoubleSpinBox(reglages_groupbox->NewRow(), "kp:", 0, 9000000, 1);
  dsat = new DoubleSpinBox(reglages_groupbox->NewRow(), "sat dref:", 0, 9000000,
                           1);
  kd = new DoubleSpinBox(reglages_groupbox->NewRow(), "kd:", 0, 9000000, 0.1);
  usat = new DoubleSpinBox(reglages_groupbox->NewRow(), "sat u:", 0, 1, .1);
}

NestedSat_impl::~NestedSat_impl(void) {}

void NestedSat_impl::UpdateFrom(const io_data *data) {
  float cons, dcons, law;
  cvmatrix *input = (cvmatrix *)data;

  input->GetMutex();

  cons = Sat(input->ValueNoMutex(0, 0), k * sat->Value());
  dcons = (cons - input->ValueNoMutex(1, 0)) * kp->Value();
  dcons = Sat(dcons, k * dsat->Value());
  law = (input->ValueNoMutex(2, 0) - dcons) * kd->Value();
  law = Sat(law, usat->Value());

  input->ReleaseMutex();

  self->output->SetValue(0, 0, law);
  self->output->SetDataTime(data->DataTime());
}

float NestedSat_impl::Sat(float value, float borne) {
  if (value < -borne)
    return -borne;
  if (value > borne)
    return borne;
  return value;
}
