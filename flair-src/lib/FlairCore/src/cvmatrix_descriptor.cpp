// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/05
//  filename:   cvmatrix_descriptor.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class describing cvmatrix elements, for log and graphs purpose
//
/*********************************************************************/

#include "cvmatrix_descriptor.h"
#include "FrameworkManager.h"

using std::string;

namespace flair {
namespace core {

cvmatrix_descriptor::cvmatrix_descriptor(uint32_t rows, uint32_t cols) {
  this->rows = rows;
  this->cols = cols;

  if (rows == 0 || cols == 0)
    getFrameworkManager()->Err("rows and cols must be >0\n");

  element_names = (string **)malloc(rows * cols * sizeof(string *));
  for (uint32_t i = 0; i < rows * cols; i++) {
    element_names[i] = new string();
  }
}

cvmatrix_descriptor::~cvmatrix_descriptor() {
  for (uint32_t i = 0; i < rows * cols; i++) {
    delete element_names[i];
  }
  free(element_names);
}

void cvmatrix_descriptor::SetElementName(uint32_t row, uint32_t col,
                                         string name) {
  if (row >= rows || col >= cols) {
    getFrameworkManager()->Err("index out of bound %s (%i,%i), range (%i,%i)\n",
                               name.c_str(), row, col, rows - 1, cols - 1);
    return;
  }
  *element_names[row * cols + col] = name;
}

string cvmatrix_descriptor::ElementName(uint32_t row, uint32_t col) const {
  if (row >= rows || col >= cols) {
    getFrameworkManager()->Err("index out of bound (%i,%i), range (%i,%i)\n",
                               row, col, rows - 1, cols - 1);
    return *element_names[0]; // safe value...
  }
  return *element_names[row * cols + col];
}

uint32_t cvmatrix_descriptor::Rows() const { return rows; }

uint32_t cvmatrix_descriptor::Cols() const { return cols; }

} // end namespace core
} // end namespace flair
