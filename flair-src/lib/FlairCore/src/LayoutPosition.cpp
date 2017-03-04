// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/12/04
//  filename:   LayoutPosition.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class to define a position in a layout on the ground station
//
//
/*********************************************************************/
#include "LayoutPosition.h"

namespace flair {
namespace gui {

LayoutPosition::LayoutPosition(const Layout *layout, int16_t row, int16_t col) {
  this->layout = layout;
  this->row = row;
  this->col = col;
}

LayoutPosition::~LayoutPosition() {}

const Layout *LayoutPosition::getLayout(void) const { return layout; }

int16_t LayoutPosition::Row(void) const { return row; }

int16_t LayoutPosition::Col(void) const { return col; }

} // end namespace gui
} // end namespace flair
