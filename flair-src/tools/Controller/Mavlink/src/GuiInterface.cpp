// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/02
//  filename:   GuiInterface.cpp
//
//  authors:    Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Create the GUI and give an abstract interface to it
//
//
/*********************************************************************/

#include "GuiInterface.h"

#include <cvmatrix.h>
#include <FrameworkManager.h>
#include <Socket.h>
#include <Thread.h>

#include <Tab.h>
#include <TabWidget.h>
#include <DoubleSpinBox.h>
#include <PushButton.h>
#include <GroupBox.h>
#include <ListWidget.h>
#include <Label.h>
#include <ComboBox.h>

#include <string>
#include <sstream>

using namespace flair::core;
using namespace flair::gui;
using namespace std;

GuiInterface::GuiInterface(const FrameworkManager *parent, string name)
                  : Thread(parent, name, 6),
                  mainTab(new Tab(parent->GetTabWidget(), name)) {

  tabWidget = new TabWidget(mainTab->NewRow(), name);

  // Main tab
  Tab* settingsTab = new Tab(tabWidget, "Settings");
  
  // Controls group
  controlsGroupBox = new GroupBox(settingsTab->NewRow(), "Controls");
  btnStartMission = new PushButton(controlsGroupBox->LastRowLastCol(), "Start mission");
  btnStopMission = new PushButton(controlsGroupBox->LastRowLastCol(), "Stop mission");
  btnPauseMission = new PushButton(controlsGroupBox->LastRowLastCol(), "Pause mission");

  // Add cmd group
  addCmdGroupBox = new GroupBox(settingsTab->NewRow(), "Add mission command");
  // commandLabel = new Label(addCmdGroupBox->NewRow(), "Command label");
  // commandLabel->SetText("Command");
  // param1Label = new Label(addCmdGroupBox->LastRowLastCol(), "Param1 label");
  // commandLabel->SetText("Param1");
  // param2Label = new Label(addCmdGroupBox->LastRowLastCol(), "Param2 label");
  // commandLabel->SetText("Param2");
  // param3Label = new Label(addCmdGroupBox->LastRowLastCol(), "Param3 label");
  // commandLabel->SetText("Param3");
  comboCmd = new ComboBox(addCmdGroupBox->NewRow(), "Select command");
  // Fill the ComboBox
  for (auto &command : commandsAvailable) {
    comboCmd->AddItem(command);    
  }
  // comboCmd->AddItem("WAYPOINT");
  // comboCmd->AddItem("TAKEOFF");
  // comboCmd->AddItem("LAND");
  // comboCmd->AddItem("RETURN");
  // comboCmd->AddItem("JUMP");
  param1Field = new DoubleSpinBox(addCmdGroupBox->NewRow(), "Param1", -90, 90, 0.5, 1, 0);
  latitudeField = new DoubleSpinBox(addCmdGroupBox->LastRowLastCol(), "Longitude", -90, 90, 0.5, 1, 1.5);
  param2Field = new DoubleSpinBox(addCmdGroupBox->NewRow(), "Param2", -90, 90, 0.5, 1, 0);
  longitudeField = new DoubleSpinBox(addCmdGroupBox->LastRowLastCol(), "Latitude", -90, 90, 0.5, 1, -1.5);
  param3Field = new DoubleSpinBox(addCmdGroupBox->NewRow(), "Param3", -90, 90, 0.5, 1, 0);
  altitudeField = new DoubleSpinBox(addCmdGroupBox->LastRowLastCol(), "Altitude", -90, 90, 0.5, 1, 2);
  btnAddMissionCmd = new PushButton(addCmdGroupBox->NewRow(), "Add mission cmd");
  btnDelMissionCmd = new PushButton(addCmdGroupBox->LastRowLastCol(), "Del mission cmd");
  btnSendMission = new PushButton(addCmdGroupBox->LastRowLastCol(), "Send mission");

  // Show wpt group
  showItemsGroupBox = new GroupBox(settingsTab->NewRow(), "Show mission items");
  listMissionItems = new ListWidget(showItemsGroupBox->NewRow(), "Mission cmd list");

  // listEntranceWpt = new ListWidget(showWptGroupBox->LastRowLastCol(), "Entrance wpt");
  // listExitWpt = new ListWidget(showWptGroupBox->LastRowLastCol(), "Exit wpt");
  // btnRemoveMissionWpt = new PushButton(showWptGroupBox->NewRow(), "Remove mission wpt");
  // btnRemoveEntranceWpt = new PushButton(showWptGroupBox->LastRowLastCol(), "Remove entrance wpt");
  // btnRemoveExitWpt = new PushButton(showWptGroupBox->LastRowLastCol(), "Remove exit wpt");

  // // Action wpt group
  // actionWptGroupBox = new GroupBox(settingsTab->NewRow(), "Action");
  // btnSendWpt = new PushButton(actionWptGroupBox->NewRow(), "Send wpt");
  // btnClearWpt = new PushButton(actionWptGroupBox->LastRowLastCol(), "Clear wpt");
  // btnLoop = new PushButton(actionWptGroupBox->LastRowLastCol(), "Loop");

  //TODO IP & PORT from config.h file
  // sendSocket = new Socket((Thread *)this, "send socket", "127.0.0.1:5000");
}

GuiInterface::~GuiInterface() {
}

void GuiInterface::Run() {
  Thread::Info("Debug: enter MavPlanner acquisition loop\n");

  if (getFrameworkManager()->ErrorOccured()) {
    SafeStop();
    Thread::Err("An error occurred, we don't launch the Run loop.\n");
  }

  while (!ToBeStopped()) {
    // TODO : time from config.h
    Thread::SleepMS(500);
    // Buttons to control GUI
  	if (btnAddMissionCmd->Clicked()) {
      listMissionItems->AddItem(MissionCmdGet());
    }
    if (btnDelMissionCmd->Clicked()) {
      listMissionItems->RemoveItem();
    }
    // Buttons to send commands
  	if (btnStartMission->Clicked()) {
  		MissionStart();
    }
  	if (btnStopMission->Clicked()) {
  		MissionStop();
    }
  	if (btnPauseMission->Clicked()) {
  		MissionPause();
    }
    if (btnSendMission->Clicked()) {
  		MissionSend();
    }
  }
}

std::string GuiInterface::MissionCmdGet() {
  std::ostringstream stringStream;
  stringStream.precision(1);
  stringStream << fixed;
  stringStream << commandsAvailable[comboCmd->CurrentIndex()] << "|" << param1Field->Value() << "|" << param2Field->Value() \
               << "|" << param3Field->Value() << "|" << latitudeField->Value() << "|" << longitudeField->Value() << "|" << altitudeField->Value();
  return stringStream.str();
}
