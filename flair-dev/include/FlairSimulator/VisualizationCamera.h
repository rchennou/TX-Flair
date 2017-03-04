// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/01
//  filename:   VisualizationCamera.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    cclass for a visualization camera in the gui
//
/*********************************************************************/

#ifndef VISUALIZATIONCAMERA_H
#define VISUALIZATIONCAMERA_H

#include <ISceneNodeAnimator.h>
#include <position2d.h>
#include <Vector3D.h>
#include <string>

namespace irr {
  namespace scene {
    class ICameraSceneNode;
  }
}

namespace flair {
namespace simulator {

class VisualizationCamera : private irr::scene::ISceneNodeAnimator {
public:
  VisualizationCamera(std::string name);
  ~VisualizationCamera();

  ISceneNodeAnimator *createClone(irr::scene::ISceneNode *node,
                                  irr::scene::ISceneManager *newManager = 0);
  virtual bool OnEvent(const irr::SEvent& event);
  irr::scene::ICameraSceneNode *getCameraSceneNode(void);
  std::string getName(void);

private:
  virtual bool isEventReceiverEnabled(void) const { return true; }

protected:
  bool LMouseKey;
  irr::scene::ICameraSceneNode *camera;
  irr::core::position2df MousePos;
  float currentZoom;
  std::string name;
};

} // end namespace simulator
} // end namespace flair

#endif // VISUALIZATIONCAMERA_H
