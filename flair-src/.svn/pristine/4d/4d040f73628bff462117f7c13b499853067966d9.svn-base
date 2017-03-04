// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/10/04
//  filename:   Thread_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe implementant un thread rt ou non
//
//
/*********************************************************************/

#include "Thread_impl.h"
#include "Thread.h"
#include "IODevice.h"
#include "IODevice_impl.h"
#include "ConditionVariable.h"
#include "config.h"
#include "FrameworkManager.h"
#include <string.h>
#ifdef __XENO__
#include <rtdk.h>
#else
#include <sys/resource.h>
#include <unistd.h>
#include <sys/syscall.h>
#endif

using std::string;
using namespace flair::core;

Thread_impl::Thread_impl(Thread *self, uint8_t priority) {
  isRunning = false;
  tobestopped = false;
  is_suspended = false;
  period_set = false;

  this->self = self;
  cond = new ConditionVariable(self, self->ObjectName());

  if (priority < MIN_THREAD_PRIORITY) {
    priority = MIN_THREAD_PRIORITY;
    //        printf("Thread::Thread, %s: priority set to
    //        %i\n",self->ObjectName().c_str(), priority);
  }
  if (priority > MAX_THREAD_PRIORITY) {
    priority = MAX_THREAD_PRIORITY;
    self->Warn("priority set to %i\n", MAX_THREAD_PRIORITY);
  }

  this->priority = priority;
  period = 100 * 1000 * 1000; // 100ms par defaut
  min_jitter = 1000 * 1000 * 1000;
  max_jitter = 0;
  mean_jitter = 0;
  last = 0;
  cpt = 0;
}

Thread_impl::~Thread_impl() {
  SafeStop();
  Join();
}

void Thread_impl::Start(void) {
  int status;

  isRunning = true;
  tobestopped = false;
  is_suspended = false;

#ifdef __XENO__
  string th_name =
      getFrameworkManager()->ObjectName() + "-" + self->ObjectName();

#ifdef RT_STACK_SIZE
  status = rt_task_create(&task_rt, th_name.c_str(), RT_STACK_SIZE,
                          (int)priority, T_JOINABLE);
#else
  status =
      rt_task_create(&task_rt, th_name.c_str(), 0, (int)priority, T_JOINABLE);
#endif // RT_STACK_SIZE
  if (status != 0) {
    self->Err("rt_task_create error (%s)\n", strerror(-status));
  } else {
    //_printf("rt_task_create ok %s\n",th_name);
  }

  status = rt_task_start(&task_rt, &main_rt, (void *)this);
  if (status != 0) {
    self->Err("rt_task_start error (%s)\n", strerror(-status));
  } else {
    //_printf("rt_task_start ok %s\n",th_name);
  }

  // Initialise the rt_print buffer for this task explicitly
  rt_print_init(512, th_name.c_str());

#else //__XENO__

  // Initialize thread creation attributes
  pthread_attr_t attr;
  if (pthread_attr_init(&attr) != 0) {
    self->Err("Error pthread_attr_init\n");
  }

#ifdef NRT_STACK_SIZE
  if (pthread_attr_setstacksize(&attr, NRT_STACK_SIZE) != 0) {
    self->Err("Error pthread_attr_setstacksize\n");
  }
#endif // NRT_STACK_SIZE

  if (pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) != 0) {
    self->Err("Error pthread_attr_setinheritsched\n");
  }

  if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
    self->Err("Error pthread_attr_setschedpolicy\n");
  }

  struct sched_param parm;
  parm.sched_priority = priority;
  if (pthread_attr_setschedparam(&attr, &parm) != 0) {
    self->Err("Error pthread_attr_setschedparam\n");
  }

  next_time = GetTime() + period;

  if (pthread_create(&task_nrt, &attr, main_nrt, (void *)this) != 0) {
    self->Err("pthread_create error\n");
  }

  if (pthread_attr_destroy(&attr) != 0) {
    self->Err("Error pthread_attr_destroy\n");
  }

#endif //__XENO__
}

#ifdef __XENO__
void Thread_impl::main_rt(void *arg) {
  Thread_impl *caller = (Thread_impl *)arg;

  // Perform auto-init of rt_print buffers if the task doesn't do so
  rt_print_auto_init(1);

  caller->self->Run();

  caller->PrintStats();
}
#else
void* Thread_impl::main_nrt(void * arg)
{
    Thread_impl *caller = (Thread_impl*)arg;
/*string th_name=getFrameworkManager()->ObjectName()+ "-" + caller->self->ObjectName();
caller->self->Info("pthread '%s' created with TID %x\n",th_name.c_str(),(pid_t)syscall(SYS_gettid));*/

  caller->self->Run();

  caller->PrintStats();

  pthread_exit(0);
}
#endif //__XENO__

void Thread_impl::SetPeriodUS(uint32_t period) {
  if (period == 0) {
    self->Err("Period must be>0\n");
    return;
  }

#ifdef __XENO__
  int status = rt_task_set_periodic(&task_rt, TM_NOW, period * 1000);
  if (status != 0)
    self->Err("Error rt_task_set_periodic %s\n", strerror(-status));
#else
  next_time -= period;
  next_time += period * 1000;
#endif
  this->period = period * 1000;
  period_set = true;
}

uint32_t Thread_impl::GetPeriodUS() const { return this->period / 1000; }

