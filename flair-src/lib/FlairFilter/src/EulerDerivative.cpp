// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   EulerDerivative.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining an euler derivative
//
//
/*********************************************************************/

#include "EulerDerivative.h"
#include "EulerDerivative_impl.h"
#include <cvmatrix.h>
#include <LayoutPosition.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

EulerDerivative::EulerDerivative(const IODevice *parent,
                                 const LayoutPosition *position, string name,
                                 const cvmatrix *init_value)
    : IODevice(parent, name) {
  pimpl_ = new EulerDerivative_impl(this, position, name, init_value);
  AddDataToLog(pimpl_->output);
}

EulerDerivative::~EulerDerivative() { delete pimpl_; }

cvmatrix *EulerDerivative::Matrix(void) const { return pimpl_->output; }

float EulerDerivative::Output(int row, int col) const {
  return pimpl_->output->Value(row, col);
}

void EulerDerivative::UpdateFrom(const io_data *data) {
  pimpl_->UpdateFrom(data);
  ProcessUpdate(pimpl_->output);
}

} // end namespace filter
} // end namespace flair
