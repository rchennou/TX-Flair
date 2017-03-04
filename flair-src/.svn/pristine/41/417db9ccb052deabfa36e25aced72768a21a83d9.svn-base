// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/22
//  filename:   Blade.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant une helice
//
/*********************************************************************/
#ifdef GL

#include "Blade.h"
#include "MeshSceneNode.h"
#include "Model.h"
#include "Gui.h"
#include "Simulator.h"
#include <IGeometryCreator.h>
#include <ISceneManager.h>
#include <IFileSystem.h>
#include <IVideoDriver.h>

using namespace irr;
using namespace irr::video;
using namespace irr::scene;
using namespace irr::core;
using namespace irr::io;
using namespace flair::core;

namespace flair {
namespace simulator {

Blade::Blade(Model *parent, const vector3df &position, bool inverted, s32 id)
    : ISceneNode(parent->getSceneNode(), getGui()->getSceneManager(), id,
                 position) {
  ISceneManager *mgr = getGui()->getSceneManager();

  const IGeometryCreator *geo;
  geo = mgr->getGeometryCreator();
  pale = geo->createCubeMesh(vector3df(63.5, 0.5, 5));

  float angle;
  if (inverted == false) {
    angle = 20;
  } else {
    angle = -20;
  }

  ITexture *texture = getGui()->getTexture("carbone.jpg");
  pale_1 = new MeshSceneNode(parent, pale, vector3df(-30, 0, 0),
                             vector3df(-angle + 90, 0, 0), texture);
  pale_1->setParent(this);
  pale_2 = new MeshSceneNode(parent, pale, vector3df(30, 0, 0),
                             vector3df(angle + 90, 0, 0), texture);
  pale_2->setParent(this);

  anim = mgr->createRotationAnimator(vector3df(0.f, 0.f, 0.f));
  addAnimator(anim);
}

void Blade::OnRegisterSceneNode() {
  if (IsVisible)
    SceneManager->registerNodeForRendering(this);

  ISceneNode::OnRegisterSceneNode();
}

void Blade::SetRotationSpeed(float value) {
  IAttributes *attribs =
      getSceneManager()->getFileSystem()->createEmptyAttributes();

  attribs->setAttribute("Type", "rotation");
  attribs->setAttribute("Rotation", vector3df(0.f, 0.f, value));
  anim->deserializeAttributes(attribs);

  attribs->drop();
}

void Blade::render() {
  IVideoDriver *driver = SceneManager->getVideoDriver();
  driver->setTransform(ETS_WORLD, AbsoluteTransformation);
}

} // end namespace simulator
} // end namespace flair
#endif // GL
