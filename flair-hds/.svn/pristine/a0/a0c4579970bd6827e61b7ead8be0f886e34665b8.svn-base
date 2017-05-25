// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/06/10
//  filename:   ArDrone2.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining an ardrone2 uav
//
//
/*********************************************************************/

#include "ArDrone2.h"
#include <FrameworkManager.h>
#include "ArDrone2Bldc.h"
#include "ArDrone2NavBoard.h"
#include "ArDrone2BatteryMonitor.h"
#include "ArDrone2CamV.h"
#include "ArDrone2CamH.h"
#include "ArDrone2Gpio.h"
#include <Unix_SerialPort.h>
#include <X4X8Multiplex.h>
#include <AhrsComplementaryFilter.h>
#include <Imu.h>
#include <Tab.h>
#include <FindArgument.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;
using namespace flair::filter;
using namespace flair::actuator;

#define GPIO_MB_GREEN_LED   180
#define GPIO_MB_RED_LED     181

namespace flair { namespace meta {

ArDrone2::ArDrone2(string name,string options,filter::UavMultiplex *multiplex) : Uav(name,multiplex) {
    Unix_SerialPort* bldc_port=new Unix_SerialPort(getFrameworkManager(),"bldc_port","/dev/ttyO0");
    Unix_SerialPort* nav_port=new Unix_SerialPort(getFrameworkManager(),"nav_port","/dev/ttyO1");

    gpio=new ArDrone2Gpio(this,"gpio");
    if(multiplex==NULL) SetMultiplex(new X4X8Multiplex("x4-multiplex",X4X8Multiplex::X4));
    SetBldc(new ArDrone2Bldc(GetUavMultiplex(),GetUavMultiplex()->GetLayout(),"parrot-bldc",bldc_port,gpio));
    navboard=new ArDrone2NavBoard("navboard",nav_port,70);
    //ahrs=new AhrsKalman(navboard->GetImu(),"parrot-ahrs");
    SetAhrs(new AhrsComplementaryFilter(navboard->GetImu(),"parrot-ahrs"));

    SetUsRangeFinder(navboard->GetUsRangeFinder());
    Tab* bat_tab=new Tab(getFrameworkManager()->GetTabWidget(),"battery");
    SetBatteryMonitor(new ArDrone2BatteryMonitor(bat_tab->NewRow(),"battery"));

    SetVerticalCamera(new ArDrone2CamV("camv",50));
    
    string camhOpts=FindArgument(options,"camh=",false);
    uint16_t camhWidth=640,camhHeight=360;
    if(camhOpts=="320x180") {
      camhWidth=320,camhHeight=180;
    } else if(camhOpts=="1280x720")  {
      camhWidth=1280,camhHeight=720;
    } 
    Info("using horizontal camera resolution: %ix%i\n",camhWidth, camhHeight);
    SetHorizontalCamera(new ArDrone2CamH("camh",camhWidth, camhHeight,50));

    gpio->SetDirection(GPIO_MB_GREEN_LED,ArDrone2Gpio::Mode_t::OutputLow);
    gpio->SetDirection(GPIO_MB_RED_LED,ArDrone2Gpio::Mode_t::OutputLow);
    gpio->SetValue(GPIO_MB_RED_LED,false);
    gpio->SetValue(GPIO_MB_GREEN_LED,true);
}

ArDrone2::~ArDrone2() {
  gpio->SetValue(GPIO_MB_GREEN_LED,false);
  gpio->SetValue(GPIO_MB_RED_LED,true);
}

void ArDrone2::StartSensors(void) {
    ((ArDrone2BatteryMonitor*)GetBatteryMonitor())->Start();
    navboard->Start();
    ((ArDrone2CamV *)GetVerticalCamera())->Start();
    ((ArDrone2CamH *)GetHorizontalCamera())->Start();
}

bool ArDrone2::isReadyToFly(void) const {
  return GetAhrs()->GetImu()->IsReady();
}


} // end namespace meta
} // end namespace flair
