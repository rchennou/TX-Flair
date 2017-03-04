// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/03/30
//  filename:   DiscreteTimeVariable.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    base class for discrete time variable
//
/*********************************************************************/

#ifndef DISCRETETIMEVARIABLE_H
#define DISCRETETIMEVARIABLE_H

#include <stdlib.h>

namespace flair {
namespace simulator {
template <typename T, size_t size> class DiscreteTimeVariable {
public:
  DiscreteTimeVariable(){};
  ~DiscreteTimeVariable(){};
  T &operator[](ssize_t idx) {
    if (idx > 0)
      idx = 0;
    if (idx < (ssize_t)(-size + 1))
      idx = -size + 1;
    return array[-idx];
  }
  const T &operator[](ssize_t idx) const {
    return const_cast<T &>(*this)[idx];
  };
  void Update(void) {
    for (int i = size - 1; i > 0; i--) {
      array[i] = array[i - 1];
    }
  }

private:
  T array[size];
};
} // end namespace simulator
} // end namespace flair
#endif // DISCRETETIMEVARIABLE_H
