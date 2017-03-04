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
#ifdef GL

#include "SimuLaserGL.h"
#include "Model.h"
#include "Gui.h"
#include <cvmatrix.h>
#include <SharedMem.h>
#include <TabWidget.h>
#include <Tab.h>
#include <DoubleSpinBox.h>
#include <Vector3DSpinBox.h>
#include <ISceneNode.h>
#include <ISceneCollisionManager.h>

using namespace irr;
using namespace irr::scene;
using namespace irr::core;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::simulator;

namespace flair {
namespace sensor {
SimuLaserGL::SimuLaserGL(const Model *parent, std::string name, int dev_id)
    : SimuLaser(parent, name, dev_id), SensorGL(parent) {
  Tab *setup_tab = new Tab(parent->GetTabWidget(), name);
  position = new Vector3DSpinBox(setup_tab->NewRow(), "position", -2, 2, .01);
  direction = new Vector3DSpinBox(setup_tab->NewRow(), "direction", -2, 2, .01);
  range = new DoubleSpinBox(setup_tab->NewRow(), "range:", 0, 30, 1);
}

SimuLaserGL::~SimuLaserGL() {}

void SimuLaserGL::UpdateFrom(const io_data *data) {
  float value[360];

  if (noGui() == false && data == NULL) {
    for (int i = 0; i < 360; i++) {
      line3d<f32> ray_laser;         // rayon provenant de l'ultra son
      vector3df intersection_laser;  // point intersection us avec le sol
      triangle3df hitTriangle_laser; // triangle intersection us avec le sol

      // get rotation matrix of node - Zeuss must be getRotation not
      // getRelativeTransformation
      matrix4 m;
      matrix4 M;
      m.setRotationDegrees(Node()->getRotation());

      // Matrice de rotation pour balayage du laser, angle i
      M.setRotationDegrees(vector3df(0, 0, i));
      // transform forward vector of us
      vector3df frv = ToIrrlichtCoordinates(direction->Value());
      M.transformVect(frv);
      m.transformVect(frv);
      frv.normalize();

      // transform pos vector of us
      vector3df pos = ToIrrlichtCoordinates(position->Value());
      m.transformVect(pos);

      ray_laser.start = Node()->getPosition() + pos;
      ray_laser.end = ray_laser.start + ToIrrlichtScale(range->Value()) * frv;

      scene::ISceneNode *selectedSceneNode =
          CollMan()->getSceneNodeAndCollisionPointFromRay(
              ray_laser, intersection_laser, hitTriangle_laser);
      // //////////////////////////////////////////
      if (selectedSceneNode) //
      {
        value[i] = ToSimulatorScale(
            ray_laser.start.getDistanceFrom(intersection_laser));
      } else {
        value[i] = -1;
      }
    }
    shmem->Write((char *)value, 360 * sizeof(float));
  }
}

} // end namespace sensor
} // end namespace flair
#endif
