// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/07/23
//  filename:   Map.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a GPS map on the ground station
//
//
/*********************************************************************/

#include "Map.h"
#include "LayoutPosition.h"
#include "Layout.h"
#include "GeoCoordinate.h"
#include "FrameworkManager.h"
#include <cmath>
#include <string.h>
#include <sstream>

using std::string;
using std::ostringstream;

namespace flair {
namespace gui {

using namespace core;

Map::Map(const LayoutPosition *position, string name)
    : SendData(position, name, "Map", 1000) {
  size_t i = 0;
  while (1) {
    double latitude, longitude;
    double altitude = 0;
    ostringstream lat_prop, long_prop, alt_prop;
    lat_prop << "lat" << i;
    long_prop << "long" << i;
    alt_prop << "alt" << i;
    if (GetPersistentXmlProp(lat_prop.str(), latitude) &&
        GetPersistentXmlProp(long_prop.str(), longitude)) {
      SetVolatileXmlProp(lat_prop.str(), latitude);
      SetVolatileXmlProp(long_prop.str(), longitude);
      if (GetPersistentXmlProp(alt_prop.str(), altitude))
        SetVolatileXmlProp(alt_prop.str(), altitude);
      GeoCoordinate *checkpoint =
          new GeoCoordinate(this, "checkpoint", latitude, longitude, altitude);
      checkpoints.push_back(checkpoint);
    } else {
      break;
    }
    i++;
  }
  for (size_t i = 0; i < checkpoints.size(); i++) {
    double latitude, longitude, altitude;
    checkpoints.at(i)->GetCoordinates(&latitude, &longitude, &altitude);
    // printf("%i %f %f\n",i,latitude,longitude);
  }

  SendXml();
  /*
      //update value from xml file
      XmlEvent(XmlFileNode());
      if(checkpoints_node.size()!=0) SendXml();//pour les checkpoints

      //on enleve les checkpoints du xml
      for(size_t i=0;i<checkpoints_node.size();i++)
      {
          xmlUnlinkNode(checkpoints_node.at(i));
          xmlFreeNode(checkpoints_node.at(i));
      }*/
}

Map::~Map() {}

void Map::ExtraXmlEvent(void) {

  // attention pas rt safe (creation/destruction checkpoint)
  size_t i = 0;
  while (1) {
    double latitude, longitude;
    double altitude = 0;
    ostringstream lat_prop, long_prop, alt_prop;
    lat_prop << "lat" << i;
    long_prop << "long" << i;
    alt_prop << "alt" << i;

    if (GetPersistentXmlProp(lat_prop.str(), latitude) &&
        GetPersistentXmlProp(long_prop.str(), longitude)) {
      GetPersistentXmlProp(alt_prop.str(), altitude);

      if (i >= checkpoints.size()) {
        //add checkpoint
        GeoCoordinate *checkpoint = new GeoCoordinate(
            this, "checkpoint", latitude, longitude, altitude);
        checkpoints.push_back(checkpoint);
      } else if(isnan(latitude) || isnan(longitude)) {
        //delete checkpoint
        removeCheckpoint(i);
        break;//si delete, la station sol n'envoit que cette info
      } else {
        //move checkpoint
        checkpoints.at(i)->SetCoordinates(latitude, longitude, altitude);
      }
    } else {
      if (i == checkpoints.size())
        break;
    }
    i++;
  }
/*
  for (size_t i = 0; i < checkpoints.size(); i++) {
    double latitude, longitude, altitude;
    checkpoints.at(i)->GetCoordinates(&latitude, &longitude, &altitude);
     printf("%i %f %f\n",i,latitude,longitude);
  }*/
}

void Map::removeCheckpoint(size_t index) {
  //left shift
  for (size_t i = index; i < checkpoints.size()-1; i++) {
    double latitude, longitude, altitude;
    checkpoints.at(i+1)->GetCoordinates(&latitude, &longitude, &altitude);
    checkpoints.at(i)->SetCoordinates(latitude,longitude,altitude);
  }

  //remove last one
  delete checkpoints.back();
  checkpoints.pop_back();

  //remove last one in xml
  ostringstream lat_prop, long_prop, alt_prop;
  lat_prop << "lat" << checkpoints.size();
  long_prop << "long" << checkpoints.size();
  alt_prop << "alt" << checkpoints.size();
  UnsetPersistentXmlProp(lat_prop.str());
  UnsetPersistentXmlProp(long_prop.str());
  UnsetPersistentXmlProp(alt_prop.str());
}

void Map::AddPoint(const GeoCoordinate *point, string name) {
  SetVolatileXmlProp("point", name);
  SendXml();

  to_draw.push_back(point);
  SetSendSize(to_draw.size() * 3 * sizeof(double)); // lat,long,alt
}

void Map::CopyDatas(char *buf) const {
  for (size_t i = 0; i < to_draw.size(); i++) {
    double latitude, longitude, altitude;
    to_draw.at(i)->GetCoordinates(&latitude, &longitude, &altitude);
    memcpy(buf + i * 3 * sizeof(double), &latitude, sizeof(double));
    memcpy(buf + sizeof(double) + i * 3 * sizeof(double), &longitude,
           sizeof(double));
    memcpy(buf + 2 * sizeof(double) + i * 3 * sizeof(double), &altitude,
           sizeof(double));
  }
}

} // end namespace gui
} // end namespace flair
