// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/05/27
//  filename:   Controller.h
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Utility classes for controllers
//
//
/*********************************************************************/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Object.h>
#include <string.h>

namespace flair {
namespace core {
class Message;
}
}

namespace flair {
namespace sensor {

enum class ControllerAction { SetLedOn, SetLedOff, Rumble, FlashLed, Exit };

class RumbleMessage : public core::Message {
public:
  RumbleMessage(unsigned int leftForce, unsigned int leftTimeout,
                unsigned int rightForce, unsigned int rightTimeout);
  unsigned int GetLeftForce() const;
  unsigned int GetLeftTimeout() const;
  unsigned int GetRightForce() const;
  unsigned int GetRightTimeout() const;
  void SetLeftForce(unsigned int leftForce);
  void SetLeftTimeout(unsigned int leftTimeout);
  void SetRightForce(unsigned int rightForce);
  void SetRightTimeout(unsigned int rightTimeout);

private:
  static const unsigned int leftForceOffset = sizeof(ControllerAction);
  static const unsigned int leftTimeoutOffset =
      sizeof(ControllerAction) + sizeof(unsigned int);
  static const unsigned int rightForceOffset =
      sizeof(ControllerAction) + 2 * sizeof(unsigned int);
  static const unsigned int rightTimeoutOffset =
      sizeof(ControllerAction) + 3 * sizeof(unsigned int);
};

class SwitchLedMessage : public core::Message {
public:
  SwitchLedMessage(bool isOn, unsigned int ledId);
  bool IsOn() const;
  unsigned int GetLedId() const;
  void SetOn();
  void SetOff();
  void SetLedId(unsigned int ledId);

private:
  static const unsigned int isOnOffset = sizeof(ControllerAction);
  static const unsigned int ledIdOffset =
      sizeof(ControllerAction) + sizeof(bool);
};

class FlashLedMessage : public core::Message {
public:
  FlashLedMessage(unsigned int ledId, unsigned int onTime,
                  unsigned int offTime);
  unsigned int GetLedId() const;
  unsigned int GetOnTime() const;
  unsigned int GetOffTime() const;
  void SetLedId(unsigned int ledId);
  void SetOnTime(unsigned int onTime);
  void SetOffTime(unsigned int offTime);

private:
  static const unsigned int ledIdOffset = sizeof(ControllerAction);
  static const unsigned int onTimeOffset =
      sizeof(ControllerAction) + sizeof(unsigned int);
  static const unsigned int offTimeOffset =
      sizeof(ControllerAction) + 2 * sizeof(unsigned int);
};
}
}

#endif // CONTROLLER_H
