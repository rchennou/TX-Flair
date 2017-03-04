// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/01
//  filename:   VisualizationCamera.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class for a visualization camera in the gui
//
/*********************************************************************/
#ifdef GL

#include "VisualizationCamera.h"
#include "Simulator.h"
#include "Model.h"
#include "Model_impl.h"
#include "Gui.h"
#include "Gui_impl.h"
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

VisualizationCamera::VisualizationCamera(std::string inName) {
  name=inName;
  currentZoom = 0;
  LMouseKey = false;

   // camera
  camera = getGui()->getSceneManager()->addCameraSceneNode();
  camera->setAspectRatio(getGui()->getAspectRatio()); // on force a cause du view port
  camera->setUpVector(vector3df(0, 0, 1));
  camera->addAnimator(this);
  camera->setFarValue(8000);

  getGui()->pimpl_->AddVisualizationCamera(this);
}

VisualizationCamera::~VisualizationCamera() {}

std::string VisualizationCamera::getName(void) {
  return name;
}

ICameraSceneNode *VisualizationCamera::getCameraSceneNode(void) {
  return camera;
}

ISceneNodeAnimator *VisualizationCamera::createClone(ISceneNode *node,
                                               ISceneManager *newManager) {
  return NULL;
}

bool VisualizationCamera::OnEvent(const irr::SEvent& event) {
  if (event.EventType != EET_MOUSE_INPUT_EVENT)
    return false;

  switch (event.MouseInput.Event) {

  case EMIE_MOUSE_WHEEL:
    currentZoom -= event.MouseInput.Wheel;
    break;
  case EMIE_LMOUSE_PRESSED_DOWN:
    LMouseKey = true;
    break;
  case EMIE_LMOUSE_LEFT_UP:
    LMouseKey = false;
    break;
  case EMIE_MOUSE_MOVED:
    MousePos = getGui()->getDevice()->getCursorControl()->getRelativePosition();
    break;
  default:
    return false;
    break;
  }

  return true;
}

} // end namespace simulator
} // end namespace flair

#endif // GL
