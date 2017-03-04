// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file RTDM_SerialPort.h
 * \brief Class for real time serial port using RTDM
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/08/19
 * \version 4.0
 */

#ifndef RTDM_SERIALPORT_H
#define RTDM_SERIALPORT_H

#include <SerialPort.h>

namespace flair {
namespace core {
/*! \class RTDM_SerialPort
*
* \brief Class for real time serial port using RTDM
*
* This class can only be used with the real time version of Framework library.
*
*/
class RTDM_SerialPort : public SerialPort {

public:
  /*!
  * \brief Constructor
  *
  * Construct an RTDM serial port, with the following default values: \n
  * - 115200bps baudrate
  *
  * \param parent parent
  * \param name name
  * \param device serial device (ex rtser1)
  */
  RTDM_SerialPort(const Object *parent, std::string port_name,
                  std::string device);

  /*!
  * \brief Destructor
  *
  */
  ~RTDM_SerialPort();

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
};
} // end namespace core
} // end namespace flair

#endif // RTDM_SERIALPORT_H
