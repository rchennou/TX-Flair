// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/15
//  filename:   NestedSat.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a PID with saturations
//
//
/*********************************************************************/

#include "NestedSat.h"
#include "NestedSat_impl.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <LayoutPosition.h>
#include <Euler.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

NestedSat::NestedSat(const LayoutPosition *position, string name)
    : ControlLaw(position->getLayout(), name) {
  pimpl_ = new NestedSat_impl(this, position, name);
}

NestedSat::~NestedSat(void) { delete pimpl_; }

void NestedSat::UpdateFrom(const io_data *data) {
  pimpl_->UpdateFrom(data);
  ProcessUpdate(output);
}

void NestedSat::SetValues(float p_ref, float p, float d) {
  input->SetValue(0, 0, p_ref);
  input->SetValue(1, 0, p);
  input->SetValue(2, 0, d);
}
// TODO: add a combobox to choose between rad and deg
void NestedSat::ConvertSatFromDegToRad(void) { pimpl_->k = Euler::ToRadian(1); }

} // end namespace filter
} // end namespace flair
