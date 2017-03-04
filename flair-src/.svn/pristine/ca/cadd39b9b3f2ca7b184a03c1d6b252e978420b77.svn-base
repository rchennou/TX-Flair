// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/07/23
//  filename:   RangeFinderPlot.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a 2D plot on the ground station for laser range
//  finder like Hokuyo
//
//
/*********************************************************************/

#include "RangeFinderPlot.h"
#include "cvmatrix.h"
#include "Layout.h"
#include "LayoutPosition.h"
#include "FrameworkManager.h"
#include <cxcore.h>

using std::string;
using namespace flair::core;

namespace flair {
namespace gui {

RangeFinderPlot::RangeFinderPlot(const LayoutPosition *position, string name,
                                 string x_name, float xmin, float xmax,
                                 string y_name, float ymin, float ymax,
                                 const cvmatrix *datas, float start_angle,
                                 float end_angle, uint32_t nb_samples)
    : SendData(position, name, "RangeFinderPlot", 200) {
  this->datas = datas;

  SetSendSize(datas->GetDataType().GetSize());

  SetVolatileXmlProp("xmin", xmin);
  SetVolatileXmlProp("xmax", xmax);
  SetVolatileXmlProp("ymin", ymin);
  SetVolatileXmlProp("ymax", ymax);
  SetVolatileXmlProp("x_name", x_name);
  SetVolatileXmlProp("y_name", y_name);
  SetVolatileXmlProp("start_angle", start_angle);
  SetVolatileXmlProp("end_angle", end_angle);
  SetVolatileXmlProp("nb_samples", nb_samples);
  SetVolatileXmlProp(
      "type", datas->GetDataType().GetElementDataType().GetDescription());
  SendXml();

  if (datas->Cols() != 1 || datas->Rows() != nb_samples)
    Err("Wrong input matrix size\n");
}

RangeFinderPlot::~RangeFinderPlot() {}

void RangeFinderPlot::CopyDatas(char *buf) const {
  datas->GetMutex();
  memcpy(buf, datas->getCvMat()->data.ptr, datas->GetDataType().GetSize());
  datas->ReleaseMutex();
}

} // end namespace gui
} // end namespace flair
