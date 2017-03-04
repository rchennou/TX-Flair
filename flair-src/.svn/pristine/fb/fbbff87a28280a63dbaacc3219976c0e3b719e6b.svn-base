// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/03/30
//  filename:   HostEthController.cpp
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
#include "HostEthController.h"
#include <Controller.h>
#include <cvmatrix.h>
#include <Tab.h>
#include <TabWidget.h>
#include <Label.h>
#include <DataPlot1D.h>
#include <FrameworkManager.h>
#include <TargetController.h>
#include <TcpSocket.h>
#include <Socket.h>
#include <cstring>
#include <string>
#include <cmath> //for sqrt
#include <sched.h>

#include <iostream>

using namespace flair::core;
using namespace flair::gui;
using std::string;

namespace flair {
namespace sensor {

HostEthController::HostEthController(const FrameworkManager *parent,
                                     string name, string _address, int _port,
                                     uint32_t period, uint32_t _bitsPerAxis,
                                     uint8_t priority)
    : Thread(parent, name, priority), IODevice(parent, name),
      tab(new Tab(parent->GetTabWidget(), name)), axisNumber(0),
      buttonNumber(0), targetAddress(_address), targetPort(_port),
      bitsPerAxis(_bitsPerAxis), dataFrameBuffer(NULL),
      meaningfulDataAvailable(false) {
  tabWidget = new TabWidget(tab->NewRow(), name);

  const bool blocking = true;
  controlSocket = new TcpSocket((Thread *)this, "eth controller control socket",
                                blocking, !blocking);
  dataSocket = new Socket((Thread *)this, "eth controller data socket",
                          _address + ":" + std::to_string(_port + 1));
  dataSender =
      new DataSender((Thread *)this, this, "eth controller data sender thread");
  dataSender->SetPeriodMS(period);
  dataSender->Start();

  // test binary
  /*
  uint16_t testValue=0b0111011010; //0x1DA
  char buffer[3]={(char)0b10101011, (char)0b01100101, (char)0b10110110}; //
  0xAB65B6
  writeBits(testValue,10,buffer,7); // 0b1010101 0 11101101 0 0110110 0xAAED36
  Thread::Info("Debug: buffer after bits written=%X %X\n",buffer[0],buffer[1]);
  */
  connectionEstablishedMutex = new Mutex((Thread *)this);
}

HostEthController::~HostEthController() {
  SafeStop();
  Join();

  if (!getFrameworkManager()->ConnectionLost())
    delete tab;
}

void HostEthController::DrawUserInterface() {
  Tab *plotTab = new Tab(tabWidget, "Measures");
  axisPlot = new DataPlot1D *[axisNumber];
  for (unsigned int i = 0; i < axisNumber; i++) {
    // Start a new row or add up to the current row? We try to keep a 4/3 ratio
    unsigned int columns = sqrt(4.0 * axisNumber / 3.0);
    LayoutPosition *position;
    if (i % columns == 0) {
      position = plotTab->NewRow();
    } else {
      position = plotTab->LastRowLastCol();
    }
    axisPlot[i] = new DataPlot1D(position, axis->Name(i, 0),
                                 -(1 << (nativeBitsPerAxis - 1)) * 1.2,
                                 (1 << (nativeBitsPerAxis - 1)) * 1.5);
    axisPlot[i]->AddCurve(axis->Element(i));
  }
  // we don't plot the button state for now
}

string HostEthController::GetAxisDescription(unsigned int axis) {
  return string("axis") + std::to_string(axis);
}

string HostEthController::GetButtonDescription(unsigned int button) {
  return string("button") + std::to_string(button);
}

bool HostEthController::ControllerInitialization() {

  buttonOffset = (axisNumber * bitsPerAxis) / 8;
  if ((axisNumber * bitsPerAxis) % 8 != 0)
    buttonOffset++;
  dataFrameSize = buttonOffset + (buttonNumber / 8) * sizeof(uint8_t);
  if ((buttonNumber % 8) != 0)
    dataFrameSize++;
  dataFrameBuffer = new char[dataFrameSize];
  return true;
}

void HostEthController::SendControllerInfo() {
  // send axis info
  controlSocket->WriteUInt32((uint32_t)axisNumber, 0);
  controlSocket->WriteUInt32(bitsPerAxis, 0);
  for (unsigned int i = 0; i < axisNumber; i++) {
    // Thread::Info("Debug: sending axis name for axis %d = %s (takes up %d
    // bytes)\n",i,GetAxisDescription(i).c_str(),GetAxisDescription(i).length());
    int stringLength = GetAxisDescription(i).length();
    controlSocket->WriteUInt32((uint32_t)stringLength, 0);
    controlSocket->SendMessage(GetAxisDescription(i).c_str(), stringLength, 0);
  }

  // send button info
  controlSocket->WriteUInt32((uint32_t)buttonNumber, 0);
  for (unsigned int i = 0; i < buttonNumber; i++) {
    int stringLength = GetButtonDescription(i).length();
    controlSocket->WriteUInt32((uint32_t)stringLength, 0);
    controlSocket->SendMessage(GetButtonDescription(i).c_str(), stringLength,
                               0);
  }
}

bool HostEthController::ConnectedWithTarget() {
  char message[1024];
  ssize_t sent, received;
  static bool connectionEstablished = false;

  connectionEstablishedMutex->GetMutex();
  if (!connectionEstablished &&
      controlSocket->Connect(targetPort, targetAddress, 10)) {
    Thread::Info("Connected to %s:%d\n", targetAddress.c_str(), targetPort);
    SendControllerInfo();
    connectionEstablished = true;
  }
  connectionEstablishedMutex->ReleaseMutex();
  return connectionEstablished;
}

void HostEthController::Run() {
  static int divider = 0;
  Message *msgControllerAction = new Message(1024);
  if (getFrameworkManager()->ErrorOccured() || !ControllerInitialization()) {
    SafeStop();
    Thread::Err("Une erreur a eu lieu, on ne lance pas la boucle\n");
  }

  if (buttonNumber % 8 != 0) {
    SafeStop();
    Thread::Err("Button number is not multiple of 8\n");
  }

  while (!ToBeStopped()) {
    // Thread::Info("Debug: entering acquisition loop\n");
    if (getFrameworkManager()->ConnectionLost() == true)
      SafeStop();

    if (IsDataFrameReady()) { // wait for next data frame
      meaningfulDataAvailable = true;
      GetAxisData();
      GetButtonData();

      if (ConnectedWithTarget()) {
        // read for commands from the target (remote control state change
        // requests such as rumble or led on/off)
        ssize_t bytesReceived =
            controlSocket->RecvMessage((char *)msgControllerAction->buffer,
                                       msgControllerAction->bufferSize);
        if (bytesReceived > 0) {
          // if the message is a cnx exit request we manage it here, if not it
          // will be managed by the derived class
          ControllerAction action;
          memcpy(&action, msgControllerAction->buffer,
                 sizeof(ControllerAction));
          if (action == ControllerAction::Exit) {
            // Thread::Info("Debug: exit request received from server\n");
            SafeStop();
          }
          ProcessMessage(msgControllerAction);
        }
      }
    } else { // try to connect even if host is not sending anything
      ConnectedWithTarget();
    }
    // Thread::Info("Debug: exiting acquisition loop\n");
  }
}

bool HostEthController::writeBits(uint16_t value, uint8_t valueSizeInBits,
                                  char *buffer, uint8_t offsetInBits) {
  if (valueSizeInBits > 16)
    return false;
  uint8_t remainingBitsToWrite = valueSizeInBits;
  // skip first bytes
  buffer += offsetInBits / 8;
  offsetInBits -= (offsetInBits / 8) * 8;
  while (remainingBitsToWrite > 0) {
    uint8_t remainingBitsInByteBeforeWrite = 8 - offsetInBits;
    uint8_t bitsToWrite = remainingBitsToWrite < remainingBitsInByteBeforeWrite
                              ? remainingBitsToWrite
                              : remainingBitsInByteBeforeWrite;
    uint8_t remainingBitsInByteAfterWrite =
        remainingBitsInByteBeforeWrite - bitsToWrite;
    // write in the current byte
    uint8_t byteMask = ((1 << bitsToWrite) - 1)
                       << remainingBitsInByteAfterWrite;
    (*buffer) &= ~byteMask;
    uint16_t valueMask = (1 << remainingBitsToWrite) - 1;
    (*buffer) |= ((value & valueMask) >> (remainingBitsToWrite - bitsToWrite))
                 << remainingBitsInByteAfterWrite;
    // update state
    remainingBitsToWrite -= bitsToWrite;
    offsetInBits = (offsetInBits + bitsToWrite) % 8;
    buffer++;
  }
  return true;
}

void HostEthController::BuildDataFrame() {
  // int16_t testValue[4]={-120,-43,27,98}; //0x 88 d5 1b 62
  for (unsigned int i = 0; i < axisNumber; i++) {
    // We shift value to always be positive (so that division/multiplication by
    // power of 2 can easily be done with bit shifts)
    uint16_t shiftedNativeAxisValue =
        axis->Value(i, 0) + (1 << (nativeBitsPerAxis - 1));
    // int16_t nativeAxisValue=testValue[i];
    uint16_t scaledAxisValue;
    if (bitsPerAxis > nativeBitsPerAxis) {
      scaledAxisValue = shiftedNativeAxisValue
                        << (bitsPerAxis - nativeBitsPerAxis);
    } else {
      scaledAxisValue =
          shiftedNativeAxisValue >> (nativeBitsPerAxis - bitsPerAxis);
    }
    // Thread::Info("Debug: shiftedNativeAxisValue=%#x, scaled axis
    // value=%#x\n",shiftedNativeAxisValue,scaledAxisValue);
    unsigned int offsetInBits = i * bitsPerAxis;
    writeBits(scaledAxisValue, bitsPerAxis, dataFrameBuffer, offsetInBits);
  }
  // Thread::Info("Buffer après: %x %x %x\n", dataFrameBuffer[0],
  // dataFrameBuffer[1], dataFrameBuffer[2]);

  int currentButton = 0;
  uint8_t buttonArray[buttonNumber / 8];
  for (unsigned int i = 0; i < buttonNumber / 8; i++) {
    buttonArray[i] = 0;
    for (unsigned int j = 0; j < 8; j++) {
      bool buttonValue = button->Value(currentButton, 0);
      if (buttonValue)
        buttonArray[i] += 1 << j;
      currentButton++;
    }

    dataSocket->HostToNetwork((char *)&buttonArray[i], sizeof(uint8_t));
    memcpy(dataFrameBuffer + buttonOffset + i * sizeof(uint8_t),
           &buttonArray[i], sizeof(uint8_t));
  }
}

HostEthController::DataSender::DataSender(Object *parent,
                                          HostEthController *_hostEthController,
                                          string name, uint8_t priority)
    : Thread(parent, name, priority), hostEthController(_hostEthController) {}

void HostEthController::DataSender::Run() {
  if (getFrameworkManager()->ErrorOccured() == true) {
    SafeStop();
  }

  while (!ToBeStopped()) {
    WaitPeriod();
    if (hostEthController->meaningfulDataAvailable &&
        hostEthController->ConnectedWithTarget()) {
      // send the data
      hostEthController->BuildDataFrame();
      hostEthController->dataSocket->SendMessage(
          hostEthController->dataFrameBuffer, hostEthController->dataFrameSize);
    }
  }
}

} // end namespace sensor
} // end namespace flair
