// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/10/04
//  filename:   Thread.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Abstract class for a thread
//
//
/*********************************************************************/

#include "Thread.h"
#include "Thread_impl.h"
#ifdef __XENO__
#include <native/timer.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

using std::string;

namespace flair {
namespace core {

Thread::Thread(const Object *parent, string name, uint8_t priority)
    : Object(parent, name, "Thread") {
  pimpl_ = new Thread_impl(this, priority);
}

Thread::~Thread() { delete pimpl_; }

void Thread::Start(void) { pimpl_->Start(); }

void Thread::SafeStop(void) { pimpl_->SafeStop(); }

bool Thread::ToBeStopped(void) const { return pimpl_->ToBeStopped(); }

#ifdef __XENO__
void Thread::WarnUponSwitches(bool value) {
  // Ask Xenomai to warn us upon switches to secondary mode.
  if (value == true) {
    rt_task_set_mode(0, T_WARNSW, NULL);
  } else {
    rt_task_set_mode(T_WARNSW, 0, NULL);
  }
}
#else
void Thread::WarnUponSwitches(bool value) {
  // Warn("Not applicable in non real time\n");
}
#endif

void Thread::Join(void) { pimpl_->Join(); }

void Thread::SetPeriodUS(uint32_t period) { pimpl_->SetPeriodUS(period); }

uint32_t Thread::GetPeriodUS(void) const { return pimpl_->GetPeriodUS(); }

void Thread::SetPeriodMS(uint32_t period) { pimpl_->SetPeriodMS(period); }

uint32_t Thread::GetPeriodMS(void) const { return pimpl_->GetPeriodMS(); }

bool Thread::IsPeriodSet(void) { return pimpl_->period_set; }

void Thread::WaitPeriod(void) const { pimpl_->WaitPeriod(); }

void Thread::Suspend(void) { pimpl_->Suspend(); }

bool Thread::SuspendUntil(Time date) { return pimpl_->SuspendUntil(date); }

bool Thread::IsSuspended(void) const { return pimpl_->IsSuspended(); }

void Thread::Resume(void) { pimpl_->Resume(); }

int Thread::WaitUpdate(const IODevice *device) {
  return pimpl_->WaitUpdate(device);
}

void Thread::SleepUntil(Time time) const {
#ifdef __XENO__
  int status = rt_task_sleep_until(time);
  if (status != 0)
    Err("%s, error rt_task_sleep_until (%s), resume time: %lld, actual time: "
        "%lld\n",
        ObjectName().c_str(), strerror(-status), time, GetTime());
// Printf("rt_task_sleep_until, resume time: %lld, actual time:
// %lld\n",time,GetTime());
#else
  Time current = GetTime();
  if (current < time) {
    usleep((time - current) / 1000);
  }
#endif
}

void Thread::SleepMS(uint32_t time) const {
#ifdef __XENO__
  int status = rt_task_sleep(time * 1000 * 1000);
  if (status != 0)
    Err("erreur rt_task_sleep (%s)\n", strerror(-status));
#else
  usleep(time * 1000);
#endif
}

void Thread::SleepUS(uint32_t time) const {
#ifdef __XENO__
  int status = rt_task_sleep(time * 1000);
  if (status != 0)
    Err("erreur rt_task_sleep (%s)\n", strerror(-status));
#else
  usleep(time);
#endif
}

} // end namespace core
} // end namespace flair
