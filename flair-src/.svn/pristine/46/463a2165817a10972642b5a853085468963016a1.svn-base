// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/08
//  filename:   MetaVrpnObject.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant objet vrpn et une dérivée
//              d'euler
//
//
/*********************************************************************/

#include "MetaVrpnObject.h"
#include "VrpnClient.h"
#include <EulerDerivative.h>
#include <LowPassFilter.h>
#include <IODevice.h>
#include <GridLayout.h>
#include <DataPlot1D.h>
#include <DataPlot2D.h>
#include <Tab.h>
#include <TabWidget.h>
#include <cvmatrix.h>
#include <Vector3D.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;
using namespace flair::filter;

namespace flair {
namespace meta {

MetaVrpnObject::MetaVrpnObject(const VrpnClient *parent, string name)
    : VrpnObject(parent, name, parent->GetTabWidget()) {
  ConstructorCommon(parent, name);
}

MetaVrpnObject::MetaVrpnObject(const VrpnClient *parent, std::string name,
                               uint8_t id)
    : VrpnObject(parent, name, id, parent->GetTabWidget()) {
  ConstructorCommon(parent, name);
}

void MetaVrpnObject::ConstructorCommon(const VrpnClient *parent, string name) {
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(6, 1);
  for (int i = 0; i < 6; i++) {
    desc->SetElementName(i, 0, Output()->Name(i, 0));
  }
  cvmatrix *prev_value = new cvmatrix(this, desc, elementDataType, name);
  for (int i = 0; i < 6; i++) {
    prev_value->SetValue(i, 0, 0);
  }

  pbas = new LowPassFilter(this, parent->GetLayout()->NewRow(),
                           name + " Passe bas", prev_value);

  desc = new cvmatrix_descriptor(6, 1);
  for (int i = 0; i < 6; i++) {
    desc->SetElementName(i, 0, "d" + Output()->Name(i, 0));
  }
  prev_value = new cvmatrix(this, desc, elementDataType, name);
  for (int i = 0; i < 6; i++) {
    prev_value->SetValue(i, 0, 0);
  }

  euler = new EulerDerivative(pbas, parent->GetLayout()->NewRow(),
                              name + "_euler", prev_value);

  vx_opti_plot = new DataPlot1D(GetPlotTab()->NewRow(), "vx", -3, 3);
  vx_opti_plot->AddCurve(euler->Matrix()->Element(3));
  vy_opti_plot = new DataPlot1D(GetPlotTab()->LastRowLastCol(), "vy", -3, 3);
  vy_opti_plot->AddCurve(euler->Matrix()->Element(4));
  vz_opti_plot = new DataPlot1D(GetPlotTab()->LastRowLastCol(), "vz", -2, 2);
  vz_opti_plot->AddCurve(euler->Matrix()->Element(5));

  plot_tab = new Tab(parent->GetTabWidget(), "Mesures (xy) " + name);
  xy_plot = new DataPlot2D(plot_tab->NewRow(), "xy", "y", -5, 5, "x", -5, 5);
  xy_plot->AddCurve(Output()->Element(4, 0), Output()->Element(3, 0));
}

MetaVrpnObject::~MetaVrpnObject() { delete plot_tab; }

DataPlot1D *MetaVrpnObject::VxPlot(void) const { return vx_opti_plot; }

DataPlot1D *MetaVrpnObject::VyPlot(void) const { return vy_opti_plot; }

DataPlot1D *MetaVrpnObject::VzPlot(void) const { return vz_opti_plot; }

DataPlot2D *MetaVrpnObject::XyPlot(void) const { return xy_plot; }

void MetaVrpnObject::GetSpeed(Vector3D &speed) const {
  speed.x = euler->Output(3, 0);
  speed.y = euler->Output(4, 0);
  speed.z = euler->Output(5, 0);
}

} // end namespace sensor
} // end namespace framewor
