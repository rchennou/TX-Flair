// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/03/21
//  filename:   cvmatrix_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant le type de données "CvMat"
//
/*********************************************************************/

#include "cvmatrix.h"
#include "cvmatrix_impl.h"
#include <cxcore.h>
#include <typeinfo>
#include <sstream>

using std::string;
using namespace flair::core;

cvmatrix_impl::cvmatrix_impl(cvmatrix *self, int rows, int cols,
                             flair::core::ScalarType const &_elementDataType,
                             int n)
    : elementDataType(_elementDataType) {
  descriptor = new cvmatrix_descriptor(rows, cols);
  Init(self, n);
}

cvmatrix_impl::cvmatrix_impl(cvmatrix *self,
                             const cvmatrix_descriptor *descriptor,
                             flair::core::ScalarType const &_elementDataType,
                             int n)
    : elementDataType(_elementDataType) {
  this->descriptor = descriptor;
  Init(self, n);
}

void cvmatrix_impl::Init(cvmatrix *self, int n) {
  this->self = self;

  mat = nullptr;
  try {
    ScalarType const &scalarType =
        dynamic_cast<ScalarType const &>(elementDataType);
    if (typeid(scalarType) == typeid(FloatType)) {
      mat = cvCreateMat(descriptor->Rows(), descriptor->Cols(), CV_32FC1);
    } else if (typeid(scalarType) == typeid(SignedIntegerType)) {
      switch (elementDataType.GetSize()) {
      case 1:
        mat = cvCreateMat(descriptor->Rows(), descriptor->Cols(), CV_8SC1);
        break;
      case 2:
        mat = cvCreateMat(descriptor->Rows(), descriptor->Cols(), CV_16SC1);
        break;
      default:
        self->Err("unsupported integer scalar type\n");
      }
    } else {
      self->Err("unsupported scalar type\n");
    }
  } catch (std::bad_cast e) {
    self->Err("type is not a scalar\n");
  }

  if (mat == nullptr)
    self->Err("allocating matrix failed\n");
  if (n > 1)
    self->Warn("n>1 not supported\n");
}

cvmatrix_impl::~cvmatrix_impl() {
  cvReleaseMat(&mat);
  delete descriptor;
}
