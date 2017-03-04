// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   ComboBox.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QComboBox on the ground station
//
//
/*********************************************************************/
#include "ComboBox.h"

using std::string;

namespace flair {
namespace gui {

ComboBox::ComboBox(const LayoutPosition *position, string name)
    : Box(position, name, "ComboBox") {
  // update value from xml file
  box_value = 0;
  GetPersistentXmlProp("value", box_value);
  SetPersistentXmlProp("value", box_value);

  SendXml();
}

ComboBox::~ComboBox() {}

void ComboBox::AddItem(string name) {
  SetVolatileXmlProp("item", name);
  SendXml();
}

int ComboBox::CurrentIndex(void) const {
  int tmp;

  GetMutex();
  tmp = box_value;
  ReleaseMutex();

  return tmp;
}

void ComboBox::XmlEvent(void) {
  GetMutex();
  if (GetPersistentXmlProp("value", box_value))
    SetValueChanged();
  ReleaseMutex();
}

} // end namespace gui
} // end namespace flair
