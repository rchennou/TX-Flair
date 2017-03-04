// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file FrameworkManager.h
 * \brief Main class of the Framework library
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/08/31
 * \version 4.0
 */

#ifndef FRAMEWORKMANAGER_H
#define FRAMEWORKMANAGER_H

#include <Object.h>

class FrameworkManager_impl;

namespace flair {
  namespace gui {
    class TabWidget;
    class SendData;
  }
}
namespace flair {
namespace core {
class IODevice;

/*! \class FrameworkManager
*
* \brief Main class of the Framework library
*
* This is the main class of the library. Only one instance of this class is
*allowed
* by program. Morevoer, its name must be unique if more than one program using
*this class
* is running on the same system (a control and a simlator for example). \n
* This class allows: \n
* -connexion with ground station, \n
* -creation of a QTabWidget on ground station, \n
* -handling of xml files, used for default values of Widgets, \n
* -logging of datas.
*/
class FrameworkManager : public Object {
public:
  /*!
  * \brief Constructor
  *
  * Construct a FrameworkManager. \n
  * Call SetupConnection method just after this constructor to setup the
  *conection with a ground station.
  *
  * \param name name, must be unique
  */
  FrameworkManager(std::string name);

  /*!
  * \brief Destructor
  *
  * Calling it will automatically destruct all childs. \n
  * Destruction implies destruction of the QTabWidget on ground station.
  *
  */
  ~FrameworkManager();

  /*!
  * \brief Setup the connection with ground station
  *
  * Call this method just after the constructor of this class. If this method is
  * not called, the program will run headless.
  * If this method is called, SetupUserInterface must also be called after this.
  *
  * \param address address of ground station
  * \param port port of ground station
  * \param watchdogTimeout watchdog timeout for the connection, passing TIME_INFINITE will disable the watchdog
  * \param rcv_buf_size receive buffer size
  */
  void SetupConnection(std::string address, uint16_t port,Time watchdogTimeout=(Time)1000000000,
                       size_t rcv_buf_size = 10000);

  /*!
  * \brief Setup the user interface
  *
  * If this method is called after SetupConnection, Widgets will be displayed in
  * the ground station.
  * If this method is called and SetupConnection was not called, it will run headless but default values of Widgets will be taken
  * from the xml file.
  * If this method is not called, Widgets will not be available. Constructing an object based on Widget class will fail.
  *
  * \param xml_file xml file for default values of Widgets
  */
  void SetupUserInterface(std::string xml_file);

  /*!
  * \brief Get TabWidget
  *
  * \return TabWidget
  */
  gui::TabWidget *GetTabWidget(void) const;

  /*!
  * \brief Logger setup
  *
  * Setup path of log files. \n
  * No logging will be performed if this method is not called. \n
  *
  * \param log_path path to store logs
  */
  void SetupLogger(std::string log_path);

  /*!
  * \brief Add log element
  *
  * The added element will be automatically logged once
  * logging started (see StartLog()). \n
  * This element must define on its side the io_data
  * to log, trough IODevice::SetDataToLog method.
  *
  * \param device IODevice to add
  */
  void AddDeviceToLog(IODevice *device);

  /*!
  * \brief Start logging
  *
  * All IODevice added through AddDeviceToLog() method
  * will automatically be logged. \n
  * SetupLogger() must have been called before.
  */
  void StartLog(void);

  /*!
  * \brief Stop logging
  *
  * Logs will automatically be sent to ground station.
  */
  void StopLog(void);

  /*!
  * \brief Is logging?
  *
  * \return true if is logging
  */
  bool IsLogging(void) const;

  /*!
  * \brief Notify that SendData's period has changed
  *
  * This funtion must be called when the period has changed. \n
  * Normally, it occurs in the Widget::XmlEvent method. \n
  * This method must be called with communication blocked (see BlockCom()).
  *
  * \param obj SendData which changed
  */
  void UpdateSendData(const gui::SendData *obj);

  /*!
  * \brief Block communication
  *
  * This funtion blocks the communication beetween the program and ground
  *station. \n
  * It must be called before changing datas or parameters exchanged between the
  *program
  * and the ground station.
  *
  */
  void BlockCom(void);

  /*!
 * \brief Unblock communication
 *
 * This funtion unblocks the communication beetween the program and ground
 *station. \n
 * It must be called after changing datas or parameters exchanged between the
 *program
 * and the ground station.
 *
 */
  void UnBlockCom(void);

  /*!
  * \brief Is connection lost?
  *
  * Once this method returns true, it will never return false back. \n
  * Note that this method return false if no connection is defined (see
  *SetupConnection).
  *
  * \return true if connection with ground station is lost
  */
  bool ConnectionLost(void) const;

  /*!
  * \brief Disable errors display
  *
  * Disable errors display, if you do not want to saturate console for exemple.
  * By defaults errors disply is enabled.
  *
  * \param value true to disable errors display
  */
  void DisableErrorsDisplay(bool value);

  /*!
  * \brief Is displaying errors?
  *
  *
  * \return true if errors display is enabled
  */
  bool IsDisplayingErrors(void) const;

private:
  class FrameworkManager_impl *pimpl_;
};

/*!
* \brief get FrameworkManager
*
* \return the FrameworkManager
*/
FrameworkManager *getFrameworkManager(void);

/*!
* \brief is big endian?
*
* \return true if big endian, false if little endian
*/
bool IsBigEndian(void);

} // end namespace core
} // end namespace flair

#endif // FRAMEWORKMANAGER_H
