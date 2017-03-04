// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Socket.h
 * \brief Class defining a UDP socket
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/11/17
 * \version 4.0
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <unistd.h>
#include <stdint.h>
#include <Object.h>

class Socket_impl;

namespace flair {
namespace core {

/*! \class Socket
*
* \brief Class encapsulating a UDP socket. It assumes packets are coming from
*only one distant host on a given port.
*
*/
class Socket : public Object {
public:
  /*!
  * \brief Constructor
  *
  * Construct the client side of the socket
  *
  * \param parent parent
  * \param name name
  * \param address server address (ex 192.168.1.1:9000)
  * \param broadcast true if address is a broadcast address
  */
  Socket(const Object *parent, std::string name, std::string address,
         bool broadcast = false);

  /*!
  * \brief Constructor
  *
  * Construct the server side of the socket
  *
  * \param parent parent
  * \param name name
  * \param port listening port
  */
  Socket(const Object *parent, std::string name, uint16_t port);

  /*!
  * \brief Destructor
  *
  */
  ~Socket();

  /*!
  * \brief Send a message
  *
  * In case of a broadcast Socket, Parent()->ObjectName() is used as source of
  *the message, this name should be unique.
  *
  * \param message message
  */
  void SendMessage(std::string message);

  /*!
  * \brief Send a message
  *
  * \param message message
  * \param message_len message length
  */
  void SendMessage(const char *message, size_t message_len);

  /*!
  * \brief Receive a message
  *
  * Receive a message and wait up to timeout. \n
  * If src and src_len are specified, the source of the message will be
  * copied in the src buffer. \n
  * Note that in case of a broadcast socket, own messages are filtered and
  * are not received.
  *
  * \param buf buffer to put the message
  * \param buf_len buffer length
  * \param timeout timeout
  * \param src buffer to put source name
  * \param src_len buffer length
  *
  * \return size of the received message
  */
  ssize_t RecvMessage(char *buf, size_t buf_len, Time timeout, char *src = NULL,
                      size_t *src_len = NULL);

  void NetworkToHost(char *data, size_t dataSize);
  void HostToNetwork(char *data, size_t dataSize);

private:
  class Socket_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // SOCKET_H
