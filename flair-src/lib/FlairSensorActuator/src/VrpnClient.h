// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file VrpnClient.h
 * \brief Class to connect to a Vrpn server
 * \author César Richard, Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS
 * 7253
 * \date 2013/04/03
 * \version 4.0
 */

#ifndef VRPNCLIENT_H
#define VRPNCLIENT_H

#include <Thread.h>

namespace flair {
namespace core {
class FrameworkManager;
class SerialPort;
}
namespace gui {
class TabWidget;
class Layout;
}
}

class VrpnClient_impl;
class VrpnObject_impl;

namespace flair {
namespace sensor {
/*! \class VrpnClient
*
* \brief Class to connect to a Vrpn server
*/
class VrpnClient : public core::Thread {
  friend class ::VrpnObject_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a VrpnClient. Connection is done by IP.
  *
  * \param parent parent
  * \param name name
  * \param address server address
  * \param us_period Thread period in us
  * \param priority priority of the Thread
  */
  VrpnClient(const core::FrameworkManager *parent, std::string name,
             std::string address, uint16_t us_period, uint8_t priority);

  /*!
  * \brief Constructor
  *
  * Construct a VrpnClient. Connection is done by XBee modem.
  *
  * \param parent parent
  * \param name name
  * \param serialport SerialPort for XBee modem
  * \param us_period Xbee RX timeout in us
  * \param priority priority of the Thread
  */
  VrpnClient(const core::FrameworkManager *parent, std::string name,
             core::SerialPort *serialport, uint16_t us_period,
             uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~VrpnClient();

  /*!
  * \brief Setup Layout
  *
  * \return a Layout available
  */
  gui::Layout *GetLayout(void) const;

  /*!
  * \brief Setup Tab
  *
  * \return a Tab available
  */
  gui::TabWidget *GetTabWidget(void) const;

  /*!
  * \brief Is XBee used?
  *
  * \return true if connection is based on XBee modem
  */
  bool UseXbee(void) const;

private:
  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);

  class VrpnClient_impl *pimpl_;
};
} // end namespace sensor
} // end namespace flair
#endif // VRPNCLIENT_H
