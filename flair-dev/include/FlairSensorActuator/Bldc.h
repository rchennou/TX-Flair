// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Bldc.h
 * \brief Base class for brushless motors drivers
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/11/14
 * \version 4.0
 */

#ifndef BLDC_H
#define BLDC_H

#include <IODevice.h>
#include <stdint.h>

namespace flair {
namespace core {
class FrameworkManager;
class cvmatrix;
}
namespace gui {
class Layout;
class TabWidget;
}
}

class Bldc_impl;

namespace flair {
namespace actuator {
/*! \class Bldc
*
* \brief Base class for brushless motors drivers
*/
class Bldc : public core::IODevice {
  friend class ::Bldc_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a Bldc.
  *
  * \param parent parent
  * \param layout layout
  * \param name name
  * \param motors_count number of motors
  */
  Bldc(const core::IODevice *parent, gui::Layout *layout, std::string name,
       uint8_t motors_count);

  /*!
  * \brief Constructor
  *
  * Construct a Bldc. \n
  * This contructor must only be called for a simulated device.
  *
  * \param parent parent
  * \param name name
  * \param motors_count number of motors
  */
  Bldc(const core::Object *parent, std::string name, uint8_t motors_count);

  /*!
  * \brief Destructor
  *
  */
  ~Bldc();

  /*!
  * \brief Lock user interface
  *
  */
  void LockUserInterface(void) const;

  /*!
  * \brief Unlock user interface
  *
  */
  void UnlockUserInterface(void) const;

  /*!
  * \brief Use default plot
  *
  * \param tabwidget TabWidget to draw plots
  */
  void UseDefaultPlot(gui::TabWidget *tabwidget);

  /*!
  * \brief Output from motors
  *
  * First column is real speed if available, secund column is current if
  *available
  *
  */
  core::cvmatrix *Output(void) const;

  /*!
  * \brief Motors count
  *
  * \return number of motors
  */
  uint8_t MotorsCount(void) const;

  /*!
  * \brief Enable motors
  *
  * \param true to enable all motors
  */
  void SetEnabled(bool status);

  /*!
  * \brief Are motors enabled?
  *
  * \return true if motors are enabled
  */
  bool AreEnabled(void) const;

  /*!
  * \brief Set motor power
  *
  * Changes the power (from 0 to 1) of a specific motor. \n
  * By default power is set to 1 for each motor which has no effect. \n
  * A value <1 will decrease the power of a motor sent to the reimplemented Bldc
  *class through SetMotors. \n
  * The power value is applied after applying saturation between min value and
  *max value.
  * So the resulting value cannot be higher than max value
  * but it can be lower than min value.
  *
  * \param motor_id id of the motor
  * \param value power value (from 0 to 1)
  *
  */
  void SetPower(int motor_id, float value);

  /*!
  * \brief Layout
  *
  * This the same Layout as passed to the constructor
  *
  * \return a Layout
  */
  gui::Layout *GetLayout(void) const;

  /*!
  * \brief Has speed measurement
  *
  * \return true if it has speed measurement
  */
  virtual bool HasSpeedMeasurement(void) const = 0;

  /*!
  * \brief Has current measurement
  *
  * \return true if it has current measurement
  */
  virtual bool HasCurrentMeasurement(void) const = 0;

protected:
  core::cvmatrix *output;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

  /*!
  * \brief Set motors values
  *
  * values size must be the same as MotorsCount()
  *
  * \param values set motors values
  */
  virtual void SetMotors(float *values) = 0;

  class Bldc_impl *pimpl_;
};
} // end namespace actuator
} // end namespace framewor
#endif // BLDC_H
