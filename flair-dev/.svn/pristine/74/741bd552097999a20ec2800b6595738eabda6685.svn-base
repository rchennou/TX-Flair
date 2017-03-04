// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   SensorGL.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un modele de capteur
//
/*********************************************************************/

#ifndef SENSORGL_H
#define SENSORGL_H

namespace irr {
namespace scene {
class ISceneNode;
class ISceneCollisionManager;
}
}

namespace flair {
namespace simulator {
class Model;
}
}

namespace flair {
namespace sensor {
class SensorGL {
public:
  SensorGL(const simulator::Model *parent);
  virtual ~SensorGL() = 0;

protected:
#ifdef GL
  irr::scene::ISceneCollisionManager *CollMan(void) const;
  irr::scene::ISceneNode *Node(void) const;
#endif
private:
#ifdef GL
  irr::scene::ISceneCollisionManager *collMan;
  irr::scene::ISceneNode *node;
#endif
};
} // end namespace sensor
} // end namespace flair
#endif // SENSORGL_H
