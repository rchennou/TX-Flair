// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/22
//  filename:   MeshSceneNode.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un IMeshSceneNode
//
/*********************************************************************/

#ifndef MESHSCENENODE_H
#define MESHSCENENODE_H

#include <IMeshSceneNode.h>

namespace flair {
namespace simulator {
class Model;

class MeshSceneNode : public irr::scene::IMeshSceneNode {
public:
  MeshSceneNode(
      Model *parent, irr::scene::IMesh *mesh,
      const irr::core::vector3df &position = irr::core::vector3df(0, 0, 0),
      const irr::core::vector3df &rotation = irr::core::vector3df(0, 0, 0),
      irr::video::ITexture *texture = NULL, irr::s32 id = -1);

  virtual void OnRegisterSceneNode(void);
  virtual void render(void);
  virtual const irr::core::aabbox3d<irr::f32> &getBoundingBox() const {
    return Box;
  }
  virtual irr::u32 getMaterialCount(void) const { return 1; }
  virtual irr::video::SMaterial &getMaterial(irr::u32 i);
  virtual void setMesh(irr::scene::IMesh *ptr);
  virtual irr::scene::IMesh *getMesh(void);
  virtual void setReadOnlyMaterials(bool readonly);
  virtual bool isReadOnlyMaterials(void) const { return false; }
  virtual irr::scene::IShadowVolumeSceneNode *
  addShadowVolumeSceneNode(const irr::scene::IMesh *shadowMesh = 0,
                           irr::s32 id = -1, bool zfailmethod = true,
                           irr::f32 infinity = 1000.0f) {
    return NULL;
  }

private:
  irr::scene::IMesh *mesh;
  irr::core::aabbox3d<irr::f32> Box;
  irr::video::SMaterial Material;
};
} // end namespace simulator
} // end namespace flair

#endif // MESHSCENENODE_H
