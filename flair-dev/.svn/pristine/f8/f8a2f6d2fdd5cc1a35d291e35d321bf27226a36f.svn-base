// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Novatel.h
 * \brief Class for Novatel gps receiver
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/08/23
 * \version 4.0
 */

#ifndef Novatel_H
#define Novatel_H

#include <Thread.h>
#include <NmeaGps.h>

namespace flair {
namespace core {
class FrameworkManager;
class SerialPort;
}
}

namespace flair {
namespace sensor {
/*! \class Novatel
*
* \brief Class for Novatel gps receiver
*/
class Novatel : public core::Thread, public NmeaGps {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Novatel.
  *
  * \param parent parent
  * \param name name
  * \param serialport serialport
  * \param NMEAFlags NMEA sentances to enable
  * \param priority priority of the Thread
  */
  Novatel(const core::FrameworkManager *parent, std::string name,
          core::SerialPort *serialport, NmeaGps::NMEAFlags_t NMEAFlags,
          uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~Novatel();

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);

  core::SerialPort *serialport;
  void Sync(void);
};
} // end namespace sensor
} // end namespace framewor
#endif // Novatel_H
