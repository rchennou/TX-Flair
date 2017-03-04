// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/22
//  filename:   UsRangeFinder.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for UsRangeFinder
//
//
/*********************************************************************/

#include "UsRangeFinder.h"
#include <FrameworkManager.h>
#include <Tab.h>
#include <TabWidget.h>
#include <GroupBox.h>
#include <Layout.h>
#include <DataPlot1D.h>
#include <cvmatrix.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

UsRangeFinder::UsRangeFinder(const FrameworkManager *parent, string name)
    : IODevice(parent, name) {
  plot_tab = NULL;

  cvmatrix_descriptor *desc = new cvmatrix_descriptor(1, 1);
  desc->SetElementName(0, 0, name);
  output = new cvmatrix(this, desc, floatType);
  AddDataToLog(output);

  // station sol
  main_tab = new Tab(parent->GetTabWidget(), name);
  tab = new TabWidget(main_tab->NewRow(), name);
  sensor_tab = new Tab(tab, "Reglages");
  setup_groupbox = new GroupBox(sensor_tab->NewRow(), name);
}

UsRangeFinder::UsRangeFinder(const IODevice *parent, std::string name)
    : IODevice(parent, name) {
  plot_tab = NULL;
  main_tab = NULL;
  tab = NULL;
  sensor_tab = NULL;
  setup_groupbox = NULL;

  output = NULL;
}

UsRangeFinder::~UsRangeFinder() {
  if (main_tab != NULL)
    delete main_tab;
}

GroupBox *UsRangeFinder::GetGroupBox(void) const { return setup_groupbox; }

Layout *UsRangeFinder::GetLayout(void) const { return sensor_tab; }

DataPlot1D *UsRangeFinder::GetPlot(void) const { return plot; }

Tab *UsRangeFinder::GetPlotTab(void) const { return plot_tab; }

void UsRangeFinder::UseDefaultPlot(void) {
  if (tab == NULL) {
    Err("not applicable for simulation part.\n");
    return;
  }

  plot_tab = new Tab(tab, "Mesures");
  plot = new DataPlot1D(plot_tab->NewRow(), ObjectName(), 0, 2);
  plot->AddCurve(output->Element(0));
}

void UsRangeFinder::LockUserInterface(void) const {
  setup_groupbox->setEnabled(false);
}

void UsRangeFinder::UnlockUserInterface(void) const {
  setup_groupbox->setEnabled(true);
}

float UsRangeFinder::Value(void) const { return output->Value(0, 0); }

} // end namespace sensor
} // end namespace flair
