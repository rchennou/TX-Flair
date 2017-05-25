// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/24
//  filename:   ArDrone2BatteryMonitor.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    ArDrone2 battery monitor
//
//
/*********************************************************************/

#include "ArDrone2BatteryMonitor.h"
#include <Layout.h>
#include <LayoutPosition.h>
#include <Unix_I2cPort.h>

#define INTERFACE_GROUP_ADDRESS 0x49
#define INTBR_GPBR1 0x91

//INTBR_GPBR1 bits
#define DEFAULT_MADC_CLK_EN (1<<4)	/* MADC clock enable */
#define MADC_HFCLK_EN       (1<<7)	/* HFCLK clock divider enable */

#define MADC_GROUP_ADDRESS 0x4a
#define MADC_CTRL1 0x00
#define MADC_SW1SELECT_LSB 0x06
#define MADC_SW1AVERAGE_LSB 0x08
#define MADC_CTRL_SW1 0x12
#define MADC_GPCH0_LSB 0x37
#define MADC_GPCH0_MSB 0x38

//MADC_CTRL1 bits
#define MADC_MADCON     (1<<0)	/* MADC power on */

//MADC_SW1SELECT_LSB bits
#define	MADC_ADCIN0		(1<<0)

//MADC_SW1AVERAGE_LSB bits
#define	MADC_AV_CH0		(1<<0)

//MADC_CTRL_SW1 bits
#define	MADC_EOC_SW1	(1<<1) /* end of convrsion SW1 */
#define	MADC_SW1		(1<<5) /* start an all channel convrsion */

using std::string;
using namespace flair::core;

namespace flair {
namespace sensor {

ArDrone2BatteryMonitor::ArDrone2BatteryMonitor(const gui::LayoutPosition* position,string name) : Thread(position->getLayout(),name,5),BatteryMonitor(position,name) {
    uint8_t tx[2];

    port=new Unix_I2cPort((BatteryMonitor*)this,"i2c1","/dev/i2c-1");

    //interface group address
    port->SetSlave(INTERFACE_GROUP_ADDRESS);

    //enable clocks
    tx[0]=INTBR_GPBR1;
    tx[1]=MADC_HFCLK_EN|DEFAULT_MADC_CLK_EN;
    port->Write(tx,2);

    //MADC group address
    port->SetSlave(MADC_GROUP_ADDRESS);

    // turn on MADC
    tx[0]=MADC_CTRL1;
    tx[1]=MADC_MADCON;
    port->Write(tx,2);

    // select channel 0
    tx[0]=MADC_SW1SELECT_LSB;
    tx[1]=MADC_ADCIN0;
    port->Write(tx,2);

    // setup averaging on channel 0
    tx[0]=MADC_SW1AVERAGE_LSB;
    tx[1]=MADC_AV_CH0;
    port->Write(tx,2);
}

ArDrone2BatteryMonitor::~ArDrone2BatteryMonitor() {
    SafeStop();
    Join();
}

void ArDrone2BatteryMonitor::Run(void) {
    unsigned char lsb, msb;
    int adc_value;
    uint8_t tx[2];
    uint8_t rx;

    SetPeriodMS(1000);

    while(!ToBeStopped()) {
        // start an all channel conversion
        tx[0]=MADC_CTRL_SW1;
        tx[1]=MADC_SW1;
        port->Write(tx,2);

        WaitPeriod();

        //check end of conversion in CTRL_SW1
        //(conversion should be ended as period is 1s)
        port->Write(tx,1);
        port->Read(&rx,1);
        if((rx&MADC_EOC_SW1)==MADC_EOC_SW1) {
            //read value
            tx[0]=MADC_GPCH0_LSB;
            port->Write(tx,1);
            port->Read(&lsb,1);

            tx[0]=MADC_GPCH0_MSB;
            port->Write(tx,1);
            port->Read(&msb,1);

            adc_value = (lsb >> 6) | (msb << 2);

            //convert to volts
            //thanks to Paparazzi (https://wiki.paparazziuav.org) for the coefficient
            SetBatteryValue(adc_value*0.013595166);
        }
    }
}

} // end namespace sensor
} // end namespace flair
