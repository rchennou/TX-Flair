// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Gx3_25_imu.h
 * \brief Class for 3dmgx3-25 Imu
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/08/19
 * \version 4.0
 */

#ifndef GX3_25_IMU_H
#define GX3_25_IMU_H

#include <Imu.h>
#include <Thread.h>

namespace flair {
namespace core {
class FrameworkManager;
class SerialPort;
}
}

class Gx3_25_imu_impl;

namespace flair {
namespace sensor {
/*! \class Gx3_25_imu
*
* \brief Class for 3dmgx3-25 Imu
*/
class Gx3_25_imu : public Imu, public core::Thread {
  friend class ::Gx3_25_imu_impl;

public:
  /*!
  \enum Command_t
  \brief Command for the continuous mode
  */
  enum Command_t {
    EulerAnglesAndAngularRates = 0xcf, /*!< Euler angles and angular rates */
    AccelerationAngularRateAndOrientationMatrix =
        0xc8, /*!< Acceleration, angular rate and orientation matrix */
    Quaternion = 0xdf, /*!< Quaternion */
  };

  /*!
  * \brief Constructor
  *
  * Construct a Gx3_25_imu.
  *
  * \param parent parent
  * \param name name
  * \param serialport SerialPort
  * \param command command for continuous mode
  * \param priority priority of the Thread
  */
  Gx3_25_imu(const core::FrameworkManager *parent, std::string name,
             core::SerialPort *serialport, Command_t command, uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~Gx3_25_imu();

private:
  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);

  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  class Gx3_25_imu_impl *pimpl_;
};
} // end namespace sensor
} // end namespace flair

#endif // GX3_25_IMU_H
