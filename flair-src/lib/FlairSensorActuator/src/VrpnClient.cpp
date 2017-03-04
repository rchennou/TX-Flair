// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/03
//  filename:   VrpnClient.cpp
//
//  author:     César Richard, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class to connect to a Vrpn server
//
/*********************************************************************/

#include "VrpnClient.h"
#include "VrpnClient_impl.h"
#include <FrameworkManager.h>
#include <TabWidget.h>
#include <Layout.h>
#include <string.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

VrpnClient::VrpnClient(const FrameworkManager *parent, string name,
                       string address, uint16_t us_period, uint8_t priority)
    : Thread(parent, name, priority) {
  pimpl_ = new VrpnClient_impl(this, name, address, us_period);
}

VrpnClient::VrpnClient(const FrameworkManager *parent, string name,
                       SerialPort *serialport, uint16_t us_period,
                       uint8_t priority)
    : Thread(parent, name, priority) {
  pimpl_ = new VrpnClient_impl(this, name, serialport, us_period);
}

VrpnClient::~VrpnClient() {
  SafeStop();
  Join();

  delete pimpl_;
}

Layout *VrpnClient::GetLayout(void) const {
  return (Layout *)(pimpl_->setup_tab);
}

TabWidget *VrpnClient::GetTabWidget(void) const { return pimpl_->tab; }

bool VrpnClient::UseXbee(void) const { return pimpl_->UseXbee(); }

void VrpnClient::Run(void) { pimpl_->Run(); }

} // end namespace sensor
} // end namespace flair
