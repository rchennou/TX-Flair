// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   Tab.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QTab on the ground station
//
//
/*********************************************************************/
#include "Tab.h"
#include "TabWidget.h"

using std::string;

namespace flair {
namespace gui {

Tab::Tab(const TabWidget *parent, string name, int position)
    : Layout(parent, name, "Tab") {
  SetVolatileXmlProp("position", position);
  SendXml();
}

Tab::~Tab() {}

} // end namespace gui
} // end namespace flair
