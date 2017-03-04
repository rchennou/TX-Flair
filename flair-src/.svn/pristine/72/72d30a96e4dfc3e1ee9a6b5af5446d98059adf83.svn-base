// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/08/23
//  filename:   NmeaGps.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for GPS using NMEA sentances
//
//
/*********************************************************************/

#include "NmeaGps.h"
#include "geodesie.h"
#include <Euler.h>
#include <DataPlot1D.h>
#include <Tab.h>
#include <TabWidget.h>
#include <GridLayout.h>
#include <GroupBox.h>
#include <PushButton.h>
#include <FrameworkManager.h>
#include <Map.h>
#include <GeoCoordinate.h>
#include <Vector3D.h>
#include <Label.h>
#include <GpsData.h>
#include <string.h>

using std::string;
using namespace Geodesie;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

NmeaGps::NmeaGps(const FrameworkManager *parent, string name, NMEAFlags_t NMEAFlags)
    : IODevice(parent, name) {
  this->NMEAFlags = NMEAFlags;

  nmea_zero_INFO(&info);
  nmea_parser_init(&parser);
  altRef = 0;

  if ((NMEAFlags & GGA) == 0) {
    Err("Enable at least the GGA sentence\n");
  }

  // station sol
  mainTab = new Tab(parent->GetTabWidget(), name);
  tab = new TabWidget(mainTab->NewRow(), name);
  sensorTab = new Tab(tab, "Setup");
  setupGroupbox = new GroupBox(sensorTab->NewRow(), name);
  buttonRef = new PushButton(setupGroupbox->NewRow(), "set ref");
  nbSatLabel = new Label(setupGroupbox->NewRow(), "nb_sat");
  fixLabel = new Label(setupGroupbox->LastRowLastCol(), "fix");

  position = new GeoCoordinate((IODevice *)this, "position", 0, 0, 0);

  takeRef = false;

  gpsData = new GpsData(this);
  AddDataToLog(gpsData);

  nbSatLabel->SetText("number of satellies: %i", gpsData->GetNumberOfSatellites());
  fixLabel->SetText("fix quality: %i", gpsData->GetFixQuality());
}

NmeaGps::NmeaGps(const IODevice *parent, std::string name) : IODevice(parent, name) {
  gpsData = new GpsData(this);
  mainTab = NULL;
  tab = NULL;
  sensorTab = NULL;
}

NmeaGps::~NmeaGps() {
  if (mainTab != NULL) {
    nmea_parser_destroy(&parser);
    delete mainTab;
  }
}

GroupBox *NmeaGps::GetGroupBox(void) const { return setupGroupbox; }

const GpsData *NmeaGps::GetDatas(void) const {
   return gpsData;
}

void NmeaGps::GetDatas(core::GpsData **outGpsData) const {
  *outGpsData = gpsData;
}

void NmeaGps::UseDefaultPlot(void) {
  plotTab = new Tab(tab, "Mesures");

  if ((NMEAFlags & GGA) != 0) {
    ePlot = new DataPlot1D(plotTab->NewRow(), "e", -10, 10);
    ePlot->AddCurve(gpsData->Element(GpsData::East));
    nPlot = new DataPlot1D(plotTab->LastRowLastCol(), "n", -10, 10);
    nPlot->AddCurve(gpsData->Element(GpsData::North));
    uPlot = new DataPlot1D(plotTab->LastRowLastCol(), "u", -10, 10);
    uPlot->AddCurve(gpsData->Element(GpsData::Up));
  }
  if ((NMEAFlags & VTG) != 0) {
    vePlot = new DataPlot1D(plotTab->NewRow(), "ve", -10, 10);
    vePlot->AddCurve(gpsData->Element(GpsData::EastVelocity));
    vnPlot = new DataPlot1D(plotTab->LastRowLastCol(), "vn", -10, 10);
    vnPlot->AddCurve(gpsData->Element(GpsData::NorthVelocity));
  }

  Tab *map_tab = new Tab(tab, "carte");
  map = new Map(map_tab->NewRow(), "map");
  map->AddPoint(position, "drone");
}

DataPlot1D *NmeaGps::EPlot(void) const {
  if ((NMEAFlags & GGA) != 0) {
    return ePlot;
  } else {
    Err("GGA sentence not requested\n");
    return NULL;
  }
}

DataPlot1D *NmeaGps::NPlot(void) const {
  if ((NMEAFlags & GGA) != 0) {
    return nPlot;
  } else {
    Err("GGA sentence not requested\n");
    return NULL;
  }
}

