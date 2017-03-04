// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file BatteryMonitor.h
 * \brief Base class for battery monitor
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/24
 * \version 4.0
 */

#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include <GroupBox.h>

namespace flair {
namespace gui {
class LayoutPosition;
class Label;
class DoubleSpinBox;
}
}

namespace flair {
namespace sensor {

/*! \class BatteryMonitor
*
* \brief Base class for battery monitor
*/

class BatteryMonitor : public gui::GroupBox {
public:
  /*!
  * \brief Constructor
  *
  * Construct a BatteryMonitor at given position.
  *
  * \param position position
  * \param name name
  */
  BatteryMonitor(const gui::LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~BatteryMonitor();

  /*!
  * \brief Is batteru low?
  *
  * \return true if battery is below threshold
  *
  */
  bool IsBatteryLow(void) const;

  /*!
  * \brief Set battery value
  *
  * \param battery value
  *
  */
  void SetBatteryValue(float value);

  /*!
  * \brief Get battery voltage
  *
  * \return battery voltage
  *
  */
  float GetVoltage(void) const;

private:
  float batteryvalue;
  gui::DoubleSpinBox *battery_thresh;
  gui::Label *battery;
};
} // end namespace sensor
} // end namespace flair

#endif // BATTERYMONITOR_H
