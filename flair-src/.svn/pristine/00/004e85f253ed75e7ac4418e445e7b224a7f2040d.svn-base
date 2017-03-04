// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/21
//  filename:   FollowMeCamera.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant une animation poursuite pour camera
//
/*********************************************************************/

#ifndef FOLLOWMECAMERA_H
#define FOLLOWMECAMERA_H

#include "VisualizationCamera.h"


namespace flair {
namespace simulator {

class FollowMeCamera : public VisualizationCamera {
public:
  FollowMeCamera(const irr::scene::ISceneNode *parent,std::string name,
                float rotateSpeed = -500.0f, float zoomSpeed = 4.0f);
  ~FollowMeCamera();

  void animateNode(irr::scene::ISceneNode *node, irr::u32 timeMs);
  void setPositionOffset(irr::core::vector3df newpos);
  void setTargetOffset(irr::core::vector3df newpos);

private:
  irr::core::vector3df pos_offset, target_offset;
  irr::core::position2df RotateStart;
  const irr::scene::ISceneNode *parent;
  bool Rotating;
  float RotY, RotZ;
  float sat(float value);
  float rotateSpeed;
  float zoomSpeed;
};

} // end namespace simulator
} // end namespace flair

#endif // FOLLOWMECAMERA_H
