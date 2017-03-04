// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file OneAxisRotation.h
 * \brief Class defining a rotation around one axis
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/17
 * \version 4.0
 */

#ifndef ONEAXISROTATION_H
#define ONEAXISROTATION_H

#include <GroupBox.h>

class OneAxisRotation_impl;

namespace flair {
namespace gui {
class LayoutPosition;
}

namespace core {
class Vector3D;
class Euler;
class Quaternion;
class RotationMatrix;

/*! \class OneAxisRotation
*
* \brief Class defining a rotation around one axis
*
* Axe and value of the rotation are placed in a GroupBox on ground station.
*
*/
class OneAxisRotation : public gui::GroupBox {
public:
  /*!
  * \brief Constructor
  *
  * Construct a OneAxisRotation at given position.
  *
  * \param position position to place the GroupBox
  * \param name name
  */
  OneAxisRotation(const gui::LayoutPosition *position, std::string namel);

  /*!
  * \brief Destructor
  *
  */
  ~OneAxisRotation();

  /*!
  * \brief Compute rotation
  *
  * \param vector Vector3D to rotate
  */
  void ComputeRotation(core::Vector3D &vector) const;

  /*!
  * \brief Compute rotation
  *
  * \param euler Euler angle to rotate
  */
  void ComputeRotation(core::Euler &euler) const;

  /*!
  * \brief Compute rotation
  *
  * \param quaternion Quaternion to rotate
  */
  void ComputeRotation(core::Quaternion &quaternion) const;

  /*!
  * \brief Compute rotation
  *
  * \param matrix RotationMatrix to rotate
  */
  void ComputeRotation(core::RotationMatrix &matrix) const;

private:
  const class OneAxisRotation_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // ONEAXISROTATION_H
