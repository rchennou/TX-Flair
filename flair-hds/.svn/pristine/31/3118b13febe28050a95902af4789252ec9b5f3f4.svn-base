// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ArDrone2Gps.h
 * \brief Class for Ardrone 2 gps receiver
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/06/04
 * \version 4.0
 */

#ifndef ARDRONE2GPS_H
#define ARDRONE2GPS_H

#include <Thread.h>
#include <NmeaGps.h>

namespace flair {
    namespace core {
        class SerialPort;
    }
}

namespace flair
{
namespace sensor
{
    /*! \class ArDrone2Gps
    *
    * \brief Class for Ardrone 2 gps receiver
    */
    class ArDrone2Gps : public core::Thread, public NmeaGps {
        public:
            /*!
            * \brief Constructor
            *
            * Construct an Ardrone 2 gps receiver.
            * It will be child of the FrameworkManager.
						* 
            * \param name name
            * \param serialport serialport
            * \param NMEAFlags NMEA sentances to enable
            * \param priority priority of the Thread
            */
            ArDrone2Gps(std::string name,core::SerialPort *serialport,NmeaGps::NMEAFlags_t NMEAFlags,uint8_t priority);

            /*!
            * \brief Destructor
            *
            */
            ~ArDrone2Gps();

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
#endif // ARDRONE2GPS_H
