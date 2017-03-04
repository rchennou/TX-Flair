// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/07
//  filename:   SimuUsGL.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for a simulation us
//
//
/*********************************************************************/
#include "SimuUsGL.h"
#include "Model.h"
#include <cvmatrix.h>
#include <SharedMem.h>
#include <TabWidget.h>
#include <Tab.h>
#include <DoubleSpinBox.h>
#include <Vector3DSpinBox.h>

#ifdef GL
#include "Gui.h"
#include <ISceneNode.h>
#include <ISceneCollisionManager.h>
using namespace irr;
using namespace irr::scene;
using namespace irr::core;
#endif
using namespace flair::core;
using namespace flair::gui;
using namespace flair::simulator;

namespace flair {
namespace sensor {
SimuUsGL::SimuUsGL(const Model *parent, std::string name, int dev_id)
    : SimuUs(parent, name, dev_id), SensorGL(parent) {
  Tab *setup_tab = new Tab(parent->GetTabWidget(), name);
  position = new Vector3DSpinBox(setup_tab->NewRow(), "position", -2, 2, .01);
  direction = new Vector3DSpinBox(setup_tab->NewRow(), "direction", -2, 2, .01);
  range = new DoubleSpinBox(setup_tab->NewRow(), "range:", 0, 6, 1);
}

SimuUsGL::~SimuUsGL() {}

void SimuUsGL::UpdateFrom(const io_data *data) {
  float value;
#ifdef GL
  if (noGui() == true) {
#endif
    // todo: utiliser le placement de l'us dans le drone et sa portée
    cvmatrix *input = (cvmatrix *)data;
    value = input->Value(9, 0);
    shmem->Write((char *)&value, sizeof(float));
#ifdef GL
  }

  if (noGui() == false && data == NULL) {
    line3d<f32> ray_us;         // rayon provenant de l'ultra son
    vector3df intersection_us;  // point intersection us avec le sol
    triangle3df hitTriangle_us; // triangle intersection us avec le sol

    // get rotation matrix of node - Zeuss must be getRotation not
    // getRelativeTransformation
    matrix4 m;
    m.setRotationDegrees(Node()->getRotation());

    // transform forward vector of us
    vector3df frv = ToIrrlichtCoordinates(direction->Value());
    m.transformVect(frv);
    frv.normalize();

    // transform pos vector of us
    vector3df pos = ToIrrlichtCoordinates(position->Value());
    m.transformVect(pos);

    ray_us.start = Node()->getPosition() + pos;
    ray_us.end = ray_us.start + ToIrrlichtScale(range->Value()) * frv;

    scene::ISceneNode *selectedSceneNode =
        CollMan()->getSceneNodeAndCollisionPointFromRay(ray_us, intersection_us,
                                                        hitTriangle_us);

    if (selectedSceneNode) {
      float value =
          ToSimulatorScale(ray_us.start.getDistanceFrom(intersection_us));
      shmem->Write((char *)&value, sizeof(float));
    }
  }
#endif
}

} // end namespace sensor
} // end namespace flair
