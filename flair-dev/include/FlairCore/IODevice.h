// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
// ---
/*!
 * \file IODevice.h
 * \brief Abstract class for input/ouput system
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef IO_DEVICE_H
#define IO_DEVICE_H

#include <Object.h>

class IODevice_impl;
class Thread_impl;
class FrameworkManager_impl;

namespace flair {
namespace core {

class io_data;
class DataType;

/*! \class IODevice
*
* \brief Abstract class for input/ouput system
*
* An input/output system is generally used to describe a sensor, an actuator or
*a filter. \n
* These systems can be linked (for exemple a sensor with a filter), when an
*IODevice
* is created with a parent of type IODevice.
* In this case, an update of the parent's data will call an update
* of the child's data (for exemple when a sensor gets new datas, a filter is
*automatically called). \n
* Output of this object can also be sent to a shared memory using the
*OutputToShMem method; in order to use it with an
* external program.
*/
class IODevice : public Object {
  friend class ::IODevice_impl;
  friend class ::Thread_impl;
  friend class ::FrameworkManager_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct an IODevice of Object's type "IODevice" (see Object::ObjectType).
  *\n
  * If parent's Object::ObjectType is also "IODevice", this IODevice will be
  *linked to its parent
  * (see ProcessUpdate()).
  *
  * \param parent parent
  * \param name name
  */
  IODevice(const Object *parent, std::string name);

  /*!
  * \brief Destructor
  *
  */
  virtual ~IODevice();

  /*!
  * \brief Add an IODevice to the logs
  *
  * The IODevice will be automatically logged among this IODevice logs,
  * if logging is enabled (see SetDataToLog(), FrameworkManager::StartLog
  * and FrameworkManager::AddDeviceToLog). \n
  * Logging happens when ProcessUpdate() is called. \n
  * Note that when an IODevice is just added for logs (ie. no parent/child
  * link between the two IODevice),
  * UpdateFrom() is not automatically called.
  *
  * \param device IODevice to log
  */
  void AddDeviceToLog(const IODevice *device);

  /*!
  * \brief Add an io_data to the log
  *
  * The io_data will be automatically logged if enabled (see
  *FrameworkManager::StartLog
  * and FrameworkManager::AddDeviceToLog),
  * during call to ProcessUpdate().
  *
  * \param data data to log
  */
  void AddDataToLog(const io_data *data);

  /*!
  * \brief Send the output to a shared memory
  *
  * Use this method to output log datas to a shared memory.
  * This can be usefull to get datas from an external progam. \n
  * Output happens when ProcessUpdate() is called. \n
  * The name and the structure of the shared memory will be displayed when
  * this method is called with true as argument. \n
  * By default it is not enabled.
  *
  *
  * \param enabled true to enable the output, false otherwise
  */
  void OutputToShMem(bool enabled);

  // TODO: these 2 method should be pure virtual
  virtual DataType const &GetInputDataType() const;
  virtual DataType const &GetOutputDataType() const;

            Time lastUpdate;
        protected:
            /*!
            * \brief Process the childs of type IODevice, and log if needed
            *
            * This method must be called after computing datas;
            * generally at the end of the reimplemented UpdateFrom or after acquiring datas in case of a sensor. \n
            * It will call UpdateFrom methods of each child of type IODevice,
            * and log all datas (this IODevice and its childs)
            * if logging is enabled (see SetDataToLog(), AddDeviceToLog(),
            * FrameworkManager::StartLog and FrameworkManager::AddDeviceToLog). \n
            * If a thread is waiting on this IODevice (see Thread::WaitUpdate), it will be resumed.
            *
            * \param data data to process
            */
            void ProcessUpdate(io_data* data);

private:
  /*!
  * \brief Update using provided datas
  *
  * This method is automatically called by ProcessUpdate()
  * of the Object::Parent's if its Object::ObjectType is "IODevice". \n
  * This method must be reimplemented, in order to process the data from the
  *parent.
  *
  * \param data data from the parent to process
  */
  virtual void UpdateFrom(const io_data *data) = 0;

  class IODevice_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // IO_DEVICE_H
