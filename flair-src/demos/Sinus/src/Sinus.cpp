//  created:    2013/06/26
//  filename:   Sinus.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class generating a sinus signal
//
//
/*********************************************************************/

#include "Sinus.h"
#include <FrameworkManager.h>
#include <TabWidget.h>
#include <Tab.h>
#include <GridLayout.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <SpinBox.h>
#include <DataPlot1D.h>
#include <cvmatrix.h>
#include <math.h>

#define PI ((float)3.14159265358979323846)

using namespace std;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

Sinus::Sinus(const FrameworkManager *parent, string name, int priority)
    : IODevice(parent, name), Thread(parent, name, priority) {

  plot = NULL;

  // 1*1 output matrix
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(1, 1);
  desc->SetElementName(0, 0, "value"); // name will be used for graphs and logs
  output = new cvmatrix((IODevice *)this, desc, floatType, name);
  output->SetValue(0, 0, 0);

  AddDataToLog(output);

  // interface initialisation
  mainTab = new Tab(parent->GetTabWidget(), name);
  tabWidget = new TabWidget(mainTab->NewRow(), name);

  Tab *settingsTab = new Tab(tabWidget, "Settings");
  GroupBox *sinusGroupBox = new GroupBox(settingsTab->NewRow(), name);
  frequency = new DoubleSpinBox(sinusGroupBox->NewRow(), "frequence:", " Hz", 0,
                                100, 1);
  amplitude = new DoubleSpinBox(sinusGroupBox->LastRowLastCol(), "amplitude:",
                                0, 10, 1);
  offset =
      new DoubleSpinBox(sinusGroupBox->LastRowLastCol(), "offset:", 0, 10, 1);
  period =
      new SpinBox(settingsTab->NewRow(), "period thread:", " ms", 1, 1000, 1);

  setupLayout = new GridLayout(
      settingsTab->NewRow(),
      "setup"); // layout sui servira à placer des filtres par exemple
}

Sinus::~Sinus() {

  SafeStop();
  Join();

  // main_tab has the FrameworkManager as parent; it will be destroyed when
  // FrameworkManager is destroyed
  // it is cleaner to delete it manually, because main_tab is unnecessary when
  // Sinus is deleted
  delete mainTab;
}

void Sinus::UseDefaultPlot(void) {
  Tab *plotTab = new Tab(tabWidget, "Graph");
  plot = new DataPlot1D(plotTab->NewRow(), "Sinus", -10, 10);
  plot->AddCurve(output->Element(0), DataPlot::Red);
}

GridLayout *Sinus::GetSetupLayout(void) const { return setupLayout; }

DataPlot1D *Sinus::GetPlot(void) const {
  if (plot == NULL)
    Printf("Sinus::Plot, plot not yet defined, call UseDefaultPlot first\n");
  return plot;
}

cvmatrix *Sinus::GetMatrix(void) const { return output; }

float Sinus::GetValue(void) const { return output->Value(0, 0); }

// main function, where  we compute the signal
void Sinus::Run(void) {

  SetPeriodMS(period->Value());

  // warn if changing from primary to secondary mode when in real time
  WarnUponSwitches(true);

  Time initTime = GetTime();

  while (!ToBeStopped()) {
    WaitPeriod();

    if (period->ValueChanged() == true)
      SetPeriodMS(period->Value());

    // compute sinus
    Time actualTime = GetTime();
    float value =
        offset->Value() +
        amplitude->Value() *
            sinf(2 * PI * frequency->Value() * (actualTime - initTime) /
                 1000000000.); // les temps sont en nanosecondes

    // put the result in output matrix
    output->SetValue(0, 0, value);
    // put corresponding time
    output->SetDataTime(actualTime);

    // ProcessUpdate is very important
    // we must call it after updating the output matrix
    // it allows:
    // -to save value in the logs
    // -to automatically call the next filter UpdateFrom method
    ProcessUpdate(output);
  }
}
} // end namespace sensor
} // end namespace flair
