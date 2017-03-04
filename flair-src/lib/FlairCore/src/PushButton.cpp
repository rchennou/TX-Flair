// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   PushButton.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QPushButton on the ground station
//
//
/*********************************************************************/

#include "PushButton.h"
#include "Layout.h"
#include "LayoutPosition.h"

using std::string;

namespace flair {
namespace gui {

PushButton::PushButton(const LayoutPosition *position, string name)
    : Widget(position->getLayout(), name, "PushButton") {
  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());
  delete position;

  SendXml();

  clicked = false;
}

PushButton::~PushButton() {}

void PushButton::XmlEvent(void) {
  int clic = 0;
  GetPersistentXmlProp("value", clic);

  if (clic == 1)
    clicked = true;
}

bool PushButton::Clicked(void) {
  if (clicked == true) {
    clicked = false;
    return true;
  } else {
    return false;
  }
}

} // end namespace gui
} // end namespace flair
