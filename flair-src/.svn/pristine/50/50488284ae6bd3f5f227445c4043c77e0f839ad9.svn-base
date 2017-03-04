// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   Simulator.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe de base du simulateur
//
/*********************************************************************/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <FrameworkManager.h>
#include <stdint.h>

class Simulator_impl;

namespace flair {
namespace core {
class Quaternion;
class Vector3D;
}
}

namespace flair {
namespace simulator {
class Model;
class Gui;

class Simulator : public core::FrameworkManager {
  friend class Model;
  friend class Gui;
  friend class GenericObject;

public:
  // yaw_deg: rotation of the vrpn coordinate with respect to the earth
  // coordinate, around z axis
  Simulator(std::string name, int optitrack_mstime = 10, float yaw_deg = 30);
  ~Simulator();
  void RunSimu(void);
  // get rotation of the vrpn coordinate with respect to the earth coordinate,
  // around z axis; in radians
  float Yaw(void) const;
  // compute rotation of the vrpn coordinate with respect to the earth
  // coordinate, around z axis
  core::Quaternion ToVRPNReference(core::Quaternion quat_in);
  core::Vector3D ToVRPNReference(core::Vector3D point_in);

private:
  Simulator_impl *pimpl_;
};

/*!
* \brief get Simulator
*
* \return the Simulator
*/
Simulator *getSimulator(void);

} // end namespace simulator
} // end namespace flair

#endif // SIMULATOR_H
