// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Unix_I2cPort.h
 * \brief Class for unix i2c port
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/08/28
 * \version 4.0
 */

#ifndef UNIX_I2CPORT_H
#define UNIX_I2CPORT_H

#include <I2cPort.h>

namespace flair {
namespace core {
/*! \class Unix_I2cPort
*
* \brief Class for unix serial port
*
*/
class Unix_I2cPort : public I2cPort {

public:
  /*!
  * \brief Constructor
  *
  * Construct an unix i2c port
  *
  * \param parent parent
  * \param name name
  * \param device serial device (ex /dev/i2c-1)
  */
  Unix_I2cPort(const Object *parent, std::string port_name, std::string device);

  /*!
  * \brief Destructor
  *
  */
  ~Unix_I2cPort();

  /*!
  * \brief Set slave's address
  *
  * This method need to be called before any communication.
  *
  * \param address slave's address
  */
  int SetSlave(uint16_t address);

  /*!
  * \brief Set RX timeout
  *
  * Timeout for waiting datas.
  *
  * \param timeout_ns timeout in nano second
  */
  void SetRxTimeout(Time timeout_ns);

  /*!
  * \brief Set TX timeout
  *
  * Timeout for waiting an ACK from the slave.
  *
  * \param timeout_ns timeout in nano second
  */
  void SetTxTimeout(Time timeout_ns);

  /*!
  * \brief Write datas
  *
  * \param buf pointer to datas
  * \param nbyte length of datas
  *
  * \return amount of written datas
  */
  ssize_t Write(const void *buf, size_t nbyte);

  /*!
  * \brief Read datas
  *
  * \param buf pointer to datas
  * \param nbyte length of datas
  *
  * \return amount of read datas
  */
  ssize_t Read(void *buf, size_t nbyte);

private:
  int fd;
};
} // end namespace core
} // end namespace flair

#endif // UNIX_I2CPORT_H
