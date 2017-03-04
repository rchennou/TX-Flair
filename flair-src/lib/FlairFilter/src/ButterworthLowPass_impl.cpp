// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/12/10
//  filename:   ButterworthLowPass_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet permettant le calcul d'un filtre passe bas de Butterworth
//
//
/*********************************************************************/

#include "ButterworthLowPass_impl.h"
#include "ButterworthLowPass.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <DoubleSpinBox.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

ButterworthLowPass_impl::ButterworthLowPass_impl(ButterworthLowPass *self,
                                                 const LayoutPosition *position,
                                                 string name, int order) {
  // init UI
  GroupBox *reglages_groupbox = new GroupBox(position, name);
  T = new DoubleSpinBox(reglages_groupbox->NewRow(), "period, 0 for auto", " s",
                        0, 10, 0.01);
  cutoff = new DoubleSpinBox(reglages_groupbox->NewRow(), "cutoff frequency",
                             " Hz", 0, 10000, 0.1, 2, 1);

  cvmatrix_descriptor *desc = new cvmatrix_descriptor(1, 1);
  desc->SetElementName(0, 0, "output");
  output = new cvmatrix(self, desc, floatType, name);

  output->SetValue(0, 0, 0);

  f = new PoleFilter(order);

  if (T->Value() != 0)
    f->setup(1. / T->Value(), cutoff->Value());
  f->reset();

  first_update = true;
}

ButterworthLowPass_impl::~ButterworthLowPass_impl() { delete f; }

void ButterworthLowPass_impl::UpdateFrom(const io_data *data) {
  float result;
  cvmatrix *input = (cvmatrix *)data;

  if (T->ValueChanged() || cutoff->ValueChanged()) {
    if (T->Value() != 0) {
      f->setup(1. / T->Value(), cutoff->Value());
    } else {
      first_update = true;
    }
  }

  // on prend une fois pour toute les mutex et on fait des accès directs
  output->GetMutex();
  input->GetMutex();

  if (T->Value() == 0) {
    float delta_t = (float)(data->DataTime() - previous_time) / 1000000000.;
    f->setup(1. / delta_t, cutoff->Value());
  }

  if (first_update == true) {
    first_update = false;
  } else {
    result = f->filter(input->ValueNoMutex(0, 0));
    output->SetValueNoMutex(0, 0, result);
  }

  input->ReleaseMutex();
  output->ReleaseMutex();

  output->SetDataTime(data->DataTime());
  previous_time = data->DataTime();
}
