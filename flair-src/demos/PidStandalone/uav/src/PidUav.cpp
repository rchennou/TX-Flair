//  created:    2016/06/01
//  filename:   PidUav.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Uav class showing the incidence of pid parameters choice
//
//
/*********************************************************************/

#include "PidUav.h"
#include <TargetController.h>
#include <cvmatrix.h>
#include <GridLayout.h>
#include <DataPlot1D.h>
#include <Tab.h>
#include <TabWidget.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <FrameworkManager.h>
#include <MetaDualShock3.h>
#include <Pid.h>
#include <AhrsData.h>

#include <stdio.h>

using namespace std;
using namespace flair::core;
using namespace flair::sensor;
using namespace flair::gui;
using namespace flair::filter;
using namespace flair::meta;

/*
** ===================================================================
**    constructor and destructor
**
** ===================================================================
*/
PidUav::PidUav(Uav *uav, TargetController *controller)
    : behaviourMode(BehaviourMode_t::Default),
      UavStateMachine(uav, controller) {
  my_uRoll = new Pid(setupLawTab->At(1, 1), "custom uRoll");
  my_uRoll->UseDefaultPlot(graphLawTab->LastRowLastCol());
  my_uPitch = new Pid(setupLawTab->At(1, 0), "custom uPitch");
  my_uPitch->UseDefaultPlot(graphLawTab->NewRow());
}

void PidUav::SignalEvent(Event_t event) {
  UavStateMachine::SignalEvent(event);
  switch (event) {
  case Event_t::TakingOff:
    // always take off in default mode
    behaviourMode = BehaviourMode_t::Default;
    break;
  case Event_t::EnteringFailSafeMode:
    // return to default mode
    Thread::Info("Entering failSafe mode\n");
    behaviourMode = BehaviourMode_t::Default;
    break;
  }
}

bool PidUav::StartCustomMode() {
  // ask UavStateMachine to enter in custom torques
  if (SetTorqueMode(TorqueMode_t::Custom)) {
    Thread::Info("CustomTorques: start\n");
    my_uPitch->Reset();
    my_uRoll->Reset();
    return true;
  } else {
    Thread::Warn("CustomTorques: could not start\n");
    return false;
  }
}

void PidUav::StartOscillatingMode() {
  if (behaviourMode == BehaviourMode_t::Default) {
    if (!StartCustomMode())
      return;
  }
  behaviourMode = BehaviourMode_t::Oscillating;
  Thread::Info("Entering oscillating mode\n");
  // remove the 'D' effect with a strong 'P'
}

void PidUav::ExtraCheckJoystick(void) {
  static bool wasOscillatingModeButtonPressed = false;
  // controller button R1 enters optical flow mode
  if (GetJoystick()->IsButtonPressed(9)) { // R1
    if (!wasOscillatingModeButtonPressed) {
      wasOscillatingModeButtonPressed = true;
      if (behaviourMode != BehaviourMode_t::Oscillating)
        StartOscillatingMode();
    }
  } else {
    wasOscillatingModeButtonPressed = false;
  }
}

void PidUav::ComputeCustomTorques(Euler &torques) {
  ComputeDefaultTorques(torques);
  // overload default torques calculation for pitch and roll
  const AhrsData *refOrientation = GetDefaultReferenceOrientation();
  Quaternion refQuaternion;
  Vector3D refAngularRates;
  refOrientation->GetQuaternionAndAngularRates(refQuaternion, refAngularRates);
  Euler refAngles = refQuaternion.ToEuler();

  const AhrsData *currentOrientation = GetDefaultOrientation();
  Quaternion currentQuaternion;
  Vector3D currentAngularRates;
  currentOrientation->GetQuaternionAndAngularRates(currentQuaternion,
                                                   currentAngularRates);
  Euler currentAngles = currentQuaternion.ToEuler();

  my_uRoll->SetValues(currentAngles.roll - refAngles.roll,
                      currentAngularRates.x);
  my_uRoll->Update(GetTime());
  torques.roll = my_uRoll->Output();

  my_uPitch->SetValues(currentAngles.pitch - refAngles.pitch,
                       currentAngularRates.y);
  my_uPitch->Update(GetTime());
  torques.pitch = my_uPitch->Output();
}

PidUav::~PidUav() {}
