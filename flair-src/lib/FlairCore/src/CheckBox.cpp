// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   CheckBox.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QCheckBox on the ground station
//
//
/*********************************************************************/
#include "CheckBox.h"

using std::string;

namespace flair {
namespace gui {

CheckBox::CheckBox(const LayoutPosition *position, string name,
                   bool default_value)
    : Box(position, name, "CheckBox") {
  // update value from xml file
  box_value = default_value;

  GetPersistentXmlProp("value", box_value);
  SetPersistentXmlProp("value", Value());
  SendXml();
}

CheckBox::~CheckBox() {}

bool CheckBox::IsChecked(void) const {
  bool tmp;

  GetMutex();
  tmp = box_value;
  ReleaseMutex();

  return tmp;
}

int CheckBox::Value(void) const {
  if (IsChecked() == true)
    return 1;
  else
    return 0;
}

void CheckBox::XmlEvent(void) {
  GetMutex();
  if (GetPersistentXmlProp("value", box_value))
    SetValueChanged();
  ReleaseMutex();
}

} // end namespace gui
} // end namespace flair
