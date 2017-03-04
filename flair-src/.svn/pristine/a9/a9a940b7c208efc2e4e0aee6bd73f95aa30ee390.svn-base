// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/17
//  filename:   OneAxisRotation.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a rotation around one axis
//
//
/*********************************************************************/

// this "filter" is in core but it should be in filter
// filter depends on sensoractuator
// sensoractuators depends on oneaxisrotation
// so if oneaxisrotation is in fiter we have a circular dependency
// TODO: fix this!

#include "OneAxisRotation.h"
#include "OneAxisRotation_impl.h"
#include <Vector3D.h>
#include <Euler.h>

using std::string;

namespace flair {
namespace core {

OneAxisRotation::OneAxisRotation(const gui::LayoutPosition *position,
                                 string name)
    : gui::GroupBox(position, name) {
  pimpl_ = new OneAxisRotation_impl(this);
}

OneAxisRotation::~OneAxisRotation() { delete pimpl_; }

void OneAxisRotation::ComputeRotation(Vector3D &vector) const {
  pimpl_->ComputeRotation(vector);
}

void OneAxisRotation::ComputeRotation(Euler &euler) const {
  pimpl_->ComputeRotation(euler);
}

void OneAxisRotation::ComputeRotation(Quaternion &quaternion) const {
  pimpl_->ComputeRotation(quaternion);
}

void OneAxisRotation::ComputeRotation(RotationMatrix &matrix) const {
  pimpl_->ComputeRotation(matrix);
}

} // end namespace core
} // end namespace flair
