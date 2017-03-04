// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/11/13
//  filename:   XBldc.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for Xufo Bldc
//
//
/*********************************************************************/

#include "XBldc.h"
#include "XBldc_impl.h"

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace actuator {

XBldc::XBldc(const IODevice *parent, Layout *layout, string name,
             I2cPort *i2cport)
    : Bldc(parent, layout, name, 4) {
  pimpl_ = new XBldc_impl(this, i2cport);
}

XBldc::~XBldc() { delete pimpl_; }

void XBldc::SetMotors(float *value) { pimpl_->SetMotors(value); }

} // end namespace actuator
} // end namespace flair
