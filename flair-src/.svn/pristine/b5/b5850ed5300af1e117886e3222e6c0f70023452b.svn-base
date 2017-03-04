// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ConditionVariable.h
 * \brief Class defining a condition variable
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/07
 * \version 4.0
 */

#ifndef CONDITIONVARIABLE_H
#define CONDITIONVARIABLE_H

#include <Mutex.h>

class ConditionVariable_impl;

namespace flair {
namespace core {

/*! \class ConditionVariable
*
* \brief Class defining a condition variable
*
*/

class ConditionVariable : public Mutex {
public:
  /*!
  * \brief Constructor
  *
  * Construct a condition variable with its associated mutex.
  *
  * \param parent parent
  * \param name name
  */
  ConditionVariable(const Object *parent, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~ConditionVariable();

  /*!
  * \brief Block on the condition variable
  *
  * This method must be called with mutex locked (see Mutex::GetMutex) by the
  *calling thread or undefined behaviour will result. \n
  * It atomically releases mutex and causes the calling thread to block on the
  *condition variable. \n
  * Only one thread can be blocked at the same time. \n
  * Upon successful return, the mutex has been locked and is owned by the
  *calling thread which should unlock it (see Mutex::ReleaseMutex).
  */
  void CondWait(void);

  /*!
  * \brief Block on the condition variable with a timeout
  *
  * This method must be called with mutex locked (see Mutex::GetMutex) by the
  *calling thread or undefined behaviour will result. \n
  * It atomically releases mutex and causes the calling thread to block on the
  *condition variable. \n
  * Only one thread can be blocked at the same time. \n
  * Upon successful return, the mutex has been locked and is owned by the
  *calling thread which should unlock it (see Mutex::ReleaseMutex).
  *
  * \param date absolute date
  * \return true if the condition variable is signaled before the date specified
  *in parameter elapses, false otherwise
  */
  bool CondWaitUntil(Time date);

  /*!
  * \brief Unblock threads blocked on the condition variable
  *
  * This method should be called with mutex locked (see Mutex::GetMutex) by the
  *calling thread. \n
  * In this case, upon return, the calling thread should unlock the mutex (see
  *Mutex::ReleaseMutex).
  *
  */
  void CondSignal(void);

private:
  class ConditionVariable_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // CONDITIONVARIABLE_H
