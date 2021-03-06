// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/06/15
//  filename:   AfroBldc.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs i2c
//
//
/*********************************************************************/

#include "AfroBldc.h"
#include "AfroBldc_impl.h"
#include <GroupBox.h>
#include <Layout.h>
#include <DoubleSpinBox.h>
#include <SpinBox.h>
#include <ComboBox.h>
#include <PushButton.h>

using std::string;
using namespace flair::core;
using namespace flair::sensor;
using namespace flair::gui;

namespace flair {
namespace actuator {

AfroBldc::AfroBldc(const IODevice *parent, Layout *layout, string name,
                   uint8_t motors_count, I2cPort *i2cport)
    : Bldc(parent, layout, name, motors_count) {
  pimpl_ = new AfroBldc_impl(this, layout, i2cport);
}

AfroBldc::~AfroBldc() { delete pimpl_; }

void AfroBldc::SetMotors(float *values) { pimpl_->SetMotors(values); }

} // end namespace actuator
} // end namespace flair
