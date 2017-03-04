// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/02/22
//  filename:   Vector3DSpinBox.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying 3 QDoubleSpinBox for x,y,z on the ground
//  station
//
//
/*********************************************************************/

#include "Vector3DSpinBox.h"

using std::string;

namespace flair {
namespace gui {

Vector3DSpinBox::Vector3DSpinBox(const LayoutPosition *position, string name,
                                 double min, double max, double step,
                                 int decimals, core::Vector3D default_value)
    : Box(position, name, "Vector3DSpinBox") {
  // update value from xml file
  default_value.Saturate(min, max);
  box_value = default_value;

  SetVolatileXmlProp("min", min);
  SetVolatileXmlProp("max", max);
  SetVolatileXmlProp("step", step);
  SetVolatileXmlProp("decimals", decimals);
  GetPersistentXmlProp("value_x", box_value.x);
  SetPersistentXmlProp("value_x", box_value.x);
  GetPersistentXmlProp("value_y", box_value.y);
  SetPersistentXmlProp("value_y", box_value.y);
  GetPersistentXmlProp("value_z", box_value.z);
  SetPersistentXmlProp("value_z", box_value.z);

  SendXml();
}

Vector3DSpinBox::~Vector3DSpinBox() {}
/*
Vector3DSpinBox::operator core::Vector3D() const {
    return Value();
}
*/
core::Vector3D Vector3DSpinBox::Value(void) const {
  core::Vector3D tmp;

  GetMutex();
  tmp = box_value;
  ReleaseMutex();

  return tmp;
}

void Vector3DSpinBox::XmlEvent(void) {
  bool changed = false;
  GetMutex();
  if (GetPersistentXmlProp("value_x", box_value.x))
    changed = true;
  if (GetPersistentXmlProp("value_y", box_value.y))
    changed = true;
  if (GetPersistentXmlProp("value_z", box_value.z))
    changed = true;
  if (changed)
    SetValueChanged();
  ReleaseMutex();
}

} // end namespace gui
} // end namespace flair
