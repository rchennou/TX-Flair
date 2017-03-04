// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/11/17
//  filename:   Socket.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a UDP socket
//
//
/*********************************************************************/
#include "Socket.h"
#include "Socket_impl.h"
#include <FrameworkManager.h>
#include <string.h>
#include <stdexcept>

using std::string;

namespace flair {
namespace core {

Socket::Socket(const Object *parent, string name, uint16_t port)
    : Object(parent, name) {
  pimpl_ = new Socket_impl(this, name, port);
}

Socket::Socket(const Object *parent, string name, string address,
               bool broadcast)
    : Object(parent, name) {
  pimpl_ = new Socket_impl(this, name, address, broadcast);
}

Socket::~Socket() { delete pimpl_; }

void Socket::SendMessage(const char *message, size_t message_len) {
  pimpl_->SendMessage(message, message_len);
}

void Socket::SendMessage(string message) { pimpl_->SendMessage(message); }

ssize_t Socket::RecvMessage(char *buf, size_t buf_len, Time timeout, char *src,
                            size_t *src_len) {
  return pimpl_->RecvMessage(buf, buf_len, timeout, src, src_len);
}

void Socket::NetworkToHost(char *data, size_t dataSize) {
  if (core::IsBigEndian())
    return;
  if (dataSize == 1)
    return;
  if ((dataSize == 2) || (dataSize == 4) || (dataSize == 8) ||
      (dataSize == 16)) {
    char dataInHostEndianness[dataSize];
    for (unsigned int i = 0; i < dataSize; i++) {
      dataInHostEndianness[i] = data[dataSize - i - 1];
    }
    memcpy(data, dataInHostEndianness, dataSize);
    return;
  }
  throw std::runtime_error(
      string("Unsupported data size (") + std::to_string(dataSize) +
      string(") in host to network endianness conversion"));
}

void Socket::HostToNetwork(char *data, size_t dataSize) {
  if (IsBigEndian())
    return;
  if (dataSize == 1)
    return;
  if ((dataSize == 2) || (dataSize == 4) || (dataSize == 8) ||
      (dataSize == 16)) {
    char dataInNetworkEndianness[dataSize];
    for (unsigned int i = 0; i < dataSize; i++) {
      dataInNetworkEndianness[i] = data[dataSize - i - 1];
    }
    memcpy(data, dataInNetworkEndianness, dataSize);
    return;
  }
  throw std::runtime_error(
      string("Unsupported data size (") + std::to_string(dataSize) +
      string(") in host to network endianness conversion"));
}

} // end namespace core
} // end namespace flair
