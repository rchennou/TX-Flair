// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/07/30
//  filename:   TabWidget.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QTabWidget on the ground station
//
//
/*********************************************************************/
#include "TabWidget.h"
#include "Tab.h"
#include "Layout.h"
#include "LayoutPosition.h"

using std::string;

namespace flair {
namespace gui {

TabWidget::TabWidget(const LayoutPosition *position, string name,
                     TabPosition_t tabPosition)
    : Widget(position->getLayout(), name, "TabWidget") {
  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());
  SetVolatileXmlProp("position", (int)tabPosition);
  SendXml();

  delete position;
}

TabWidget::~TabWidget() {}

} // end namespace gui
} // end namespace flair
