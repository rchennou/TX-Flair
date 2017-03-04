// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Thread.h
 * \brief Abstract class for a thread
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/10/04
 * \version 4.0
 */

#ifndef THREAD_H
#define THREAD_H

#include <Object.h>
#include <stdint.h>

class Thread_impl;

namespace flair {
namespace core {

class IODevice;

/*! \class Thread
*
* \brief Abstract class for a thread
*
* To implement a thread, Run() method must be reimplemented. \n
* When Start() is called, it will automatically call Run() reimplemented method.
* A thread can be periodic, in this case WaitPeriod() will block untill period
*is met.
* Thread can also e synnchronized with an IODevice, using WaitUpdate() method.
*\n
* Thread period is by default 100ms.
*/
class Thread : public Object {
  friend class ::Thread_impl;

public:
  /*!
  * \brief Constructor
  *
  * \param parent parent
  * \param name name
  * \param priority priority, should be >20 (<20 is reserved for internal use)
  */
  Thread(const Object *parent, std::string name,
         uint8_t priority); // priority>20, for real time only

  /*!
  * \brief Destructor
  *
  * If thread is started, SafeStop() and Join() will
  * be automatically called.
  *
  */
  virtual ~Thread();

  /*!
  * \brief Start the thread
  *
  */
  void Start(void);

  /*!
  * \brief Set a stop flag
  *
  * ToBeStopped() will return true after calling this method.
  */
  void SafeStop(void);

  /*!
  * \brief Set a stop flag
  *
  * Reimplemented Run() can poll this method to
  * determine when to stop the thread.
  *
  * \return true if SafeStop() was called
  */
  bool ToBeStopped(void) const;

  /*!
  * \brief Join the thread
  *
  * This method will block untill Run() returns.
  *
  */
  void Join(void);

  /*!
  * \brief Set the period in micro second
  *
  * After calling this method, IsPeriodSet will return true.
  *
  * \param period_us period in us
  */
  void SetPeriodUS(uint32_t period_us);

  uint32_t GetPeriodUS() const;

  /*!
  * \brief Set the period in milli second
  *
  * After calling this method, IsPeriodSet will return true.
  *
  * \param period_ums period in ms
  */
  void SetPeriodMS(uint32_t period_ms);

  uint32_t GetPeriodMS() const;

  /*!
  * \brief Returns if period was set
  *
  * \return true if a period was set using SetPeriodUS or SetPeriodMS
  * false otherwise
  */
  bool IsPeriodSet(void);

  /*!
  * \brief Wait the period
  *
  * This method will block untill period is met. \n
  * If no period was set (see SetPeriodUS, SetPeriodMS and IsPeriodSet), this
  *method
  * returns immediately.
  *
  */
  void WaitPeriod(void) const;

  /*!
  * \brief Wait update of an IODevice
  *
  * This method will block untill IODevice::ProcessUpdate
  * is called. \n
  * This method is usefull to synchronize a thread with an IODevice.
  *
  * \param device IODevice to wait update from
  */
  int WaitUpdate(const IODevice *device);

  /*!
  * \brief Suspend the thread
  *
  * This method will block untill Resume() is called.
  *
  */
  void Suspend(void);

  /*!
  * \brief Suspend the thread with timeout
  *
  * This method will block until Resume() is called or the absolute date
  *specified occurs
  *
  * \param date absolute date in ns
  * \return true if thread is woken up by a call to Resume, false otherwise
  */
  bool SuspendUntil(Time date);

  /*!
  * \brief Resume the thread
  *
  * This method will unblock the call to Suspend().
  *
  */
  void Resume(void);

  /*!
  * \brief Is the thread suspended?
  *
  * \return true if thread is suspended
  *
  */
  bool IsSuspended(void) const;

  /*!
  * \brief Sleep until absolute time
  *
  * This method will block untill time is reached.
  *
  * \param time absolute time
  */
  void SleepUntil(Time time) const;

  /*!
  * \brief Sleep for a certain time in micro second
  *
  * This method will block untill time is elapsed.
  *
  * \param time_us time to wait in micro second
  */
  void SleepUS(uint32_t time_us) const;

  /*!
  * \brief Sleep for a cartain time in milli second
  *
  * This method will block untill time is elapsed.
  *
  * \param time_ms time to wait in milli second
  */
  void SleepMS(uint32_t time_ms) const;

  /*!
  * \brief Warn if real time / non real time switches occur
  *
  * If enabled, a message with the call stack will be displayed
  * in case of real time / non real time switches. \n
  * This method can help to debug application and see if switches occur. \n
  * Note that it as no effect if this method is called from the non real time
  * Framework library.
  *
  * \param enable enable or disable warns
  */
  static void WarnUponSwitches(bool enable);

private:
  /*!
  * \brief Run method
  *
  * This method is automatically called by Start(). \n
  * This method must be reimplemented, in order to implement the thread.
  *
  */
  virtual void Run(void) = 0;

  class Thread_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // THREAD_H
