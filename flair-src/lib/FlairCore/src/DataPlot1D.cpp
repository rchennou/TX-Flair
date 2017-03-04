// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   DataPlot1D.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a 1D plot on the ground station
//
//
/*********************************************************************/

#include "DataPlot1D.h"
#include "LayoutPosition.h"
#include "IODataElement.h"
#include "FrameworkManager.h"

using std::string;

namespace flair {
namespace gui {

using namespace core;

DataPlot1D::DataPlot1D(const LayoutPosition *position, string name, float ymin,
                       float ymax)
    : DataPlot(position, name, "DataPlot1D") {
  SetVolatileXmlProp("min", ymin);
  SetVolatileXmlProp("max", ymax);
  SendXml();
}

DataPlot1D::~DataPlot1D() {}

void DataPlot1D::AddCurve(const core::IODataElement *element, uint8_t r,
                          uint8_t g, uint8_t b, string curve_name) {
  if (curve_name != "") {
    SetVolatileXmlProp("curve", curve_name);
  } else {
    SetVolatileXmlProp("curve", element->Parent()->ObjectName() + "\\" +
                                    element->ObjectName());
  }
  SetVolatileXmlProp("type", element->GetDataType().GetDescription());
  SetVolatileXmlProp("r", r);
  SetVolatileXmlProp("g", g);
  SetVolatileXmlProp("b", b);

  SendXml();

  // save data information
  AddDataToSend(element);
}

void DataPlot1D::AddCurve(const core::IODataElement *element, Color_t color,
                          string curve_name) {
  uint8_t r, g, b;
  RGBFromColor(color, r, g, b);
  AddCurve(element, r, g, b, curve_name);
}

} // end namespace gui
} // end namespace flair
