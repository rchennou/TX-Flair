// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/07
//  filename:   Layout.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Abstract class to display a layout on the ground station
//
//
/*********************************************************************/
#include "Layout.h"
#include "LayoutPosition.h"
#include "Mutex.h"

using std::string;

namespace flair {
namespace gui {

Layout::Layout(const Widget *parent, string name, string type)
    : Widget(parent, name, type) {
  mutex = new core::Mutex(this, name);
}

Layout::~Layout() {}

LayoutPosition *Layout::LastRowLastCol(void) const {
  return new LayoutPosition(this, -1, 0);
}

LayoutPosition *Layout::NewRow(void) const {
  return new LayoutPosition(this, -1, -1);
}

LayoutPosition *Layout::At(uint16_t row, uint16_t col) const {
  return new LayoutPosition(this, row, col);
}

} // end namespace gui
} // end namespace flair
