// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/01/30
//  filename:   Picture.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a Picture on the ground station
//
//
/*********************************************************************/

#include "Picture.h"
#include "FrameworkManager.h"
#include "cvimage.h"
#include "Layout.h"
#include "LayoutPosition.h"

using std::string;

namespace flair {
namespace gui {

using namespace core;

Picture::Picture(const LayoutPosition *position, string name,
                 const cvimage *image)
    : SendData(position, name, "Picture", 200) {
  this->image = image;

  SetSendSize(image->GetDataType().GetSize());

  SetVolatileXmlProp("width", image->GetDataType().GetWidth());
  SetVolatileXmlProp("height", image->GetDataType().GetHeight());
  SendXml();
}

Picture::~Picture() {}

void Picture::CopyDatas(char *buf) const {
  if (image != NULL) {
    image->GetMutex();
    memcpy(buf, image->img->imageData, image->GetDataType().GetSize());
    image->ReleaseMutex();
  }
}

} // end namespace gui
} // end namespace flair
