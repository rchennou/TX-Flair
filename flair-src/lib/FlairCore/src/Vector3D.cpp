// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/05/02
//  filename:   Vector3D.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a 3D vector
//
//
/*********************************************************************/

#include "Vector3D.h"
#include "Vector2D.h"
#include "RotationMatrix.h"
#include "Euler.h"
#include "Quaternion.h"
#include "Object.h"
#include <math.h>
//#include "Vector3DSpinBox.h"

namespace flair {
namespace core {

Vector3D::Vector3D(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}

Vector3D::~Vector3D() {}
/*
void Vector3D::operator=(const gui::Vector3DSpinBox *vector) {
    Vector3D vect=vector->Value();
    x=vect.x;
    y=vect.y;
    z=vect.z;
}*/

Vector3D &Vector3D::operator=(const Vector3D &vector) {
  x = vector.x;
  y = vector.y;
  z = vector.z;
  return (*this);
}

Vector3D &Vector3D::operator+=(const Vector3D &vector) {
  x += vector.x;
  y += vector.y;
  z += vector.z;
  return (*this);
}

Vector3D &Vector3D::operator-=(const Vector3D &vector) {
  x -= vector.x;
  y -= vector.y;
  z -= vector.z;
  return (*this);
}

float &Vector3D::operator[](size_t idx) {
  if (idx == 0) {
    return x;
  } else if (idx == 1) {
    return y;
  } else if (idx == 2) {
    return z;
  } else {
    Printf("Vector3D: index %i out of bound\n", idx);
    return z;
  }
}

const float &Vector3D::operator[](size_t idx) const {
  if (idx == 0) {
    return x;
  } else if (idx == 1) {
    return y;
  } else if (idx == 2) {
    return z;
  } else {
    Printf("Vector3D: index %i out of bound\n", idx);
    return z;
  }
}

Vector3D CrossProduct(const Vector3D &vectorA, const Vector3D &vectorB) {
  return Vector3D(vectorA.y * vectorB.z - vectorA.z * vectorB.y,
                  vectorA.z * vectorB.x - vectorA.x * vectorB.z,
                  vectorA.x * vectorB.y - vectorA.y * vectorB.x);
}

float DotProduct(const Vector3D &vectorA, const Vector3D &vectorB) {
  return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}

Vector3D operator+(const Vector3D &vectorA, const Vector3D &vectorB) {
  return Vector3D(vectorA.x + vectorB.x, vectorA.y + vectorB.y,
                  vectorA.z + vectorB.z);
}

Vector3D operator-(const Vector3D &vectorA, const Vector3D &vectorB) {
  return Vector3D(vectorA.x - vectorB.x, vectorA.y - vectorB.y,
                  vectorA.z - vectorB.z);
}

Vector3D operator-(const Vector3D &vector) {
  return Vector3D(-vector.x, -vector.y, -vector.z);
}

Vector3D operator*(const Vector3D &vectorA, const Vector3D &vectorB) {
  return Vector3D(vectorA.x * vectorB.x, vectorA.y * vectorB.y,
                  vectorA.z * vectorB.z);
}

Vector3D operator*(const Vector3D &vector, float coeff) {
  return Vector3D(vector.x * coeff, vector.y * coeff, vector.z * coeff);
}

Vector3D operator*(float coeff, const Vector3D &vector) {
  return Vector3D(vector.x * coeff, vector.y * coeff, vector.z * coeff);
}

Vector3D operator/(const Vector3D &vector, float coeff) {
  if (coeff != 0) {
    return Vector3D(vector.x / coeff, vector.y / coeff, vector.z / coeff);
  } else {
    printf("Vector3D: err divinding by 0\n");
    return Vector3D(0, 0, 0);
  }
}

void Vector3D::RotateX(float value) {
  float y_tmp;
  y_tmp = y * cosf(value) - z * sinf(value);
  z = y * sinf(value) + z * cosf(value);
  y = y_tmp;
}

void Vector3D::RotateXDeg(float value) { RotateX(Euler::ToRadian(value)); }

void Vector3D::RotateY(float value) {
  float x_tmp;
  x_tmp = x * cosf(value) + z * sinf(value);
  z = -x * sinf(value) + z * cosf(value);
  x = x_tmp;
}

void Vector3D::RotateYDeg(float value) { RotateY(Euler::ToRadian(value)); }

void Vector3D::RotateZ(float value) {
  float x_tmp;
  x_tmp = x * cosf(value) - y * sinf(value);
  y = x * sinf(value) + y * cosf(value);
  x = x_tmp;
}

void Vector3D::RotateZDeg(float value) { RotateZ(Euler::ToRadian(value)); }

void Vector3D::Rotate(const RotationMatrix &matrix) {
  float a[3] = {0, 0, 0};
  float b[3] = {x, y, z};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      a[i] += matrix.m[i][j] * b[j];
    }
  }

  x = a[0];
  y = a[1];
  z = a[2];
}

void Vector3D::Rotate(const Quaternion &quaternion) {
  RotationMatrix matrix;
  quaternion.ToRotationMatrix(matrix);
  Rotate(matrix);
}

void Vector3D::To2Dxy(Vector2D &vector) const {
  vector.x = x;
  vector.y = y;
}

Vector2D Vector3D::To2Dxy(void) const {
  Vector2D vect;
  To2Dxy(vect);
  return vect;
}

float Vector3D::GetNorm(void) const { return sqrt(x * x + y * y + z * z); }

void Vector3D::Normalize(void) {
  float n = GetNorm();
  if (n != 0) {
    x = x / n;
    y = y / n;
    z = z / n;
  }
}

void Vector3D::Saturate(const Vector3D &min, const Vector3D &max) {
  if (x < min.x)
    x = min.x;
  if (x > max.x)
    x = max.x;

  if (y < min.y)
    y = min.y;
  if (y > max.y)
    y = max.y;

  if (z < min.z)
    z = min.z;
  if (z > max.z)
    z = max.z;
}

void Vector3D::Saturate(float min, float max) {
  Saturate(Vector3D(min, min, min), Vector3D(max, max, max));
}

void Vector3D::Saturate(const Vector3D &value) {
  float x = fabs(value.x);
  float y = fabs(value.y);
  float z = fabs(value.z);
  Saturate(Vector3D(-x, -y, -z), Vector3D(x, y, z));
}

void Vector3D::Saturate(float value) {
  float sat = fabs(value);
  Saturate(Vector3D(-sat, -sat, -sat), Vector3D(sat, sat, sat));
}

} // end namespace core
} // end namespace flair
