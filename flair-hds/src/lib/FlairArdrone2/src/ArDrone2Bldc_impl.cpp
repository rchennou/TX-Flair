// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/12/19
//  filename:   ArDrone2Bldc_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Classe integrant les moteurs ardrone
//
//  thanks to Paparazzi (https://wiki.paparazziuav.org) for the protocol
//
//
/*********************************************************************/
#include "ArDrone2Bldc_impl.h"
#include "ArDrone2Bldc.h"
#include "ArDrone2Gpio.h"
#include <SerialPort.h>
#include <string.h>
#include <unistd.h>

#define MAX_VALUE           0x1ff

#define MOT_LEDOFF          0
#define MOT_LEDRED          1
#define MOT_LEDGREEN        2
#define MOT_LEDORANGE       3

#define GPIO_MOTOR1         171
#define GPIO_MOTOR2         172
#define GPIO_MOTOR3         173
#define GPIO_MOTOR4         174

#define GPIO_IRQ_FLIPFLOP   175
#define GPIO_IRQ_INPUT      176

using namespace flair::core;
using namespace flair::gui;
using namespace flair::actuator;

ArDrone2Bldc_impl::ArDrone2Bldc_impl(ArDrone2Bldc* self,SerialPort* serialport,ArDrone2Gpio* gpio) {
    this->self=self;
    this->serialport=serialport;
    this->gpio=gpio;

    gpio->SetDirection(GPIO_MOTOR1,ArDrone2Gpio::Mode_t::OutputLow);
    gpio->SetDirection(GPIO_MOTOR2,ArDrone2Gpio::Mode_t::OutputLow);
    gpio->SetDirection(GPIO_MOTOR3,ArDrone2Gpio::Mode_t::OutputLow);
    gpio->SetDirection(GPIO_MOTOR4,ArDrone2Gpio::Mode_t::OutputLow);
    gpio->SetDirection(GPIO_IRQ_FLIPFLOP,ArDrone2Gpio::Mode_t::OutputLow);
    gpio->SetDirection(GPIO_IRQ_INPUT,ArDrone2Gpio::Mode_t::Input);

    ResetBldc();
}

ArDrone2Bldc_impl::~ArDrone2Bldc_impl() {
    SetLeds(MOT_LEDRED,MOT_LEDRED, MOT_LEDRED, MOT_LEDRED);
}

void ArDrone2Bldc_impl::ResetBldc() {
    gpio->SetValue(GPIO_IRQ_FLIPFLOP,false);
    usleep(20000);
    gpio->SetValue(GPIO_IRQ_FLIPFLOP,true);

    //all select lines inactive
    gpio->SetValue(GPIO_MOTOR1,false);
    gpio->SetValue(GPIO_MOTOR2,false);
    gpio->SetValue(GPIO_MOTOR3,false);
    gpio->SetValue(GPIO_MOTOR4,false);

    //configure motors
    uint8_t reply[121];
    for(int i=0; i<4; i++) {
        gpio->SetValue(GPIO_MOTOR1 + i,true);

        WriteCmd(0xe0,reply,2);
        if(reply[1]==0x50) {
            self->Warn("Init motor %i\n",i);
            WriteCmd(0x91,reply,121);
            WriteCmd(0xa1,reply,2);
            WriteCmd(i+1,reply,1);
            usleep(200000);//wait before reconfiguring motor, otherwise it does not reply
            WriteCmd(0xe0,reply,2);
        }
        if(reply[1]!=0x00) {
            self->Err("Init motor error %i\n",i);
        }

        WriteCmd(i+1,reply,1);
        gpio->SetValue(GPIO_MOTOR1+i,false);
    }

    //all select lines active
    gpio->SetValue(GPIO_MOTOR1,true);
    gpio->SetValue(GPIO_MOTOR2,true);
    gpio->SetValue(GPIO_MOTOR3,true);
    gpio->SetValue(GPIO_MOTOR4,true);

    //start multicast
    for(int i=0; i<6; i++) WriteCmd(0xa0,reply,1);

    //reset IRQ flipflop
    //on error GPIO_IRQ_INPUT reads 1, this code resets GPIO_IRQ_INPUT to 0
    gpio->SetValue(GPIO_IRQ_FLIPFLOP,false);
    gpio->SetValue(GPIO_IRQ_FLIPFLOP,true);

    usleep(200000);//wait, otherwise leds stay red when motor is stopped
    SetLeds(MOT_LEDGREEN,MOT_LEDGREEN, MOT_LEDGREEN, MOT_LEDGREEN);

    is_reseted=true;
}

