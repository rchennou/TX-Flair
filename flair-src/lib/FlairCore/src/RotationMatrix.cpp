// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/02/09
//  filename:   RotationMatrix.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a rotation matrix
//
//
/*********************************************************************/

#include "RotationMatrix.h"
#include "Object.h"
#include "Euler.h"
#include "Quaternion.h"
#include "math.h"

using std::max;

namespace flair {
namespace core {

RotationMatrix::RotationMatrix() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j) {
        m[i][j] = 1;
      } else {
        m[i][j] = 0;
      }
    }
  }
}

RotationMatrix::~RotationMatrix() {}

void RotationMatrix::ToEuler(Euler &euler) const {
  euler.roll = atanf(m[1][2] / m[2][2]);
  euler.pitch = asinf(-m[0][2]);
  euler.yaw = atan2f(m[0][1], m[0][0]);
}

Euler RotationMatrix::ToEuler(void) const {
  Euler euler;
  ToEuler(euler);
  return euler;
}

//from 3dmgx3-25 manual
void RotationMatrix::ToQuaternion(Quaternion &quaternion) const {
  float test1 = m[0][0] + m[1][1] + m[2][2];
  float test2 = m[0][0] - m[1][1] - m[2][2];
  float test3 = -m[0][0] + m[1][1] - m[2][2];
  float test4 = -m[0][0] - m[1][1] + m[2][2];

  if(test1==max(max(test1,test2),max(test3,test4))) {
    float s=2*sqrtf(1+test1);
    quaternion.q0 = s/4.;
    quaternion.q1 = ( m[1][2] - m[2][1] ) / s;
    quaternion.q2 = ( m[2][0] - m[0][2] ) / s;
    quaternion.q3 = ( m[0][1] - m[1][0] ) / s;
  }

  if(test2==max(max(test1,test2),max(test3,test4))) {
    float s=2*sqrtf(1+test2);
    quaternion.q0 = ( m[2][1] - m[1][2] ) / s;
    quaternion.q1 = -s/4.;
    quaternion.q2 = -( m[1][0] + m[0][1] ) / s;
    quaternion.q3 = -( m[0][2] + m[2][0] ) / s;
  }

  if(test3==max(max(test1,test2),max(test3,test4))) {
    float s=2*sqrtf(1+test3);
    quaternion.q0 = (m[0][2] - m[2][0] ) / s;
    quaternion.q1 = -( m[1][0] + m[0][1] ) / s;
    quaternion.q2 = -s/4.;
    quaternion.q3 = -( m[2][1] + m[1][2] ) / s;
  }

  if(test4==max(max(test1,test2),max(test3,test4))) {
    float s=2*sqrtf(1+test4);
    quaternion.q0 = (m[1][0] - m[0][1] ) / s;
    quaternion.q1 = -( m[0][2] + m[2][0] ) / s;
    quaternion.q2 = -( m[2][1] + m[1][2] ) / s;
    quaternion.q3 = -s/4.;
  }
  quaternion.Normalize();
}

Quaternion RotationMatrix::ToQuaternion(void) const {
  Quaternion quaternion;
  ToQuaternion(quaternion);
  return quaternion;
}

float &RotationMatrix::operator()(size_t row, size_t col) {
  if (row < 3 && col < 3) {
    return m[row][col];
  } else {
    Printf("RotationMatrix: index (%i,%i) out of bound\n", row, col);
    return m[2][2];
  }
}

const float &RotationMatrix::operator()(size_t row, size_t col) const {
  if (row < 3 && col < 3) {
    return m[row][col];
  } else {
    Printf("RotationMatrix: index (%i,%i) out of bound\n", row, col);
    return m[2][2];
  }
}

} // end namespace core
} // end namespace flair
