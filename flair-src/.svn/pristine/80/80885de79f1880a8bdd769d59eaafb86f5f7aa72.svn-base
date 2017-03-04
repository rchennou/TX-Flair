// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   GenericObject.h
//
//  author:     Cesar Richard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un modele a simuler
//
/*********************************************************************/

#ifndef GENERICOBJECT_H
#define GENERICOBJECT_H
#ifdef GL

#include "Simulator.h"

#include "ConditionVariable.h"
#include "Gui.h"
#include "Gui_impl.h"
#include <ISceneManager.h>
#include <ISceneNodeAnimatorCollisionResponse.h>
#include <IMetaTriangleSelector.h>
#include <IVideoDriver.h>
#include <ICameraSceneNode.h>
#include "FollowMeCamera.h"

#include <IODevice.h>
#include <Euler.h>
#include <Vector3D.h>

#include <aabbox3d.h>
#include <IMeshSceneNode.h>

namespace irr {
class SEvent;
namespace scene {
class IMesh;
class ISceneManager;
class ITriangleSelector;
class IMetaTriangleSelector;
class ISceneNodeAnimatorCollisionResponse;
}
}

class Gui_impl;
class Simulator_impl;

namespace flair {
namespace core {
class ConditionVariable;
}
namespace simulator {
class Simulator;
class AnimPoursuite;

class GenericObject : public irr::scene::IMeshSceneNode {
  friend class ::Simulator_impl;

public:
  GenericObject(Simulator *parent, std::string name,
                irr::scene::ISceneManager *sceneManager);
  virtual ~GenericObject();

  // FROM IMPL
  irr::scene::ITriangleSelector *TriangleSelector(void);
  irr::core::aabbox3d<irr::f32> box;
  // END FROM IMPL

  irr::scene::ISceneNode *getSceneNode();
  virtual const irr::core::aabbox3d<irr::f32> &getBoundingBox(void) const {
    return box;
  }

  void setPosition(irr::core::vector3df position);
  void setScale(float value);
  void setScale(irr::core::vector3df scale);
  void setRotation(irr::core::vector3df rotation);
  void OnRegisterSceneNode(void);
  void setMesh(irr::scene::IMesh *mesh);
  irr::scene::IMesh *getMesh(void);
  void render(void);
  virtual void setReadOnlyMaterials(bool readonly){};
  virtual bool isReadOnlyMaterials(void) const { return false; }
  virtual irr::scene::IShadowVolumeSceneNode *
  addShadowVolumeSceneNode(const irr::scene::IMesh *shadowMesh = 0,
                           irr::s32 id = -1, bool zfailmethod = true,
                           irr::f32 infinity = 1000.0f) {
    return NULL;
  }

private:
  void UpdateFrom(core::io_data *data){};
  irr::scene::IMesh *mesh;
  irr::scene::ITriangleSelector *selector;
  flair::core::ConditionVariable *cond;
  irr::video::SMaterial Material;
};
} // end namespace simulator
} // end namespace flair
#endif // GL
#endif // GENERICOBJECT_H
