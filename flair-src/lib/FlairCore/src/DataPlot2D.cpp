// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/08
//  filename:   DataPlot2D.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a 2D plot on the ground station
//
//
/*********************************************************************/

#include "DataPlot2D.h"
#include "LayoutPosition.h"
#include "IODataElement.h"
#include <typeinfo>

using std::string;

namespace flair {
namespace gui {

DataPlot2D::DataPlot2D(const LayoutPosition *position, string name,
                       string x_name, float xmin, float xmax, string y_name,
                       float ymin, float ymax)
    : DataPlot(position, name, "DataPlot2D") {
  SetVolatileXmlProp("xmin", xmin);
  SetVolatileXmlProp("xmax", xmax);
  SetVolatileXmlProp("ymin", ymin);
  SetVolatileXmlProp("ymax", ymax);
  SetVolatileXmlProp("x_name", x_name);
  SetVolatileXmlProp("y_name", y_name);
  SendXml();
}

DataPlot2D::~DataPlot2D() {}

void DataPlot2D::AddCurve(const core::IODataElement *x_element,
                          const core::IODataElement *y_element, Color_t color,
                          string curve_name) {
  uint8_t r, g, b;
  RGBFromColor(color, r, g, b);
  AddCurve(x_element, y_element, r, g, b, curve_name);
}

void DataPlot2D::AddCurve(const core::IODataElement *x_element,
                          const core::IODataElement *y_element, uint8_t r,
                          uint8_t g, uint8_t b, string curve_name) {
  if (typeid(x_element->GetDataType()) != typeid(y_element->GetDataType())) {
    Err("x_element type is different from y_element type (%i-%i)\n",
        x_element->GetDataType().GetDescription().c_str(),
        y_element->GetDataType().GetDescription().c_str());
    // gerer erreur
    return;
  }

  if (curve_name != "") {
    SetVolatileXmlProp("curve", curve_name);
  } else {
    SetVolatileXmlProp("curve", x_element->Parent()->ObjectName() + "\\" +
                                    x_element->ObjectName() + "\\" +
                                    y_element->ObjectName());
  }
  SetVolatileXmlProp("type", x_element->GetDataType().GetDescription());
  SetVolatileXmlProp("r", r);
  SetVolatileXmlProp("g", g);
  SetVolatileXmlProp("b", b);

  SendXml();

  // save data information
  AddDataToSend(x_element);
  AddDataToSend(y_element);
}

} // end namespace gui
} // end namespace flair
