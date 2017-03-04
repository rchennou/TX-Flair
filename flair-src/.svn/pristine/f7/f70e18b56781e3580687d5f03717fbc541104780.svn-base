// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/07
//  filename:   ConditionVariable.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a condition variable
//
//
/*********************************************************************/

#include "ConditionVariable.h"
#include "ConditionVariable_impl.h"

using std::string;

namespace flair {
namespace core {

ConditionVariable::ConditionVariable(const Object *parent, string name)
    : Mutex(parent, name) {
  pimpl_ = new ConditionVariable_impl(this);
}

ConditionVariable::~ConditionVariable() { delete pimpl_; }

void ConditionVariable::CondWait(void) { pimpl_->CondWait(); }

bool ConditionVariable::CondWaitUntil(Time date) {
  return pimpl_->CondWaitUntil(date);
}

void ConditionVariable::CondSignal(void) { pimpl_->CondSignal(); }

} // end namespace core
} // end namespace flair
