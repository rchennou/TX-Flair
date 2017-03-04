// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/03/30
//  filename:   TargetController.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for target side remote controls
//
//
/*********************************************************************/
#include "TargetController.h"
#include "Controller.h"
#include <TabWidget.h>
#include <Tab.h>
#include <FrameworkManager.h>
#include <cvmatrix.h>

#include <cstring>
#include <string>

#include <unistd.h> //for usleep

using namespace flair::core;
using namespace flair::gui;
using std::string;

namespace flair {
namespace sensor {

TargetController::TargetController(const FrameworkManager* parent,string name,uint8_t priority) :
    Thread(parent,name,priority),IODevice(parent,name) {
    main_tab=new Tab(getFrameworkManager()->GetTabWidget(),name);
    TabWidget* tab=new TabWidget(main_tab->NewRow(),name);
    setup_tab=new Tab(tab,"Reglages");
}

TargetController::~TargetController() {
  SafeStop();
  Join();
}

std::string TargetController::GetAxisName(unsigned int axisId) const {
  return string("axis") + std::to_string(axisId);
}

std::string TargetController::GetButtonName(unsigned int buttonId) const {
  return string("button") + std::to_string(buttonId);
}

bool TargetController::SetLedOn(unsigned int ledId) {
  if (!IsControllerActionSupported(ControllerAction::SetLedOn))
    return false;
  SwitchLedMessage *msgLed = new SwitchLedMessage(true, ledId);
  changeStateQueue.push(msgLed);
  return true;
}

bool TargetController::SetLedOff(unsigned int ledId) {
  if (!IsControllerActionSupported(ControllerAction::SetLedOn))
    return false;
  SwitchLedMessage *msgLed = new SwitchLedMessage(false, ledId);
  changeStateQueue.push(msgLed);
  return true;
}

bool TargetController::Rumble(unsigned int leftForce, unsigned int leftTimeout,
                              unsigned int rightForce,
                              unsigned int rightTimeout) {
  if (!IsControllerActionSupported(ControllerAction::Rumble))
    return false;
  RumbleMessage *msgRumble =
      new RumbleMessage(leftForce, leftTimeout, rightForce, rightTimeout);
  changeStateQueue.push(msgRumble);
  return true;
}

bool TargetController::FlashLed(unsigned int ledId, unsigned int onTimeout,
                                unsigned int offTimeout) {
  if (!IsControllerActionSupported(ControllerAction::FlashLed))
    return false;
  FlashLedMessage *msgFlashLed =
      new FlashLedMessage(ledId, onTimeout, offTimeout);
  changeStateQueue.push(msgFlashLed);
  return true;
}

float TargetController::GetAxisValue(unsigned int axisId) const {
  // TODO we'd better throw an exception here
  if (axis == NULL)
    return 0;

  axis->GetMutex();
  float axisValue = axis->Value(axisId, 0);
  axis->ReleaseMutex();
  return axisValue;
}

bool TargetController::IsButtonPressed(unsigned int buttonId) const {
  // TODO we'd better throw an exception here
  if (button == NULL)
    return false;

  button->GetMutex();
  bool buttonValue = button->Value(buttonId, 0);
  button->ReleaseMutex();
  return buttonValue;
}

void TargetController::Run() {
  SetPeriodMS(20);; //50Hz

  Message *message;

  if (getFrameworkManager()->ErrorOccured() || !ControllerInitialization()) {
    SafeStop();
    Thread::Err("An error occured, we don't proceed with the loop.\n");
  } else {

    axis = new cvmatrix((IODevice *)this, axisNumber, 1, floatType);
    button =
        new cvmatrix((IODevice *)this, buttonNumber, 1, SignedIntegerType(8));

    while (!ToBeStopped()) {
      // Thread::Info("Debug: entering acquisition loop\n");
      if (getFrameworkManager()->ConnectionLost() == true)
        SafeStop();

      if (IsDataFrameReady()) {
        // Thread::Info("Debug: data frame is ready\n");

        AcquireAxisData(*axis);
        AcquireButtonData(*button);

        // send the data
        axis->SetDataTime(GetTime());
        ProcessUpdate(axis);

        // send pending controller state change request(s)

        while (changeStateQueue.size() != 0) {
          message = changeStateQueue.front();
          if (ProcessMessage(message)) {
            changeStateQueue.pop();
            delete message;
          }
        }
      }
      WaitPeriod();
    }
  }
}

Tab *TargetController::GetTab() const { return setup_tab; }

} // end namespace sensor
} // end namespace flair
