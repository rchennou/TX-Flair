// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file BlCtrlV2.h
 * \brief Class for Mikrokopter's blctrlv2
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/09/13
 * \version 4.0
 */

#ifndef BLCTRLV2_H
#define BLCTRLV2_H

#include "Bldc.h"

namespace flair {
namespace core {
class FrameworkManager;
class I2cPort;
}
namespace sensor {
class BatteryMonitor;
}
}

class BlCtrlV2_impl;

namespace flair {
namespace actuator {
/*! \class BlCtrlV2
*
* \brief Class for Mikrokopter's blctrlv2
*
* blctrlv2 drivers can also monitor the battery level. See GetBatteryMonitor().
*/
class BlCtrlV2 : public Bldc {
  friend class ::BlCtrlV2_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a BlCtrlV2.
  *
  * \param parent parent
  * \param layout layout
  * \param name name
  * \param motors_count number of motors
  * \param i2cport I2cPort
  */
  BlCtrlV2(const core::IODevice *parent, gui::Layout *layout, std::string name,
           uint8_t motors_count, core::I2cPort *i2cport);

  /*!
  * \brief Destructor
  *
  */
  ~BlCtrlV2();

  /*!
  * \brief Get battery monitor
  *
  * \return BatteryMonitor
  */
  sensor::BatteryMonitor *GetBatteryMonitor(void) const;

  /*!
  * \brief Has speed measurement
  *
  * Reimplemented from Bldc. \n
  *
  * \return true if it has speed measurement
  */
  bool HasSpeedMeasurement(void) const { return true; };

  /*!
  * \brief Has current measurement
  *
  * Reimplemented from Bldc. \n
  *
  * \return true if it has current measurement
  */
  bool HasCurrentMeasurement(void) const { return true; };

private:
  /*!
  * \brief Set motors values
  *
  * Reimplemented from Bldc. \n
  * Values size must be the same as MotorsCount()
  *
  * \param values motor values
  */
  void SetMotors(float *values);

  class BlCtrlV2_impl *pimpl_;
};
} // end namespace actuator
} // end namespace flair
#endif // BLCTRLV2_H
