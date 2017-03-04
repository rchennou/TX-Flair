// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   SpinBox.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QSpinBox on the ground station
//
//
/*********************************************************************/

#include "SpinBox.h"

using std::string;

namespace flair {
namespace gui {

SpinBox::SpinBox(const LayoutPosition *position, string name, int min, int max,
                 int step, int default_value)
    : Box(position, name, "SpinBox") {
  // update value from xml file
  if (default_value < min)
    default_value = min;
  if (default_value > max)
    default_value = max;
  box_value = default_value;

  SetVolatileXmlProp("min", min);
  SetVolatileXmlProp("max", max);
  SetVolatileXmlProp("step", step);
  GetPersistentXmlProp("value", box_value);
  SetPersistentXmlProp("value", box_value);

  SendXml();
}

SpinBox::SpinBox(const LayoutPosition *position, string name, string suffix,
                 int min, int max, int step, int default_value)
    : Box(position, name, "SpinBox") {
  // update value from xml file
  if (default_value < min)
    default_value = min;
  if (default_value > max)
    default_value = max;
  box_value = default_value;

  SetVolatileXmlProp("suffix", suffix);
  SetVolatileXmlProp("min", min);
  SetVolatileXmlProp("max", max);
  SetVolatileXmlProp("step", step);
  GetPersistentXmlProp("value", box_value);
  SetPersistentXmlProp("value", box_value);
  SendXml();
}

SpinBox::~SpinBox() {}

int SpinBox::Value(void) const {
  int tmp;

  GetMutex();
  tmp = box_value;
  ReleaseMutex();

  return tmp;
}

void SpinBox::XmlEvent(void) {
  GetMutex();
  if (GetPersistentXmlProp("value", box_value))
    SetValueChanged();
  ReleaseMutex();
}

} // end namespace gui
} // end namespace flair
