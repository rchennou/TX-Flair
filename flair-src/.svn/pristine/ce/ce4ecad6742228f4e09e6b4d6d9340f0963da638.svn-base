// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   Model_impl.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un modele a simuler
//
/*********************************************************************/

#ifndef MODEL_IMPL_H
#define MODEL_IMPL_H

#include <Thread.h>
#include <vrpn_Tracker.h>
#include "Model.h"
#include "Quaternion.h"

namespace flair {
namespace core {
class cvmatrix;
class Mutex;
class ConditionVariable;
}
namespace gui {
class TabWidget;
class CheckBox;
class DoubleSpinBox;
class SpinBox;
class Vector3DSpinBox;
}
namespace simulator {
class Simulator;
class FollowMeCamera;
}
}

#ifdef GL
#include <Vector3D.h>
#include <IMeshSceneNode.h>

namespace irr {
namespace scene {
class ISceneManager;
class ITriangleSelector;
class IMetaTriangleSelector;
class ISceneNodeAnimatorCollisionResponse;
}
}
#endif

#ifdef GL
class Model_impl : public irr::scene::ISceneNode,
                   public flair::core::Thread,
                   private vrpn_Tracker
#else
class Model_impl : public flair::core::Thread,
                   private vrpn_Tracker
#endif
                   {
public:
#ifdef GL
  Model_impl(flair::simulator::Model *self, std::string name,
             irr::scene::ISceneManager *scenemanager, vrpn_Connection_IP *vrpn);
#else
  Model_impl(flair::simulator::Model *self, std::string name,
             vrpn_Connection_IP *vrpn);
#endif
  ~Model_impl();

#ifdef GL
  void OnRegisterSceneNode(void);
  void render(void);
  void Draw(void) {
    printf("CA MARCHE PAS PUNAISE\r\n");
    ExtraDraw();
  };
  void ExtraDraw(void) { printf("nope\r\n"); };

  const irr::core::aabbox3d<irr::f32> &getBoundingBox(void) const {
    return box;
  }
  void UpdatePos(void);
  void CheckCollision(void);
  irr::scene::ITriangleSelector *TriangleSelector(void);
  irr::scene::IMetaTriangleSelector *MetaTriangleSelector(void);
  irr::core::aabbox3d<irr::f32> box;
  void SynchronizationPoint();
  flair::simulator::FollowMeCamera *camera;
  irr::scene::ITriangleSelector *selector;
#endif
  void mainloop(void);

  flair::gui::TabWidget *tabwidget;
  flair::gui::DoubleSpinBox *dT;

private:
  flair::gui::Vector3DSpinBox *pos_init;
  flair::gui::SpinBox *yaw_init;
  flair::gui::CheckBox *enable_opti;
  flair::simulator::Model *self;
  flair::core::cvmatrix *output;
  flair::core::Mutex *states_mutex;

  struct timeval _timestamp;
  void Run(void);
  flair::core::Quaternion ComputeInitRotation(flair::core::Quaternion quat_in);
#ifdef GL
  void CollisionHandler(void);

  irr::scene::IMetaTriangleSelector *meta_selector;
  irr::scene::ISceneNodeAnimatorCollisionResponse *anim;

  bool position_init;

  flair::core::ConditionVariable *cond;
  int sync_count;

  flair::core::Mutex *collision_mutex;
  bool collision_occured;
  flair::core::Vector3D collision_point;
#endif
};

#endif // MODEL_IMPL_H
