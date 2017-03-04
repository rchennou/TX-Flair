//  created:    2013/06/26
//  filename:   Loop.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//
//
/*********************************************************************/

// include header of the class
#include "Loop.h"
// include only header of class declared in Loop.h (forward declaration)
#include "Sinus.h"
#include "MeanFilter.h"
#include <LowPassFilter.h>
#include <ButterworthLowPass.h>
#include <FrameworkManager.h>
#include <Tab.h>
#include <GridLayout.h>
#include <SpinBox.h>
#include <PushButton.h>
#include <DataPlot1D.h>
#include <cvmatrix.h>

using namespace std;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;
using namespace flair::sensor;

Loop::Loop(FrameworkManager *parent, string name, int priority)
    : Thread(parent, name, priority) {
  Tab *mainTab = new Tab(parent->GetTabWidget(), ObjectName());
  killButton = new PushButton(mainTab->NewRow(), "kill");
  startLogButton = new PushButton(mainTab->NewRow(), "start_log");
  stopLogButton = new PushButton(mainTab->LastRowLastCol(), "stop_log");
  period = new SpinBox(mainTab->NewRow(), "period thread:", " ms", 10, 1000, 1);

  sinus = new Sinus(parent, "sinus");
  sinus->UseDefaultPlot();

  // 1st order law pass filter on raw signal, its parent is the sinus
  firstLowPass = new LowPassFilter(sinus, sinus->GetSetupLayout()->NewRow(),
                                   "1st order lawpass filter");
  sinus->GetPlot()->AddCurve(
      firstLowPass->Matrix()->Element(0),
      DataPlot::Blue); // add output of the filter to signal's graph

  // 3rd order law pass filter on raw signal, its parent is the sinus
  thirdLowPass = new ButterworthLowPass(
      sinus, sinus->GetSetupLayout()->NewRow(), "3rd order lawpass filter", 3);
  sinus->GetPlot()->AddCurve(
      thirdLowPass->Matrix()->Element(0),
      DataPlot::Yellow); // add output of the filter to signal's graph

  // mean filter on raw signal, its parent is the sinus
  mean =
      new MeanFilter(sinus, sinus->GetSetupLayout()->NewRow(), "Mean filter");
  sinus->GetPlot()->AddCurve(
      mean->GetMatrix()->Element(0),
      DataPlot::Green); // add output of the filter to signal's graph

  // mean filter on 1st order law pass filter, its parent is the 1st order law
  // pass filter
  meanOnfirstLowPass =
      new MeanFilter(firstLowPass, sinus->GetSetupLayout()->NewRow(),
                     "Mean filter on 1st order lawpass filter");
  sinus->GetPlot()->AddCurve(
      meanOnfirstLowPass->GetMatrix()->Element(0),
      DataPlot::Black); // add output of the filter to signal's graph

  // set ojects to be logged
  // as the law pass filters and the mean filters have the sinus as parent, they
  // are automatically logged
  parent->AddDeviceToLog(sinus);
}

Loop::~Loop() {}

// main loop of the Thread
void Loop::Run(void) {
  // warn if changing from primary to secondary mode when in real time
  WarnUponSwitches(true);

  sinus->Start();

  SetPeriodMS(period->Value());

  while (1) {
    WaitPeriod();

    if (period->ValueChanged())
      SetPeriodMS(period->Value());

    if (killButton->Clicked())
      break;
    if (startLogButton->Clicked())
      getFrameworkManager()->StartLog();
    if (stopLogButton->Clicked())
      getFrameworkManager()->StopLog();

    // nothing more to do
    // this is a very simple example

    // normaly, we should use results of filters to calculate a control law
  }

  WarnUponSwitches(false);
}
