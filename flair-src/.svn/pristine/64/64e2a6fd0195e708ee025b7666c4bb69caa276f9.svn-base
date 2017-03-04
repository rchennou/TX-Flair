// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ConnectedSocket.h
 * \brief Class defining a socket working in connected mode
 * \author Gildas Bayard, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2015/04/21
 * \version 4.0
 */

#ifndef CONNECTEDSOCKET_H
#define CONNECTEDSOCKET_H

#include <Object.h>

namespace flair {
namespace core {

/*! \class ConnectedSocket
*
* \brief Interface class encapsulating a connected socket. Preserves packets
*order and guaranty delivery.
*
*/
class ConnectedSocket : public Object {
public:
  /*!
  * \brief Constructor
  *
  */
  ConnectedSocket(const Object *parent, const std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~ConnectedSocket();

  /*!
  * \brief Returns a socket which listens on a specific port/address
  *
  * \param const Object* parentObject
  * \param const string name
  * \param unsigned int port
  * \param const localAddress (defaults to any)
  */
  virtual void Listen(const unsigned int port,
                      const std::string localAddress = "ANY") = 0;

  /*!
  * \brief Returns a socket on a new incoming connexion
  *
  * \param ConnectedSocket &listeningSocket
  */
  virtual ConnectedSocket *Accept(
      Time timeout) = 0; // should throw an exception if not a listening socket

  /*!
  * \brief Returns a socket connected to a distant host
  *
  * \param const Object* parentObject
  * \param const string name
  * \param unsigned int port
  * \param const distantAddress
  * \param timeout timeout (in milliseconds)
  */
  virtual bool Connect(const unsigned int port,
                       const std::string distantAddress, Time timeout) = 0;

  /*!
  * \brief Send a message
  *
  * \param message message
  * \param message_len message length
  * \param timeout timeout (in milliseconds)
  */
  virtual ssize_t SendMessage(const char *message, size_t message_len,
                              Time timeout) = 0;

  /*!
  * \brief Receive a message
  *
  * Receive a message and wait up to timeout. \n
  *
  * \param buf buffer to put the message
  * \param buf_len buffer length
  * \param timeout timeout (in milliseconds)
  *
  * \return size of the received message
  */
  virtual ssize_t RecvMessage(char *buf, size_t buf_len, Time timeout) = 0;

  std::string ReadString(const size_t &stringLength, Time timeout);
  uint16_t ReadUInt16(Time const &timeout);
  void WriteUInt16(uint16_t const &data, Time const &timeout);
  uint32_t ReadUInt32(Time const &timeout);
  void WriteUInt32(uint32_t const &data, Time const &timeout);

  //!! See Socket.h for a more generic implementation of network/host endianness
  // conversion
  virtual uint16_t NetworkToHost16(uint16_t data) = 0;
  virtual uint16_t HostToNetwork16(uint16_t data) = 0;
  virtual uint32_t NetworkToHost32(uint32_t data) = 0;
  virtual uint32_t HostToNetwork32(uint32_t data) = 0;
};

} // end namespace core
} // end namespace flair

#endif // CONNECTEDSOCKET_H
