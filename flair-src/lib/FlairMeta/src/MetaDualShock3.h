// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file MetaDualShock3.h
 * \brief Classe intégrant la manette DualShock3 et les consignes joystick
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/14
 * \version 3.4
 */

#ifndef METADUALSHOCK3_H
#define METADUALSHOCK3_H

#include <TargetController.h>
#include <IODevice.h>

namespace flair {
namespace core {
class AhrsData;
class Quaternion;
}
namespace filter {
class Ahrs;
}
}

class MetaDualShock3_impl;

namespace flair {
namespace meta {

/*! \class MetaDualShock3
*
* \brief Classe intégrant la manette MetaDualShock3
*/
class MetaDualShock3 : public core::IODevice {
  friend class ::MetaDualShock3_impl;

public:
  MetaDualShock3(core::FrameworkManager *parent, std::string name,
                 sensor::TargetController *controller);
  ~MetaDualShock3();
  core::AhrsData *GetReferenceOrientation(void) const;
  float ZRef(void) const;
  float DzRef(void) const;
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
  void SetZRef(float value);
  float RollTrim(void) const;
  float PitchTrim(void) const;
  void ErrorNotify(void);
  void Rumble(uint8_t left_force, uint8_t left_timeout = 20,
              uint8_t right_force = 0, uint8_t right_timeout = 0);
  void SetLedON(unsigned int ledId);
  void SetLedOFF(unsigned int ledId);
  void FlashLed(unsigned int ledId, uint8_t on_timeout, uint8_t off_timeout);

        private:
            class MetaDualShock3_impl* pimpl_;
            void UpdateFrom(const flair::core::io_data *data);
            sensor::TargetController *controller;
    };
} // end namespace meta
} // end namespace flair
#endif // METADUALSHOCK3_H
