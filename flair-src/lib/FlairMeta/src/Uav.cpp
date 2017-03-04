// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/06/10
//  filename:   Uav.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class to construct sensors/actuators depending on uav type
//
//
/*********************************************************************/

#include "Uav.h"
#include <FrameworkManager.h>
#include <Tab.h>
#include <GridLayout.h>
#include <DataPlot1D.h>
#include <VrpnClient.h>
#include <Ahrs.h>
#include <Imu.h>
#include <UavMultiplex.h>
#include <UsRangeFinder.h>
#include <Bldc.h>
#include <cvmatrix.h>
#include "MetaUsRangeFinder.h"
#include "MetaVrpnObject.h"

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;
using namespace flair::sensor;
using namespace flair::actuator;

namespace flair {
namespace meta {

Uav::Uav(FrameworkManager *parent, string name, UavMultiplex *multiplex)
    : Object(parent, name) {
  vrpnclient = NULL;
  uav_vrpn = NULL;
  verticalCamera = NULL;
  this->multiplex = multiplex;
}

Uav::~Uav() {}

void Uav::SetUsRangeFinder(const UsRangeFinder *inUs) {
  us = (UsRangeFinder *)inUs;
  meta_us = new MetaUsRangeFinder(us);
  getFrameworkManager()->AddDeviceToLog(us);
}

void Uav::SetAhrs(const Ahrs *inAhrs) {
  ahrs = (Ahrs *)inAhrs;
  imu = (Imu *)ahrs->GetImu();
  getFrameworkManager()->AddDeviceToLog(imu);
}

void Uav::SetBldc(const Bldc *inBldc) { bldc = (Bldc *)inBldc; }

void Uav::SetBatteryMonitor(const BatteryMonitor *inBattery) {
  battery = (BatteryMonitor *)inBattery;
}

void Uav::SetMultiplex(const UavMultiplex *inMultiplex) {
  multiplex = (UavMultiplex *)inMultiplex;
  getFrameworkManager()->AddDeviceToLog(multiplex);
}

void Uav::SetVerticalCamera(const Camera *inVerticalCamera) {
  verticalCamera = (Camera *)inVerticalCamera;
}
/*
void Uav::SetupVRPNSerial(SerialPort *vrpn_port,string name,int
VRPNSerialObjectId) {
    vrpnclient=new VrpnClient(getFrameworkManager(),"vrpn",vrpn_port,10000,80);
    uav_vrpn=new MetaVrpnObject(vrpnclient,name,VRPNSerialObjectId);

    getFrameworkManager()->AddDeviceToLog(uav_vrpn);
}
*/
void Uav::SetupVRPNAutoIP(string name) {
  SetupVRPN("192.168.147.197:3883", name);
}

void Uav::SetupVRPN(string optitrack_address, string name) {
  vrpnclient = new VrpnClient(getFrameworkManager(), "vrpn", optitrack_address,
                              10000, 80);
  uav_vrpn = new MetaVrpnObject(vrpnclient, name);

  getFrameworkManager()->AddDeviceToLog(uav_vrpn);

  GetAhrs()->YawPlot()->AddCurve(uav_vrpn->State()->Element(2),
                                 DataPlot::Green);
  // GetAhrs()->RollPlot()->AddCurve(uav_vrpn->State()->Element(0),DataPlot::Green);
  // GetAhrs()->PitchPlot()->AddCurve(uav_vrpn->State()->Element(1),DataPlot::Green);
}

void Uav::StartSensors(void) {
  if (vrpnclient != NULL) {
    vrpnclient->Start();
  }
}
void Uav::UseDefaultPlot(void) {
  multiplex->UseDefaultPlot();

  if (bldc->HasSpeedMeasurement()) {
    Tab *plot_tab = new Tab(multiplex->GetTabWidget(), "Speeds");
    DataPlot1D *plots[4];
    plots[0] = new DataPlot1D(plot_tab->NewRow(), "front left", 0, 7000);
    plots[1] =
        new DataPlot1D(plot_tab->LastRowLastCol(), "front right", 0, 7000);
    plots[2] = new DataPlot1D(plot_tab->NewRow(), "rear left", 0, 7000);
    plots[3] =
        new DataPlot1D(plot_tab->LastRowLastCol(), "rear right", 0, 7000);

    if (bldc->MotorsCount() == 8) {
      for (int i = 0; i < 4; i++)
        plots[i]->AddCurve(
            bldc->Output()->Element(multiplex->MultiplexValue(i), 0),
            DataPlot::Red, "top");
      for (int i = 0; i < 4; i++)
        plots[i]->AddCurve(
            bldc->Output()->Element(multiplex->MultiplexValue(i + 4), 0),
            DataPlot::Blue, "bottom");
    } else {
      for (int i = 0; i < 4; i++)
        plots[i]->AddCurve(
            bldc->Output()->Element(multiplex->MultiplexValue(i), 0));
    }
  }

  if (bldc->HasCurrentMeasurement()) {
    Tab *plot_tab = new Tab(multiplex->GetTabWidget(), "Currents");
    DataPlot1D *plots[4];
    plots[0] = new DataPlot1D(plot_tab->NewRow(), "front left", 0, 10);
    plots[1] = new DataPlot1D(plot_tab->LastRowLastCol(), "front right", 0, 10);
    plots[2] = new DataPlot1D(plot_tab->NewRow(), "rear left", 0, 10);
    plots[3] = new DataPlot1D(plot_tab->LastRowLastCol(), "rear right", 0, 10);

    if (bldc->MotorsCount() == 8) {
      for (int i = 0; i < 4; i++)
        plots[i]->AddCurve(
            bldc->Output()->Element(multiplex->MultiplexValue(i), 1),
            DataPlot::Red, "top");
      for (int i = 0; i < 4; i++)
        plots[i]->AddCurve(
            bldc->Output()->Element(multiplex->MultiplexValue(i + 4), 1),
            DataPlot::Blue, "bottom");
    } else {
      for (int i = 0; i < 4; i++)
        plots[i]->AddCurve(
            bldc->Output()->Element(multiplex->MultiplexValue(i), 1));
    }
  }

  meta_us->UseDefaultPlot();
  ahrs->UseDefaultPlot();
}

UavMultiplex *Uav::GetUavMultiplex(void) const { return multiplex; }

Bldc *Uav::GetBldc(void) const { return bldc; }

Ahrs *Uav::GetAhrs(void) const { return ahrs; }

Imu *Uav::GetImu(void) const { return imu; }

MetaUsRangeFinder *Uav::GetMetaUsRangeFinder(void) const { return meta_us; }

UsRangeFinder *Uav::GetUsRangeFinder(void) const { return us; }

BatteryMonitor *Uav::GetBatteryMonitor(void) const { return battery; }

VrpnClient *Uav::GetVrpnClient(void) const {
  if (vrpnclient == NULL)
    Err("vrpn is not setup, call SetupVRPN before\n");
  return vrpnclient;
}

MetaVrpnObject *Uav::GetVrpnObject(void) const { return uav_vrpn; }

Camera *Uav::GetVerticalCamera(void) const { return verticalCamera; }

} // end namespace meta
} // end namespace flair
