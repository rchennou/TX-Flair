// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   GridLayout.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QGridLayout on the ground station
//
//
/*********************************************************************/
#include "GridLayout.h"
#include "LayoutPosition.h"

using std::string;

namespace flair {
namespace gui {

GridLayout::GridLayout(const LayoutPosition *position, string name)
    : Layout(position->getLayout(), name, "GridLayout") {
  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());
  SendXml();

  delete position;
}

GridLayout::~GridLayout() {}

} // end namespace gui
} // end namespace flair
