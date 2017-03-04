// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file RadioReceiver.h
 * \brief Base class for radio receiver
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/07/08
 * \version 4.0
 */

#ifndef RADIORECEIVER_H
#define RADIORECEIVER_H

#include <IODevice.h>
#include <stdint.h>

namespace flair {
namespace core {
class FrameworkManager;
class cvmatrix;
}
namespace gui {
class Tab;
class TabWidget;
class Layout;
}
}

namespace flair {
namespace sensor {
/*! \class RadioReceiver
*
* \brief Base class for radio receiver
*/
class RadioReceiver : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a RadioReceiver.
  *
  * \param parent parent
  * \param name name
  * \param nb_channels number of supported channels
  */
  RadioReceiver(const core::FrameworkManager *parent, std::string name,
                unsigned int nb_channels);

  /*!
  * \brief Destructor
  *
  */
  ~RadioReceiver();

  /*!
  * \brief get channel value
  *
  * \param id channel id
  * \return value of the channel, between 0 and 1.
  *  Returns -1 if channel is out of bound
  */
  float ChannelValue(unsigned int id) const;

  /*!
  * \brief Is transmitter connected?
  *
  * \return true if transmitter is connected
  */
  bool IsConnected(void) const;

  /*!
  * \brief Setup Layout
  *
  * \return a Layout available
  */
  gui::Layout *GetLayout(void) const;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  core::cvmatrix *output;
  bool is_connected;
  unsigned int nb_channels;
  gui::Tab *main_tab;
  gui::TabWidget *tab;
  gui::Tab *setup_tab;
};
} // end namespace sensor
} // end namespace flair
#endif // RADIORECEIVER_H
