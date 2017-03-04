// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/12/10
//  filename:   ButterworthLowPass.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a Butterworth low pass filter
//
//
/*********************************************************************/

#include "ButterworthLowPass.h"
#include "ButterworthLowPass_impl.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <LayoutPosition.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

ButterworthLowPass::ButterworthLowPass(const IODevice *parent,
                                       const LayoutPosition *position,
                                       string name, int order)
    : IODevice(parent, name) {
  pimpl_ = new ButterworthLowPass_impl(this, position, name, order);
  AddDataToLog(pimpl_->output);
}

ButterworthLowPass::ButterworthLowPass(const gui::LayoutPosition *position,
                                       string name, int order)
    : IODevice(position->getLayout(), name) {
  pimpl_ = new ButterworthLowPass_impl(this, position, name, order);
  AddDataToLog(pimpl_->output);
}

ButterworthLowPass::~ButterworthLowPass() { delete pimpl_; }

cvmatrix *ButterworthLowPass::Matrix(void) const { return pimpl_->output; }

float ButterworthLowPass::Output(void) const {
  return pimpl_->output->Value(0, 0);
}

void ButterworthLowPass::UpdateFrom(const io_data *data) {
  pimpl_->UpdateFrom(data);
  ProcessUpdate(pimpl_->output);
}

} // end namespace filter
} // end namespace flair
