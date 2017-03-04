// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/05/02
//  filename:   Vector2D.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a 2D vector
//
//
/*********************************************************************/

#include "Vector2D.h"
#include "Euler.h"
#include <math.h>

namespace flair {
namespace core {

Vector2D::Vector2D(float inX, float inY) : x(inX), y(inY) {}

Vector2D::~Vector2D() {}

Vector2D &Vector2D::operator=(const Vector2D &vector) {
  x = vector.x;
  y = vector.y;
  return (*this);
}

Vector2D operator+(const Vector2D &vectorA, const Vector2D &vectorB) {
  return Vector2D(vectorA.x + vectorB.x, vectorA.y + vectorB.y);
}

Vector2D operator-(const Vector2D &vectorA, const Vector2D &vectorB) {
  return Vector2D(vectorA.x - vectorB.x, vectorA.y - vectorB.y);
}

Vector2D operator/(const Vector2D &vector, float coeff) {
  if (coeff != 0) {
    return Vector2D(vector.x / coeff, vector.y / coeff);
  } else {
    return Vector2D(0, 0);
  }
}

Vector2D operator*(const Vector2D &vector, float coeff) {
  return Vector2D(vector.x * coeff, vector.y * coeff);
}

Vector2D operator*(float coeff, const Vector2D &vector) {
  return Vector2D(vector.x * coeff, vector.y * coeff);
}

void Vector2D::Rotate(float value) {
  float xTmp;
  xTmp = x * cosf(value) - y * sinf(value);
  y = x * sinf(value) + y * cosf(value);
  x = xTmp;
}

void Vector2D::RotateDeg(float value) { Rotate(Euler::ToRadian(value)); }

float Vector2D::GetNorm(void) const { return sqrt(x * x + y * y); }

void Vector2D::Normalize(void) {
  float n = GetNorm();
  if (n != 0) {
    x = x / n;
    y = y / n;
  }
}

void Vector2D::Saturate(Vector2D min, Vector2D max) {
  if (x < min.x)
    x = min.x;
  if (x > max.x)
    x = max.x;

  if (y < min.y)
    y = min.y;
  if (y > max.y)
    y = max.y;
}

void Vector2D::Saturate(float min, float max) {
  Saturate(Vector2D(min, min), Vector2D(max, max));
}

void Vector2D::Saturate(const Vector2D &value) {
  float x = fabs(value.x);
  float y = fabs(value.y);
  Saturate(Vector2D(-x, -y), Vector2D(x, y));
}

void Vector2D::Saturate(float value) {
  float sat = fabs(value);
  Saturate(Vector2D(-sat, -sat), Vector2D(sat, sat));
}

} // end namespace core
} // end namespace flair
