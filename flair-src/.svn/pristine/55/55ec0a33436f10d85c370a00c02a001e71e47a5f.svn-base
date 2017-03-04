// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   DoubleSpinBox.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QDoubleSpinBox on the ground station
//
//
/*********************************************************************/

#include "DoubleSpinBox.h"

using std::string;

namespace flair {
namespace gui {

DoubleSpinBox::DoubleSpinBox(const LayoutPosition *position, string name,
                             double min, double max, double step, int decimals,
                             double default_value)
    : Box(position, name, "DoubleSpinBox") {
  // update value from xml file
  if (default_value < min)
    default_value = min;
  if (default_value > max)
    default_value = max;
  box_value = default_value;

  SetVolatileXmlProp("min", min);
  SetVolatileXmlProp("max", max);
  SetVolatileXmlProp("step", step);
  SetVolatileXmlProp("decimals", decimals);
  GetPersistentXmlProp("value", box_value);
  SetPersistentXmlProp("value", box_value);

  SendXml();
}

DoubleSpinBox::DoubleSpinBox(const LayoutPosition *position, string name,
                             string suffix, double min, double max, double step,
                             int decimals, double default_value)
    : Box(position, name, "DoubleSpinBox") {
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
  SetVolatileXmlProp("decimals", decimals);
  GetPersistentXmlProp("value", box_value);
  SetPersistentXmlProp("value", box_value);

  SendXml();
}

DoubleSpinBox::~DoubleSpinBox() {}

double DoubleSpinBox::Value(void) const {
  double tmp;

  GetMutex();
  tmp = box_value;
  ReleaseMutex();

  return tmp;
}

void DoubleSpinBox::XmlEvent(void) {
  GetMutex();
  if (GetPersistentXmlProp("value", box_value))
    SetValueChanged();
  ReleaseMutex();
}

} // end namespace gui
} // end namespace flair
