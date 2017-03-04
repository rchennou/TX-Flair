// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/10
//  filename:   DataPlot.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Abstract class to display plots on ground station
//
//
/*********************************************************************/

#include "DataPlot.h"
#include "DataPlot_impl.h"
#include "LayoutPosition.h"
#include "FrameworkManager.h"
#include "IODataElement.h"

using std::string;

namespace flair {
namespace gui {

using namespace core;

void RGBFromColor(DataPlot::Color_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
  switch (color) {
  case DataPlot::Red:
    r = 255;
    g = 0;
    b = 0;
    break;
  case DataPlot::Blue:
    r = 0;
    g = 0;
    b = 255;
    break;
  case DataPlot::Green:
    r = 0;
    g = 255;
    b = 0;
    break;
  case DataPlot::Yellow:
    r = 255;
    g = 255;
    b = 0;
    break;
  case DataPlot::Black:
    r = 0;
    g = 0;
    b = 0;
    break;
  case DataPlot::White:
    r = 255;
    g = 255;
    b = 255;
    break;
  }
}

DataPlot::DataPlot(const LayoutPosition *position, string name, string type)
    : SendData(position, name, type) {
  pimpl_ = new DataPlot_impl();
}

DataPlot::~DataPlot() { delete pimpl_; }

void DataPlot::AddDataToSend(const IODataElement *element) {
  pimpl_->tosend.push_back(element);

  SetSendSize(SendSize() + element->Size());
}

void DataPlot::CopyDatas(char *buf) const {
  int buf_size = 0;

  for (size_t i = 0; i < pimpl_->tosend.size(); i++) {
    pimpl_->tosend[i]->CopyData(buf + buf_size);
    buf_size += pimpl_->tosend[i]->Size();
  }
}

} // end namespace gui
} // end namespace flair
