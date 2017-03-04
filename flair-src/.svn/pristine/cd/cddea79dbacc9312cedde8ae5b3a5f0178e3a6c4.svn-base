// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/04/21
//  filename:   ConnectedSocket.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a connected socket
//
//
/*********************************************************************/
#include "ConnectedSocket.h"
#include <string.h>
#include <stdexcept>

using std::string;

namespace flair {
namespace core {

ConnectedSocket::ConnectedSocket(const Object *parent, const std::string name)
    : Object(parent, name){};

ConnectedSocket::~ConnectedSocket(){};

uint16_t ConnectedSocket::ReadUInt16(Time const &timeout) {
  char buffer[sizeof(uint16_t)];
  size_t alreadyReceived = 0;
  Time remainingTimeout = timeout; // ms
  do {
    Time beforeTime = GetTime(); // ns
    ssize_t received =
        RecvMessage(buffer + alreadyReceived,
                    sizeof(uint16_t) - alreadyReceived, remainingTimeout);
    remainingTimeout -= (GetTime() - beforeTime) / 100000;
    if ((received < 0) || (remainingTimeout < 0))
      throw std::runtime_error("Timeout");
    alreadyReceived += received;
  } while (alreadyReceived != sizeof(uint16_t));
  uint16_t *dataInNetworkEndianness = (uint16_t *)buffer;
  uint16_t myinteger = NetworkToHost16(*dataInNetworkEndianness);
  return myinteger;
}

void ConnectedSocket::WriteUInt16(uint16_t const &data, Time const &timeout) {
  uint16_t dataInNetworkEndianness = HostToNetwork16(data);
  char *buffer = (char *)&dataInNetworkEndianness;
  size_t alreadySent = 0;
  Time remainingTimeout = timeout; // ms
  do {
    Time beforeTime = GetTime(); // ns
    ssize_t sent = SendMessage(
        buffer + alreadySent, sizeof(uint16_t) - alreadySent, remainingTimeout);
    remainingTimeout -= (GetTime() - beforeTime) / 100000;
    if ((sent < 0) || (remainingTimeout < 0))
      throw std::runtime_error("Timeout");
    alreadySent += sent;
  } while (alreadySent != sizeof(uint16_t));
}

uint32_t ConnectedSocket::ReadUInt32(Time const &timeout) {
  char buffer[sizeof(uint32_t)];
  size_t alreadyReceived = 0;
  Time remainingTimeout = timeout; // ms
  do {
    Time beforeTime = GetTime(); // ns
    ssize_t received =
        RecvMessage(buffer + alreadyReceived,
                    sizeof(uint32_t) - alreadyReceived, remainingTimeout);
    remainingTimeout -= (GetTime() - beforeTime) / 100000;
    if ((received < 0) || (remainingTimeout < 0))
      throw std::runtime_error("Timeout");
    alreadyReceived += received;
  } while (alreadyReceived != sizeof(uint32_t));
  uint32_t *dataInNetworkEndianness = (uint32_t *)buffer;
  uint32_t myinteger = NetworkToHost32(*dataInNetworkEndianness);
  return myinteger;
}

void ConnectedSocket::WriteUInt32(uint32_t const &data, Time const &timeout) {
  uint32_t dataInNetworkEndianness = HostToNetwork32(data);
  char *buffer = (char *)&dataInNetworkEndianness;
  size_t alreadySent = 0;
  Time remainingTimeout = timeout; // ms
  do {
    Time beforeTime = GetTime(); // ns
    ssize_t sent = SendMessage(
        buffer + alreadySent, sizeof(uint32_t) - alreadySent, remainingTimeout);
    remainingTimeout -= (GetTime() - beforeTime) / 100000;
    if ((sent < 0) || (remainingTimeout < 0))
      throw std::runtime_error("Timeout");
    alreadySent += sent;
  } while (alreadySent != sizeof(uint32_t));
}

string ConnectedSocket::ReadString(const size_t &stringSize, Time timeout) {
  char buffer[stringSize + 1];
  size_t alreadyReceived = 0;
  Time remainingTimeout = timeout; // ms
  do {
    Time beforeTime = GetTime(); // ns
    ssize_t received =
        RecvMessage(buffer + alreadyReceived, stringSize - alreadyReceived,
                    remainingTimeout);
    remainingTimeout -= (GetTime() - beforeTime) / 100000;
    if ((received < 0) || (remainingTimeout < 0))
      throw std::runtime_error("Timeout");
    alreadyReceived += received;
  } while (alreadyReceived != stringSize);
  buffer[stringSize] = '\0';

  string mystring = buffer;
  return mystring;
}

} // end namespace core
} // end namespace flair
