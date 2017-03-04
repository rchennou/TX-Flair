// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/03/21
//  filename:   io_data.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Abstract class for data types
//
//
/*********************************************************************/

#include "io_data.h"
#include "io_data_impl.h"

using std::string;

namespace flair {
namespace core {

DummyType dummyType;
FloatType floatType;
DoubleType doubleType;
SignedIntegerType Int8Type(8);
SignedIntegerType Int16Type(16);
UnsignedIntegerType UInt8Type(8);
UnsignedIntegerType UInt16Type(16);

io_data::io_data(const Object *parent, string name, int n)
    : Mutex(parent, name) {
  pimpl_ = new io_data_impl(this, n);
}

io_data::~io_data() { delete pimpl_; }

void io_data::AppendLogDescription(string description,
                                   DataType const &datatype) {
  pimpl_->AppendLogDescription(description, datatype);
}

void io_data::SetDataTime(Time time) {
  GetMutex();
  pimpl_->time = time;
  ReleaseMutex();
}

Time io_data::DataTime(void) const {
  Time tmp;
  GetMutex();
  tmp = pimpl_->time;
  ReleaseMutex();
  return tmp;
}

const io_data *io_data::Prev(int n) const {
  if (n > 0)
    return prev->Prev(n - 1);
  else
    return this;
}

void io_data::SetPtrToCircle(void **ptr) { pimpl_->circle_ptr = ptr; }

} // end namespace core
} // end namespace flair
