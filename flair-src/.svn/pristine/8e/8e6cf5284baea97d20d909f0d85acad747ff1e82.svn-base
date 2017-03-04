// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   Simulator.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe de base du Simulator
//
/*********************************************************************/

#include "Simulator.h"
#include "Simulator_impl.h"
#include "Euler.h"
#include "Quaternion.h"
#include "Vector3D.h"
#ifdef GL
#include "Gui.h"
#endif

using namespace std;
using namespace flair::core;

namespace {
flair::simulator::Simulator *simu = NULL;
}

namespace flair {
namespace simulator {

Simulator *getSimulator(void) { return simu; }

Simulator::Simulator(string name, int optitrack_mstime, float yaw_deg)
    : FrameworkManager(name) {
  if (simu != NULL)
    Err("Simulator should be instanced only one time\n");

  pimpl_ = new Simulator_impl(this, optitrack_mstime, yaw_deg);
  simu = this;
}

Simulator::~Simulator() { delete pimpl_; }

Quaternion Simulator::ToVRPNReference(Quaternion quat_in) {
  Quaternion yaw_rot_quat;
  Euler yaw_rot_euler(
      0, 0, -pimpl_->yaw_rad); // yaw_rad is vrpn rotation in earth reference
  yaw_rot_euler.ToQuaternion(yaw_rot_quat);

  return yaw_rot_quat * quat_in;
}

Vector3D Simulator::ToVRPNReference(Vector3D point_in) {
  Quaternion yaw_rot_quat;
  Euler yaw_rot_euler(
      0, 0, -pimpl_->yaw_rad); // yaw_rad is vrpn rotation in earth reference
  yaw_rot_euler.ToQuaternion(yaw_rot_quat);
  point_in.Rotate(yaw_rot_quat);

  return point_in;
}

float Simulator::Yaw(void) const { return pimpl_->yaw_rad; }

void Simulator::RunSimu(void) { pimpl_->RunSimu(); }

} // end namespace simulator
} // end namespace flair
