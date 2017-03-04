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

#include "Mutex_impl.h"
#include "Mutex.h"
#include <string.h>

using std::string;
using namespace flair::core;

Mutex_impl::Mutex_impl(Mutex *self) {
  this->self = self;
#ifdef __XENO__
  int status = rt_mutex_create(&mutex, NULL);
  if (status != 0)
    self->Err("rt_mutex_create error (%s)\n", strerror(-status));
#else
  // flag_locked=false;//revoir l'implementation nrt du is_locked
  pthread_mutexattr_t attr;
  if (pthread_mutexattr_init(&attr) != 0) {
    self->Err("pthread_mutexattr_init error\n");
  }
  if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0) {
    self->Err("pthread_mutexattr_settype error\n");
  }
  if (pthread_mutex_init(&mutex, &attr) != 0) {
    self->Err("pthread_mutex_init error\n");
  }
  if (pthread_mutexattr_destroy(&attr) != 0) {
    self->Err("pthread_mutexattr_destroy error\n");
  }
#endif
}

Mutex_impl::~Mutex_impl() {
  int status;
#ifdef __XENO__
  status = rt_mutex_delete(&mutex);
#else
  status = pthread_mutex_destroy(&mutex);
#endif
  if (status != 0)
    self->Err("error destroying mutex (%s)\n", strerror(-status));
}

void Mutex_impl::GetMutex(void) {
  int status;
#ifdef __XENO__
  status = rt_mutex_acquire(&mutex, TM_INFINITE);
#else
  // flag_locked=true;
  status = pthread_mutex_lock(&mutex);
#endif
  if (status != 0)
    self->Err("error (%s)\n", strerror(-status));
}

void Mutex_impl::ReleaseMutex(void) {
  int status;
#ifdef __XENO__
  status = rt_mutex_release(&mutex);
#else
  status = pthread_mutex_unlock(&mutex);
// flag_locked=false;
#endif
  if (status != 0)
    self->Err("error (%s)\n", strerror(-status));
}

/*
bool Mutex_impl::IsLocked(void)
{
#ifdef __XENO__
    RT_MUTEX_INFO info;
    int status=rt_mutex_inquire(&mutex_rt,&info);
    if(status!=0) mutex->Err("erreur rt_mutex_inquire
(%s)\n",strerror(-status));
    if(info.locked>0) return true;
    return false;
#else
    return flag_locked;
#endif
}
*/
