// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/04/21
//  filename:   UdtSocket.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a UDT socket
//
//
/*********************************************************************/
#include "UdtSocket.h"
#include <udt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

using std::string;

namespace flair {
namespace core {

UdtSocket::UdtSocket(const Object *parent, const std::string name,
                     bool _blockOnSend, bool _blockOnReceive)
    : ConnectedSocket(parent, name) {
  UDT::startup();
  blockOnSend = _blockOnSend;
  blockOnReceive = _blockOnReceive;
}

UdtSocket::~UdtSocket() {}

void UdtSocket::Listen(const unsigned int port,
                       const std::string localAddress) {
  socket = UDT::socket(AF_INET, SOCK_DGRAM, 0);

  UDT::setsockopt(socket, 0, UDT_SNDSYN, &blockOnSend, sizeof(bool));
  UDT::setsockopt(socket, 0, UDT_RCVSYN, &blockOnReceive, sizeof(bool));
  bool reuse = true;
  UDT::setsockopt(socket, 0, UDT_REUSEADDR, &reuse, sizeof(bool));

  sockaddr_in my_addr;
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(port);
  if (localAddress == "ANY") {
    my_addr.sin_addr.s_addr = INADDR_ANY;
  } else {
    inet_aton(localAddress.c_str(), &(my_addr.sin_addr));
  }
  memset(&(my_addr.sin_zero), '\0', 8);

  if (UDT::ERROR == UDT::bind(socket, (sockaddr *)&my_addr, sizeof(my_addr))) {
    Err("bind, %s\n", UDT::getlasterror().getErrorMessage());
  }

  UDT::listen(socket, 1);
}

UdtSocket *UdtSocket::Accept(Time timeout) {
  // TIMEOUT UNSUPPORTED!!
  UdtSocket *acceptedSocket = new UdtSocket(this->Parent(), this->ObjectName());
  acceptedSocket->blockOnSend = this->blockOnSend;
  acceptedSocket->blockOnReceive = this->blockOnReceive;

  sockaddr_in their_addr;
  int namelen = sizeof(their_addr);

  if ((acceptedSocket->socket = UDT::accept(socket, (sockaddr *)&their_addr,
                                            &namelen)) == UDT::INVALID_SOCK) {
    Err("accept: %s, code %i\n", UDT::getlasterror().getErrorMessage(),
        UDT::getlasterror().getErrorCode());
  }

  return acceptedSocket;
}

bool UdtSocket::Connect(const unsigned int port,
                        const std::string distantAddress, Time timeout) {
  bool success = true;
  socket = UDT::socket(AF_INET, SOCK_DGRAM, 0);

  UDT::setsockopt(socket, 0, UDT_SNDSYN, &blockOnSend, sizeof(bool));
  UDT::setsockopt(socket, 0, UDT_RCVSYN, &blockOnReceive, sizeof(bool));
  bool reuse = true;
  UDT::setsockopt(socket, 0, UDT_REUSEADDR, &reuse, sizeof(bool));

  sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(short(port));
  if (inet_pton(AF_INET, distantAddress.c_str(), &serv_addr.sin_addr) <= 0) {
    printf("incorrect network address.");
    success = false;
  }
  memset(&(serv_addr.sin_zero), '\0', 8);

  if (UDT::ERROR ==
      UDT::connect(socket, (sockaddr *)&serv_addr, sizeof(serv_addr))) {
    success = false;
  }
  if (!success) {
    UDT::close(socket);
    return false;
  } else
    return true;
}

ssize_t UdtSocket::SendMessage(const char *buffer, size_t bufferSize,
                               Time timeout) {
  int udtTimeout = timeout;
  if (blockOnSend) {
    if (UDT::setsockopt(socket, 0, UDT_SNDTIMEO, &udtTimeout,
                        sizeof(udtTimeout)) != 0)
      Err("error UDT_SNDTIMEO %s\n", UDT::getlasterror().getErrorMessage());
  }
  ssize_t bytesSent = UDT::sendmsg(socket, buffer, bufferSize, -1, true);

  return bytesSent;
}

ssize_t UdtSocket::RecvMessage(char *buffer, size_t bufferSize, Time timeout) {
  int udtTimeout = timeout;
  if (blockOnReceive) {
    if (UDT::setsockopt(socket, 0, UDT_RCVTIMEO, &udtTimeout,
                        sizeof(udtTimeout)) != 0)
      Err("error UDT_RCVTIMEO %s\n", UDT::getlasterror().getErrorMessage());
  }
  ssize_t bytesRead = UDT::recvmsg(socket, buffer, bufferSize);

  /*
      if(bytesRead<0) {
          if(UDT::getlasterror().getErrorCode()==CUDTException::ECONNLOST) {
              connection_lost=true;
          }
      }
  */
  return bytesRead;
}

uint16_t UdtSocket::NetworkToHost16(uint16_t data) { return ntohs(data); }

uint16_t UdtSocket::HostToNetwork16(uint16_t data) { return htons(data); }

uint32_t UdtSocket::NetworkToHost32(uint32_t data) { return ntohl(data); }

uint32_t UdtSocket::HostToNetwork32(uint32_t data) { return htonl(data); }

} // end namespace core
} // end namespace flair
