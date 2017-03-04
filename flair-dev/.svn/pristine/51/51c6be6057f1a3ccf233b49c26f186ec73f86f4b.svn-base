// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/01
//  filename:   FixedCamera.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    cclass for a fixed camera in the gui
//
/*********************************************************************/

#ifndef FIXEDCAMERA_H
#define FIXEDCAMERA_H

#include "VisualizationCamera.h"
#include <Vector3D.h>

namespace flair {
namespace simulator {

class FixedCamera : public VisualizationCamera {
public:
  FixedCamera(std::string name,core::Vector3D position,core::Vector3D lookat=core::Vector3D(0,0,0),float rotateSpeed = -500.0f, float zoomSpeed = .05f);
  ~FixedCamera();

  void animateNode(irr::scene::ISceneNode *node, irr::u32 timeMs);

private:
  float sat(float value);
  irr::core::position2df RotateStart;
  irr::core::vector3df rotation,target;
  bool Rotating;
  float rotateSpeed;
  float zoomSpeed;
  float fov;
  bool init;
};

} // end namespace simulator
} // end namespace flair

#endif // FIXEDCAMERA_H
