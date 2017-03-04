// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Vector2D.h
 * \brief Class defining a 2D vector
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/05/02
 * \version 4.0
 */

#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace flair {
namespace core {

/*! \class Vector2D
*
* \brief Class defining a 2D vector
*/
class Vector2D {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Vector2D using specified values.
  *
  * \param x
  * \param y
  */
  Vector2D(float x = 0, float y = 0);

  /*!
  * \brief Destructor
  *
  */
  ~Vector2D();

  /*!
  * \brief Rotation
  *
  * \param value rotation value in radians
  */
  void Rotate(float value);

  /*!
  * \brief Rotation
  *
  * \param value rotation value in degrees
  */
  void RotateDeg(float value);

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
  * \param min minimum Vector2D value
  * \param max maximum Vector2D value
  */
  void Saturate(Vector2D min, Vector2D max);

  /*!
  * \brief Saturate
  *
  * Saturate between min and max
  *
  * \param min minimum Vector2D(min,min) value
  * \param max maximum Vector2D(max,max) value
  */
  void Saturate(float min, float max);

  /*!
  * \brief Saturate
  *
  * Saturate between -abs(value) and abs(value)
  *
  * \param value saturation Vector2D value
  */
  void Saturate(const Vector2D &value);

  /*!
  * \brief Saturate
  *
  * Saturate between -abs(Vector2D(value,value)) and abs(Vector2D(value,value))
  *
  * \param value saturation Vector2D(value,value)
  */
  void Saturate(float value);

  /*!
  * \brief x
  */
  float x;

  /*!
  * \brief y
  */
  float y;

  Vector2D &operator=(const Vector2D &vector);
};

/*! Add
*
* \brief Add
*
* \param vectorA vector
* \param vectorB vector
*/
Vector2D operator+(const Vector2D &vectorA, const Vector2D &vectorB);

/*! Substract
*
* \brief Substract
*
* \param vectorA vector
* \param vectorB vector
*/
Vector2D operator-(const Vector2D &vectorA, const Vector2D &vectorB);

/*! Divid
*
* \brief Divid
*
* \param vector vector
* \param coeff coefficent
* \return vector/coefficient
*/
Vector2D operator/(const Vector2D &vector, float coeff);

/*! Multiply
*
* \brief Multiplyf
*
* \param vector vector
* \param coeff coefficent
* \return coefficient*vector
*/
Vector2D operator*(const Vector2D &vector, float coeff);

/*! Multiply
*
* \brief Multiply
*
* \param coeff coefficent
* \param vector vector
* \return coefficient*vector
*/
Vector2D operator*(float coeff, const Vector2D &vector);

} // end namespace core
} // end namespace flair

#endif // VECTOR2D_H
