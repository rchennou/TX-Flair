// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   LowPassFilter_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet permettant le calcul d'un filtre passe bas
//
//
/*********************************************************************/

#include "LowPassFilter_impl.h"
#include "LowPassFilter.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <DoubleSpinBox.h>

#define PI ((float)3.14159265358979323846)

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

LowPassFilter_impl::LowPassFilter_impl(const LowPassFilter *self,
                                       const LayoutPosition *position,
                                       string name,
                                       const cvmatrix *init_value) {
  first_update = true;

  if (init_value != NULL) {
    prev_value = (cvmatrix *)init_value;
  } else {
    // if NULL, assume dimension 1, and init=0
    cvmatrix_descriptor *desc = new cvmatrix_descriptor(1, 1);
    desc->SetElementName(0, 0, "output");
    prev_value = new cvmatrix(self, desc, floatType, name);
    prev_value->SetValue(0, 0, 0);
  }

  // init UI
  GroupBox *reglages_groupbox = new GroupBox(position, name);
  T = new DoubleSpinBox(reglages_groupbox->NewRow(), "period, 0 for auto", " s",
                        0, 10, 0.01);
  freq = new DoubleSpinBox(reglages_groupbox->NewRow(), "cutoff frequency",
                           " Hz", 0, 10000, 0.1, 2, 1);

  // init output matrix of same size as init
  cvmatrix_descriptor *desc =
      new cvmatrix_descriptor(prev_value->Rows(), prev_value->Cols());

  for (int i = 0; i < prev_value->Rows(); i++) {
    for (int j = 0; j < prev_value->Cols(); j++) {
      desc->SetElementName(i, j, prev_value->Name(i, j));
    }
  }

  output = new cvmatrix(self, desc,
                        prev_value->GetDataType().GetElementDataType(), name);

  output->SetValue(0, 0, 0);
}

LowPassFilter_impl::~LowPassFilter_impl() {}

void LowPassFilter_impl::UpdateFrom(const io_data *data) {
  float delta_t;
  float result;
  cvmatrix *input = (cvmatrix *)data;

  // on prend une fois pour toute les mutex et on fait des accès directs
  output->GetMutex();
  input->GetMutex();

  if (first_update == true) {
    for (int i = 0; i < input->Rows(); i++) {
      for (int j = 0; j < input->Cols(); j++) {
        output->SetValueNoMutex(i, j, prev_value->ValueNoMutex(i, j));
        prev_value->SetValueNoMutex(i, j, input->ValueNoMutex(i, j));
      }
    }
    first_update = false;
  } else {
    if (T->Value() == 0) {
      delta_t = (float)(data->DataTime() - previous_time) / 1000000000.;
    } else {
      delta_t = T->Value();
    }
    for (int i = 0; i < input->Rows(); i++) {
      for (int j = 0; j < input->Cols(); j++) {

        if (freq->Value() != 0) {
          output->SetValueNoMutex(i, j, (1 - 2 * PI * freq->Value() * delta_t) *
                                                prev_value->ValueNoMutex(i, j) +
                                            2 * PI * freq->Value() * delta_t *
                                                input->ValueNoMutex(i, j));
        } else {
          output->SetValueNoMutex(i, j, input->ValueNoMutex(i, j));
        }
        prev_value->SetValueNoMutex(i, j, output->ValueNoMutex(i, j));
      }
    }
  }
  input->ReleaseMutex();
  output->ReleaseMutex();

  output->SetDataTime(data->DataTime());
  previous_time = data->DataTime();
}
