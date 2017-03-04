// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Mutex_impl.h
 * \brief Class defining a mutex
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/14
 * \version 4.0
 */

#ifndef MUTEX_IMPL_H
#define MUTEX_IMPL_H

#ifdef __XENO__
#include <native/mutex.h>
#else
#include <pthread.h>
#endif

namespace flair {
namespace core {
class Mutex;
}
}

class Mutex_impl {
public:
  Mutex_impl(flair::core::Mutex *self);
  ~Mutex_impl();
  void GetMutex(void);
  void ReleaseMutex(void);
//        bool IsLocked(void);
#ifdef __XENO__
  RT_MUTEX mutex;
#else
  pthread_mutex_t mutex;
// bool flag_locked;
#endif

private:
  flair::core::Mutex *self;
};

#endif // MUTEX_IMPL_H
