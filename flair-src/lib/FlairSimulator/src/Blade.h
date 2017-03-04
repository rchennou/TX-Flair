// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/22
//  filename:   Blade.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant une Blade
//
/*********************************************************************/

#ifndef BLADE_H
#define BLADE_H

#include <ISceneNode.h>

namespace irr {
namespace scene {
class IMesh;
}
}

namespace flair {
namespace simulator {
class MeshSceneNode;
class Model;

class Blade : public irr::scene::ISceneNode {
public:
  Blade(Model *parent,
        const irr::core::vector3df &position = irr::core::vector3df(0, 0, 0),
        bool inverted = false, irr::s32 id = -1);
  virtual void OnRegisterSceneNode(void);
  virtual void render(void);
  virtual const irr::core::aabbox3d<irr::f32> &getBoundingBox(void) const {
    return Box;
  }
  void SetRotationSpeed(float value);

private:
  irr::scene::IMesh *pale;
  irr::core::aabbox3d<irr::f32> Box;
  MeshSceneNode *pale_1, *pale_2;
  irr::scene::ISceneNodeAnimator *anim;
};
} // end namespace simulator
} // end namespace flair
#endif // BLADE_H
