// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/03
//  filename:   VrpnObject_impl.h
//
//  author:     César Richard, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet vrpn
//
//
/*********************************************************************/

#ifndef VRPNOBJECT_IMPL_H
#define VRPNOBJECT_IMPL_H

#include <IODevice.h>
#include <string>
#include <stdint.h>
#include <vrpn_Tracker.h>
#include "Quaternion.h"

namespace flair {
namespace core {
class cvmatrix;
class Vector3D;
class Euler;
}
namespace gui {
class TabWidget;
class Tab;
class DataPlot1D;
}
namespace sensor {
class VrpnClient;
class VrpnObject;
}
}

class VrpnObject_impl {
  friend class VrpnClient_impl;

public:
  VrpnObject_impl(flair::sensor::VrpnObject *self,
                  const flair::sensor::VrpnClient *parent, std::string name,
                  int id, const flair::gui::TabWidget *tab);
  ~VrpnObject_impl(void);

  void mainloop(void);
  void GetEuler(flair::core::Euler &euler);
  void GetQuaternion(flair::core::Quaternion &quaternion);
  void GetPosition(flair::core::Vector3D &point);
  bool IsTracked(unsigned int timeout_ms);

  flair::gui::Tab *plot_tab;
  flair::gui::DataPlot1D *x_plot;
  flair::gui::DataPlot1D *y_plot;
  flair::gui::DataPlot1D *z_plot;
  flair::core::cvmatrix *output, *state;

  static void VRPN_CALLBACK handle_pos(void *userdata, const vrpn_TRACKERCB t);

private:
  flair::sensor::VrpnObject *self;
  const flair::sensor::VrpnClient *parent;
  vrpn_Tracker_Remote *tracker;
  flair::core::Quaternion quaternion; // todo: quaternion should be included in
                                      // the output to replace euler angles
  void Update(void);
};

#endif // VRPNOBJECT_IMPL_H
