// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/02
//  filename:   GuiInterface.h
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

#ifndef MAVPLANNER_GUI_INTERFACE_H
#define MAVPLANNER_GUI_INTERFACE_H

#include <string>
#include <Thread.h>

namespace flair {
namespace core {
  class FrameworkManager;
  class Socket;
}
namespace gui {
  class Tab;
  class TabWidget;
  class DoubleSpinBox;
  class PushButton;
  class ComboBox;
  class GroupBox;
  class ListWidget;
  class Label;
}
}

class GuiInterface : public flair::core::Thread {
public:

  GuiInterface(const flair::core::FrameworkManager *parent, std::string name);
  ~GuiInterface();

protected:
  // reimplement the run of the Thread class
  void Run();
  
  // First tab callbacks
  virtual void MissionStart() = 0;
  virtual void MissionStop() = 0;
  virtual void MissionPause() = 0;
  virtual void MissionSend() = 0;

  std::string MissionCmdGet();

  // Main GUI
  flair::gui::TabWidget* tabWidget;
  flair::gui::Tab* mainTab;
  flair::gui::Tab* settingsTab;

  // Controls groupbox
  flair::gui::GroupBox* controlsGroupBox;
  flair::gui::PushButton* btnStartMission;
  flair::gui::PushButton* btnStopMission;
  flair::gui::PushButton* btnPauseMission;
  
  // Add cmd groupbox
  flair::gui::GroupBox* addCmdGroupBox;
  // flair::gui::Label* commandLabel;
  // flair::gui::Label* param1Label;
  // flair::gui::Label* param2Label;
  // flair::gui::Label* param3Label;
  flair::gui::ComboBox* comboCmd; 
  flair::gui::DoubleSpinBox* param1Field;
  flair::gui::DoubleSpinBox* param2Field;
  flair::gui::DoubleSpinBox* param3Field;
  flair::gui::DoubleSpinBox* latitudeField;
  flair::gui::DoubleSpinBox* longitudeField;
  flair::gui::DoubleSpinBox* altitudeField;
  flair::gui::PushButton* btnAddMissionCmd;
  flair::gui::PushButton* btnDelMissionCmd;
  flair::gui::PushButton* btnSendMission;

  // Show wpt groupbox
  flair::gui::GroupBox* showItemsGroupBox;
  flair::gui::ListWidget* listMissionItems;
  // flair::gui::ListWidget* listEntranceWpt;
  // flair::gui::ListWidget* listExitWpt;
  // flair::gui::PushButton* btnRemoveMissionWpt;
  // flair::gui::PushButton* btnRemoveEntranceWpt;
  // flair::gui::PushButton* btnRemoveExitWpt;  

  // Action wpt groupbox
  // flair::gui::GroupBox* actionWptGroupBox;
  // flair::gui::PushButton* btnSendWpt;
  // flair::gui::PushButton* btnClearWpt;
  // flair::gui::PushButton* btnLoop;

  // Socket to send commands
  flair::core::Socket* sendSocket;

  //TODO : think if useful to have private members
  
private:
  const std::vector<std::string> commandsAvailable = {"WAYPOINT", "TAKEOFF", "LAND", "RETURN", "JUMP"};
};

#endif // MAVPLANNER_GUI_INTERFACE_H
