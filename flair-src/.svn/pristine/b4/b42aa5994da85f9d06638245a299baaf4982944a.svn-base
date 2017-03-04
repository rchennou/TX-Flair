// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/28
//  filename:   Box.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Abstract class to display a box on the ground station
//
//
/*********************************************************************/
#include "Box.h"
#include "Layout.h"
#include "LayoutPosition.h"

using std::string;

namespace flair {
namespace gui {

Box::Box(const LayoutPosition *position, string name, string type)
    : Widget(position->getLayout(), name, type) {
  value_changed = true;
  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());
  delete position;
}

Box::~Box() { core::Object::ObjectName(); }

bool Box::ValueChanged(void) {
  bool ret;

  GetMutex();
  if (value_changed == true) {
    value_changed = false;
    ret = true;
  } else {
    ret = false;
  }
  ReleaseMutex();

  return ret;
}

void Box::SetValueChanged(void) { value_changed = true; }

void Box::GetMutex(void) const { ((Layout *)Parent())->mutex->GetMutex(); }

void Box::ReleaseMutex(void) const {
  ((Layout *)Parent())->mutex->ReleaseMutex();
}

} // end namespace gui
} // end namespace flair
