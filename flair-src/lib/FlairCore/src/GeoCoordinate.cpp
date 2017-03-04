// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/07/29
//  filename:   GeoCoordinate.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a point by its lla coordinates
//
//
/*********************************************************************/

#include "GeoCoordinate.h"

using std::string;

namespace flair {
namespace core {

GeoCoordinate::GeoCoordinate(const Object *parent, string name,
                             const GeoCoordinate *point, int n)
    : io_data(parent, name, n) {
  if (n > 1)
    Warn("n>1 not supported\n");
  CopyFrom(point);
}

GeoCoordinate::GeoCoordinate(const Object *parent, string name, double latitude,
                             double longitude, double altitude, int n)
    : io_data(parent, name, n) {
  this->latitude = latitude;
  this->longitude = longitude;
  this->altitude = altitude;
}

GeoCoordinate::~GeoCoordinate() {}

void GeoCoordinate::CopyFrom(const GeoCoordinate *point) {
  double latitude, longitude, altitude;
  point->GetCoordinates(&latitude, &longitude, &altitude);
  GetMutex();
  this->latitude = latitude;
  this->longitude = longitude;
  this->altitude = altitude;
  ReleaseMutex();
}

void GeoCoordinate::SetCoordinates(double latitude, double longitude,
                                   double altitude) {
  GetMutex();
  this->latitude = latitude;
  this->longitude = longitude;
  this->altitude = altitude;
  ReleaseMutex();
}

void GeoCoordinate::GetCoordinates(double *latitude, double *longitude,
                                   double *altitude) const {
  GetMutex();
  *latitude = this->latitude;
  *longitude = this->longitude;
  *altitude = this->altitude;
  ReleaseMutex();
}

void GeoCoordinate::CopyDatas(char *ptr) const { Warn("a ecrire"); }

} // end namespace core
} // end namespace flair
