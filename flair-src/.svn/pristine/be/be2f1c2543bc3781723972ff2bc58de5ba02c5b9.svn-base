// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/02/05
//  filename:   UavFactory.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:   construct a Uav based on the type name
//
//
/*********************************************************************/

#include "UavFactory.h"
#include "FrameworkManager.h"
#include "SimuX4.h"
#include "SimuX8.h"
#include "HdsX8.h"
#include "XAir.h"
#include "compile_info.h"

using namespace std;
using namespace flair::core;
using namespace flair::filter;
using namespace flair::meta;

namespace { // anonymous
     vector<flair::meta::Uav* (*)(FrameworkManager*,string,string,UavMultiplex*)> *vectoroffunctions=NULL;
}


static void constructor() __attribute__((constructor));

void constructor() {
  compile_info("FlairMeta");
}


Uav *CreateUav(FrameworkManager *parent, string uav_name, string uav_type,
               UavMultiplex *multiplex) {

  Uav *uav;

  if(vectoroffunctions!=NULL) {
    for(int i=0;i<vectoroffunctions->size();i++) {
      uav=vectoroffunctions->at(i)(parent, uav_name, uav_type,multiplex);
      if(uav!=NULL) {
        free(vectoroffunctions);
        vectoroffunctions=NULL;
        return uav;
      }
    }
  }

  if (uav_type == "hds_x4") {
    parent->Err("UAV type %s not yet implemented\n", uav_type.c_str());
    return NULL;
  } else if (uav_type == "hds_x8") {
    return new HdsX8(parent, uav_name, multiplex);
  } else if (uav_type == "xair") {
    return new XAir(parent, uav_name, multiplex);
  } else if (uav_type == "hds_xufo") {
    parent->Err("UAV type %s not yet implemented\n", uav_type.c_str());
    return NULL;
  } else if (uav_type.compare(0, 7, "x4_simu") == 0) {
    int simu_id = 0;
    if (uav_type.size() > 7) {
      simu_id = atoi(uav_type.substr(7, uav_type.size() - 7).c_str());
    }
    return new SimuX4(parent, uav_name, simu_id, multiplex);
  } else if (uav_type.compare(0, 7, "x8_simu") == 0) {
    int simu_id = 0;
    if (uav_type.size() > 7) {
      simu_id = atoi(uav_type.substr(7, uav_type.size() - 7).c_str());
    }
    return new SimuX8(parent, uav_name, simu_id, multiplex);
  } else {
    parent->Err("UAV type %s unknown\n", uav_type.c_str());
    return NULL;
  }
}

void RegisterUavCreator(flair::meta::Uav*(*func)(FrameworkManager *parent, string uav_name, string uav_type,
               UavMultiplex *multiplex)) {
  if(vectoroffunctions==NULL) vectoroffunctions=(vector<flair::meta::Uav* (*)(FrameworkManager*,string,string,UavMultiplex*)>*)malloc(sizeof(vector<flair::meta::Uav* (*)(FrameworkManager*,string,string,UavMultiplex*)>));

  vectoroffunctions->push_back(func);
}
