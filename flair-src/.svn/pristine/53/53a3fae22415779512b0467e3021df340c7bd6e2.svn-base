// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Thread_impl.h
 * \brief Classe définissant un thread
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/10/04
 * \version 4.0
 */
#ifndef THREAD_IMPL_H
#define THREAD_IMPL_H

#include <string>
#include <stdint.h>
#include <Object.h>
#ifdef __XENO__
#include <native/task.h>
#else
#include <pthread.h>
#endif

namespace flair {
namespace core {
class Thread;
class IODevice;
class ConditionVariable;
}
}

class Thread_impl {
public:
  Thread_impl(flair::core::Thread *self, uint8_t priority);
  ~Thread_impl();
  void Start(void);
  void Join(void);
  void SafeStop(void);
  bool ToBeStopped(void);
  void SetPeriodUS(uint32_t period);
  uint32_t GetPeriodUS(void) const;
  void SetPeriodMS(uint32_t period);
  uint32_t GetPeriodMS(void) const;
  void WaitPeriod(void);
  void Suspend(void);
  bool SuspendUntil(flair::core::Time date);
  void Resume(void);
  bool IsSuspended(void);
  int WaitUpdate(const flair::core::IODevice *device);
  bool period_set;

private:
  flair::core::Thread *self;
  flair::core::ConditionVariable *cond;
  uint8_t priority;
  flair::core::Time max_jitter, min_jitter, mean_jitter;
  flair::core::Time last;
  uint64_t cpt;
  flair::core::Time period;
  bool isRunning;
  bool tobestopped;
  bool is_suspended;
  void PrintStats(void);
  void ComputeJitter(flair::core::Time time);
#ifdef __XENO__
  RT_TASK task_rt;
  static void main_rt(void *arg);
#else
  pthread_t task_nrt;
  static void *main_nrt(void *arg);
  flair::core::Time next_time;
#endif
};
#endif // THREAD_IMPL_H
