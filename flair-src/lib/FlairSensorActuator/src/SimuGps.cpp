// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/05/26
//  filename:   SimuGps.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for a simulation GPS
//
//
/*********************************************************************/

#include "SimuGps.h"
#include <FrameworkManager.h>
#include <GeoCoordinate.h>
#include <GpsData.h>
#include <SharedMem.h>
#include <SpinBox.h>
#include <DoubleSpinBox.h>
#include <GroupBox.h>
#include <Euler.h>
#include <cvmatrix.h>
#include <sstream>
#include "geodesie.h"

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;
using namespace Geodesie;

namespace flair {
namespace sensor {

SimuGps::SimuGps(const FrameworkManager *parent, string name,
                 NmeaGps::NMEAFlags_t NMEAFlags, uint32_t deviceId,uint8_t priority)
    : NmeaGps(parent, name, NMEAFlags),Thread(parent, name, priority) {

  dataRate = new SpinBox(GetGroupBox()->NewRow(), "data rate", " Hz", 1, 500, 1, 200);
  latitudeRef = new DoubleSpinBox(GetGroupBox()->NewRow(), "latitude ref", " deg", -90, 90, 1, 6,49.402313);
  longitudeRef = new DoubleSpinBox(GetGroupBox()->LastRowLastCol(), "longitude ref", " deg", -180, 180, 1, 6,2.795463);
  altitudeRef= new DoubleSpinBox(GetGroupBox()->LastRowLastCol(), "altitude ref", " m", 0, 6000, 100, 1,0);
  fixQuality = new SpinBox(GetGroupBox()->NewRow(), "fix quality", 1, 8, 1, 1);
  numberOfSatellites = new SpinBox(GetGroupBox()->NewRow(), "number of satellites", 1, 15, 1, 5);

  ostringstream dev_name;
  dev_name << "simu_gps_" << deviceId;
  shmem = new SharedMem((Thread *)this, dev_name.str().c_str(),
                        sizeof(gps_states_t));
}


SimuGps::SimuGps(const IODevice *parent, string name, uint32_t deviceId)
    : NmeaGps(parent, name), Thread(parent, name, 0) {
  dataRate = NULL;

  ostringstream dev_name;
  dev_name << "simu_gps_" << deviceId;
  shmem = new SharedMem((Thread *)this, dev_name.str().c_str(),
                        sizeof(gps_states_t));
}

SimuGps::~SimuGps() {
  SafeStop();
  Join();
}

void SimuGps::UpdateFrom(const io_data *data) {
  if (data != NULL) {
    cvmatrix *input = (cvmatrix *)data;
    gps_states_t state;

    input->GetMutex();
    //simulator is ned, convert it to enu
    //TODO: put simulator in enu?
    state.e = input->ValueNoMutex(5, 0);//y simulator
    state.n = input->ValueNoMutex(4, 0);//x simulator
    state.u = -input->ValueNoMutex(6, 0);//z simulator
    state.ve = input->ValueNoMutex(11, 0);//vy simulator
    state.vn = input->ValueNoMutex(10, 0);//vx simulator
    input->ReleaseMutex();

    shmem->Write((char *)&state, sizeof(gps_states_t));
  }
}

void SimuGps::Run(void) {
  gps_states_t state;
  char buf[512];
  nmeaGPGGA gga;
  nmeaGPVTG vtg;
  nmeaPOS pos;
  nmeaINFO info;

  vtg.dir_t='T';
  vtg.dec_m='M';
  vtg.spk_k='K';
  vtg.spn_n='N';

  if (dataRate == NULL) {
    Thread::Err("not applicable for simulation part.\n");
    return;
  }

  SetPeriodUS((uint32_t)(1000000. / dataRate->Value()));

  WarnUponSwitches(true);


  while (!ToBeStopped()) {
    WaitPeriod();

    if (dataRate->ValueChanged() == true) {
      SetPeriodUS((uint32_t)(1000000. / dataRate->Value()));
    }

    shmem->Read((char *)&state, sizeof(gps_states_t));

    double x, y, z;
    ENU_2_ECEF(state.e, state.n, state.u, x,y,z, Euler::ToRadian(longitudeRef->Value()), Euler::ToRadian(latitudeRef->Value()), altitudeRef->Value());
    ECEF_2_Geographique( x, y, z,pos.lon, pos.lat, gga.elv);
    nmea_pos2info(&pos,&info);

    if(pos.lat>0) {
      gga.ns='N';
      gga.lat=info.lat;
    } else {
      gga.ns='S';
      gga.lat=-info.lat;
    }
    if(pos.lon>0) {
      gga.ew='E';
      gga.lon=info.lon;
    } else {
      gga.ew='W';
      gga.lon=-info.lon;
    }

    gga.sig=fixQuality->Value();
    gga.satinuse=numberOfSatellites->Value();

    nmea_gen_GPGGA(buf,sizeof(buf),&gga);
    parseFrame(buf,sizeof(buf));

    vtg.dir=90-Euler::ToDegree(atan2f(state.vn,state.ve));
    vtg.spk=sqrtf(state.ve*state.ve+state.vn*state.vn)*3600./1000.;
    nmea_gen_GPVTG(buf,sizeof(buf),&vtg);
    parseFrame(buf,sizeof(buf));
  }

  WarnUponSwitches(false);
}

} // end namespace sensor
} // end namespace framewor
