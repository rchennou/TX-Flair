// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   LowPassFilter.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a first order low pass filter
//
//
/*********************************************************************/

#include "LowPassFilter.h"
#include "LowPassFilter_impl.h"
#include <cvmatrix.h>
#include <LayoutPosition.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

LowPassFilter::LowPassFilter(const IODevice *parent,
                             const LayoutPosition *position, string name,
                             const cvmatrix *init_value)
    : IODevice(parent, name) {
  pimpl_ = new LowPassFilter_impl(this, position, name, init_value);
  AddDataToLog(pimpl_->output);
}

LowPassFilter::~LowPassFilter() { delete pimpl_; }

cvmatrix *LowPassFilter::Matrix(void) const { return pimpl_->output; }

float LowPassFilter::Output(int row, int col) const {
  return pimpl_->output->Value(row, col);
}

void LowPassFilter::UpdateFrom(const io_data *data) {
  pimpl_->UpdateFrom(data);
  ProcessUpdate(pimpl_->output);
}

} // end namespace filter
} // end namespace flair
