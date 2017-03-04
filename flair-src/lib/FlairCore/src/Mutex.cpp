// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/03/14
//  filename:   Mutex.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a mutex
//
//
/*********************************************************************/

#include "Mutex.h"
#include "Mutex_impl.h"

using std::string;

namespace flair {
namespace core {

Mutex::Mutex(const Object *parent, string name)
    : Object(parent, name, "mutex") {
  pimpl_ = new Mutex_impl(this);
}

Mutex::~Mutex() { delete pimpl_; }

void Mutex::GetMutex(void) const { pimpl_->GetMutex(); }

void Mutex::ReleaseMutex(void) const { pimpl_->ReleaseMutex(); }

/*
bool Mutex::IsLocked(void)
{
    return pimpl_->IsLocked();
}
*/

} // end namespace core
} // end namespace flair
