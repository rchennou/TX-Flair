// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/07/17
//  filename:   V4LCamera.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    base class for V4l camera
//
//
/*********************************************************************/

#include "V4LCamera.h"
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <CheckBox.h>
#include <GridLayout.h>
#include <Label.h>
#include <cvimage.h>
#include <FrameworkManager.h>
#include <linux/videodev2.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

V4LCamera::V4LCamera(const FrameworkManager *parent, string name,
                     uint8_t camera_index, uint16_t width, uint16_t height,
                     cvimage::Type::Format format, uint8_t priority)
    : Thread(parent, name, priority),
      Camera(parent, name, width, height, format) {
  capture = cvCaptureFromCAM(camera_index); // a mettre apres l'init dsp

  if (capture < 0)
    Thread::Err("cvCaptureFromCAM error\n");

  if (cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width) < 0)
    Thread::Err("cvSetCaptureProperty error\n");
  if (cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height) < 0)
    Thread::Err("cvSetCaptureProperty error\n");

  if (format == cvimage::Type::Format::UYVY) {
    if (cvSetCaptureProperty(capture, CV_CAP_PROP_FORMAT, V4L2_PIX_FMT_UYVY) <
        0)
      Thread::Err("cvSetCaptureProperty error\n");
  } else if (format == cvimage::Type::Format::YUYV) {
    if (cvSetCaptureProperty(capture, CV_CAP_PROP_FORMAT, V4L2_PIX_FMT_YUYV) <
        0)
      Thread::Err("cvSetCaptureProperty error\n");
  } else {
    Thread::Err("format not supported\n");
  }

  // station sol
  gain = new DoubleSpinBox(GetGroupBox()->NewRow(), "gain:", 0, 1, 0.1);
  exposure = new DoubleSpinBox(GetGroupBox()->LastRowLastCol(), "exposure:", 0,
                               1, 0.1);
  bright =
      new DoubleSpinBox(GetGroupBox()->LastRowLastCol(), "bright:", 0, 1, 0.1);
  contrast = new DoubleSpinBox(GetGroupBox()->LastRowLastCol(), "contrast:", 0,
                               1, 0.1);
  hue = new DoubleSpinBox(GetGroupBox()->LastRowLastCol(), "hue:", 0, 1, 0.1);
  sharpness = new DoubleSpinBox(GetGroupBox()->LastRowLastCol(), "sharpness:",
                                0, 1, 0.1);
  sat = new DoubleSpinBox(GetGroupBox()->LastRowLastCol(), "saturation:", 0, 1,
                          0.1);
  autogain = new CheckBox(GetGroupBox()->NewRow(), "autogain:");
  autoexposure = new CheckBox(GetGroupBox()->LastRowLastCol(), "autoexposure:");
  awb = new CheckBox(GetGroupBox()->LastRowLastCol(), "awb:");
  fps = new Label(GetGroupBox()->NewRow(), "fps");
}

V4LCamera::~V4LCamera() {
  SafeStop();
  Join();
}

void V4LCamera::Run(void) {
  Time cam_time, new_time, fpsNow, fpsPrev;
  IplImage *img; // raw image
  int fpsCounter = 0;

  // init image old
  if (!cvGrabFrame(capture)) {
    Printf("Could not grab a frame\n");
  }
  cam_time = GetTime();
  fpsPrev = cam_time;

  while (!ToBeStopped()) {
    // fps counter
    fpsCounter++;
    if (fpsCounter == 100) {
      fpsNow = GetTime();
      fps->SetText("fps: %.1f",
                   fpsCounter / ((float)(fpsNow - fpsPrev) / 1000000000.));
      fpsCounter = 0;
      fpsPrev = fpsNow;
    }

    // cam properties
    if (gain->ValueChanged() == true && autogain->Value() == false)
      SetGain(gain->Value());
    if (exposure->ValueChanged() == true && autoexposure->Value() == false)
      SetExposure(exposure->Value());
    if (bright->ValueChanged() == true)
      SetBrightness(bright->Value());
    if (sat->ValueChanged() == true)
      SetSaturation(sat->Value());
    if (contrast->ValueChanged() == true)
      SetContrast(contrast->Value());
    if (hue->ValueChanged() == true)
      SetHue(hue->Value());
    if (sharpness->ValueChanged() == true)
      cvSetCaptureProperty(capture, CV_CAP_PROP_SHARPNESS, sharpness->Value());
    if (autogain->ValueChanged() == true) {
      if (autogain->Value() == true) {
        gain->setEnabled(false);
      } else {
        gain->setEnabled(true);
        SetGain(gain->Value());
      }
      SetAutoGain(autogain->Value());
    }
    if (autoexposure->ValueChanged() == true) {
      if (autoexposure->Value() == true) {
        exposure->setEnabled(false);
      } else {
        exposure->setEnabled(true);
        SetExposure(exposure->Value());
      }
      SetAutoExposure(autoexposure->Value());
    }
    if (awb->ValueChanged() == true)
      cvSetCaptureProperty(capture, CV_CAP_PROP_AWB, awb->Value());

    // cam pictures
    img = cvRetrieveRawFrame(capture);
    if (!cvGrabFrame(capture)) {
      Printf("Could not grab a frame\n");
    }
    new_time = GetTime();

    output->GetMutex();
    output->img->imageData = img->imageData;
    output->ReleaseMutex();

    output->SetDataTime(cam_time);
    ProcessUpdate(output);

    cam_time = new_time;
  }

  cvReleaseCapture(&capture);
}

void V4LCamera::SetAutoGain(bool value) {
  cvSetCaptureProperty(capture, CV_CAP_PROP_AUTOGAIN, value);
}

void V4LCamera::SetAutoExposure(bool value) {
  Thread::Warn("not implemented in opencv\n");
}

void V4LCamera::SetGain(float value) {
  cvSetCaptureProperty(capture, CV_CAP_PROP_GAIN, value);
}

void V4LCamera::SetExposure(float value) {
  cvSetCaptureProperty(capture, CV_CAP_PROP_EXPOSURE, value);
}

void V4LCamera::SetBrightness(float value) {
  cvSetCaptureProperty(capture, CV_CAP_PROP_BRIGHTNESS, value);
}

void V4LCamera::SetSaturation(float value) {
  cvSetCaptureProperty(capture, CV_CAP_PROP_SATURATION, value);
}

void V4LCamera::SetHue(float value) {
  cvSetCaptureProperty(capture, CV_CAP_PROP_HUE, value);
}

void V4LCamera::SetContrast(float value) {
  cvSetCaptureProperty(capture, CV_CAP_PROP_CONTRAST, value);
}

} // end namespace sensor
} // end namespace flair
