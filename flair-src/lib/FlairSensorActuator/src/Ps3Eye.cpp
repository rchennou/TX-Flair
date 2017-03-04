// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/01/19
//  filename:   Ps3Eye.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant la camera Ps3Eye
//
//
/*********************************************************************/

#include "Ps3Eye.h"
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <CheckBox.h>
#include <GridLayout.h>
#include <cvimage.h>
#include <FrameworkManager.h>
#include <stdio.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

Ps3Eye::Ps3Eye(const FrameworkManager *parent, string name, int camera_index,
               uint8_t priority)
    : V4LCamera(parent, name, camera_index, 320, 240,
                cvimage::Type::Format::YUYV, priority) {}

Ps3Eye::~Ps3Eye() {}

} // end namespace sensor
} // end namespace flair
