// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/02
//  filename:   GuiGcs.h
//
//  authors:    Thomas Fuhrmann
//              Milan Erdelj
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Implementation of GuiInterface, using sockets
//
//
/*********************************************************************/

#include "GuiGcs.h"
#include "GuiInterface.h"

#include <Socket.h>
#include <FrameworkManager.h>

#include "MavlinkUDP.h"

#include <ListWidget.h>

#include <iostream>
#include <array>

using namespace std;
using namespace flair::core;
using namespace flair::gui;

const std::string delimiter = "|";

GuiGcs::GuiGcs(const FrameworkManager *parent, string name,
  		 	   std::string &outputAddress, int outputPort):
			   GuiInterface(parent, name) {
  cout << "MavPlanner GuiGcs constructor" << endl;
  //outputSocket = new Socket((Thread *)this, "output socket", outputAddress + ":" + to_string(outputPort));

  missionPauseEnabled = false;

  mavCom = new MavlinkUDP(outputAddress, outputPort);
}

GuiGcs::~GuiGcs() {
  if (mavCom) {
    mavCom->stopThreads();
    delete mavCom;
  }
}

void GuiGcs::MissionStart() {
  cout << "MavPlanner GuiGcs MissionStart" << endl;

  Initialize();

    cout << "--------------------\n";
    cout << "   MISSION START\n";
    cout << "--------------------\n";

    // set auto armed mode
    mavCom->cmdDoSetMode(mavCom->target.getSysID(), mavCom->target.getCompID(), MAV_MODE_AUTO_ARMED);
    mavCom->waitCommandAck(ACK_TIMEOUT);

    usleep(INTER_COMMAND_PAUSE);

    // mission start message
    mavCom->cmdMissionStart(mavCom->target.getSysID(), mavCom->target.getCompID(), mavCom->missionFirst, mavCom->missionLast);
    mavCom->waitCommandAck(ACK_TIMEOUT);

    mavCom->missionStarted();
}

void GuiGcs::MissionStop() {
  cout << "MavPlanner GuiGcs MissionStop" << endl;
}

void GuiGcs::MissionPause() {
  cout << "MavPlanner GuiGcs MissionPause" << endl;
  // send pause/continue depending on the state of the button
  if(missionPauseEnabled) {
      missionPauseEnabled = false;
      cout << "Sent pause command.\n";
      mavCom->cmdDoPauseContinue(mavCom->target.getSysID(), mavCom->target.getCompID(), 0);
  } else {
      missionPauseEnabled = true;
      cout << "Sent continue command.\n";
      mavCom->cmdDoPauseContinue(mavCom->target.getSysID(), mavCom->target.getCompID(), 1);
  }
  mavCom->waitCommandAck(ACK_TIMEOUT);
}

void GuiGcs::MissionSend() {
  cout << "MavPlanner GuiGcs MissionSend" << endl;

  // upload a flight plan
  cout << "---------------\n";
  cout << "Flight planning \n";
  cout << "---------------\n";

  // get the list of commands to send
  std::vector<std::string> missionCommandList = listMissionItems->GetItemList();

  // reset all the previous waypoints
  mavCom->sendMissionClearAll(mavCom->target.getSysID(), mavCom->target.getCompID());

  cout << "[INFO] Mission write partial list.\n";
  // write partial list, takeoff + 4 waypoints + land
  mavCom->sendMissionWritePartialList(mavCom->target.getSysID(),mavCom->target.getCompID(), 0, missionCommandList.size());
  mavCom->waitMissionAck(ACK_TIMEOUT);

  // sending mission items
  cout << "[INFO] Mission items.\n";
  for (auto &missionCommand : missionCommandList) {
    cout << "[INFO] Mission item : " << missionCommand << "\n";
    // Parse command
    std::string command = missionCommand.substr(0, missionCommand.find(delimiter));
    missionCommand.erase(0, missionCommand.find(delimiter) + delimiter.length());
    std::array<float, 6> missionParameters;
    ParametersParse(missionCommand, missionParameters);

    mavCom->sendMissionItem(mavCom->target.getSysID(), mavCom->target.getCompID(), 0, MAV_FRAME_GLOBAL_RELATIVE_ALT, MavCommandGet(command), 0, 1,
            missionParameters[0], missionParameters[1], missionParameters[2], 0, missionParameters[3], missionParameters[4], missionParameters[5]);
    mavCom->waitMissionAck(ACK_TIMEOUT);
  }

  cout << "[INFO] Check mission item list.\n";
  // mission request list (to check)
  mavCom->sendMissionRequestList(mavCom->target.getSysID(), mavCom->target.getCompID());
  //mavCom.waitMissionCount(ACK_TIMEOUT);

  cout << "----------------\n";
  cout << "Flight plan sent \n";
  cout << "----------------\n";
}

