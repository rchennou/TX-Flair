/*!
 * \file Bebop.h
 * \brief Class defining a bebop uav
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/07/25
 * \version 4.0
 */

#ifndef BEBOP_H
#define BEBOP_H

#include "Uav.h"

namespace flair {
    namespace core {
        class FrameworkManager;
    }
    namespace filter {
        class UavMultiplex;
    }
}

namespace flair
{
namespace meta
{
    /*! \class Bebop
    *
    * \brief Class defining an ardrone2 uav
    */
    class Bebop : public Uav {
        public:
            Bebop(std::string uav_name,filter::UavMultiplex *multiplex=NULL);
            ~Bebop();
            void StartSensors(void);
            virtual std::string GetType(void) const{return "bebop";}

        private:

    };
} // end namespace meta
} // end namespace flair
#endif // BEBOP_H
