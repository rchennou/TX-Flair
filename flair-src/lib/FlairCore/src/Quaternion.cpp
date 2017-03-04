// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/02/03
//  filename:   Quaternion.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a quaternion
//
//
/*********************************************************************/

#include "Quaternion.h"
#include "Vector3D.h"
#include "Euler.h"
#include "RotationMatrix.h"
#include <math.h>
#include <stdio.h>

namespace flair {
namespace core {

Quaternion::Quaternion(float inQ0, float inQ1, float inQ2, float inQ3)
    : q0(inQ0), q1(inQ1), q2(inQ2), q3(inQ3) {}

Quaternion::~Quaternion() {}

Quaternion &Quaternion::operator=(const Quaternion &quaternion) {
  q0 = quaternion.q0;
  q1 = quaternion.q1;
  q2 = quaternion.q2;
  q3 = quaternion.q3;
  return (*this);
}

float Quaternion::GetNorm(void) const {
  return sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
}

void Quaternion::Normalize(void) {
  float n = GetNorm();
  if (n != 0) {
    q0 = q0 / n;
    q1 = q1 / n;
    q2 = q2 / n;
    q3 = q3 / n;
  }
}

void Quaternion::Conjugate(void) {
  q1 = -q1;
  q2 = -q2;
  q3 = -q3;
}

Quaternion Quaternion::GetConjugate(void) {
  return Quaternion(q0, -q1, -q2, -q3);
}

void Quaternion::GetLogarithm(Vector3D &logarithm) {
  Normalize();
  float v_norm = sqrtf(q1 * q1 + q2 * q2 + q3 * q3);

  if (v_norm != 0) {
    float v_arccos = acosf(q0);
    logarithm.x = (q1 * v_arccos) / v_norm;
    logarithm.y = (q2 * v_arccos) / v_norm;
    logarithm.z = (q3 * v_arccos) / v_norm;
  } else {
    logarithm.x = 0;
    logarithm.y = 0;
    logarithm.z = 0;
  }
}

Vector3D Quaternion::GetLogarithm(void) {
  Vector3D vector;
  GetLogarithm(vector);
  return vector;
}

Quaternion Quaternion::GetDerivative(const Vector3D &angularSpeed) const {
  const Quaternion Qw(0, angularSpeed.x, angularSpeed.y, angularSpeed.z);
  return 0.5 * (*this) * Qw;
}

void Quaternion::Derivate(const Vector3D &angularSpeed) {
  Quaternion Q = GetDerivative(angularSpeed);
  (*this) = Q;
}

void Quaternion::ToEuler(Euler &euler) const {
  euler.roll = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
  euler.pitch = asin(2 * (q0 * q2 - q1 * q3));
  euler.yaw = atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3));
}

Euler Quaternion::ToEuler(void) const {
  Euler euler;
  ToEuler(euler);
  return euler;
}

void Quaternion::ToRotationMatrix(RotationMatrix &matrix) const {
  float aSq = q0 * q0;
  float bSq = q1 * q1;
  float cSq = q2 * q2;
  float dSq = q3 * q3;
  matrix.m[0][0] = aSq + bSq - cSq - dSq;
  matrix.m[0][1] = 2.0f * (q1 * q2 - q0 * q3);
  matrix.m[0][2] = 2.0f * (q0 * q2 + q1 * q3);
  matrix.m[1][0] = 2.0f * (q1 * q2 + q0 * q3);
  matrix.m[1][1] = aSq - bSq + cSq - dSq;
  matrix.m[1][2] = 2.0f * (q2 * q3 - q0 * q1);
  matrix.m[2][0] = 2.0f * (q1 * q3 - q0 * q2);
  matrix.m[2][1] = 2.0f * (q0 * q1 + q2 * q3);
  matrix.m[2][2] = aSq - bSq - cSq + dSq;
}

Quaternion &Quaternion::operator+=(const Quaternion &quaternion) {
  q0 += quaternion.q0;
  q1 += quaternion.q1;
  q2 += quaternion.q2;
  q3 += quaternion.q3;
  return (*this);
}

Quaternion &Quaternion::operator-=(const Quaternion &quaternion) {
  q0 -= quaternion.q0;
  q1 -= quaternion.q1;
  q2 -= quaternion.q2;
  q3 -= quaternion.q3;
  return (*this);
}

Quaternion operator+(const Quaternion &quaternionA,
                     const Quaternion &quaterniontB) {
  return Quaternion(
      quaternionA.q0 + quaterniontB.q0, quaternionA.q1 + quaterniontB.q1,
      quaternionA.q2 + quaterniontB.q2, quaternionA.q3 + quaterniontB.q3);
}

Quaternion operator-(const Quaternion &quaterniontA,
                     const Quaternion &quaterniontB) {
  return Quaternion(
      quaterniontA.q0 - quaterniontB.q0, quaterniontA.q1 - quaterniontB.q1,
      quaterniontA.q2 - quaterniontB.q2, quaterniontA.q3 - quaterniontB.q3);
}

Quaternion operator-(const Quaternion &quaternion) {
  return Quaternion(-quaternion.q0, -quaternion.q1, -quaternion.q2,
                    -quaternion.q3);
}

Quaternion operator*(const Quaternion &quaterniontA,
                     const Quaternion &quaterniontB) {
  return Quaternion(
      quaterniontA.q0 * quaterniontB.q0 - quaterniontA.q1 * quaterniontB.q1 -
          quaterniontA.q2 * quaterniontB.q2 - quaterniontA.q3 * quaterniontB.q3,
      quaterniontA.q0 * quaterniontB.q1 + quaterniontA.q1 * quaterniontB.q0 +
          quaterniontA.q2 * quaterniontB.q3 - quaterniontA.q3 * quaterniontB.q2,
      quaterniontA.q0 * quaterniontB.q2 - quaterniontA.q1 * quaterniontB.q3 +
          quaterniontA.q2 * quaterniontB.q0 + quaterniontA.q3 * quaterniontB.q1,
      quaterniontA.q0 * quaterniontB.q3 + quaterniontA.q1 * quaterniontB.q2 -
          quaterniontA.q2 * quaterniontB.q1 +
          quaterniontA.q3 * quaterniontB.q0);
}

Quaternion operator*(float coeff, const Quaternion &quaternion) {
  return Quaternion(coeff * quaternion.q0, coeff * quaternion.q1,
                    coeff * quaternion.q2, coeff * quaternion.q3);
}

Quaternion operator*(const Quaternion &quaternion, float coeff) {
  return Quaternion(coeff * quaternion.q0, coeff * quaternion.q1,
                    coeff * quaternion.q2, coeff * quaternion.q3);
}

} // end namespace core
} // end namespace flair
