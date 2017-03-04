// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file I2cPort.h
 * \brief Base class for i2c port
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/04/24
 * \version 4.0
 */

#ifndef I2CPORT_H
#define I2CPORT_H

#include <Mutex.h>
#include <stdint.h>

namespace flair {
namespace core {
/*! \class I2cPort
*
* \brief Base class for i2c port
*
* This class has a Mutex which must be used to protect access to the port in
*case
* that more than one Thread is using it. Lock the Mutex before any communication
*(including SetSlave)
* and release it after communication.
*/
class I2cPort : public Mutex {
public:
  /*!
  * \brief Constructor
  *
  * Construct an i2c port.
  *
  * \param parent parent
  * \param name name
  */
  I2cPort(const Object *parent, std::string name) : Mutex(parent, name) {}

  /*!
  * \brief Destructor
  *
  */
  ~I2cPort(){};

  /*!
  * \brief Set slave's address
  *
  * This function need to be called before any communication.
  *
  * \param address slave's address
  */
  virtual int SetSlave(uint16_t address) = 0;

  /*!
  * \brief Write datas
  *
  * \param buf pointer to datas
  * \param nbyte length of datas
  *
  * \return amount of written datas
  */
  virtual ssize_t Write(const void *buf, size_t nbyte) = 0;

  /*!
  * \brief Read datas
  *
  * \param buf pointer to datas
  * \param nbyte length of datas
  *
  * \return amount of read datas
  */
  virtual ssize_t Read(void *buf, size_t nbyte) = 0;

  /*!
  * \brief Set RX timeout
  *
  * Timeout for waiting an ACK from the slave.
  *
  * \param timeout_ns timeout in nano second
  */
  virtual void SetRxTimeout(Time timeout_ns) = 0;

  /*!
  * \brief Set TX timeout
  *
  * Timeout for waiting an ACK from the slave.
  *
  * \param timeout_ns timeout in nano second
  */
  virtual void SetTxTimeout(Time timeout_ns) = 0;
};
} // end namespace core
} // end namespace framework

#endif // I2CPORT_H
