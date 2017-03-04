// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/03/06
//  filename:   Camera.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Virtual class for Camera
//
//
/*********************************************************************/

#include "Camera.h"
#include <FrameworkManager.h>
#include <Tab.h>
#include <TabWidget.h>
#include <GroupBox.h>
#include <GridLayout.h>
#include <DataPlot1D.h>
#include <Picture.h>
#include <highgui.h>
#include <fstream>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

Camera::Camera(const FrameworkManager *parent, string name, uint16_t width,
               uint16_t height, cvimage::Type::Format format)
    : IODevice(parent, name) {
  plot_tab = NULL;

  // do not allocate imagedata, allocation is done by the camera
  output = new cvimage((IODevice *)this, width, height, format, "out", false);

  // station sol
  main_tab = new Tab(parent->GetTabWidget(), name);
  tab = new TabWidget(main_tab->NewRow(), name);
  sensor_tab = new Tab(tab, "Setup");
  setup_groupbox = new GroupBox(sensor_tab->NewRow(), name);
  setup_layout = new GridLayout(sensor_tab->NewRow(), "setup");
}

Camera::Camera(const IODevice *parent, std::string name)
    : IODevice(parent, name) {
  plot_tab = NULL;
  main_tab = NULL;
  tab = NULL;
  sensor_tab = NULL;
  setup_groupbox = NULL;

  output = NULL;
}

Camera::~Camera() {
  if (main_tab != NULL)
    delete main_tab;
}

DataType const &Camera::GetOutputDataType() const {
  return output->GetDataType();
}

GroupBox *Camera::GetGroupBox(void) const { return setup_groupbox; }

GridLayout *Camera::GetLayout(void) const { return setup_layout; }

void Camera::UseDefaultPlot(const core::cvimage *image) {
  if (tab == NULL) {
    Err("not applicable for simulation part.\n");
    return;
  }

  plot_tab = new Tab(tab, "Picture");
  Picture *plot = new Picture(plot_tab->NewRow(), ObjectName(), image);
}

Tab *Camera::GetPlotTab(void) const { return plot_tab; }

uint16_t Camera::Width(void) const { return output->GetDataType().GetWidth(); }

uint16_t Camera::Height(void) const {
  return output->GetDataType().GetHeight();
}

core::cvimage *Camera::Output(void) { return output; }

void Camera::SaveToFile(string filename) const {
  Printf("saving %s, size %i\n", filename.c_str(), output->img->imageSize);
  std::ofstream pFile;
  pFile.open(filename);
  output->GetMutex();
  pFile.write(output->img->imageData, output->img->imageSize);
  output->ReleaseMutex();

  pFile.close();
}

} // end namespace sensor
} // end namespace flair
