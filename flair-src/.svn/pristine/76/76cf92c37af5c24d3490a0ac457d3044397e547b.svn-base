// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file cvmatrix_impl.h
 * \brief Classe définissant une matrice opencv
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/21
 * \version 4.0
 */

#ifndef CVMATRIX_IMPL_H
#define CVMATRIX_IMPL_H

#include <io_data.h>
#include <cvmatrix.h>

struct CvMat;

/*! \class cvmatrix_impl
* \brief Classe définissant une matrice opencv
*
*/
class cvmatrix_impl {
public:
  cvmatrix_impl(flair::core::cvmatrix *self, int rows, int cols,
                flair::core::ScalarType const &elementDataType, int n);
  cvmatrix_impl(flair::core::cvmatrix *self,
                const flair::core::cvmatrix_descriptor *descriptor,
                flair::core::ScalarType const &elementDataType, int n);
  ~cvmatrix_impl();

  CvMat *mat;
  flair::core::ScalarType const &elementDataType;
  // const since if element description is modified it would be a mess in the
  // log
  const flair::core::cvmatrix_descriptor *descriptor;

private:
  flair::core::cvmatrix *self;
  void Init(flair::core::cvmatrix *self, int n);
};

#endif // CVMATRIX_IMPL_H
