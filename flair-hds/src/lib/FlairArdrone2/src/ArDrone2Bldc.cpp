// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/12/19
//  filename:   ArDrone2Bldc.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs ardrone
//
//
/*********************************************************************/

#include "ArDrone2Bldc.h"
#include "ArDrone2Bldc_impl.h"

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::actuator;

namespace flair {
namespace actuator {

ArDrone2Bldc::ArDrone2Bldc(const IODevice* parent,Layout* layout,string name,SerialPort* serialport,ArDrone2Gpio* gpio) : Bldc(parent,layout,name,4) {
    pimpl_=new ArDrone2Bldc_impl(this,serialport,gpio);
    SetIsReady(true);
}

ArDrone2Bldc::~ArDrone2Bldc() {
    delete pimpl_;
}

void ArDrone2Bldc::SetMotors(float* value) {
    pimpl_->SetMotors(value);
}

} // end namespace actuator
} // end namespace flair
