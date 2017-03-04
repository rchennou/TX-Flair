// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Watchdog.h
 * \brief Watchdog Class
 * \author Gildas Bayard, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/02/25
 * \version 1.0
 */

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <Thread.h>
#include <functional>

namespace flair {
namespace core {

/*! \class Watchdog
*
* \brief Watchdog class
*
* Calls a given function if not touched within a specified period of time
*
*/
class Watchdog : public Thread {
public:
  Watchdog(const Object *parent, std::function<void()> _expired, Time _timer);
  ~Watchdog();

  // reset the timer
  void Touch();
  void SetTimer(Time _Timer);

private:
  void Run();
  std::function<void()> expired;
  Time timer;
};

} // end namespace core
} // end namespace flair

#endif // WATCHDOG_H
