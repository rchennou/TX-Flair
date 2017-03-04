// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file RTDM_I2cPort.h
 * \brief Class for real time i2c port using RTDM
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/08/19
 * \version 4.0
 */

#ifndef RTDM_I2CPORT_H
#define RTDM_I2CPORT_H

#include <I2cPort.h>

namespace flair {
namespace core {
/*! \class RTDM_I2cPort
*
* \brief Class for real time i2c port using RTDM
*
* This class can only be used with the real time version of Framework library.
*
*/
class RTDM_I2cPort : public I2cPort {
public:
  /*!
  * \brief Constructor
  *
  * Construct an RTDM i2c port, with the following default values: \n
  * - 400kbits baudrate \n
  * - 500000ns RX timeout \n
  * - 1000000ns TX timeout
  *
  * \param parent parent
  * \param name name
  * \param device i2c device (ex rti2c1)
  */
  RTDM_I2cPort(const Object *parent, std::string name, std::string device);

  /*!
  * \brief Destructor
  *
  */
  ~RTDM_I2cPort();

  /*!
  * \brief Set slave's address
  *
  * This method need to be called before any communication.
  *
  * \param address slave's address
  */
  int SetSlave(uint16_t address);

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
  * \brief Set RX timeout
  *
  * Timeout for waiting an ACK from the slave.
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

private:
  int fd;
};
} // end namespace core
} // end namespace flair

#endif // RTDM_I2CPORT_H
