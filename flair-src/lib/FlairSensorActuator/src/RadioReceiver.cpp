// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/07/08
//  filename:   RadioReceiver.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for radio receiver
//
//
/*********************************************************************/

#include "RadioReceiver.h"
#include <Tab.h>
#include <TabWidget.h>
#include <FrameworkManager.h>
#include <cvmatrix.h>
#include <sstream>

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

RadioReceiver::RadioReceiver(const FrameworkManager *parent, string name,
                             unsigned int nb_channels)
    : IODevice(parent, name) {
  is_connected = false;
  this->nb_channels = nb_channels;

  // init matrix
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(nb_channels, 1);
  for (int i = 0; i < nb_channels; i++) {
    ostringstream channel_name;
    channel_name << "channel " << i;
    desc->SetElementName(i, 0, channel_name.str());
  }
  output = new cvmatrix(this, desc, floatType, name);

  // station sol
  main_tab = new Tab(parent->GetTabWidget(), name);
  tab = new TabWidget(main_tab->NewRow(), name);
  setup_tab = new Tab(tab, "Setup");

  AddDataToLog(output);
}

RadioReceiver::~RadioReceiver() { delete main_tab; }

Layout *RadioReceiver::GetLayout(void) const { return setup_tab; }

float RadioReceiver::ChannelValue(unsigned int id) const {
  if (id < nb_channels) {
    return output->Value(id, 0);
  } else {
    Err("channel %i/%i is out of bound\n", id, nb_channels);
    return -1;
  }
}

bool RadioReceiver::IsConnected(void) const { return is_connected; }

} // end namespace sensor
} // end namespace flair
