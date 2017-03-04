// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/27
//  filename:   Castle.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe chargeant une map chateau
//
/*********************************************************************/
#ifdef GL

#include "Castle.h"
#include "Simulator.h"
#include <IrrlichtDevice.h>
#include <IFileSystem.h>

using namespace irr::core;
using namespace flair::core;

namespace flair {
namespace simulator {

Castle::Castle(const Simulator *parent, int app_width, int app_height,
               int scene_width, int scene_height, std::string media_path)
    : Gui(parent, "Castle", app_width, app_height, scene_width, scene_height,
          media_path) {
  // carte
  std::string file = media_path + "/map-20kdm2.pk3";
  getDevice()->getFileSystem()->addFileArchive(file.c_str());
  setMesh("20kdm2.bsp", vector3df(-1400, -65, -1349));
}

Castle::~Castle() {}

} // end namespace simulator
} // end namespace flair
#endif // GL
