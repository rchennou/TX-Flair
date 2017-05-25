// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ArDrone2.h
 * \brief Class defining an ardrone2 uav
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/06/10
 * \version 4.0
 */

#ifndef ARDRONE2_H
#define ARDRONE2_H

#include "Uav.h"

namespace flair {
    namespace sensor {
        class ArDrone2NavBoard;
    }
    namespace actuator {
        class ArDrone2Gpio;
    }
    namespace filter {
        class UavMultiplex;
    }
}


namespace flair
{
namespace meta
{
    /*! \class ArDrone2
    *
    * \brief Class defining an ardrone2 uav
    */
    class ArDrone2 : public Uav {
        public:
            ArDrone2(std::string name,std::string options="",filter::UavMultiplex *multiplex=NULL);
            ~ArDrone2();
            void StartSensors(void);
						std::string GetDefaultVrpnAddress(void) const{return "192.168.147.197:3883";}
            bool isReadyToFly(void) const;
            virtual std::string GetType(void) const{return "ardrone2";}

        private:
            sensor::ArDrone2NavBoard *navboard;
            actuator::ArDrone2Gpio* gpio;
    };
} // end namespace meta
} // end namespace flair
#endif // ARDRONE2_H