DataPlot1D *NmeaGps::UPlot(void) const {
  if ((NMEAFlags & GGA) != 0) {
    return uPlot;
  } else {
    Err("GGA sentence not requested\n");
    return NULL;
  }
}

DataPlot1D *NmeaGps::VEPlot(void) const {
  if ((NMEAFlags & VTG) != 0) {
    return vePlot;
  } else {
    Err("GGA sentence not requested\n");
    return NULL;
  }
}

DataPlot1D *NmeaGps::VNPlot(void) const {
  if ((NMEAFlags & VTG) != 0) {
    return vnPlot;
  } else {
    Err("GGA sentence not requested\n");
    return NULL;
  }
}

Layout *NmeaGps::GetLayout(void) const { return sensorTab; }

Tab *NmeaGps::GetPlotTab(void) const { return plotTab; }

TabWidget *NmeaGps::GetTab(void) const { return tab; }

void NmeaGps::SetRef(void) { takeRef = true; }

void NmeaGps::GetEnu(Vector3D *point) {
  gpsData->GetMutex();
  gpsData->GetEnu(point->x,point->y,point->z);
  gpsData->ReleaseMutex();
}

void NmeaGps::parseFrame(const char *frame, int frame_size) {

  int result;

  result = nmea_parse(&parser, frame, frame_size, &info);
  if (result != 1) {
    Warn("unrecognized nmea sentence: %s\n",frame);
    return;
  }

  result = nmea_parse_GPGGA(frame, frame_size, &pack);

  if (result == 1) {
    nmea_info2pos(&info, &pos);
    // Printf("%s\n",frame);
   //  Printf("nb:%i fix:%i lat:%f long:%f alt:%f vel:%f angle:%f\n",pack.satinuse,pack.sig,info.lat,info.lon,info.elv,info.speed*1000./3600.,info.direction);
//Printf("lat:%f long:%f\n",pos.lat,pos.lon);

    gpsData->GetMutex(); // on utilise le mutex de gpsData pour fix et nb_sat
    if (gpsData->GetFixQuality() != (GpsData::FixQuality_t)pack.sig) {
      gpsData->SetFixQuality((GpsData::FixQuality_t)pack.sig);
      fixLabel->SetText("fix: %i", pack.sig);
    }
    if (gpsData->GetNumberOfSatellites() != pack.satinuse) {
      gpsData->SetNumberOfSatellites(pack.satinuse) ;
      nbSatLabel->SetText("nb_sat: %i", pack.satinuse);
    }
    gpsData->ReleaseMutex();

    gpsData->SetLla(Euler::ToDegree(pos.lat), Euler::ToDegree(pos.lon),info.elv);
    position->SetCoordinates(Euler::ToDegree(pos.lat), Euler::ToDegree(pos.lon),
                             info.elv);

    if ((info.sig == 2 && altRef == 0) || buttonRef->Clicked() == true ||
        takeRef == true) {
      Printf("prise pos ref\n");
      latRef = pos.lat;
      longRef = pos.lon;
      altRef = info.elv;
      takeRef = false;
    }
    // if(alt_ref!=0)
    {
      double x, y, z;
      double e, n, u;
      Geographique_2_ECEF(pos.lon, pos.lat, info.elv, x, y, z);
      ECEF_2_ENU(x, y, z, e, n, u, longRef, latRef, altRef);
      // Printf("lon:%f lat:%f elv:%f\n",pos.lon,pos.lat,info.elv);

      gpsData->SetEnu(e,n,u);

      if ((NMEAFlags & VTG) != 0) {
        gpsData->SetVelocity(info.speed * 1000. / 3600. * sin(Euler::ToRadian(info.direction)),
                                  info.speed * 1000. / 3600. * cos(Euler::ToRadian(info.direction)));
      }/*
      if ((NMEAFlags & GST) != 0) {
        // Thread::Printf("dev_lon:%f dev_lat:%f
        // dev_elv:%f\n",info.dev_lat,info.dev_lon,info.dev_elv);
        output->SetValueNoMutex(index, 0, info.dev_lat);
        output->SetValueNoMutex(index + 1, 0, info.dev_lon);
        output->SetValueNoMutex(index + 2, 0, info.dev_elv);
        index += 3;
      }*/


      gpsData->SetDataTime(GetTime());
      ProcessUpdate(gpsData);
    }
  }
}

} // end namespace sensor
} // end namespace framewor
