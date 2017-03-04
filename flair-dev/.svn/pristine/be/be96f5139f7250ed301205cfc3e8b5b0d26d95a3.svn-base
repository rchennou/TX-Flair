// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Unix_SerialPort.h
 * \brief Class for unix serial port
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/08/19
 * \version 4.0
 */

#ifndef UNIX_SERIALPORT_H
#define UNIX_SERIALPORT_H

#include <SerialPort.h>
#include <termios.h> /* POSIX terminal control definitions */

namespace flair {
namespace core {
/*! \class RTDM_I2cPort
*
* \brief Class for unix serial port
*
*/
class Unix_SerialPort : public SerialPort {

public:
  /*!
  * \brief Constructor
  *
  * Construct an unix serial port, with the following default values: \n
  * - 115200bps baudrate
  *
  * \param parent parent
  * \param name name
  * \param device serial device (ex rtser1)
  */
  Unix_SerialPort(const Object *parent, std::string port_name,
                  std::string device);

  /*!
  * \brief Destructor
  *
  */
  ~Unix_SerialPort();

  /*!
  * \brief Set baudrate
  *
  * \param baudrate baudrate
  *
  */
  void SetBaudrate(int baudrate);

  /*!
  * \brief Set RX timeout
  *
  * Timeout for waiting datas.
  *
  * \param timeout_ns timeout in nano second
  */
  void SetRxTimeout(Time timeout_ns);

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

  /*!
  * \brief Flush input datas
  *
  */
  void FlushInput(void);

private:
  int fd;
  struct termios options;
};
} // end namespace core
} // end namespace flair

#endif // UNIX_SERIALPORT_H
