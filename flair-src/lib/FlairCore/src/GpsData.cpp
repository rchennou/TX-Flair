// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/07/01
//  filename:   GpsData.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class defining gps datas
//
//
/*********************************************************************/

#include "GpsData.h"
#include "Euler.h"
#include "IODataElement.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

using std::string;

namespace flair {
namespace core {

/*! \class GpsDataElement
    */
class GpsDataElement : public IODataElement {
public:
  GpsDataElement(const GpsData *inGpsdata, string name,
                 GpsData::PlotableData_t inPlotableData)
      : IODataElement(inGpsdata, name) {
    gpsdata = inGpsdata;
    plotableData = inPlotableData;

    switch (plotableData) {
    case GpsData::Latitude:
    case GpsData::Longitude:
      size = 8;
      break;
    case GpsData::Altitude:
    case GpsData::East:
    case GpsData::North:
    case GpsData::Up:
    case GpsData::EastVelocity:
    case GpsData::NorthVelocity:
      size=4;
      break;
    case GpsData::NumberOfSatellites:
    case GpsData::FixQuality:
      size=1;
      break;
    }
  }

  ~GpsDataElement() {}

  void CopyData(char *dst) const {
    double latitude,longitude;
    float altitude,east,north,up,eastVelocity,northVelocity;

    gpsdata->GetLla(latitude,longitude,altitude);
    uint8_t numberOfSatellites=gpsdata->GetNumberOfSatellites();
    GpsData::FixQuality_t fixQuality=gpsdata->GetFixQuality();
    gpsdata->GetEnu(east,north,up);
    gpsdata->GetVelocity(eastVelocity,northVelocity);

    switch (plotableData) {
    case GpsData::Latitude:
      memcpy(dst, &latitude, sizeof(latitude));
      break;
    case GpsData::Longitude:
      memcpy(dst, &longitude, sizeof(longitude));
      break;
    case GpsData::Altitude:
      memcpy(dst, &altitude, sizeof(altitude));
      break;
    case GpsData::NumberOfSatellites:
      memcpy(dst, &numberOfSatellites, sizeof(numberOfSatellites));
      break;
    case GpsData::FixQuality:
      memcpy(dst, &fixQuality, sizeof(fixQuality));
      break;
    case GpsData::East:
      memcpy(dst, &east, sizeof(east));
      break;
    case GpsData::North:
      memcpy(dst, &north, sizeof(north));
      break;
    case GpsData::Up:
      memcpy(dst, &up, sizeof(up));
      break;
     case GpsData::EastVelocity:
      memcpy(dst, &eastVelocity, sizeof(eastVelocity));
      break;
    case GpsData::NorthVelocity:
      memcpy(dst, &northVelocity, sizeof(northVelocity));
      break;
    default:
      gpsdata->Err("data type unavailable.\n");
      break;
    }
  }

