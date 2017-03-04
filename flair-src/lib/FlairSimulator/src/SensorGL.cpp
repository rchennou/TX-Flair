// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   SensorGL.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un modele de capteur
//
/*********************************************************************/
#ifdef GL

#include "SensorGL.h"
#include "Gui.h"
#include "Model.h"
#include "Model_impl.h"
#include <ISceneManager.h>

using namespace irr::scene;
using namespace flair::simulator;

namespace flair {
namespace sensor {

SensorGL::SensorGL(const Model *parent) {
  collMan = getGui()->getSceneManager()->getSceneCollisionManager();
  node = parent->Model::pimpl_;
}

SensorGL::~SensorGL() {}

ISceneCollisionManager *SensorGL::CollMan(void) const { return collMan; }

ISceneNode *SensorGL::Node(void) const { return node; }

} // end namespace simulator
} // end namespace flair
#endif
