// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/03/30
//  filename:   HostEthController.h
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for host side remote controls that talks to target
//  side through ethernet connection
//
//
/*********************************************************************/

#ifndef HOSTETHCONTROLLER_H
#define HOSTETHCONTROLLER_H

#include <IODevice.h>
#include <Thread.h>
#include <stdint.h>

namespace flair {
namespace core {
class FrameworkManager;
class cvmatrix;
class TcpSocket;
class Socket;
class Mutex;
}
namespace gui {
class Tab;
class TabWidget;
class DataPlot1D;
}
}

namespace flair {
namespace sensor {
enum class ControllerAction;

/*! \class HostEthController
*
* \brief Base Class for host side remote controls that talks to target side
*through ethernet connection
*
* There are 2 communication channels:
*   - 1 connection with the ground station to display the values. Output for
*analog sticks is normalized in the range [-1, 1] (float values)
*   - 1 connection with the target to send the controller values (and receive
*controller state modification requests)
*/
class HostEthController : public core::Thread, public core::IODevice {
public:
  HostEthController(const core::FrameworkManager *parent, std::string name,
                    std::string address, int port, uint32_t period = 10,
                    uint32_t _bitsPerAxis = 7, uint8_t priority = 0);
  ~HostEthController();
  void DrawUserInterface();

protected:
  std::string controllerName;
  core::TcpSocket *controlSocket; // connection to the target
  core::Socket *dataSocket;
  std::string targetAddress;
  int targetPort;
  gui::Tab *tab;
  gui::TabWidget *tabWidget;
  virtual bool IsDataFrameReady() { return true; };
  virtual void CompleteDataFrameGrab(){};
  //        int8_t *datas;
  //        uint8_t dataSize;
  char *dataFrameBuffer;
  size_t dataFrameSize;
  virtual void ProcessMessage(core::Message *controllerAction){};

  virtual std::string GetAxisDescription(unsigned int axis);
  virtual void
  GetAxisData() = 0; // responsible for getting the axis data from the hardware
  unsigned int axisNumber;
  core::cvmatrix *axis;
  gui::DataPlot1D **axisPlot;
  uint32_t bitsPerAxis;
  uint32_t nativeBitsPerAxis;

  virtual std::string GetButtonDescription(unsigned int button);
  virtual void GetButtonData() = 0; // responsible for getting the button data
                                    // from the hardware
  unsigned int buttonNumber;
  core::cvmatrix *button;
  uint8_t buttonOffset;
  bool meaningfulDataAvailable;

private:
  class DataSender : public core::Thread {
  public:
    DataSender(Object *parent, HostEthController *hostEthController,
               std::string name, uint8_t priority = 0);
    void Run();

  private:
    HostEthController *hostEthController;
  };
  DataSender *dataSender;

  bool ControllerInitialization();
  bool ConnectedWithTarget();
  void SendControllerInfo();
  void Run();
  void BuildDataFrame();
  bool writeBits(uint16_t value, uint8_t valueSizeInBits, char *buffer,
                 uint8_t offsetInBits);
  core::Mutex *connectionEstablishedMutex;
};
}
}

#endif // HOSTETHCONTROLLER_H
