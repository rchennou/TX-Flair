// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Mb800.h
 * \brief Class for mb800 gps receiver
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/08/23
 * \version 4.0
 */

#ifndef MB800_H
#define MB800_H

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
/*! \class Mb800
*
* \brief Class for mb800 gps receiver
*/
class Mb800 : public core::Thread, public NmeaGps {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Mb800.
  *
  * \param parent parent
  * \param name name
  * \param serialport serialport
  * \param NMEAFlags NMEA sentances to enable
  * \param priority priority of the Thread
  */
  Mb800(const core::FrameworkManager *parent, std::string name,
        core::SerialPort *serialport, NmeaGps::NMEAFlags_t NMEAFlags,
        uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~Mb800();

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

  void Sync(void);
  core::SerialPort *serialport;
};
} // end namespace sensor
} // end namespace framewor
#endif // MB800_H
