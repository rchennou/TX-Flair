// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Euler.h
 * \brief Class defining euler angles
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/05/02
 * \version 4.0
 */

#ifndef EULER_H
#define EULER_H

namespace flair {
namespace core {
class Quaternion;

/*! \class Euler
*
* \brief Class defining euler angles
*
* Euler angles are expressed in radians.
*
*/
class Euler {
public:
  /*!
  * \brief Constructor
  *
  * Construct euler angles using specified values.
  *
  * \param roll roll value
  * \param pitch pitch value
  * \param yaw yaw value
  */
  Euler(float roll = 0, float pitch = 0, float yaw = 0);

  /*!
  * \brief Destructor
  *
  */
  ~Euler();

  /*!
  * \brief x axis rotation
  *
  * \param value rotation value in radians
  */
  // todo: passer par un quaternion
  // void RotateX(float value);

  /*!
  * \brief x axis rotation
  *
  * \param value rotation value in degrees
  */
  // void RotateXDeg(float value);

  /*!
  * \brief y axis rotation
  *
  * \param value rotation value in radians
  */
  // void RotateY(float value);

  /*!
  * \brief y axis rotation
  *
  * \param value rotation value in degrees
  */
  // void RotateYDeg(float value);

  /*!
  * \brief z axis rotation
  *
  * \param value rotation value in radians
  */
  // void RotateZ(float value);

  /*!
  * \brief z axis rotation
  *
  * \param value rotation value in degrees
  */
  // void RotateZDeg(float value);

  /*!
  * \brief Convert to quaternion
  *
  * \param quaternion output quaternion
  */
  void ToQuaternion(Quaternion &quaternion) const;

  /*!
  * \brief Convert to quaternion
  *
  * \return quaternion
  */
  Quaternion ToQuaternion(void) const;
  /*!
  * \brief Convert from radian to degree
  *
  * \param radianValue value in radian
  *
  * \return value in degree
  */
  static float ToDegree(float radianValue);

  /*!
  * \brief Convert from degree to radian
  *
  * \param degreeValue value in degree
  *
  * \return value in radian
  */
  static float ToRadian(float degreeValue);

  /*!
  * \brief Compute yaw distance
  *
  * Compute yaw distance from given angle. This is the minimum distance.
  *
  * \param angle starting angle
  *
  * \return value distance in radian
  */
  float YawDistanceFrom(float angle) const;

  /*!
  * \brief roll value
  */
  float roll;

  /*!
  * \brief pitch value
  */
  float pitch;

  /*!
  * \brief yaw value
  */
  float yaw;

  Euler &operator=(const Euler &euler);
};

} // end namespace core
} // end namespace flair

#endif // EULER_H
