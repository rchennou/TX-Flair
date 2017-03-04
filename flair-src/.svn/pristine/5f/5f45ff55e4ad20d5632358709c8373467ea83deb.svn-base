// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   Simulator_impl.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe de base du simulateur
//
/*********************************************************************/

#ifndef SIMULATOR_IMPL_H
#define SIMULATOR_IMPL_H

#include <vrpn_Connection.h>
#include <Thread.h>

namespace flair {
namespace simulator {
class Simulator;
class Model;
class GenericObject;
}
}

class Simulator_impl : public vrpn_Connection_IP, private flair::core::Thread {
  friend class flair::simulator::Model;
  friend class flair::simulator::GenericObject;

public:
  Simulator_impl(flair::simulator::Simulator *self, int optitrack_mstime = 10,
                 float yaw_deg = 30);
  ~Simulator_impl();

  void RunSimu(void);
  float yaw_rad;

private:
  void Run(void);
  flair::simulator::Simulator *self;
  std::vector<flair::simulator::Model *> models;
  std::vector<flair::simulator::GenericObject *> objects;
  int optitrack_mstime;
};

#endif // SIMULATOR_IMPL_H
