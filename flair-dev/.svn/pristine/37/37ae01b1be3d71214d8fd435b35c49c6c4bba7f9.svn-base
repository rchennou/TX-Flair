// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file UdtSocket.h
 * \brief Class defining a UDT socket
 * \author Gildas Bayard, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2015/04/21
 * \version 4.0
 */

#ifndef UDTSOCKET_H
#define UDTSOCKET_H

typedef int UDTSOCKET;

#include <ConnectedSocket.h>

namespace flair {
namespace core {
/*! \class UdtSocket
*
* \brief Class encapsulating a UDT socket
*
*/
class UdtSocket : public ConnectedSocket {
public:
  UdtSocket(const Object *parent, const std::string name,
            bool blockOnSend = false, bool blockOnReceive = true);
  ~UdtSocket();
  void Listen(const unsigned int port, const std::string localAddress = "ANY");
  UdtSocket *
  Accept(Time timeout); // should throw an exception if not a listening socket
  bool Connect(const unsigned int port, const std::string distantAddress,
               Time timeout); // /!\ timeout is ignored
  ssize_t SendMessage(const char *message, size_t message_len, Time timeout);
  ssize_t RecvMessage(char *buf, size_t buf_len, Time timeout);

  uint16_t NetworkToHost16(uint16_t data);
  uint16_t HostToNetwork16(uint16_t data);
  uint32_t NetworkToHost32(uint32_t data);
  uint32_t HostToNetwork32(uint32_t data);

private:
  UDTSOCKET socket;
  bool blockOnSend;
  bool blockOnReceive;
};

} // end namespace core
} // end namespace flair

#endif // UDTSOCKET_H
