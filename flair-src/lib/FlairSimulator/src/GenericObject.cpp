// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   GenericObject.cpp
//
//  author:     Cesar Richard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un modele a simuler
//
/*********************************************************************/

#ifdef GL
#include "GenericObject.h"
#include "Simulator_impl.h"

#include "Quaternion.h"
#include <ISceneManager.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

using namespace flair::core;
using namespace flair::simulator;

namespace flair {
namespace simulator {

GenericObject::GenericObject(Simulator *parent, std::string name,
                             ISceneManager *sceneManager)
    : IMeshSceneNode(sceneManager->getRootSceneNode(), sceneManager,
                     -1) //, IODevice(parent,name)
{
  setMaterialFlag(EMF_LIGHTING, false);
  Material = getMaterial(0);
  // setMaterialTexture(0,sceneManager->getVideoDriver()->getTexture("/home/cesar/igep/uav_dev_svn/trunk/media/nskinbl.jpg"));
  Material.NormalizeNormals = true;
  Material.Wireframe = false;
  Material.Lighting = false;

  parent->pimpl_->objects.push_back(this);
}

GenericObject::~GenericObject() {}

void GenericObject::setScale(float value) {
  ISceneNode::setScale(vector3df(value, value, value));
}

void GenericObject::setScale(vector3df scale) { ISceneNode::setScale(scale); }

ITriangleSelector *GenericObject::TriangleSelector(void) { return selector; }

void GenericObject::OnRegisterSceneNode(void) {
  if (IsVisible)
    SceneManager->registerNodeForRendering(this);

  ISceneNode::OnRegisterSceneNode();
}

void GenericObject::render(void) {
  IVideoDriver *driver = SceneManager->getVideoDriver();

  driver->setMaterial(Material);

  driver->setTransform(ETS_WORLD, AbsoluteTransformation);
  driver->drawMeshBuffer(mesh->getMeshBuffer(0));
}

void GenericObject::setMesh(IMesh *mesh) {
  this->mesh = mesh;
  box = mesh->getBoundingBox();

  selector = getSceneManager()->createTriangleSelector(mesh, this);
  setTriangleSelector(selector);
}

IMesh *GenericObject::getMesh(void) { return mesh; }

void GenericObject::setPosition(irr::core::vector3df pos) {
  ISceneNode::setPosition(ToIrrlichtCoordinates(pos));
}

void GenericObject::setRotation(irr::core::vector3df rotation) {
  Euler eulerA(rotation.X, rotation.Y, rotation.Z);
  Euler eulerB;
  Quaternion quatA, quatB;
  eulerA.ToQuaternion(quatA);
  quatB = ToIrrlichtOrientation(quatA);
  quatB.ToEuler(eulerB);

  ISceneNode::setRotation(Euler::ToDegree(1) *
                          vector3df(eulerB.roll, eulerB.pitch, eulerB.yaw));
}

} // end namespace simulator
} // end namespace flair
#endif
