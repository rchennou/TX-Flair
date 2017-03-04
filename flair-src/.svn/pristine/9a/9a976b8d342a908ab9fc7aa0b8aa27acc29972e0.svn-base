// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/21
//  filename:   FollowMeCamera.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant une animation poursuite pour camera
//
/*********************************************************************/
#ifdef GL

#include "FollowMeCamera.h"
#include "Simulator.h"
#include "Model.h"
#include "Model_impl.h"
#include "Gui.h"
#include <ICursorControl.h>
#include <ICameraSceneNode.h>
#include <IrrlichtDevice.h>
#include <ISceneManager.h>

using namespace irr;
using namespace gui;
using namespace core;
using namespace scene;

namespace flair {
namespace simulator {

FollowMeCamera::FollowMeCamera(const ISceneNode *parent, std::string name,float inRotateSpeed,
                             float inZoomSpeed):VisualizationCamera(name)  {
  this->parent = parent;
  rotateSpeed=inRotateSpeed;
  zoomSpeed=inZoomSpeed;
  RotY = 20;
  RotZ = 0;
  Rotating = false;
}

FollowMeCamera::~FollowMeCamera() {}

void FollowMeCamera::setPositionOffset(vector3df newpos) {
  pos_offset = ToIrrlichtCoordinates(newpos);
}

void FollowMeCamera::setTargetOffset(vector3df newpos) {
  target_offset = ToIrrlichtCoordinates(newpos);
}

float FollowMeCamera::sat(float value) {
  if (value > 89)
    value = 89;
  if (value < -89)
    value = -89;
  return value;
}

void FollowMeCamera::animateNode(ISceneNode *node, u32 timeMs) {

  float nRotY = RotY;
  float nRotZ = RotZ;

  if (LMouseKey == true) {
    if (!Rotating) {
      RotateStart = MousePos;
      Rotating = true;
      nRotY = RotY;
      nRotZ = RotZ;
    } else {
      nRotY += (RotateStart.Y - MousePos.Y) * rotateSpeed;
      nRotZ += (RotateStart.X - MousePos.X) * rotateSpeed;
      nRotY = sat(nRotY);
    }
  } else if (Rotating) {
    RotY += (RotateStart.Y - MousePos.Y) * rotateSpeed;
    RotZ += (RotateStart.X - MousePos.X) * rotateSpeed;
    RotY = sat(RotY);
    nRotY = RotY;
    nRotZ = RotZ;
    Rotating = false;
  }

  float newCurrentZoom= 100+currentZoom * zoomSpeed;
  if (newCurrentZoom <= 0) {
    newCurrentZoom =zoomSpeed;
    currentZoom =1-100/zoomSpeed;
  }

  vector3df pos;
  pos.X = -newCurrentZoom;
  pos.Y = 0;
  pos.Z = 0;

  pos.rotateXZBy(-nRotY);
  pos.rotateXYBy(getSimulator()->Yaw() + nRotZ + parent->getRotation().Z);

  camera->setPosition(parent->getPosition() + pos + pos_offset);
  camera->setTarget(parent->getPosition() + target_offset);
}


} // end namespace simulator
} // end namespace flair

#endif // GL
