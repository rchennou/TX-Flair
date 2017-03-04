// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SendData.h
 * \brief Abstract class for sending datas to ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/07
 * \version 4.0
 */

#ifndef SENDDATA_H
#define SENDDATA_H

#include <Widget.h>

class SendData_impl;

namespace flair {
namespace gui {
class LayoutPosition;

/*! \class SendData
*
* \brief Abstract class for sending datas to ground station
*
*/
class SendData : public Widget {
public:
  /*!
  * \brief Constructor
  *
  */
  SendData(const LayoutPosition *position, std::string name, std::string type,
           uint16_t default_periodms = 100, bool default_enabled = false);

  /*!
  * \brief Destructor
  *
  */
  virtual ~SendData();

  /*!
  * \brief Copy datas to specified buffer
  *
  * This method must be reimplemented, in order to send datas to ground station.
  *
  * \param buf output buffer
  */
  virtual void CopyDatas(char *buf) const = 0;

  size_t SendSize(void) const;
  uint16_t SendPeriod(void) const; // in ms
  bool IsEnabled(void) const;

protected:
  /*!
  * \brief Notify that SenData's datas have changed
  *
  * This method must be called when the datas have changed. \n
  * Normally, it occurs when a curve is added to a plot for example. \n
  * This method automatically blocks and unblocks the communication.
  *
  */
  void SetSendSize(size_t value);

  /*!
  * \brief Extra Xml event
  *
  * This method must be reimplemented to handle extra xml event. \n
  * It is automatically called when something changed from
  * ground station, through XmlEvent method. \n
  */
  virtual void ExtraXmlEvent(void) = 0;

private:
  /*!
  * \brief XmlEvent from ground station
  *
  * Reimplemented from Widget. \n
  * This method handles period and enabled properties of the SendData. \n
  * Then it calls ExtraXmlEvent to handle specific xml events of reimplemented
  *class.
  *
  */
  void XmlEvent(void);

  void SetSendPeriod(uint16_t value);
  void SetEnabled(bool value);

  class SendData_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // SENDDATA_H
