// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Quaternion.h
 * \brief Class defining a quaternion
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/02/03
 * \version 4.0
 */
#ifndef QUATERNION_H
#define QUATERNION_H

namespace flair {
namespace core {
class Euler;
class Vector3D;
class RotationMatrix;

/*! \class Quaternion
*
* \brief Class defining a quaternion
*/
class Quaternion {
public:
  /*!
  * \brief Constructor
  *
  * Construct a quaternion using specified values.
  *
  * \param q0, scalar part
  * \param q1
  * \param q2
  * \param q3
  */
  Quaternion(float q0 = 1, float q1 = 0, float q2 = 0, float q3 = 0);

  /*!
  * \brief Destructor
  *
  */
  ~Quaternion();

  /*!
  * \brief Norm
  *
  * \return norm
  */
  float GetNorm(void) const;

  /*!
  * \brief Normalize
  */
  void Normalize(void);

  /*!
  * \brief Logarithm
  *
  * This method also Normalize the quaternion.
  *
  * \param logarithm output logarithm
  */
  void GetLogarithm(Vector3D &logarithm);

  /*!
  * \brief Logarithm
  *
  * This method also Normalize the quaternion.
  *
  * \return output logarithm
  */
  Vector3D GetLogarithm(void);

  /*!
  * \brief Conjugate
  */
  void Conjugate(void);

  /*!
  * \brief Conjugate
  *
  * \return Conjugate
  */
  Quaternion GetConjugate(void);

  /*!
  * \brief Derivative
  *
  * \param w angular speed
  *
  * \return derivative
  */
  Quaternion GetDerivative(const Vector3D &angularSpeed) const;

  /*!
  * \brief Derivate
  *
  * \param w rotationonal speed
  */
  void Derivate(const Vector3D &angularSpeed);

  /*!
  * \brief Convert to euler angles
  *
  * \param euler output euler angles
  */
  void ToEuler(Euler &euler) const;

  /*!
  * \brief Convert to euler angles
  *
  * \return euler angles
  */
  Euler ToEuler(void) const;

  /*!
  * \brief Convert to rotation matrix
  *
  * \param m output matrix
  */
  void ToRotationMatrix(RotationMatrix &matrix) const;

  /*!
  * \brief q0
  */
  float q0;

  /*!
  * \brief q1
  */
  float q1;

  /*!
  * \brief q2
  */
  float q2;

  /*!
  * \brief q3
  */
  float q3;

  Quaternion &operator+=(const Quaternion &quaternion);
  Quaternion &operator-=(const Quaternion &quaternion);
  Quaternion &operator=(const Quaternion &quaternion);
};

/*! Add
*
* \brief Add
*
* \param quaterniontA quaternion
* \param quaterniontB quaternion
*
* \return quaterniontA+quaterniontB
*/
Quaternion operator+(Quaternion const &quaterniontA,
                     Quaternion const &quaterniontB);

/*! Substract
*
* \brief Substract
*
* \param quaterniontA quaternion
* \param quaterniontB quaternion
*
* \return quaterniontA-quaterniontB
*/
Quaternion operator-(Quaternion const &quaternionA,
                     Quaternion const &quaterniontB);

/*! Minus
*
* \brief Minus
*
* \param quaternion quaternion
*
* \return -quaternion
*/
Quaternion operator-(const Quaternion &quaternion);

/*! Multiply
*
* \brief Multiply
*
* \param quaterniontA quaternion
* \param quaterniontB quaternion
*
* \return quaterniontA*quaterniontB
*/
Quaternion operator*(Quaternion const &quaternionA,
                     Quaternion const &quaterniontB);

/*! Multiply
*
* \brief Multiply
*
* \param coeff coefficient
* \param quat quaternion
*
* \return coeff*quat
*/
Quaternion operator*(float coeff, Quaternion const &quaternion);

/*! Multiply
*
* \brief Multiply
*
* \param quat quaternion
* \param coeff coefficient
*
* \return coeff*quat
*/
Quaternion operator*(Quaternion const &quaternion, float coeff);

} // end namespace core
} // end namespace flair

#endif // QUATERNION_H
