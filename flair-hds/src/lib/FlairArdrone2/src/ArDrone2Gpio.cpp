// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/07/21
//  filename:   ArDrone2Gpio.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Classe integrant les gpio ardrone
//
//
//
/*********************************************************************/
#include "ArDrone2Gpio.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define GPIO_MAGIC          'p'
#define GPIO_DIRECTION      _IOW(GPIO_MAGIC, 0, Direction_t)
#define GPIO_READ           _IOWR(GPIO_MAGIC, 1, Data_t)
#define GPIO_WRITE          _IOW(GPIO_MAGIC, 2, Data_t)

using namespace flair::core;

namespace flair {
namespace actuator {

ArDrone2Gpio::ArDrone2Gpio(const Object *parent, std::string name): Mutex(parent, name) {

    fd=open("/dev/gpio",O_RDWR);
    if (fd <= 0) Err("/dev/gpio open error\n");
}

ArDrone2Gpio::~ArDrone2Gpio() {
    close(fd);
}

void ArDrone2Gpio::SetDirection(int gpio,Mode_t mode) {
    typedef struct Direction_t {
            int gpio;
            Mode_t mode;
        } Direction_t;

    Direction_t dir;

    dir.gpio = gpio;
    dir.mode = mode;

    GetMutex();
    if(ioctl(fd, GPIO_DIRECTION, &dir)<0) Err("ioctl error\n");
    ReleaseMutex();
}

void ArDrone2Gpio::SetValue(int gpio,bool value) {
    typedef struct Data_t {
            int gpio;
            int value;
        } Data_t;

    Data_t data;

    data.gpio = gpio;
    if(value) {
        data.value = 1;
    } else {
        data.value = 0;
    }

    GetMutex();
    if(ioctl(fd, GPIO_WRITE, &data)<0) Err("ioctl error\n");
    ReleaseMutex();
}

} // end namespace actuator
} // end namespace flair
