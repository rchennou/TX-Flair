// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/14
//  filename:   Ahrs.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Virtual class for AHRS
//
//
/*********************************************************************/

#include "Ahrs.h"
#include "Ahrs_impl.h"
#include <Imu.h>
#include <DataPlot1D.h>
#include <AhrsData.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;

namespace flair {
namespace filter {

Ahrs::Ahrs(const Imu *parent, string name) : IODevice(parent, name) {
  pimpl_ = new Ahrs_impl(this);
  AddDataToLog(pimpl_->ahrsData);
}

Ahrs::~Ahrs() { delete pimpl_; }

const Imu *Ahrs::GetImu(void) const { return (Imu *)Parent(); }

const AhrsData *Ahrs::GetDatas(void) const { return pimpl_->ahrsData; }

void Ahrs::GetDatas(core::AhrsData **ahrsData) const {
  *ahrsData = pimpl_->ahrsData;
}

void Ahrs::LockUserInterface(void) const {
  //((Imu*)Parent())->LockUserInterface();
}

void Ahrs::UnlockUserInterface(void) const {
  //((Imu*)Parent())->UnlockUserInterface();
}

void Ahrs::UseDefaultPlot(void) {
  pimpl_->UseDefaultPlot();
  ((Imu *)Parent())->UseDefaultPlot();
}

void Ahrs::AddPlot(const AhrsData *ahrsData, DataPlot::Color_t color) {
  pimpl_->AddPlot(ahrsData, color);
}

DataPlot1D *Ahrs::RollPlot(void) const { return pimpl_->rollPlot; }

DataPlot1D *Ahrs::PitchPlot(void) const { return pimpl_->pitchPlot; }

DataPlot1D *Ahrs::YawPlot(void) const { return pimpl_->yawPlot; }

DataPlot1D *Ahrs::WXPlot(void) const { return pimpl_->wXPlot; }

DataPlot1D *Ahrs::WYPlot(void) const { return pimpl_->wYPlot; }

DataPlot1D *Ahrs::WZPlot(void) const { return pimpl_->wZPlot; }

} // end namespace filter
} // end namespace flair
