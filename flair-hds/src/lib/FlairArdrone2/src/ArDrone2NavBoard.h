// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ArDrone2NavBoard.h
 * \brief Class for ArDrone 2 sensors
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/12/19
 * \version 4.0
 */

//thanks to Paparazzi (https://wiki.paparazziuav.org) for the struct nav_struct

#ifndef ARDRONE2NAVBOARD_H
#define ARDRONE2NAVBOARD_H

#include <Thread.h>

namespace flair {
    namespace core {
        class cvmatrix;
        class ImuData;
        class SerialPort;
    }
}

namespace flair { namespace sensor {
    class Imu;
    class UsRangeFinder;

    /*! \class ArDrone2NavBoard
    *
    * \brief Class for ArDrone 2 sensors
    */
    class ArDrone2NavBoard : public core::Thread {
        public:
            /*!
            * \brief Constructor
            *
            * Construct a ArDrone2NavBoard.
						* It will be child of the FrameworkManager.
            *
            * \param name name
            * \param serialport serialport
            * \param priority priority of the Thread
            */
            ArDrone2NavBoard(std::string name,core::SerialPort* serialport,uint8_t priority);

            /*!
            * \brief Destructor
            *
            */
            ~ArDrone2NavBoard();

            /*!
            * \brief Use default plot
            *
            */
            void UseDefaultPlot(void);

            /*!
            * \brief Get Imu
            *
            * \return Associated Imu
            */
            Imu* GetImu(void) const;

            /*!
            * \brief Get UsRangeFinder
            *
            * \return Associated UsRangeFinder
            */
            UsRangeFinder* GetUsRangeFinder(void) const;

        private:
            typedef struct nav_struct
            {
                uint16_t size;                // +0x00 Size of the following data (always 0x3a)
                uint16_t seq;                 // +0x02 Sequence number, increases every update
                uint16_t acc[3];              // +0x04 Raw data (10-bit) of the accelerometers multiplied by 4
                int16_t gyro[3];             // +0x0A Raw data for the gyros, 12-bit A/D converted voltage of the gyros. X,Y=IDG, Z=Epson
                uint16_t acc_temp;            // +0x10 Accs temperature -- startup value 120 @ 25C, rising to 143
                uint16_t gyro_temp;           // +0x12 XYGyro temperature (IDG), 12-bit A/D converted voltage of IDG's temperature sensor -- startup value 1532 @ 25C, rising to 1572
                uint16_t us_echo;             // +0x14 bit15=1 echo pulse transmitted, bit14-0 first echo. Value 30 = 1cm. min value: 784 = 26cm
                uint16_t us_echo_start;       // +0x16 Array with starts of echos (8 array values @ 25Hz, 9 values @ 22.22Hz)
                uint16_t us_echo_end;         // +0x18 Array with ends of echos   (8 array values @ 25Hz, 9 values @ 22.22Hz)
                uint16_t us_association_echo; // +0x1a Ultrasonic parameter -- echo number starting with 0. max value 3758. examples: 0,1,2,3,4,5,6,7  ; 0,1,2,3,4,86,6,9
                uint16_t us_distance_echo;    // +0x1c Ultrasonic parameter -- no clear pattern
                uint16_t us_courbe_temps;     // +0x1e Ultrasonic parameter -- counts up from 0 to approx 24346 in 192 sample cycles of which 12 cylces have value 0
                uint16_t us_courbe_valeur;    // +0x20 Ultrasonic parameter -- value between 0 and 4000, no clear pattern. 192 sample cycles of which 12 cylces have value 0
                uint16_t us_courbe_ref;       // +0x22 Ultrasonic parameter -- coutns down from 4000 to 0 in 192 sample cycles of which 12 cylces have value 0
                uint16_t nb_echo;
                uint32_t sum_echo;
                int16_t gradient;
                uint16_t flag_echo_ini;
                int32_t pressure;
                int16_t temprature_pressure;
                int16_t mag[3];
                uint16_t checksum;
            } __attribute__ ((packed)) nav_struct;

            /*!
            * \brief Run function
            *
            * Reimplemented from Thread.
            *
            */
            void Run(void);

            uint16_t Checksum(const uint8_t *data) const;
            void computeDatas(nav_struct* nav,core::Time time);

            Imu* imu;
            UsRangeFinder* us;
            core::SerialPort* serialport;
    };
} // end namespace sensor
} // end namespace flair

#endif // ARDRONE2NAVBOARD_H
