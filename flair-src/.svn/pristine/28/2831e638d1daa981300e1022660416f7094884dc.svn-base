// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/05/27
//  filename:   Controller.cpp
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
#include "Controller.h"

using namespace flair::core;

namespace flair {
namespace sensor {

RumbleMessage::RumbleMessage(unsigned int leftForce, unsigned int leftTimeout,
                             unsigned int rightForce, unsigned int rightTimeout)
    : Message(sizeof(ControllerAction) + sizeof(leftForce) +
              sizeof(leftTimeout) + sizeof(rightForce) + sizeof(rightTimeout)) {
  SetLeftForce(leftForce);
  SetLeftTimeout(leftTimeout);
  SetRightForce(rightForce);
  SetRightTimeout(rightTimeout);
  buffer[0] = (char)ControllerAction::Rumble;
}

unsigned int RumbleMessage::GetLeftForce() const {
  unsigned int leftForce;
  memcpy(&leftForce, buffer + leftForceOffset, sizeof(leftForce));
  return leftForce;
}

unsigned int RumbleMessage::GetLeftTimeout() const {
  unsigned int leftTimeout;
  memcpy(&leftTimeout, buffer + leftTimeoutOffset, sizeof(leftTimeout));
  return leftTimeout;
}

unsigned int RumbleMessage::GetRightForce() const {
  unsigned int rightForce;
  memcpy(&rightForce, buffer + rightForceOffset, sizeof(rightForce));
  return rightForce;
}

unsigned int RumbleMessage::GetRightTimeout() const {
  unsigned int rightTimeout;
  memcpy(&rightTimeout, buffer + rightTimeoutOffset, sizeof(rightTimeout));
  return rightTimeout;
}

void RumbleMessage::SetLeftForce(unsigned int leftForce) {
  memcpy(buffer + leftForceOffset, &leftForce, sizeof(leftForce));
}

void RumbleMessage::SetLeftTimeout(unsigned int leftTimeout) {
  memcpy(buffer + leftTimeoutOffset, &leftTimeout, sizeof(leftTimeout));
}

void RumbleMessage::SetRightForce(unsigned int rightForce) {
  memcpy(buffer + rightForceOffset, &rightForce, sizeof(rightForce));
}

void RumbleMessage::SetRightTimeout(unsigned int rightTimeout) {
  memcpy(buffer + rightTimeoutOffset, &rightTimeout, sizeof(rightTimeout));
}

SwitchLedMessage::SwitchLedMessage(bool isOn, unsigned int ledId)
    : Message(sizeof(ControllerAction) + sizeof(isOn) + sizeof(ledId)) {
  if (isOn)
    SetOn();
  else
    SetOff();
  SetLedId(ledId);
}

bool SwitchLedMessage::IsOn() const {
  bool isOn;
  memcpy(&isOn, buffer + isOnOffset, sizeof(isOn));
  return isOn;
}

unsigned int SwitchLedMessage::GetLedId() const {
  unsigned int ledId;
  memcpy(&ledId, buffer + ledIdOffset, sizeof(ledId));
  return ledId;
}

void SwitchLedMessage::SetOn() {
  bool isOn = true;
  memcpy(buffer + isOnOffset, &isOn, sizeof(isOn));
}

void SwitchLedMessage::SetOff() {
  bool isOn = false;
  memcpy(buffer + isOnOffset, &isOn, sizeof(isOn));
}

void SwitchLedMessage::SetLedId(unsigned int ledId) {
  memcpy(buffer + ledIdOffset, &ledId, sizeof(ledId));
}

FlashLedMessage::FlashLedMessage(unsigned int ledId, unsigned int onTime,
                                 unsigned int offTime)
    : Message(sizeof(ControllerAction) + sizeof(ledId) + sizeof(onTime) +
              sizeof(offTime)) {
  SetLedId(ledId);
  SetOnTime(onTime);
  SetOffTime(offTime);
}

unsigned int FlashLedMessage::GetLedId() const {
  unsigned int ledId;
  memcpy(&ledId, buffer + ledIdOffset, sizeof(ledId));
  return ledId;
}

unsigned int FlashLedMessage::GetOnTime() const {
  unsigned int onTime;
  memcpy(&onTime, buffer + onTimeOffset, sizeof(onTime));
  return onTime;
}

unsigned int FlashLedMessage::GetOffTime() const {
  unsigned int offTime;
  memcpy(&offTime, buffer + offTimeOffset, sizeof(offTime));
  return offTime;
}

void FlashLedMessage::SetLedId(unsigned int ledId) {
  memcpy(buffer + ledIdOffset, &ledId, sizeof(ledId));
}

void FlashLedMessage::SetOnTime(unsigned int onTime) {
  memcpy(buffer + onTimeOffset, &onTime, sizeof(onTime));
}

void FlashLedMessage::SetOffTime(unsigned int offTime) {
  memcpy(buffer + offTimeOffset, &offTime, sizeof(offTime));
}

} // end namespace sensor
} // end namespace flair
