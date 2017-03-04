// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/27
//  filename:   Gui.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant une Gui
//
/*********************************************************************/
#ifdef GL

#include "Gui.h"
#include "Gui_impl.h"
#include "Simulator.h"
#include "Model.h"
#include <IMeshSceneNode.h>
#include <IVideoDriver.h>
#include <ISceneManager.h>
#include <algorithm>
#include <GL/gl.h>
#include "compile_info.h"

//todo: put it on seprate file, but not possible with static lib?
static void constructor() __attribute__((constructor));

void constructor() {
  compile_info("FlairSimulator");
}

using namespace irr;
using namespace irr::video;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace flair::core;

namespace {
flair::simulator::Gui *gui_ = NULL;
std::vector<std::string> extensions;
bool getGlInfo();
}

namespace flair {
namespace simulator {

Gui *getGui(void) { return gui_; }

bool noGui(void) {
  if (gui_ == NULL) {
    return true;
  } else {
    return false;
  }
}

// getGlinfo, code from Song Ho Ahn (song.ahn@gmail.com)
bool getGlInfo() {
  char *str = 0;
  char *tok = 0;

  // get all extensions as a string
  str = (char *)glGetString(GL_EXTENSIONS);

  // split extensions
  if (str) {
    tok = strtok((char *)str, " ");
    while (tok) {
      extensions.push_back(tok); // put a extension into struct
      tok = strtok(0, " ");      // next token
    }
  } else {
    printf("cannot get gl extensions\n");
  }

  // sort extension by alphabetical order
  std::sort(extensions.begin(), extensions.end());
}

// isGlExtensionSupported, code from Song Ho Ahn (song.ahn@gmail.com)
bool isGlExtensionSupported(const std::string &ext) {
  if (extensions.size() == 0)
    getGlInfo();

  // search corresponding extension
  std::vector<std::string>::const_iterator iter = extensions.begin();
  std::vector<std::string>::const_iterator endIter = extensions.end();

  while (iter != endIter) {
    if (ext == *iter)
      return true;
    else
      ++iter;
  }
  return false;
}

float ToIrrlichtScale(float value) { return value * 100.; }

float ToSimulatorScale(float value) { return value / 100.; }

vector3df ToIrrlichtCoordinates(vector3df vect) {
  return ToIrrlichtScale(1) * vector3df(vect.X, vect.Y, -vect.Z);
}

vector3df ToIrrlichtCoordinates(Vector3D vect) {
  return ToIrrlichtScale(1) * vector3df(vect.x, vect.y, -vect.z);
}

Vector3D ToSimulatorCoordinates(vector3df vect) {
  return ToSimulatorScale(1) * Vector3D(vect.X, vect.Y, -vect.Z);
}

Quaternion ToIrrlichtOrientation(Quaternion quat) {
  /* original code
  Euler euler;
  quat.ToEuler(euler);
  matrix4 m;
  m.setRotationRadians(vector3df(0, 0, euler.yaw));
  matrix4 n;
  n.setRotationRadians(vector3df(0, -euler.pitch,0));
  m *= n;
  n.setRotationRadians(vector3df(-euler.roll, 0, 0));
  m *= n;
  */
  // seems to be equivalent to:
  return Quaternion(quat.q0, -quat.q1, -quat.q2, quat.q3);
}

Gui::Gui(const Simulator *parent, std::string name, int app_width,
         int app_height, int scene_width, int scene_height,
         std::string media_path, E_DRIVER_TYPE driver_type)
    : Object(parent, name, "Gui") {
  if (gui_ != NULL)
    Err("Gui should be instanced only one time\n");
  pimpl_ = new Gui_impl(this, app_width, app_height, scene_width, scene_height,
                        media_path, driver_type);
  gui_ = this;
}

Gui::~Gui() { delete pimpl_; }

float Gui::getAspectRatio(void) const {
  return (float)pimpl_->scene_width / (float)pimpl_->scene_height;
}

ISceneManager *Gui::getSceneManager(void) const { return pimpl_->smgr; }

void Gui::setMesh(std::string file, vector3df position, vector3df rotation,
                  vector3df scale) {
  pimpl_->setMesh(file, position, rotation, scale);
}

vector3df Gui::getRotation(void) const { return pimpl_->node->getRotation(); }

IrrlichtDevice *Gui::getDevice(void) const { return pimpl_->device; }

ITexture *Gui::getTexture(std::string filename) const {
  filename = pimpl_->media_path + "/" + filename;
  return pimpl_->driver->getTexture(filename.c_str());
}

IAnimatedMesh *Gui::getMesh(std::string filename) const {
  filename = pimpl_->media_path + "/" + filename;
  return pimpl_->smgr->getMesh(filename.c_str());
}

} // end namespace simulator
} // end namespace flair
#endif // GL
