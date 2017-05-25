// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file BebopBatteryMonitor.h
 * \brief Bebop battery monitor
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/24
 * \version 4.0
 */

#ifndef ARDRONE2BATTERYMONITOR_H
#define ARDRONE2BATTERYMONITOR_H

#include <BatteryMonitor.h>
#include <Thread.h>

namespace flair
{
namespace gui
{
    class Layout;
}
namespace core
{
    class Unix_I2cPort;
}

namespace sensor
{
    /*! \class BebopBatteryMonitor
    *
    * \brief Bebop battery monitor
    */
    class BebopBatteryMonitor : public core::Thread,public BatteryMonitor
    {
        public:
            /*!
            * \brief Constructor
            *
            * Construct a BebopBatteryMonitor at given position.
            *
            * \param position position
            * \param name name
            */
            BebopBatteryMonitor(const gui::LayoutPosition* position,std::string name);

            /*!
            * \brief Destructor
            *
            */
            ~BebopBatteryMonitor();

        private:
            /*!
            * \brief Run function
            *
            * Reimplemented from Thread.
            *
            */
            void Run(void);

            core::Unix_I2cPort* port;
    };
}; // end namespace sensor
}; // end namespace flair
#endif // ARDRONE2BATTERYMONITOR_H
