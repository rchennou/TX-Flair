// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/22
//  filename:   MeshSceneNode.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un IMeshSceneNode
//
/*********************************************************************/
#ifdef GL

#include "MeshSceneNode.h"
#include "Gui.h"
#include "Model.h"
#include <ISceneManager.h>
#include <IVideoDriver.h>

using namespace irr;
using namespace irr::video;
using namespace irr::scene;
using namespace irr::core;
using namespace flair::core;

namespace flair {
namespace simulator {

MeshSceneNode::MeshSceneNode(Model *parent, IMesh *mesh,
                             const vector3df &position,
                             const vector3df &rotation, ITexture *texture,
                             s32 id)
    : IMeshSceneNode(parent->getSceneNode(), getGui()->getSceneManager(), id,
                     position, rotation) {
  Material.Wireframe = false;
  Material.Lighting = false;

  setMesh(mesh);

  if (texture != NULL) {
    setMaterialTexture(0, texture);
  }

  parent->Box()->addInternalBox(getTransformedBoundingBox());
}

void MeshSceneNode::OnRegisterSceneNode(void) {
  if (IsVisible)
    SceneManager->registerNodeForRendering(this);

  ISceneNode::OnRegisterSceneNode();
}

void MeshSceneNode::render(void) {
  IVideoDriver *driver = SceneManager->getVideoDriver();

  driver->setMaterial(Material);
  driver->setTransform(ETS_WORLD, AbsoluteTransformation);
  driver->drawMeshBuffer(mesh->getMeshBuffer(0));
}

SMaterial &MeshSceneNode::getMaterial(u32 i) { return Material; }

void MeshSceneNode::setMesh(IMesh *ptr) {
  mesh = ptr;
  Box = mesh->getBoundingBox();
}

IMesh *MeshSceneNode::getMesh(void) { return mesh; }

void MeshSceneNode::setReadOnlyMaterials(bool readonly) {}

} // end namespace simulator
} // end namespace flair
#endif // GL
