// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/02/25
//  filename:   Watchdog.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Watchdog class
//
/*********************************************************************/

#include "Watchdog.h"

namespace flair {
namespace core {

Watchdog::Watchdog(const Object *parent, std::function<void()> _expired,
                   Time _timer)
    : Thread(parent, "watchdog", 0), expired(_expired), timer(_timer) {}

Watchdog::~Watchdog() {
  SafeStop();
  Join();
}

void Watchdog::Touch() {
  if (IsSuspended())
    Resume();
}

void Watchdog::SetTimer(Time _Timer) {
  timer = _Timer;
  Touch();
}

void Watchdog::Run() {
  while (!ToBeStopped()) {
    Time current = GetTime();
    Time date = current + timer;
    // Printf("watchdog goes to sleep at %llu, scheduled to wake up at
    // %llu\n",current,date);
    if (!SuspendUntil(date)) {
      expired();
    }
  }
};

} // end namespace core
} // end namespace flair
