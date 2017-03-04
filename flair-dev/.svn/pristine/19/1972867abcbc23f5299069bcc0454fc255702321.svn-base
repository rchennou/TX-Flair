// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file UavMultiplex.h
 * \brief Class defining uav multiplexing
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/04/11
 * \version 4.0
 */

#ifndef UAVMULTIPLEX_H
#define UAVMULTIPLEX_H

#include <IODevice.h>
#include <stdint.h>

namespace flair {
namespace core {
class FrameworkManager;
class io_data;
}
namespace gui {
class TabWidget;
class Layout;
}
}

class UavMultiplex_impl;

namespace flair {
namespace filter {
/*! \class UavMultiplex
*
* \brief Class defining uav multiplexing
*/
class UavMultiplex : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a uav multiplexing
  *
  * \param parent parent
  * \param name name
  */
  UavMultiplex(const core::FrameworkManager *parent, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~UavMultiplex();

  /*!
  * \brief Set roll torque
  *
  * roll torque is placed in input(0,0)
  *
  * \param value value between -1 and 1
  */
  void SetRoll(float value);

  /*!
  * \brief Set pitch torque
  *
  * pitch torque is placed in input(1,0)
  *
  * \param value value between -1 and 1
  */
  void SetPitch(float value);

  /*!
  * \brief Set yaw torque
  *
  * yaw torque is placed in input(2,0)
  *
  * \param value value between -1 and 1
  */
  void SetYaw(float value);

  /*!
  * \brief Set thrust
  *
  * thrust is placed in input(3,0)
  *
  * \param value value between 0 and 1
  */
  void SetThrust(float value);

  /*!
  * \brief Set roll trim
  *
  * trim is placed in input(4,0)
  *
  * \param value value
  */
  void SetRollTrim(float value);

  /*!
  * \brief Set pitch trim
  *
  * trim is placed in input(5,0)
  *
  * \param value value
  */
  void SetPitchTrim(float value);

  /*!
  * \brief Set yaw trim
  *
  * trim is placed in input(6,0)
  *
  * \param value value
  */
  void SetYawTrim(float value);

  /*!
  * \brief Update using provided datas
  *
  * Uses values specified by Set*().
  *
  * \param time time of the update
  */
  void Update(core::Time time);

  /*!
  * \brief Lock user interface
  *
  * User interface will be grayed out.\n
  * Use it do disallow changes when flying.
  *
  */
  void LockUserInterface(void) const;

  /*!
  * \brief Unlock user interface
  *
  * User interface will be enabled.\n
  *
  */
  void UnlockUserInterface(void) const;

  /*!
  * \brief Layout
  *
  * Layout to place custom widgets.\n
  *
  * \return the layout
  */
  gui::Layout *GetLayout(void) const;

  /*!
  * \brief Use default plot
  *
  * Derived class can implement this function do draw default plot.
  *
  */
  virtual void UseDefaultPlot(void){};

  /*!
  * \brief Motors count
  *
  * This function must be reimplemented, in order to get the number of motors.
  *
  * \return motors count
  */
  virtual uint8_t MotorsCount(void) const = 0;

  /*!
  * \brief Multiplex value
  *
  * Get the mutliplexed value of a motor, if SetMultiplexComboBox() was used.\n
  *
  * \param index index of the motor, from 0 to MotorsCount()
  * \return multiplexed index of the motor
  */
  int MultiplexValue(int index) const;

  /*!
  * \brief Get TabWidget
  *
  * Usefull to add tabs.\n
  *
  * \return the TabWidget
  */
  gui::TabWidget *GetTabWidget(void) const;

protected:
  /*!
  * \brief Set multiplex ComboBox
  *
  * Draws a ComboBox to define motor multiplexing. \n
  * This is used to change the order of the output motors.
  *
  * \param name description of the motor (ex front left)
  * \param index index of the motor, from 0 to MotorsCount()
  */
  void SetMultiplexComboBox(std::string name, int index);

private:
  /*!
  * \brief Update using provided datas
  *
  * This function is automatically called by ProcessUpdate()
  * of the Object::Parent's if its Object::ObjectType is "IODevice". \n
  * This function must be reimplemented, in order to process the data from the
  *parent.
  *
  * \param data data from the parent to process
  */
  virtual void UpdateFrom(const core::io_data *data) = 0;

  UavMultiplex_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // UAVMULTIPLEX_H
