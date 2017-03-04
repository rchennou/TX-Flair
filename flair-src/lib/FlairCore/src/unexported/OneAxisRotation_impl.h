// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file OneAxisRotation_impl.h
 * \brief Classe définissant une rotation autour d'un axe
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/17
 * \version 4.0
 */

#ifndef ONEAXISROTATION_IMPL_H
#define ONEAXISROTATION_IMPL_H

namespace flair {
namespace core {
class Vector3D;
class Euler;
class Quaternion;
class RotationMatrix;
}
namespace gui {
class GroupBox;
class ComboBox;
class DoubleSpinBox;
}
}

/*! \class OneAxisRotation_impl
* \brief Classe définissant une rotation autour d'un axe
*
*/
class OneAxisRotation_impl {
public:
  OneAxisRotation_impl(flair::gui::GroupBox *box);
  ~OneAxisRotation_impl();
  void ComputeRotation(flair::core::Vector3D &point) const;
  void ComputeRotation(flair::core::Quaternion &quat) const;
  void ComputeRotation(flair::core::RotationMatrix &matrix) const;
  void ComputeRotation(flair::core::Euler &euler) const;

private:
  flair::gui::ComboBox *rot_axe;
  flair::gui::DoubleSpinBox *rot_value;
};

#endif // ONEAXISROTATION_IMPL_H
