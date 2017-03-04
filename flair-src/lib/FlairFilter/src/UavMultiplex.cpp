// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/11
//  filename:   UavMultiplex.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining uav multiplexing
//
//
/*********************************************************************/

#include "UavMultiplex.h"
#include "UavMultiplex_impl.h"
#include <cvmatrix.h>
#include <FrameworkManager.h>
#include <Tab.h>
#include <GridLayout.h>
#include "compile_info.h"

using std::string;
using namespace flair::core;
using namespace flair::gui;

//todo: put it on seprate file, but not possible with static lib?
static void constructor() __attribute__((constructor));

void constructor() {
  compile_info("FlairFilter");
}


namespace flair {
namespace filter {

UavMultiplex::UavMultiplex(const core::FrameworkManager *parent,
                           std::string name)
    : IODevice(parent, name) {
  pimpl_ = new UavMultiplex_impl(parent, this, name);
}

UavMultiplex::~UavMultiplex(void) { delete pimpl_; }

void UavMultiplex::Update(core::Time time) {
  pimpl_->input->SetDataTime(time);
  UpdateFrom(pimpl_->input);
}

void UavMultiplex::SetMultiplexComboBox(string name, int index) {
  pimpl_->SetMultiplexComboBox(name, index);
}

int UavMultiplex::MultiplexValue(int index) const {
  return pimpl_->MultiplexValue(index);
}

TabWidget *UavMultiplex::GetTabWidget(void) const { return pimpl_->tabwidget; }

Layout *UavMultiplex::GetLayout(void) const { return pimpl_->setup_tab; }

void UavMultiplex::LockUserInterface(void) const {
  pimpl_->setup_tab->setEnabled(false);
}

void UavMultiplex::UnlockUserInterface(void) const {
  pimpl_->setup_tab->setEnabled(true);
}

void UavMultiplex::SetRoll(float value) {
  pimpl_->input->SetValue(0, 0, value);
}

void UavMultiplex::SetPitch(float value) {
  pimpl_->input->SetValue(1, 0, value);
}

void UavMultiplex::SetYaw(float value) { pimpl_->input->SetValue(2, 0, value); }

void UavMultiplex::SetThrust(float value) {
  pimpl_->input->SetValue(3, 0, value);
}

void UavMultiplex::SetRollTrim(float value) {
  pimpl_->input->SetValue(4, 0, value);
}

void UavMultiplex::SetPitchTrim(float value) {
  pimpl_->input->SetValue(5, 0, value);
}

void UavMultiplex::SetYawTrim(float value) {
  pimpl_->input->SetValue(6, 0, value);
}

} // end namespace filter
} // end namespace flair
