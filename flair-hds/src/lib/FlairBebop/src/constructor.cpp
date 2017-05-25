// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/07/25
//  filename:   constructor.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    constructor for bebop lib
//
//
/*********************************************************************/

#include <stdio.h>
#include <UavFactory.h>
#include "Bebop.h"
#include "compile_info.h"

static void constructor() __attribute__((constructor));

using namespace std;
using namespace flair::core;
using namespace flair::filter;
using namespace flair::meta;

Uav *CreateBebop(string name, string uav_type,string options,
                 UavMultiplex *multiplex) {
  if (uav_type == "bebop") {
    return new Bebop(name, multiplex);
  } else {
    return NULL;
  }
}

void constructor() {
  compile_info("FlairBebop");
  RegisterUavCreator(CreateBebop);
}