void GuiGcs::ParametersParse(const std::string& parametersString, std::array<float, 6>& parametersFloat) {
  std::string parametersBuffer = parametersString;
  for (int count = 0; count < parametersFloat.size(); count++) {
    parametersFloat[count] = std::stof(parametersBuffer.substr(0, parametersBuffer.find(delimiter)));
    parametersBuffer.erase(0, parametersBuffer.find(delimiter) + delimiter.length());
  }
}

uint16_t GuiGcs::MavCommandGet(const std::string& command) const {
  uint16_t returnValue = -1;
  if (command == "WAYPOINT") {
    returnValue = MAV_CMD_NAV_WAYPOINT;
  }
  if (command == "TAKEOFF") {
    returnValue = MAV_CMD_NAV_TAKEOFF;
  }
  if (command == "LAND") {
    returnValue = MAV_CMD_NAV_LAND;
  }
  if (command == "RETURN") {
    returnValue = MAV_CMD_NAV_RETURN_TO_LAUNCH;
  }
  if (command == "JUMP") {
    returnValue = MAV_CMD_DO_JUMP;
  }
  return returnValue;
}

void GuiGcs::Initialize() {
    cout << "--------------------\n";
    cout << "Initialization START\n";
    cout << "--------------------\n";

    // UAV start heartbeat, message ID=0, interval 1000 ms
    mavCom->cmdSetMessageInterval(mavCom->target.getSysID(), mavCom->target.getCompID(), MAVLINK_MSG_ID_HEARTBEAT, PERIOD_SECOND);
    mavCom->waitCommandAck(ACK_TIMEOUT);

    usleep(INTER_COMMAND_PAUSE);

    // ask for the autopilot capabilities
    mavCom->cmdRequestAutopilotCapabilities(mavCom->target.getSysID(), mavCom->target.getCompID());
    // TODO wait for autopilot version
    //

    usleep(INTER_COMMAND_PAUSE);

    // initiate system status callback on the UAV, message ID=1, interval 1000 ms
    mavCom->cmdSetMessageInterval(mavCom->target.getSysID(), mavCom->target.getCompID(), MAVLINK_MSG_ID_SYS_STATUS, PERIOD_SECOND);

    usleep(INTER_COMMAND_PAUSE);

    // initiate system time callback on the UAV
    mavCom->cmdSetMessageInterval(mavCom->target.getSysID(), mavCom->target.getCompID(), MAVLINK_MSG_ID_SYSTEM_TIME, PERIOD_SECOND);

    usleep(INTER_COMMAND_PAUSE);

    // set preflight mode
    mavCom->cmdDoSetMode(mavCom->target.getSysID(), mavCom->target.getCompID(), MAV_MODE_PREFLIGHT);
    mavCom->waitCommandAck(ACK_TIMEOUT);

    usleep(INTER_COMMAND_PAUSE);

    // set home position
    mavCom->cmdDoSetHome(mavCom->target.getSysID(), mavCom->target.getCompID(), 0);
    mavCom->waitCommandAck(ACK_TIMEOUT);

    usleep(INTER_COMMAND_PAUSE);

    // clear all mission waypoints
    mavCom->sendMissionClearAll(mavCom->target.getSysID(), mavCom->target.getCompID());
    usleep(INTER_COMMAND_PAUSE);
    mavCom->waitMissionAck(ACK_TIMEOUT);
    cout << "--------------------\n";
    cout << "Initialization END\n";
    cout << "--------------------\n";
}
