// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file AfroBldc.h
 * \brief Class for Mikrokopter's blctrlv2
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2015/06/15
 * \version 4.0
 */

#ifndef AFROBLDC_H
#define AFROBLDC_H

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

class AfroBldc_impl;

namespace flair {
namespace actuator {
/*! \class AfroBldc
*
* \brief Class for Mikrokopter's blctrlv2
*
* blctrlv2 drivers can also monitor the battery level. See GetBatteryMonitor().
*/
class AfroBldc : public Bldc {
  friend class ::AfroBldc_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a AfroBldc.
  *
  * \param parent parent
  * \param layout layout
  * \param name name
  * \param motors_count number of motors
  * \param i2cport I2cPort
  */
  AfroBldc(const core::IODevice *parent, gui::Layout *layout, std::string name,
           uint8_t motors_count, core::I2cPort *i2cport);

  /*!
  * \brief Destructor
  *
  */
  ~AfroBldc();

  /*!
  * \brief Has speed measurement
  *
  * Reimplemented from Bldc. \n
  *
  * \return true if it has speed measurement
  */
  bool HasSpeedMeasurement(void) const { return false; };

  /*!
  * \brief Has current measurement
  *
  * Reimplemented from Bldc. \n
  *
  * \return true if it has current measurement
  */
  bool HasCurrentMeasurement(void) const { return false; };

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

  class AfroBldc_impl *pimpl_;
};
} // end namespace actuator
} // end namespace flair
#endif // AFROBLDC_H
