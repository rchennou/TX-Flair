// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/03/30
//  filename:   TargetEthController.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class that gets remote controls through an ethernet connection.
//              Typical use case: a remote control is plugged in a workstation
//              and sends remote control
//              data to a distant target (this class) through Wifi//
//
/*********************************************************************/
#include "TargetEthController.h"
#include <Controller.h>
#include <FrameworkManager.h>
#include <TcpSocket.h>
#include <Socket.h>
#include <cstring>
#include <string>
#include <cvmatrix.h>
#include <stdexcept>

#include <unistd.h> // for sleep (debug)

using namespace flair::core;
using namespace flair::gui;
using std::string;

namespace flair {
namespace sensor {

TargetEthController::TargetEthController(const FrameworkManager *parent,
                                         string name, uint16_t _port,
                                         uint8_t priority)
    : TargetController(parent, name, priority), listeningPort(_port),
      receiveCurrentPosition(0) {
  const bool blocking = true;
  listeningSocket =
      new TcpSocket(parent, "TEC_listening_socket", blocking, blocking);
  dataSocket =
      new Socket(parent, "TEC_data_socket", _port + 1); // receiving side
}

TargetEthController::~TargetEthController() {
  // We are (currently) the server side. We must ask the client side to initiate
  // tcp connexion closing to avoid the server socket
  // to get stuck in TIME_WAIT state
  Message msg(32);
  if (controlSocket) {
    Message cancelAcquisition(sizeof(ControllerAction));
    ControllerAction exit = ControllerAction::Exit;
    memcpy(cancelAcquisition.buffer, &exit, sizeof(ControllerAction));
    controlSocket->SendMessage(cancelAcquisition.buffer,
                               cancelAcquisition.bufferSize);
    // We don't expect any more data from the client, we're just waiting for the
    // socket to be closed by the client
    controlSocket->RecvMessage(msg.buffer, msg.bufferSize);
  }

  // TargetController calls TargetEthController methods in its run
  // we must stop the thread now
  SafeStop();
  Join();
}

bool TargetEthController::IsConnected() const {
  // TODO
}

bool TargetEthController::IsDataFrameReady() {
  // read up to the last data
  ssize_t received;
  size_t bytesToReceive = dataFrameSize - receiveCurrentPosition;
  bool fullDatagramReceived = false;

    do {
        received=dataSocket->RecvMessage(receiveFrameBuffer+receiveCurrentPosition,bytesToReceive,TIME_NONBLOCK);
        if (received>0) {
            receiveCurrentPosition+=received;
            bytesToReceive-=received;
            if (bytesToReceive==0) {
                //a full datagram has been read in receiveFrameBuffer
                fullDatagramReceived=true;
                //we swap the data and reception buffers to avoid copy
                char *swapFrameBuffer=dataFrameBuffer;
                dataFrameBuffer=receiveFrameBuffer;
                receiveFrameBuffer=swapFrameBuffer;
                receiveCurrentPosition=0;
                bytesToReceive=dataFrameSize;
            }
        }
    } while (!(received<0));

  return fullDatagramReceived;
}

uint8_t TargetEthController::getByteOrNull(char *buffer, int byte,
                                           size_t bufferSize) {
  if (byte < bufferSize)
    return buffer[byte];
  else
    return 0;
}

uint32_t TargetEthController::charBufferToUint32(char *buffer,
                                                 size_t bufferSize) {
  union {
    uint32_t int32;
    char byte[4];
  } bitField;
  if (!IsBigEndian()) {
    bitField.byte[0] = getByteOrNull(buffer, 3, bufferSize);
    bitField.byte[1] = getByteOrNull(buffer, 2, bufferSize);
    bitField.byte[2] = getByteOrNull(buffer, 1, bufferSize);
    bitField.byte[3] = getByteOrNull(buffer, 0, bufferSize);
  } else {
    bitField.byte[0] = getByteOrNull(buffer, 0, bufferSize);
    bitField.byte[1] = getByteOrNull(buffer, 1, bufferSize);
    bitField.byte[2] = getByteOrNull(buffer, 2, bufferSize);
    bitField.byte[3] = getByteOrNull(buffer, 3, bufferSize);
  }
  return bitField.int32;
}

// read _up_to_16_bits_ in a buffer
uint16_t TargetEthController::readBits(uint8_t offsetInBits,
                                       uint8_t valueSizeInBits, char *buffer,
                                       size_t bufferSize) {
  // parameters check
  if (valueSizeInBits > 16)
    throw std::range_error("bitfield should be at max 16bits wide");
  size_t minBufferSize = (offsetInBits + valueSizeInBits) / 8;
  if ((offsetInBits + valueSizeInBits) % 8 != 0)
    minBufferSize++;
  if (bufferSize < minBufferSize)
    throw std::range_error("buffer too small");
  // skip first bytes
  size_t bytesToSkip = offsetInBits / 8;
  buffer += bytesToSkip;
  bufferSize -= bytesToSkip;
  offsetInBits -= bytesToSkip * 8;
  // take care of endianness
  uint32_t value = charBufferToUint32(buffer, bufferSize);
  value >>= 32 - offsetInBits - valueSizeInBits;
  value &= (1 << valueSizeInBits) - 1;
  return (uint16_t)value;
}

void TargetEthController::AcquireAxisData(core::cvmatrix &axis) {
  axis.GetMutex();
  // char testFrameBuffer[3]={(char)0x09,(char)0x59,(char)0xB8};
  for (unsigned int i = 0; i < axisNumber; i++) {
    uint16_t rawAxisValue =
        readBits(i * bitsPerAxis, bitsPerAxis, dataFrameBuffer, dataFrameSize);
    //        uint16_t
    //        rawAxisValue=readBits(i*bitsPerAxis,bitsPerAxis,testFrameBuffer);
    uint16_t scale = 1 << (bitsPerAxis - 1);
    // Thread::Info("RawAxisValue=%d, scale=%d => scaled rawValue=%d, float
    // value)%f\n",rawAxisValue,scale,rawAxisValue-scale,(rawAxisValue-scale)/(float)scale);
    axis.SetValueNoMutex(i, 0, (rawAxisValue - scale) / (float)scale);
  }
  axis.ReleaseMutex();
}

void TargetEthController::AcquireButtonData(core::cvmatrix &button) {
  uint8_t buttonValue;
  int currentButton = 0;
  button.GetMutex();
  /*
  for (unsigned int i=0;i<buttonNumber;i++) {
      memcpy(&buttonValue,buttonOffset+i*sizeof(bool),sizeof(bool));
      dataSocket->NetworkToHost((char*)&buttonValue,sizeof(bool));
      button.SetValueNoMutex(i,0,buttonValue);
//        if (buttonValue) Thread::Info("Debug: button '%s' pressed\n",
GetButtonName(i).c_str());
  }*/
  for (unsigned int i = 0; i < buttonNumber / 8; i++) {
    memcpy(&buttonValue, dataFrameBuffer + buttonOffset + i * sizeof(uint8_t),
           sizeof(uint8_t));
    //        dataSocket->NetworkToHost((char*)&buttonValue,sizeof(uint8_t));
    for (unsigned int j = 0; j < 8; j++) {
      button.SetValueNoMutex(currentButton, 0, (buttonValue >> j) & 0x01);
      currentButton++;
    }
  }
  button.ReleaseMutex();
}

string TargetEthController::GetAxisName(unsigned int axisId) const {
  // TODO: should throw an exception if axisName==NULL or axisId>axisNumber
  return axisName[axisId];
}

string TargetEthController::GetButtonName(unsigned int buttonId) const {
  // TODO: should throw an exception if buttonName==NULL or
  // buttonId>buttonNumber
  return buttonName[buttonId];
}

bool TargetEthController::ProcessMessage(Message *msg) {
  return !(controlSocket->SendMessage(msg->buffer, msg->bufferSize, 0) < 0);
}

bool TargetEthController::IsControllerActionSupported(
    ControllerAction action) const {
  // TODO: here we should ask the remote side (host). Probably through the
  // control socket
  switch (action) {
  case ControllerAction::SetLedOn:
    return true;
  case ControllerAction::SetLedOff:
    return true;
  case ControllerAction::Rumble:
    return true;
  case ControllerAction::FlashLed:
    return true;
  default:
    return false;
  }
}

bool TargetEthController::ControllerInitialization() {
  char message[1024];
  ssize_t received;
  bool connected = false;
  bool mustReadMore;

  listeningSocket->Listen(listeningPort);
  Thread::Info("Debug: Listening to port %d\n", listeningPort);
  // accept incoming connection
  bool connectionAccepted = false;
  while (!connectionAccepted) {
    controlSocket = listeningSocket->Accept(10);
    if (controlSocket == nullptr) {
      // Timeout (or error btw)
      if (ToBeStopped())
        return false;
    } else
      connectionAccepted = true;
  }
  Thread::Info("Debug: Connexion accepted\n");

  // get axis stuff
  bool axisNumberRead = false;
  while (!axisNumberRead) {
    try {
      axisNumber = controlSocket->ReadUInt32(10);
      // Thread::Info("Debug: axisNumber %d\n", axisNumber);
      axisNumberRead = true;
    } catch (std::runtime_error e) {
      // timeout
      if (ToBeStopped())
        return false;
    }
  }
  bool bitsPerAxisRead = false;
  while (!bitsPerAxisRead) {
    try {
      bitsPerAxis = controlSocket->ReadUInt32(10);
      // Thread::Info("Debug: bits per axis %d\n", bitsPerAxis);
      bitsPerAxisRead = true;
    } catch (std::runtime_error e) {
      // timeout
      if (ToBeStopped())
        return false;
    }
  }
  axisName = new string[axisNumber];
  for (unsigned int i = 0; i < axisNumber; i++) {
    // read string size
    int stringSize;
    bool stringSizeRead = false;
    while (!stringSizeRead) {
      try {
        stringSize = controlSocket->ReadUInt32(10);
        stringSizeRead = true;
      } catch (std::runtime_error e) {
        // timeout
        if (ToBeStopped())
          return false;
      }
    }
    // read string
    bool axisNameRead = false;
    while (!axisNameRead) {
      try {
        axisName[i] = controlSocket->ReadString(stringSize, 10);
        axisNameRead = true;
      } catch (std::runtime_error e) {
        // timeout
        if (ToBeStopped())
          return false;
      }
    }
    // Thread::Info("Debug: axisName for axis %d %s\n", i, axisName[i].c_str());
  }

  // get button stuff
  bool buttonNumberRead = false;
  while (!buttonNumberRead) {
    try {
      buttonNumber = controlSocket->ReadUInt32(10);
      buttonNumberRead = true;
    } catch (std::runtime_error e) {
      // timeout
      if (ToBeStopped())
        return false;
    }
  }
  // Thread::Info("Debug: buttonNumber %d\n", buttonNumber);
  buttonName = new string[buttonNumber];
  for (unsigned int i = 0; i < buttonNumber; i++) {
    // read string size
    int stringSize;
    bool stringSizeRead = false;
    while (!stringSizeRead) {
      try {
        stringSize = controlSocket->ReadUInt32(10);
        stringSizeRead = true;
      } catch (std::runtime_error e) {
        // timeout
        if (ToBeStopped())
          return false;
      }
    }
    // read string
    bool buttonNameRead = false;
    while (!buttonNameRead) {
      try {
        buttonName[i] = controlSocket->ReadString(stringSize, 10);
        buttonNameRead = true;
      } catch (std::runtime_error e) {
        // timeout
        if (ToBeStopped())
          return false;
      }
    }
    // Thread::Info("Debug: buttonName for button %d %s\n", i,
    // buttonName[i].c_str());
  }

  //    dataFrameSize=axisNumber*sizeof(float)+buttonNumber/8*sizeof(uint8_t);
  buttonOffset = (axisNumber * bitsPerAxis) / 8;
  if ((axisNumber * bitsPerAxis) % 8 != 0)
    buttonOffset++;
  dataFrameSize = buttonOffset + (buttonNumber / 8) * sizeof(uint8_t);
  if ((buttonNumber % 8) != 0)
    dataFrameSize++;
  dataFrameBuffer = new char[dataFrameSize];
  receiveFrameBuffer = new char[dataFrameSize];

  Thread::Info("Controller connected with host side\n");
  if (buttonNumber % 8 != 0)
    Thread::Err("Button number is not multiple of 8\n");
  return true;
}

} // end namespace sensor
} // end namespace flair