  DataType const &GetDataType(void) const {
    switch (plotableData) {
    case GpsData::Latitude:
    case GpsData::Longitude:
      return doubleType;
      break;
    case GpsData::Altitude:
    case GpsData::East:
    case GpsData::North:
    case GpsData::Up:
    case GpsData::EastVelocity:
    case GpsData::NorthVelocity:
      return floatType;
      break;
    case GpsData::NumberOfSatellites:
    case GpsData::FixQuality:
      return UInt8Type;
      break;
    default:
      return dummyType;
    }
  }

private:
  const GpsData *gpsdata;
  GpsData::PlotableData_t plotableData;
};

GpsData::GpsData(const Object *parent, std::string name, int n)
    : io_data(parent, name, n), dataType() {
  if (n > 1)
    Warn("n>1 not supported\n");

  AppendLogDescription("latitude", doubleType);
  AppendLogDescription("longitude", doubleType);
  AppendLogDescription("altitude", floatType);
  AppendLogDescription("nb_sat",UInt8Type);
  AppendLogDescription("fix quality",UInt8Type);
  AppendLogDescription("east", floatType);
  AppendLogDescription("north", floatType);
  AppendLogDescription("up", floatType);
  AppendLogDescription("east velocity", floatType);
  AppendLogDescription("north velocity", floatType);

  numberOfSatellites=0;
  fixQuality=FixQuality_t::Invalid;
}

GpsData::~GpsData() {}

void GpsData::GetLla(double &outLatitude, double &outLongitude, float &outAltitude) const {
  GetMutex();
  outLatitude=latitude;
  outLongitude=longitude;
  outAltitude=altitude;
  ReleaseMutex();
}

void GpsData::SetLla(double inLatitude,double inLongitude,float inAltitude) {
  GetMutex();
  latitude=inLatitude;
  longitude=inLongitude;
  altitude=inAltitude;
  ReleaseMutex();
}

void GpsData::GetEnu(float &outEast, float &outNorth,float &outUp) const {
  GetMutex();
  outEast=east;
  outNorth=north;
  outUp=up;
  ReleaseMutex();
}

void GpsData::SetEnu(float inEast, float inNorth,float inUp) {
  GetMutex();
  east=inEast;
  north=inNorth;
  up=inUp;
  ReleaseMutex();
}


void GpsData::GetVelocity(float &outEastVelocity, float &outNorthVelocity) const {
  GetMutex();
  outEastVelocity=eastVelocity;
  outNorthVelocity=northVelocity;
  ReleaseMutex();
}

void GpsData::SetVelocity(float inEastVelocity, float inNorthVelocity) {
  GetMutex();
  eastVelocity=inEastVelocity;
  northVelocity=inNorthVelocity;
  ReleaseMutex();
}

uint8_t GpsData::GetNumberOfSatellites(void) const {
  return numberOfSatellites;
}

void GpsData::SetNumberOfSatellites(uint8_t inNumberOfSatellites) {
  numberOfSatellites=inNumberOfSatellites;
}

GpsData::FixQuality_t GpsData::GetFixQuality(void) const {
  return fixQuality;
}

void GpsData::SetFixQuality(FixQuality_t inFixQuality) {
  fixQuality=inFixQuality;
}

IODataElement *GpsData::Element(PlotableData_t data_type) const {
  string name;
  switch (data_type) {
  case GpsData::Latitude:
    name = "Latitude";
    break;
  case GpsData::Longitude:
    name = "Longitude";
    break;
  case GpsData::Altitude:
    name = "Altitude";
    break;
  case GpsData::NumberOfSatellites:
    name = "NumberOfSatellites";
    break;
  case GpsData::FixQuality:
    name = "FixQuality";
    break;
  case GpsData::East:
    name = "East";
    break;
  case GpsData::North:
    name = "North";
    break;
  case GpsData::Up:
    name = "Up";
    break;
  case GpsData::EastVelocity:
    name = "EastVelocity";
    break;
  case GpsData::NorthVelocity:
    name = "NorthVelocity";
    break;
  }

  return new GpsDataElement(this, name, data_type);
}

void GpsData::CopyDatas(char *dst) const {
  GetMutex();

  Queue(&dst, &latitude, sizeof(latitude));
  Queue(&dst, &longitude, sizeof(longitude));
  Queue(&dst, &altitude, sizeof(altitude));
  Queue(&dst, &numberOfSatellites, sizeof(numberOfSatellites));
  Queue(&dst, &fixQuality, sizeof(FixQuality_t));
  Queue(&dst, &east, sizeof(east));
  Queue(&dst, &north, sizeof(north));
  Queue(&dst, &up, sizeof(up));
  Queue(&dst, &eastVelocity, sizeof(eastVelocity));
  Queue(&dst, &northVelocity, sizeof(northVelocity));

  ReleaseMutex();
}

void GpsData::Queue(char **dst, const void *src, size_t size) const {
  memcpy(*dst, src, size);
  *dst += size;
}

} // end namespace core
} // end namespace flair
