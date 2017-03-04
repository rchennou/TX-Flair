// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file JoyReference.h
 * \brief Class creating references from a joystick
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/08/29
 * \version 4.0
 */

#ifndef JOYREFERENCE_H
#define JOYREFERENCE_H

#include <IODevice.h>
#include <stdint.h>

namespace flair {
namespace core {
class Quaternion;
class AhrsData;
}
namespace gui {
class LayoutPosition;
}
}

class JoyReference_impl;

namespace flair {
namespace filter {
/*! \class JoyReference
*
* \brief Class creating references from a joystick
*/
class JoyReference : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a JoyReference at given position. \n
  * The JoyReference will automatically be child of position->getLayout()
  *Layout. After calling this function,
  * position will be deleted as it is no longer usefull. \n
  * JoyReference compute reference in quaternion, wz, altitude and altitude
  *speed.
  *
  * \param position position
  * \param name name
  */
  JoyReference(const gui::LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~JoyReference();

  /*!
  * \brief Set roll axis value
  *
  * \param value value
  */
  void SetRollAxis(float value);

  /*!
  * \brief Set pitch axis value
  *
  * \param value value
  */
  void SetPitchAxis(float value);

  /*!
  * \brief Set yaw axis value
  *
  * \param value value
  */
  void SetYawAxis(float value);

  /*!
  * \brief Set thrust axis value
  *
  * \param value value
  */
  void SetAltitudeAxis(float value);

  /*!
  * \brief Get orientation reference
  *
  * \return reference
  */
  core::AhrsData *GetReferenceOrientation(void) const;

  /*!
  * \brief Get z reference
  *
  * \return reference
  */
  float ZRef(void) const;

  /*!
  * \brief Get z derivative reference
  *
  * \return reference
  */
  float DzRef(void) const;

  /*!
  * \brief Get roll trim
  *
  * \return trim value
  */
  float RollTrim(void) const;

  /*!
  * \brief Get pitch trim
  *
  * \return trim value
  */
  float PitchTrim(void) const;

  /*!
  * \brief Set yaw reference
  *
  * Yaw part of the output quaternion is obtained by integrating the wz desired
  *angular speed.\n
  * This method reset the yaw.
  *
  * \param value value
  */
  void SetYawRef(float value);

  /*!
  * \brief Set yaw reference
  *
  * Yaw part of the output quaternion is obtained by integrating the wz desired
  *angular speed.\n
  * This method reset the yaw.
  *
  * \param value value, only the yaw part of the quaternion is used
  */
  void SetYawRef(core::Quaternion const &value);

  /*!
  * \brief Set z reference
  *
  * Altitude of the output is obtained by integrating the vz desired altitude
  *speed.\n
  * This method reset z.
  *
  * \param value value
  */
  void SetZRef(float value);

  /*!
  * \brief Trim up roll
  *
  * Roll trim value is increased by one
  */
  void RollTrimUp(void);

  /*!
  * \brief Trim down roll
  *
  * Roll trim value is decreased by one
  */
  void RollTrimDown(void);

  /*!
  * \brief Trim up pitch
  *
  * Pitch trim value is increased by one
  */
  void PitchTrimUp(void);

  /*!
  * \brief Trim down pitch
  *
  * Pitch trim value is decreased by one
  */
  void PitchTrimDown(void);

  /*!
  * \brief Update references
  *
  * Calls UpdateFrom with values entered manually.
  *
  * \param time time
  */
  void Update(core::Time time);

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

  class JoyReference_impl *pimpl_;
};
} // end namespace sensor
} // end namespace flair

#endif // JOYREFERENCE_H
