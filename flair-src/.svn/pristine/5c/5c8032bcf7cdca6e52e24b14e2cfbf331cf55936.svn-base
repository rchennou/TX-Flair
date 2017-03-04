// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/02
//  filename:   GuiFlair.h
//
//  authors:    Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Implementation of GuiInterface using Flair
//  			communication mechanism
//
//
/*********************************************************************/

#ifndef MAVPLANNER_GUI_FLAIR_H
#define MAVPLANNER_GUI_FLAIR_H

#include <string>

#include "GuiInterface.h"

namespace flair {
namespace core {
  class FrameworkManager;
  class Socket;
}
}

class GuiFlair : public GuiInterface {
public:

  GuiFlair(const flair::core::FrameworkManager *parent, std::string name);
  ~GuiFlair();

protected:

  virtual void MissionStart();
  virtual void MissionStop();
  virtual void MissionPause();
  virtual void MissionSend();

private:
  flair::core::Socket *inputSocket;
  flair::core::Socket *outputSocket;
  std::string outputAddress;
  int outputPort;	
};

#endif // MAVPLANNER_GUI_FLAIR_H
