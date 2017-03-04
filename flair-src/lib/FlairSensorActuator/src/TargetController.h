// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/04/14
//  filename:   TargetController.h
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

#ifndef TARGETCONTROLLER_H
#define TARGETCONTROLLER_H

#include <IODevice.h>
#include <Thread.h>
#include <stdint.h>
#include <queue>

namespace flair {
namespace core {
class FrameworkManager;
class cvmatrix;
class Socket;
class io_data;
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

/*! \class TargetController
*
* \brief Base Class for target side remote controls
*
*/
class TargetController : public core::Thread, public core::IODevice {
public:
  TargetController(const core::FrameworkManager *parent, std::string name,
                   uint8_t priority = 0);
  ~TargetController();
  // void DrawUserInterface();
  virtual bool IsConnected() const = 0;
  virtual bool IsDataFrameReady() = 0;
  // axis stuff
  unsigned int GetAxisNumber() const;
  virtual std::string GetAxisName(unsigned int axisId) const;
  float
  GetAxisValue(unsigned int axisId) const; // always in the range [-1.0,1.0]
  // button stuff
  unsigned int GetButtonNumber() const;
  bool IsButtonPressed(unsigned int buttonId) const;
  virtual std::string GetButtonName(unsigned int axisId) const;
  // controller state stuff
  virtual bool IsControllerActionSupported(ControllerAction action) const {
    return false;
  };
  bool SetLedOn(unsigned int ledId);
  bool SetLedOff(unsigned int ledId);
  bool Rumble(unsigned int left_force, unsigned int left_timeout,
              unsigned int right_force, unsigned int right_timeout);
  bool FlashLed(unsigned int ledId, unsigned int on_timeout,
                unsigned int off_timeout);
  void UpdateFrom(const core::io_data *data){}; // TODO
  gui::Tab *GetTab(void) const;

protected:
  virtual bool ProcessMessage(core::Message *msg) = 0;
  void QueueMessage(core::Message msg);
  virtual bool ControllerInitialization() = 0; // {return true;};
  // axis stuff
  unsigned int axisNumber;
  core::cvmatrix *axis = NULL;
  virtual void AcquireAxisData(core::cvmatrix &axis) = 0; // responsible for
                                                          // getting the axis
                                                          // data from the
                                                          // hardware
  uint16_t bitsPerAxis;
  // button stuff
  unsigned int buttonNumber;
  core::cvmatrix *button = NULL;
  virtual void AcquireButtonData(core::cvmatrix &button) = 0; // responsible for
                                                              // getting the
                                                              // button data
                                                              // from the
                                                              // hardware
  // controller state stuff
  unsigned int ledNumber;

private:
  void Run();
  std::queue<core::Message *> changeStateQueue;
  flair::gui::Tab *main_tab;
  flair::gui::Tab *setup_tab;
};
}
}

#endif // TARGETCONTROLLER_H
