// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/07
//  filename:   ConditionVariable_impl.cpp
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

#include "ConditionVariable_impl.h"
#include "ConditionVariable.h"
#include "Mutex_impl.h"
#include <string.h>

using std::string;
using namespace flair::core;

ConditionVariable_impl::ConditionVariable_impl(ConditionVariable *self) {
  this->self = self;
  int status;

#ifdef __XENO__
  status = rt_cond_create(&m_ResumeCond, NULL);
#else
  status = pthread_cond_init(&m_ResumeCond, 0);
#endif
  if (status != 0)
    self->Err("error creating condition variable (%s)\n", strerror(-status));
}

ConditionVariable_impl::~ConditionVariable_impl() {
  int status;

#ifdef __XENO__
  status = rt_cond_delete(&m_ResumeCond);
#else
  status = pthread_cond_destroy(&m_ResumeCond);
#endif
  if (status != 0)
    self->Err("error destroying condition variable (%s)\n", strerror(-status));
}

void ConditionVariable_impl::CondWait(void) {
  int status;
#ifdef __XENO__
  status =
      rt_cond_wait(&m_ResumeCond, &self->Mutex::pimpl_->mutex, TM_INFINITE);
#else
  status = pthread_cond_wait(&m_ResumeCond, &self->Mutex::pimpl_->mutex);
#endif
  if (status != 0)
    self->Err("error (%s)\n", strerror(-status));
}

bool ConditionVariable_impl::CondWaitUntil(Time date) {
  int status;
#ifdef __XENO__
  status = rt_cond_wait_until(&m_ResumeCond, &self->Mutex::pimpl_->mutex, date);
#else
  struct timespec restrict;
  restrict.tv_sec = date / 1000000000;
  restrict.tv_nsec = date % 1000000000;
  status = pthread_cond_timedwait(&m_ResumeCond, &self->Mutex::pimpl_->mutex,
                                  &restrict);
#endif
  if (status == 0)
    return true;
  if (status != ETIMEDOUT)
    self->Err("error (%s)\n", strerror(-status));
  return false;
}

void ConditionVariable_impl::CondSignal(void) {
  int status;
#ifdef __XENO__
  status = rt_cond_signal(&m_ResumeCond);
#else
  status = pthread_cond_signal(&m_ResumeCond);
#endif
  if (status != 0)
    self->Err("error (%s)\n", strerror(-status));
}