void ArDrone2Bldc_impl::SetMotors(float* value) {
    uint8_t tx[5];
    uint8_t rx[5];
    uint16_t mot_value[4];

    for(int i=0; i<4; i++) mot_value[i]=(uint16_t)(MAX_VALUE*value[i]);

    if(mot_value[0]!=0 || mot_value[1]!=0 || mot_value[2]!=0 || mot_value[3]!=0) {

        tx[0] = 0x20 | ((mot_value[0]&MAX_VALUE)>>4);
        tx[1] = ((mot_value[0]&MAX_VALUE)<<4) | ((mot_value[1]&MAX_VALUE)>>5);
        tx[2] = ((mot_value[1]&MAX_VALUE)<<3) | ((mot_value[3]&MAX_VALUE)>>6);
        tx[3] = ((mot_value[3]&MAX_VALUE)<<2) | ((mot_value[2]&MAX_VALUE)>>7);
        tx[4] = ((mot_value[2]&MAX_VALUE)<<1);
        ssize_t written=serialport->Write(tx, sizeof(tx));

        if(written<0) {
            self->Err("write error (%s)\n",strerror(-written));
        } else if (written != sizeof(tx)) {
            self->Err("write error %i/%i\n",written,sizeof(tx));
        }

        ssize_t read=serialport->Read(rx, sizeof(rx));
        if(read<0) {
            self->Err("read error (%s)\n",strerror(-read));
        } else if (read != sizeof(rx)) {
            self->Err("read error %i/%i\n",read,sizeof(rx));
        }
        for(int i=0; i<5; i++) {
            if(rx[i]!=tx[i]) {
                self->Warn("wrong response\n");
                for(int i=0; i<5; i++) Printf("%x %x",tx[i],rx[i]);
                Printf("\n");
            }
        }

        is_reseted=false;

    } else {
        if(is_reseted==false) ResetBldc();
    }
}

int ArDrone2Bldc_impl::WriteCmd(uint8_t cmd, uint8_t *reply, int replylen) {
    ssize_t written=serialport->Write(&cmd, 1);
    if(written<0) {
        self->Err("write error (%s)\n",strerror(-written));
    } else if (written != 1) {
        self->Err("write error %i/1\n",written);
    }

    return serialport->Read(reply, replylen);
}

void ArDrone2Bldc_impl::SetLeds(uint8_t led0, uint8_t led1, uint8_t led2, uint8_t led3) {
    uint8_t tx[2];

    led0 &= 0x03;
    led1 &= 0x03;
    led2 &= 0x03;
    led3 &= 0x03;

    tx[0]=0x60 | ((led0&1)<<4) | ((led1&1)<<3) | ((led2&1)<<2) | ((led3&1) <<1);
    tx[1]=((led0&2)<<3) | ((led1&2)<<2) | ((led2&2)<<1) | ((led3&2)<<0);

    ssize_t written=serialport->Write(tx, sizeof(tx));
    if(written<0) {
        self->Err("write error (%s)\n",strerror(-written));
    } else if (written != sizeof(tx)) {
        self->Err("write error %i/%i\n",written,sizeof(tx));
    }

    serialport->Read(tx, sizeof(tx));//flush
}
