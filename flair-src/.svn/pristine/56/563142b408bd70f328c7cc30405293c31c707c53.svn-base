// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ConditionVariable_impl.h
 * \brief Class defining a condition variable
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/07
 * \version 4.0
 */

#ifndef CONDITIONVARIABLE_IMPL_H
#define CONDITIONVARIABLE_IMPL_H

#include "Object.h"
#ifdef __XENO__
#include <native/cond.h>
#include <native/timer.h>
#else
#include <pthread.h>
#endif

namespace flair {
namespace core {
class ConditionVariable;
}
}

/*! \class ConditionVariable_impl
* \brief Class defining a condition variable
*
*/
class ConditionVariable_impl {

public:
  ConditionVariable_impl(flair::core::ConditionVariable *self);
  ~ConditionVariable_impl();
  void CondWait(void);
  bool CondWaitUntil(flair::core::Time date);
  void CondSignal(void);

private:
  flair::core::ConditionVariable *self;
#ifdef __XENO__
  RT_COND m_ResumeCond;
#else
  pthread_cond_t m_ResumeCond;
#endif
};

#endif // CONDITIONVARIABLE_IMPL_H
