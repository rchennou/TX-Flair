// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SerialPort.h
 * \brief Base class for serial port
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/04/25
 * \version 4.0
 */

#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <Object.h>
#include <stdint.h>

namespace flair {
namespace core {
/*! \class SerialPort
*
* \brief Base class for serial port
*/
class SerialPort : public Object {
public:
  /*!
  * \brief Constructor
  *
  * Construct a serial port.
  *
  * \param parent parent
  * \param name name
  */
  SerialPort(const Object *parent, std::string name) : Object(parent, name) {}

  /*!
  * \brief Destructor
  *
  */
  ~SerialPort(){};

  /*!
  * \brief Set baudrate
  *
  * \param baudrate baudrate
  *
  */
  virtual void SetBaudrate(int baudrate) = 0;

  /*!
  * \brief Set RX timeout
  *
  * Timeout for waiting datas.
  *
  * \param timeout_ns timeout in nano second
  */
  virtual void SetRxTimeout(Time timeout_ns) = 0;

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
  * \brief Flush input datas
  *
  */
  virtual void FlushInput(void) = 0;
};
} // end namespace core
} // end namespace framework

#endif // SERIALPORT_H
