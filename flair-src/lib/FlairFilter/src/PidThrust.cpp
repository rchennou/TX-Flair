// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/11/07
//  filename:   PidThrust.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a PidThrust
//
//
/*********************************************************************/

#include "PidThrust.h"
#include "PidThrust_impl.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <LayoutPosition.h>
#include <DoubleSpinBox.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

PidThrust::PidThrust(const LayoutPosition *position, string name)
    : ControlLaw(position->getLayout(), name) {
  pimpl_ = new PidThrust_impl(this, position, name);
}

PidThrust::~PidThrust(void) { delete pimpl_; }

void PidThrust::UseDefaultPlot(const flair::gui::LayoutPosition *position) {
  pimpl_->UseDefaultPlot(position);
}

void PidThrust::Reset(void) {
  pimpl_->i = 0;
  pimpl_->offset_g = 0;
}

void PidThrust::ResetI(void) { pimpl_->i = 0; }

float PidThrust::GetOffset(void) { return pimpl_->offset_g; }

void PidThrust::UpdateFrom(const io_data *data) {
  pimpl_->UpdateFrom(data);
  ProcessUpdate(output);
}

void PidThrust::SetValues(float p, float d) {
  input->SetValue(0, 0, p);
  input->SetValue(1, 0, d);
}

void PidThrust::ResetOffset(void) { pimpl_->offset_g = 0; }

void PidThrust::SetOffset(void) { pimpl_->offset_g = pimpl_->offset->Value(); }

bool PidThrust::OffsetStepUp(void) {
  pimpl_->offset_g += pimpl_->pas_offset->Value();
  if (pimpl_->offset_g > 1) {
    pimpl_->offset_g = 1;
    return false;
  } else {
    return true;
  }
}

bool PidThrust::OffsetStepDown(void) {
  pimpl_->offset_g -= pimpl_->pas_offset->Value();
  if (pimpl_->offset_g < pimpl_->offset->Value()) {
    pimpl_->offset_g = pimpl_->offset->Value();
    return false;
  } else {
    return true;
  }
}

} // end namespace filter
} // end namespace flair
