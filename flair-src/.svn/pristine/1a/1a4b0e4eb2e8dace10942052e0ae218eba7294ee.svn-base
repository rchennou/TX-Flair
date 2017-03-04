// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/03/20
//  filename:   cvimage.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining an image of kind IplImage
//
/*********************************************************************/

#include "cvimage.h"

using std::string;

namespace flair {
namespace core {

cvimage::cvimage(const Object *parent, uint16_t width, uint16_t height,
                 Type::Format format, string name, bool allocate_data, int n)
    : io_data(parent, name, n), dataType(width, height, format) {
  this->allocate_data = allocate_data;

  if (allocate_data) {
    switch (format) {
    case Type::Format::YUYV:
    case Type::Format::UYVY:
      img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 2);
      break;
    case Type::Format::BGR:
      img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
      break;
    case Type::Format::GRAY:
      img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
      break;
    default:
      Err("format no supported");
      break;
    }
  } else {
    if (n > 1)
      Err("number of samples!=1 not possible when not allocating data\n");
    n = 1;
    switch (format) {
    case Type::Format::YUYV:
    case Type::Format::UYVY:
      img = cvCreateImageHeader(cvSize(width, height), IPL_DEPTH_8U, 2);
      break;
    case Type::Format::BGR:
      img = cvCreateImageHeader(cvSize(width, height), IPL_DEPTH_8U, 3);
      break;
    case Type::Format::GRAY:
      img = cvCreateImageHeader(cvSize(width, height), IPL_DEPTH_8U, 1);
      break;
    default:
      Err("format no supported");
      break;
    }
  }

  SetPtrToCircle((void **)&img);

  if (n > 1)
    prev = new cvimage(this, width, height, format, name, n - 1);
}

cvimage::~cvimage() {
  // printf("destructeur cvimage\n");

  cvReleaseImage(&img);
}

void cvimage::CopyDatas(char *dst) const { Warn("non implementé\n"); }

} // end namespace core
} // end namespace flair
