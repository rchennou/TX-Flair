// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Mutex.h
 * \brief Class defining a mutex
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/14
 * \version 4.0
 */

#ifndef MUTEX_H
#define MUTEX_H

#include <Object.h>

class Mutex_impl;
class ConditionVariable_impl;

namespace flair {
namespace core {

/*! \class Mutex
*
* \brief Class defining a mutex
*
*/
class Mutex : public Object {
  friend class ::ConditionVariable_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a mutex.
  *
  * \param parent parent
  * \param name name
  */
  Mutex(const Object *parent, std::string name = "");

  /*!
  * \brief Destructor
  *
  */
  ~Mutex();

  /*!
  * \brief GetMutex
  *
  * Lock the mutex.
  *
  */
  void GetMutex(void) const;

  /*!
  * \brief ReleaseMutex
  *
  * Unlock the mutex.
  *
  */
  void ReleaseMutex(void) const;

private:
  class Mutex_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // MUTEX_H
