// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}

/*!
 * \file Vector3D.h
 * \brief Class defining a 3D vector
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/05/02
 * \version 4.0
 */
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <stddef.h>

namespace flair {
namespace core {
class Vector2D;
class RotationMatrix;
class Quaternion;

/*! \class Vector3D
*
* \brief Class defining a 3D vector
*/
class Vector3D {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Vector3D using specified values.
  *
  * \param x
  * \param y
  * \param z
  */
  Vector3D(float x = 0, float y = 0, float z = 0);

  /*!
  * \brief Destructor
  *
  */
  ~Vector3D();

  /*!
  * \brief x
  */
  float x;

  /*!
  * \brief y
  */
  float y;

  /*!
  * \brief z
  */
  float z;

  /*!
  * \brief x axis rotation
  *
  * \param value rotation value in radians
  */
  void RotateX(float value);

  /*!
  * \brief x axis rotation
  *
  * \param value rotation value in degrees
  */
  void RotateXDeg(float value);

  /*!
  * \brief y axis rotation
  *
  * \param value rotation value in radians
  */
  void RotateY(float value);

  /*!
  * \brief y axis rotation
  *
  * \param value rotation value in degrees
  */
  void RotateYDeg(float value);

  /*!
  * \brief z axis rotation
  *
  * \param value rotation value in radians
  */
  void RotateZ(float value);

  /*!
  * \brief z axis rotation
  *
  * \param value rotation value in degrees
  */
  void RotateZDeg(float value);

  /*!
  * \brief rotation
  *
  * \param matrix rotation matrix
  */
  void Rotate(const RotationMatrix &matrix);

  /*!
  * \brief rotation
  *
  * Compute a rotation from a quaternion. This method uses a rotation matrix
  * internaly.
  *
  * \param quaternion quaternion
  */
  void Rotate(const Quaternion &quaternion);

  /*!
  * \brief Convert to a Vector2D
  *
  * Uses x and y coordinates.
  *
  * \param vector destination
  */
  void To2Dxy(Vector2D &vector) const;

  /*!
  * \brief Convert to a Vector2D
  *
  * Uses x and y coordinates.
  *
  * \return destination
  */
  Vector2D To2Dxy(void) const;

  /*!
  * \brief Norm
  *
  * \return value
  */
  float GetNorm(void) const;

  /*!
  * \brief Normalize
  */
  void Normalize(void);

  /*!
  * \brief Saturate
  *
  * Saturate between min and max
  *
  * \param min minimum value
  * \param max maximum value
  */
  void Saturate(const Vector3D &min, const Vector3D &max);

  /*!
  * \brief Saturate
  *
  * Saturate between min and max
  *
  * \param min minimum Vector3D(min,min,min) value
  * \param max maximum Vector3D(max,max,max) value
  */
  void Saturate(float min, float max);

  /*!
  * \brief Saturate
  *
  * Saturate between -abs(value) and abs(value)
  *
  * \param value saturation Vector3D value
  */
  void Saturate(const Vector3D &value);

  /*!
  * \brief Saturate
  *
  * Saturate between -abs(Vector3D(value,value,value)) and
  *abs(Vector3D(value,value,value))
  *
  * \param value saturation Vector3D(value,value,value)
  */
  void Saturate(float value);

  float &operator[](size_t idx);
  const float &operator[](size_t idx) const;
  Vector3D &operator=(const Vector3D &vector);
  Vector3D &operator+=(const Vector3D &vector);
  Vector3D &operator-=(const Vector3D &vector);

private:
};

/*! Add
*
* \brief Add
*
* \param vectorA vector
* \param vectorB vector
*
* \return vectorA+vectorB
*/
Vector3D operator+(const Vector3D &vectorA, const Vector3D &vectorB);

/*! Substract
*
* \brief Substract
*
* \param vectorA vector
* \param vectorB vector
*
* \return vectorA-vectorB
*/
Vector3D operator-(const Vector3D &vectorA, const Vector3D &vectorB);

/*! Minus
*
* \brief Minus
*
* \param vector vector
*
* \return -vector
*/
Vector3D operator-(const Vector3D &vector);

/*! Divid
*
* \brief Divid
*
* \param vector vector
* \param coeff coefficent
*
* \return vector/coefficient
*/
Vector3D operator/(const Vector3D &vector, float coeff);

/*! Hadamard product
*
* \brief Hadamard product
*
* \param vectorA vector
* \param vectorBA vector
*
* \return Hadamard product
*/
Vector3D operator*(const Vector3D &vectorA, const Vector3D &vectorB);

/*! Multiply
*
* \brief Multiply
*
* \param vector vector
* \param coeff coefficent
*
* \return coefficient*vector
*/
Vector3D operator*(const Vector3D &vector, float coeff);

/*! Multiply
*
* \brief Multiply
*
* \param coeff coefficent
* \param vector vector
*
* \return coefficient*vector
*/
Vector3D operator*(float coeff, const Vector3D &vector);

/*! Cross product
*
* \brief Cross product
*
* \param vectorA first vector
* \param vectorB second vector
*
* \return cross product
*/
Vector3D CrossProduct(const Vector3D &vectorA, const Vector3D &vectorB);

/*! Dot product
*
* \brief Dot product
*
* \param vectorA first vector
* \param vectorB second vector
*
* \return dot product
*/
float DotProduct(const Vector3D &vectorA, const Vector3D &vectorB);

} // end namespace core
} // end namespace flair

#endif // VECTOR3D_H
