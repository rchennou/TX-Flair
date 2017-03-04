// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/07/22
//  filename:   LaserRangeFinder.cpp
//
//  author:     César RICHARD
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Classe generique des recepteurs LaserRangeFinder
//
//
/*********************************************************************/

#include "LaserRangeFinder.h"
#include <cvmatrix.h>
#include <Tab.h>
#include <TabWidget.h>
#include <GridLayout.h>
#include <GroupBox.h>
#include <PushButton.h>
#include <FrameworkManager.h>
#include <Label.h>
#include <RangeFinderPlot.h>
#include <string.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

LaserRangeFinder::LaserRangeFinder(const FrameworkManager *parent, string name)
    : IODevice(parent, name) {
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(360, 1);
  output = new cvmatrix(this, desc, floatType);
  AddDataToLog(output);

  // station sol
  main_tab = new Tab(parent->GetTabWidget(), name);
  tab = new TabWidget(main_tab->NewRow(), name);
  sensor_tab = new Tab(tab, "Reglages");
  setup_groupbox = new GroupBox(sensor_tab->NewRow(), name);
}

LaserRangeFinder::LaserRangeFinder(const IODevice *parent, std::string name)
    : IODevice(parent, name) {
  plot_tab = NULL;
  main_tab = NULL;
  tab = NULL;
  sensor_tab = NULL;
  setup_groupbox = NULL;

  output = NULL;
}

LaserRangeFinder::~LaserRangeFinder() {}

GroupBox *LaserRangeFinder::GetGroupBox(void) const { return setup_groupbox; }

Layout *LaserRangeFinder::GetLayout(void) const { return sensor_tab; }

RangeFinderPlot *LaserRangeFinder::GetPlot(void) const { return plot; }

void LaserRangeFinder::UseDefaultPlot(void) {
  if (tab == NULL) {
    Err("not applicable for simulation part.\n");
    return;
  }

  plot_tab = new Tab(tab, "Mesures");
  plot = new RangeFinderPlot(plot_tab->NewRow(), "plot", "x", -30, 30, "y", -30,
                             30, output, 0, 359, output->Rows());
}
} // end namespace sensor
} // end namespace flair