void Thread_impl::SetPeriodMS(uint32_t period) {
  if (period == 0) {
    self->Err("Period must be>0\n");
    return;
  }

#ifdef __XENO__
  int status = rt_task_set_periodic(&task_rt, TM_NOW, period * 1000 * 1000);
  if (status != 0)
    self->Err("Error rt_task_set_periodic %s\n", strerror(-status));
#else
  next_time -= period;
  next_time += period * 1000 * 1000;
#endif
  this->period = period * 1000 * 1000;
  period_set = true;
}

uint32_t Thread_impl::GetPeriodMS() const { return this->period / 1000 / 1000; }

void Thread_impl::WaitPeriod(void) {
  if (period_set == false) {
    self->Err("Period must be set befaore calling this method\n");
    return;
  }
#ifdef __XENO__
  unsigned long overruns_r;
  int status = rt_task_wait_period(&overruns_r);
  if (status != 0)
    self->Err("Error rt_task_wait_period %s\n", strerror(-status));
  if (status == -ETIMEDOUT)
    self->Err("overrun: %lld\n", overruns_r);
#else
  self->SleepUntil(next_time);
  next_time += period;
#endif
  ComputeJitter(GetTime());
}

void Thread_impl::Suspend(void) {
  if (isRunning == false) {
    self->Err("thread is not started\n");
    return;
  }

  cond->GetMutex(), is_suspended = true;
  cond->CondWait();
  is_suspended = false;
  cond->ReleaseMutex();
}

bool Thread_impl::SuspendUntil(Time date) {
  if (isRunning == false) {
    self->Err("thread is not started\n");
    return false;
  }

  cond->GetMutex(), is_suspended = true;
  bool success = cond->CondWaitUntil(date);
  is_suspended = false;
  cond->ReleaseMutex();
  return success;
}

bool Thread_impl::IsSuspended(void) {
  bool result;

  cond->GetMutex();
  result = is_suspended;
  cond->ReleaseMutex();

  return result;
}

void Thread_impl::Resume(void) {
  if (isRunning == false) {
    self->Err("thread is not started\n");
    return;
  }

  cond->GetMutex();
  if (is_suspended == true) {
    cond->CondSignal();
  } else {
    self->Err("thread is not suspended\n");
  }
  cond->ReleaseMutex();
}

int Thread_impl::WaitUpdate(const IODevice *device) {
  int status = 0;

  if (IsSuspended() == true) {
    self->Err("thread is already supended\n");
    status = -1;
  } else {
    cond->GetMutex();

    if (device->pimpl_->SetToWake(self) == 0) {
      is_suspended = true;
      cond->CondWait();
      is_suspended = false;
    } else {
      self->Err("%s is already waiting an update\n",
                device->ObjectName().c_str());
      status = -1;
    }

    cond->ReleaseMutex();
  }

  return status;
}

void Thread_impl::PrintStats(void) {
#ifdef __XENO__
  RT_TASK_INFO info;

  int status = rt_task_inquire(NULL, &info);
  if (status != 0) {
    self->Err("Error rt_task_inquire %s\n", strerror(-status));
  } else
#endif
  {
#ifndef __XENO__
// if(last!=0)
#endif
    { Printf("Thread::%s :\n", self->ObjectName().c_str()); }
#ifdef __XENO__
    Printf("    number of context switches: %i\n", info.ctxswitches);
    Printf("    number of primary->secondary mode switch: %i\n",
           info.modeswitches);
    // printf("number of page faults: %i\n",info.pagefaults);
    Printf("    execution time (ms) in primary mode: %lld\n",
           info.exectime / 1000000);
#else
/*
        struct rusage r_usage;
        getrusage(RUSAGE_THREAD,&r_usage);
        printf("    memory usage = %ld\n",r_usage.ru_maxrss);
        printf("RUSAGE :ru_utime => %lld [sec] : %lld [usec], :ru_stime => %lld
   [sec] : %lld [usec] \n",
           (int64_t)r_usage.ru_utime.tv_sec, (int64_t)r_usage.ru_utime.tv_usec,
           (int64_t)r_usage.ru_stime.tv_sec,
   (int64_t)r_usage.ru_stime.tv_usec);*/
#endif
    if (last != 0) {
      Printf("    min jitter (ns): %lld\n", min_jitter);
      Printf("    max jitter (ns): %lld\n", max_jitter);
      Printf("    jitter moy (ns): %lld\n", mean_jitter / cpt);
      Printf("    itertions: %lld\n", cpt);
    }
  }
}

void Thread_impl::Join(void) {
  if (isRunning == true) {
    int status;

#ifdef __XENO__
    status = rt_task_join(&task_rt);
#else
    status = pthread_join(task_nrt, NULL);
#endif
    if (status != 0)
      self->Err("error %s\n", strerror(-status));
    isRunning = false;
  }
}

void Thread_impl::ComputeJitter(Time time) {
  Time diff, delta;
  diff = time - last;

  if (diff >= period) {
    delta = diff - period;
  } else {
    delta = period - diff;
  }
  // if(delta==0) rt_printf("%lld %lld\n",time,last);
  last = time;
  if (diff == time)
    return;

  if (delta > max_jitter)
    max_jitter = delta;
  if (delta < min_jitter)
    min_jitter = delta;
  mean_jitter += delta;
  cpt++;

  // Printf("Thread::%s jitter moy (ns):
  // %lld\n",self->ObjectName().c_str(),mean_jitter/cpt);
}

void Thread_impl::SafeStop(void) {
  tobestopped = true;
  if (IsSuspended())
    Resume();
}

bool Thread_impl::ToBeStopped(void) { return tobestopped; }
