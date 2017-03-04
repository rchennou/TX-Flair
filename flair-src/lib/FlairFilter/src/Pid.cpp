// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   Pid.cpp
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

#include "Pid.h"
#include "Pid_impl.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <LayoutPosition.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

Pid::Pid(const LayoutPosition *position, string name)
    : ControlLaw(position->getLayout(), name) {
  pimpl_ = new Pid_impl(this, position, name);
}

Pid::~Pid(void) { delete pimpl_; }

void Pid::UseDefaultPlot(const gui::LayoutPosition *position) {
  pimpl_->UseDefaultPlot(position);
}

void Pid::Reset(void) {
  pimpl_->i = 0;
  pimpl_->first_update = true;
}

void Pid::UpdateFrom(const io_data *data) {
  pimpl_->UpdateFrom(data);
  ProcessUpdate(output);
}

void Pid::SetValues(float p, float d) {
  input->SetValue(0, 0, p);
  input->SetValue(1, 0, d);
}

} // end namespace filter
} // end namespace flair
