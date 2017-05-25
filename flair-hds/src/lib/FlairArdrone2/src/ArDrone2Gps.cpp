// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/06/04
//  filename:   ArDrone2Gps.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant le recepteur gps de l'ardrone2
//
//
/*********************************************************************/

#include "ArDrone2Gps.h"
#include <SerialPort.h>
#include <FrameworkManager.h>
#include <string.h>

using std::string;
using namespace flair::core;

namespace flair
{
namespace sensor
{

ArDrone2Gps::ArDrone2Gps(string name,SerialPort *serialport,NmeaGps::NMEAFlags_t NMEAFlags,uint8_t priority) : Thread(getFrameworkManager(),name,priority), NmeaGps(name,NMEAFlags)
{
    this->serialport=serialport;

    serialport->SetBaudrate(4800);
    serialport->SetRxTimeout(100000000);
}

ArDrone2Gps::~ArDrone2Gps()
{
    SafeStop();
    Join();
}

void ArDrone2Gps::Run(void)
{
    char response[200] = {0};
    int size;

    Sync();

    WarnUponSwitches(true);

    while(!ToBeStopped())
    {
        SleepMS(10);
        size=0;
        while(!ToBeStopped())
        {
            ssize_t read = serialport->Read(&response[size],1);
            if(read<0)
            {
                Thread::Err("erreur Read (%s)\n",strerror(-read));
            }
            if(response[size]==0x0a) break;
            size++;
        }
        size++;
        parseFrame(response, size);

    }

    WarnUponSwitches(false);
}

void ArDrone2Gps::Sync(void)
{
    char data=0;
    ssize_t read = 0;

    //attente fin trame
    while(data!=0x0a)
    {
        read = serialport->Read(&data,1);
        if(read<0)
        {
            Thread::Err("erreur Read (%s)\n",strerror(-read));
        }
    }
}

} // end namespace sensor
} // end namespace flair
