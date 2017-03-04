// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/08
//  filename:   MetaUsRangeFinder.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant une dérivée
//              d'euler, un passe bas et un generateur de consigne
//              -> adapté pour un capteur d'altitude
//
//
/*********************************************************************/

#include "MetaUsRangeFinder.h"
#include "UsRangeFinder.h"
#include <LowPassFilter.h>
#include <ButterworthLowPass.h>
#include <Layout.h>
#include <DataPlot1D.h>
#include <Tab.h>
#include <EulerDerivative.h>
#include <GroupBox.h>
#include <cvmatrix.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;
using namespace flair::sensor;

namespace flair {
namespace meta {

MetaUsRangeFinder::MetaUsRangeFinder(UsRangeFinder *us)
    : Object(us, us->ObjectName()) {
  this->us = us;
  pbas_z =
      new ButterworthLowPass(us, us->GetLayout()->NewRow(), "Passe bas", 3);
  vz_euler = new EulerDerivative(pbas_z, us->GetLayout()->NewRow(), "Vz");
  pbas_vz = new ButterworthLowPass(vz_euler, us->GetLayout()->NewRow(),
                                   "Passe bas v", 3);
}

MetaUsRangeFinder::~MetaUsRangeFinder() {}

void MetaUsRangeFinder::UseDefaultPlot(void) {
  us->UseDefaultPlot();

  us->GetPlot()->AddCurve(pbas_z->Matrix()->Element(0), DataPlot::Blue);

  vz_plot = new DataPlot1D(us->GetPlotTab()->LastRowLastCol(), "vz", -2, 2);
  vz_plot->AddCurve(vz_euler->Matrix()->Element(0));
  vz_plot->AddCurve(pbas_vz->Matrix()->Element(0), DataPlot::Blue);
}

gui::DataPlot1D *MetaUsRangeFinder::GetZPlot() { return us->GetPlot(); }

gui::DataPlot1D *MetaUsRangeFinder::GetVzPlot() { return vz_plot; }

float MetaUsRangeFinder::z(void) const { return pbas_z->Output(); }

float MetaUsRangeFinder::Vz(void) const { return pbas_vz->Output(); }

} // end namespace sensor
} // end namespace framewor
