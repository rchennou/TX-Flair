// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/03/21
//  filename:   cvmatrix.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a matrix of kind CvMat
//
/*********************************************************************/

#include "cvmatrix.h"
#include "cvmatrix_impl.h"
#include <cxcore.h>
#include <typeinfo>

#include <iostream>

using std::string;

namespace flair {
namespace core {
/*! \class cvmatrixElement
*/
class cvmatrixElement : public IODataElement {
public:
  cvmatrixElement(const cvmatrix *matrix, string name, uint32_t row,
                  uint32_t col)
      : IODataElement(matrix, name) {
    this->matrix = matrix;
    this->row = row;
    this->col = col;
    if (row >= matrix->Rows() || col >= matrix->Cols()) {
      matrix->Err("index (%i,%i) out of bound (%i,%i)\n", row, col,
                  matrix->Rows() - 1, matrix->Cols() - 1);
      size = 0;
    } else {
      try {
        ScalarType const &scalarType = dynamic_cast<ScalarType const &>(
            matrix->GetDataType().GetElementDataType());
        size = scalarType.GetSize();
      } catch (std::bad_cast e) {
        matrix->Err("type not handled\n");
        size = 0;
      }
    }
  }

  ~cvmatrixElement() {}

  void CopyData(char *dst) const {
    if (typeid(matrix->GetDataType().GetElementDataType()) ==
        typeid(FloatType)) {
      float value = matrix->Value(row, col);
      memcpy(dst, &value, sizeof(value));
    } else if (typeid(matrix->GetDataType().GetElementDataType()) ==
               typeid(SignedIntegerType)) {
      switch (matrix->GetDataType().GetElementDataType().GetSize()) {
      case 1: {
        int8_t int8Value = matrix->Value(row, col);
        memcpy(dst, &int8Value, 1);
      } break;
      case 2: {
        int16_t int16Value = matrix->Value(row, col);
        memcpy(dst, &int16Value, 2);
      } break;
      }
    }
  }

  DataType const &GetDataType(void) const {
    return matrix->GetDataType().GetElementDataType();
  }

private:
  const cvmatrix *matrix;
  uint32_t row, col;
};

cvmatrix::cvmatrix(const Object *parent, uint32_t rows, uint32_t cols,
                   ScalarType const &elementDataType, string name, uint32_t n)
    : io_data(parent, name, n), dataType(rows, cols, elementDataType) {
  pimpl_ = new cvmatrix_impl(this, rows, cols, elementDataType, n);

  for (uint32_t i = 0; i < rows; i++) {
    for (uint32_t j = 0; j < cols; j++) {
      AppendLogDescription(pimpl_->descriptor->ElementName(i, j),
                           elementDataType);
      SetValue(i, j, 0);
    }
  }
}

cvmatrix::cvmatrix(const Object *parent, const cvmatrix_descriptor *descriptor,
                   ScalarType const &elementDataType, string name, uint32_t n)
    : io_data(parent, name, n),
      dataType(descriptor->Rows(), descriptor->Cols(), elementDataType) {
  pimpl_ = new cvmatrix_impl(this, descriptor, elementDataType, n);

  for (uint32_t i = 0; i < descriptor->Rows(); i++) {
    for (uint32_t j = 0; j < descriptor->Cols(); j++) {
      AppendLogDescription(descriptor->ElementName(i, j), elementDataType);
      SetValue(i, j, 0);
    }
  }
}

cvmatrix::~cvmatrix() { delete pimpl_; }

IODataElement *cvmatrix::Element(uint32_t row, uint32_t col) const {
  return new cvmatrixElement(this, Name(row, col), row, col);
}

IODataElement *cvmatrix::Element(uint32_t index) const {
  if (Rows() == 1) {
    return new cvmatrixElement(this, Name(0, index), 0, index);
  } else if (Cols() == 1) {
    return new cvmatrixElement(this, Name(index, 0), index, 0);
  } else {
    Err("matrix is not 1D\n");
    return nullptr;
  }
}

float cvmatrix::Value(uint32_t row, uint32_t col) const {
  float value;

  if (row >= (uint32_t)pimpl_->mat->rows ||
      col >= (uint32_t)pimpl_->mat->cols) {
    Warn("index (%i,%i) out of bound (%i,%i)\n", row, col,
         pimpl_->mat->rows - 1, pimpl_->mat->cols - 1);
    return 0;
  }

  GetMutex();
  value = cvGetReal2D(pimpl_->mat, row, col);
  ReleaseMutex();

  return value;
}

float cvmatrix::ValueNoMutex(uint32_t row, uint32_t col) const {
  if (row >= (uint32_t)pimpl_->mat->rows ||
      col >= (uint32_t)pimpl_->mat->cols) {
    Warn("index (%i,%i) out of bound (%i,%i)\n", row, col,
         pimpl_->mat->rows - 1, pimpl_->mat->cols - 1);
    return 0;
  }

  return cvGetReal2D(pimpl_->mat, row, col);
}

void cvmatrix::SetValue(uint32_t row, uint32_t col, float value) {
  if (row >= (uint32_t)pimpl_->mat->rows ||
      col >= (uint32_t)pimpl_->mat->cols) {
    Warn("index (%i,%i) out of bound (%i,%i)\n", row, col,
         pimpl_->mat->rows - 1, pimpl_->mat->cols - 1);
  } else {
    GetMutex();
    cvSetReal2D(pimpl_->mat, row, col, value);
    ReleaseMutex();
  }
}

void cvmatrix::SetValueNoMutex(uint32_t row, uint32_t col, float value) {
  if (row >= (uint32_t)pimpl_->mat->rows ||
      col >= (uint32_t)pimpl_->mat->cols) {
    Warn("index (%i,%i) out of bound (%i,%i)\n", row, col,
         pimpl_->mat->rows - 1, pimpl_->mat->cols - 1);
  } else {
    cvSetReal2D(pimpl_->mat, row, col, value);
  }
}

CvMat *cvmatrix::getCvMat(void) const { return pimpl_->mat; }

void cvmatrix::CopyDatas(char *dst) const {
  GetMutex();
  // printf("%f %x %i\n",cvGetReal2D(pimpl_->mat,0,0),dst,Size());
  memcpy(dst, pimpl_->mat->data.ptr, dataType.GetSize());
  ReleaseMutex();
}

uint32_t cvmatrix::Rows(void) const { return pimpl_->mat->rows; }

uint32_t cvmatrix::Cols(void) const { return pimpl_->mat->cols; }

string cvmatrix::Name(uint32_t row, uint32_t col) const {
  return pimpl_->descriptor->ElementName(row, col);
}

} // end namespace core
} // end namespace flair
