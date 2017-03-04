// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   GroupBox.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QGroupBox on the ground station
//
//
/*********************************************************************/
#include "GroupBox.h"
#include "LayoutPosition.h"

using std::string;

namespace flair {
namespace gui {

GroupBox::GroupBox(const LayoutPosition *position, string name)
    : Layout(position->getLayout(), name, "GroupBox") {
  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());
  SendXml();

  delete position;
}

GroupBox::~GroupBox() {}

} // end namespace gui
} // end namespace flair
