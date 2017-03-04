// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/04/14
//  filename:   TargetEthController.h
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class that gets remote controls through an ethernet connection.
//              Typical use case: a remote control is plugged in a workstation
//              and sends remote control
//              data to a distant target (this class) through Wifi
//
//
/*********************************************************************/

#ifndef TARGETETHCONTROLLER_H
#define TARGETETHCONTROLLER_H

#include "TargetController.h"

namespace flair {
namespace core {
class FrameworkManager;
class cvmatrix;
class TcpSocket;
class Socket;
}
namespace gui {
class Tab;
class TabWidget;
class DataPlot1D;
}
}

namespace flair {
namespace sensor {
/*! \class TargetController
*
* \brief Base Class for target side remote controls
*
*/
class TargetEthController : public TargetController {
public:
  TargetEthController(const core::FrameworkManager *parent, std::string name,
                      uint16_t port, uint8_t priority = 0);
  ~TargetEthController();
  // void DrawUserInterface();
protected:
  bool IsConnected() const;
  // axis stuff
  std::string GetAxisName(unsigned int axisId) const;
  // button stuff
  std::string GetButtonName(unsigned int axisId) const;
  // controller state stuff
  bool ProcessMessage(core::Message *msg);
  bool IsControllerActionSupported(ControllerAction action) const;

  bool IsDataFrameReady();
  void AcquireAxisData(core::cvmatrix &axis);     // responsible for getting the
                                                  // axis data from the hardware
  void AcquireButtonData(core::cvmatrix &button); // responsible for getting the
                                                  // button data from the
                                                  // hardware

  bool ControllerInitialization();

private:
  uint16_t readBits(uint8_t offsetInBits, uint8_t valueSizeInBits, char *buffer,
                    size_t bufferSize);
  uint8_t getByteOrNull(char *buffer, int byte, size_t bufferSize);
  uint32_t charBufferToUint32(char *buffer, size_t bufferSize);
  core::TcpSocket *listeningSocket;
  int listeningPort;
  core::TcpSocket *controlSocket = NULL;
  core::Socket *dataSocket;
  std::string *axisName = NULL;
  std::string *buttonName = NULL;
  size_t dataFrameSize;
  char *dataFrameBuffer;
  char *receiveFrameBuffer;
  size_t receiveCurrentPosition;
  uint8_t buttonOffset;
};
}
}

#endif // TARGETCONTROLLER_H
