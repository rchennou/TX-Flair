// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/01
//  filename:   FixedCamera.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class for a fixed camera in the gui
//
/*********************************************************************/
#ifdef GL

#include "FixedCamera.h"
#include "Simulator.h"
#include "Model.h"
#include "Model_impl.h"
#include "Gui.h"
#include <ICursorControl.h>
#include <ICameraSceneNode.h>
#include <IrrlichtDevice.h>
#include <ISceneManager.h>
#include <Euler.h>

using namespace irr;
using namespace gui;
using namespace core;
using namespace scene;

namespace flair {
namespace simulator {

FixedCamera::FixedCamera(std::string name,core::Vector3D position,core::Vector3D lookat,float inRotateSpeed,float inZoomSpeed):VisualizationCamera(name)  {
  Rotating = false;
  rotateSpeed=inRotateSpeed;
  zoomSpeed=inZoomSpeed;

  camera->bindTargetAndRotation(true);
  camera->setPosition(vector3df(ToIrrlichtCoordinates(position)));
  camera->setTarget(vector3df(ToIrrlichtCoordinates(lookat)));
  target=vector3df(ToIrrlichtCoordinates(lookat));
  init=false;
  rotation=camera->getRotation();
  printf("%f %f %f\n",rotation.X,rotation.Y,rotation.Z);
  fov=camera->getFOV();
}

FixedCamera::~FixedCamera() {}

float FixedCamera::sat(float value) {
  if (value >= -1)
    value = -1;
  if (value <= -179)
    value = -179;
  return value;
}

void FixedCamera::animateNode(ISceneNode *node, u32 timeMs) {
  ICameraSceneNode *camera = static_cast<ICameraSceneNode *>(node);
  vector3df newRotation=rotation;
  vector3df newTarget=target;

if(init==false) {
  rotation=camera->getRotation();
  printf("%f %f %f\n",rotation.X,rotation.Y,rotation.Z);
  init=true;
}
  float nRotY = 0;//rotation.Y;
  float nRotZ = rotation.Z;

  if (LMouseKey == true) {
    if (!Rotating) {
      RotateStart = MousePos;
      Rotating = true;
      //nRotY = rotation.Y;
      //nRotZ =0;// rotation.Z;
    } else {
      nRotY = (RotateStart.Y - MousePos.Y) * rotateSpeed;
      nRotZ = (RotateStart.X - MousePos.X) * rotateSpeed;
      newRotation.rotateXZBy(-nRotY);
      //nRotY = sat(nRotY);

      //newTarget.rotateXZBy(-nRotY,camera->getPosition());
      newTarget.rotateXYBy( nRotZ,camera->getPosition());
      camera->setTarget(newTarget);
    }
  } else if (Rotating) {
    //rotation.Y += (RotateStart.Y - MousePos.Y) * rotateSpeed;
    //rotation.Z += (RotateStart.X - MousePos.X) * rotateSpeed;
    //rotation.Y = sat(rotation.Y);
    //nRotY = rotation.Y;
    //nRotZ = rotation.Z;
    Rotating = false;
    target=camera->getTarget();
    rotation=camera->getRotation();
  printf("%f %f %f\n",rotation.X,rotation.Y,rotation.Z);
  }

  float newFov=fov+currentZoom*zoomSpeed;
  if(newFov>fov) {
    newFov=fov;
    currentZoom=0;
  }
  if(newFov<0) {
    newFov=zoomSpeed;
    currentZoom=1-fov/zoomSpeed;
  }

//newTarget.rotateXZBy(-nRotY,camera->getPosition());
//  newTarget.rotateXYBy( nRotZ,camera->getPosition());

  //camera->setRotation(vector3df(rotation.X,-180-nRotY,nRotZ));
  //camera->setRotation(vector3df(rotation.X,nRotY,0));
  //camera->bindTargetAndRotation(true);
 // camera->setRotation(rotation);
 // camera->setTarget(newTarget);
  //rotation=camera->getRotation();
  //printf("%f %f %f\n",rotation.X,rotation.Y,rotation.Z);

  camera->setFOV(newFov);
}


} // end namespace simulator
} // end namespace flair

#endif // GL
