// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/17
//  filename:   OneAxisRotation_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant pour une rotation sur un axe
//
//
/*********************************************************************/

#include "OneAxisRotation_impl.h"
#include "GroupBox.h"
#include "ComboBox.h"
#include "DoubleSpinBox.h"
#include <Vector3D.h>
#include <Euler.h>
#include <Quaternion.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

OneAxisRotation_impl::OneAxisRotation_impl(GroupBox *box) {
  rot_value =
      new DoubleSpinBox(box->NewRow(), "value", " deg", -180., 180., 10., 1);
  rot_axe = new ComboBox(box->LastRowLastCol(), "axis");
  rot_axe->AddItem("x");
  rot_axe->AddItem("y");
  rot_axe->AddItem("z");
}

OneAxisRotation_impl::~OneAxisRotation_impl() {}

// compute rotation of each axis through ComputeRotation(Vector3D& vector)
void OneAxisRotation_impl::ComputeRotation(Quaternion &quat) const {
  Vector3D rot = Vector3D(quat.q1, quat.q2, quat.q3);
  ComputeRotation(rot);
  quat.q1 = rot.x;
  quat.q2 = rot.y;
  quat.q3 = rot.z;
}

void OneAxisRotation_impl::ComputeRotation(RotationMatrix &matrix) const {
  Printf("not yet implemented\n");
}

// on utilise la rotation d'un vector pour faire une rotation de repere
// d'ou le signe negatif
void OneAxisRotation_impl::ComputeRotation(Vector3D &vector) const {
  switch (rot_axe->CurrentIndex()) {
  case 0:
    vector.RotateXDeg(-rot_value->Value());
    break;
  case 1:
    vector.RotateYDeg(-rot_value->Value());
    break;
  case 2:
    vector.RotateZDeg(-rot_value->Value());
    break;
  }
}

void OneAxisRotation_impl::ComputeRotation(Euler &euler) const {
  Quaternion quat;
  euler.ToQuaternion(quat);
  ComputeRotation(quat);
  quat.ToEuler(euler);
}
