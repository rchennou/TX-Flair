// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Gx3_25_ahrs.h
 * \brief Class for 3dmgx3-25 ahrs
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/01/16
 * \version 4.0
 */

#ifndef GX3_25_AHRS_H
#define GX3_25_AHRS_H

#include <Ahrs.h>
#include <Gx3_25_imu.h>

namespace flair {
namespace filter {
/*! \class Gx3_25_ahrs
*
* \brief Class for 3dmgx3-25 ahrs
*
* This class constructs a Gx3_25_imu as Imu of this Ahrs.
*/
class Gx3_25_ahrs : public Ahrs {
public:
  /*!
  * \brief Constructor
  *
  * Construct an Ahrs for 3dmgx3-25
  *
  * \param parent parent
  * \param name name
  * \param serialport Imu SerialPort
  * \param command command for the Gx3_25_imu continuous mode
  * \param priority priority of the Gx3_25_imu Thread
  */
  Gx3_25_ahrs(const core::FrameworkManager *parent, std::string name,
              core::SerialPort *serialport,
              sensor::Gx3_25_imu::Command_t command, uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~Gx3_25_ahrs();

  /*!
  * \brief Start Gx3_25_imu Thread
  *
  */
  void Start(void);

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);
};
} // end namespace filter
} // end namespace flair
#endif // GX3_25_AHRS_H
