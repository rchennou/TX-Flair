// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file RotationMatrix.h
 * \brief Class defining a rotation matrix
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/02/09
 * \version 4.0
 */
#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include <stddef.h>

namespace flair {
namespace core {
class Euler;
class Quaternion;

/*! \class RotationMatrix
*
* \brief Class defining a rotation matrix
*/
class RotationMatrix {
public:
  /*!
  * \brief Constructor
  *
  * Construct an identity rotation matrix
  *
  */
  RotationMatrix();

  /*!
  * \brief Destructor
  *
  */
  ~RotationMatrix();

  /*!
  * \brief Convert to euler angles
  *
  * \param euler output euler angles
  */
  void ToEuler(Euler &euler) const;

  /*!
  * \brief Convert to euler angles
  *
  * \return euler angles
  */
  Euler ToEuler(void) const;

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
  * \brief matrix
  *
  */
  float m[3][3];

  float &operator()(size_t row, size_t col);
  const float &operator()(size_t row, size_t col) const;
};

} // end namespace core
} // end namespace flair

#endif // ROTATIONMATRIX_H
