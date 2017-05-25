// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/12/19
//  filename:   ArDrone2Bldc_impl.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Classe integrant les moteurs ardrone
//
//
/*********************************************************************/

#ifndef ARDRONE2BLDC_IMPL_H
#define ARDRONE2BLDC_IMPL_H

#include <IODevice.h>
#include <stdint.h>

namespace flair {
    namespace core {
        class SerialPort;
    }
    namespace actuator {
        class ArDrone2Bldc;
        class ArDrone2Gpio;
    }
}

class ArDrone2Bldc_impl {

    public:
        ArDrone2Bldc_impl(flair::actuator::ArDrone2Bldc* self,flair::core::SerialPort* serialport,flair::actuator::ArDrone2Gpio* gpio);
        ~ArDrone2Bldc_impl();
        void UpdateFrom(flair::core::io_data *data);
        void SetMotors(float* value);

    private:
        void StartTest(void);
        void StopTest(void);
        void ResetBldc(void);
        int WriteCmd(uint8_t cmd, uint8_t *reply, int replylen);
        void SetLeds(uint8_t led0, uint8_t led1, uint8_t led2, uint8_t led3);

        flair::actuator::ArDrone2Bldc* self;
        flair::core::SerialPort* serialport;
        bool is_reseted;
        flair::actuator::ArDrone2Gpio* gpio;
};

#endif // ARDRONE2BLDC_IMPL_H
