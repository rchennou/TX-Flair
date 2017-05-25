// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/07/21
//  filename:   ArDrone2Gpio.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Classe integrant les gpio ardrone2
//
//
/*********************************************************************/

//see linux-ardrone2-2.6.32-9/drivers/parrot/char/gpio2_ioctl.h for ardrone2 specific gpios definitions

#ifndef ARDRONE2GPIO_H
#define ARDRONE2GPIO_H

#include <Mutex.h>

namespace flair { namespace actuator {

class ArDrone2Gpio : private core::Mutex {

    public:
        /*!
        * \brief Constructor
        *
        * Construct a ArDrone2Gpio manager.
        *
        * \param parent parent
        * \param name name
        */
        ArDrone2Gpio(const Object *parent, std::string name);
        ~ArDrone2Gpio();

         enum class Mode_t {
            Input = 0, // Pin configured for input
            OutputLow, // Pin configured for output with low level
            OutputHigh, // Pin configured for output with high level
        };

        void SetDirection(int gpio,Mode_t mode);
        void SetValue(int gpio,bool value);

    private:
        int fd;
};

} // end namespace actuator
} // end namespace framewor

#endif // ARDRONE2GPIO_H
