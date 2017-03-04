// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/10
//  filename:   SharedMem.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a shared memory
//
//
/*********************************************************************/

#include "SharedMem.h"
#include "SharedMem_impl.h"

using std::string;

namespace flair {
namespace core {

SharedMem::SharedMem(const Object *parent, string name, size_t size)
    : Object(parent, name, "shmem") {
  pimpl_ = new SharedMem_impl(this, name, size);
}

SharedMem::~SharedMem() { delete pimpl_; }

void SharedMem::Write(const char *buf, size_t size) {
  pimpl_->Write(buf, size);
}

void SharedMem::Read(char *buf, size_t size) const { pimpl_->Read(buf, size); }

} // end namespace core
} // end namespace flair
