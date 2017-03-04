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

#ifndef MAVPLANNER_GUI_GCS_H
#define MAVPLANNER_GUI_GCS_H

#include <string>
#include <array>

#include "GuiInterface.h"

#include "MavlinkUDP.h"

#define INTER_COMMAND_PAUSE 10000 // us
#define PERIOD_SECOND 1000000 // us

namespace flair {
namespace core {
  class FrameworkManager;
  class Socket;
}
}

class GuiGcs : public GuiInterface {
public:

  GuiGcs(const flair::core::FrameworkManager *parent, std::string name,
  		 std::string &outputAddress, int outputPort);
  ~GuiGcs();

protected:

  virtual void MissionStart();
  virtual void MissionStop();
  virtual void MissionPause();
  virtual void MissionSend();

  uint16_t MavCommandGet(const std::string& command) const;

private:
  std::string outputAddress;
  int outputPort;

  MavlinkUDP* mavCom;

  bool missionPauseEnabled;

  void Initialize();
  void ParametersParse(const std::string& parametersString, std::array<float, 6>& parametersFloat);
};

#endif // MAVPLANNER_GUI_GCS_H
