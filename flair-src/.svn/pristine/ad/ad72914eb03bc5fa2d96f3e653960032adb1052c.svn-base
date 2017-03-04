// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/16
//  filename:   Imu.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Virtual class for Imu
//
//
/*********************************************************************/

#include "Imu.h"
#include <FrameworkManager.h>
#include <Tab.h>
#include <TabWidget.h>
#include <GroupBox.h>
#include <GridLayout.h>
#include <DataPlot1D.h>
#include <ImuData.h>
#include <OneAxisRotation.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

Imu::Imu(const FrameworkManager *parent, string name) : IODevice(parent, name) {
  imuData = new ImuData(this);

  // station sol
  mainTab = new Tab(parent->GetTabWidget(), name);
  tab = new TabWidget(mainTab->NewRow(), name);
  sensorTab = new Tab(tab, "Reglages");
  setupGroupbox = new GroupBox(sensorTab->NewRow(), name);
  rotation = new OneAxisRotation(sensorTab->NewRow(), "post rotation");
}

Imu::Imu(const IODevice *parent, std::string name) : IODevice(parent, name) {
  imuData = new ImuData(this);
  mainTab = NULL;
  tab = NULL;
  sensorTab = NULL;
  setupGroupbox = NULL;
  rotation = NULL;
}

Imu::~Imu() {
  if (mainTab != NULL)
    delete mainTab;
}

void Imu::GetDatas(ImuData **outImuData) const { *outImuData = imuData; }

OneAxisRotation *Imu::GetOneAxisRotation(void) const {
  return rotation;
}

void Imu::UpdateImu() {
  if (rotation == NULL) {
    Err("not applicable for simulation part.\n");
    return;
  }
  Vector3D rawAcc, rawMag, rawGyr;
  imuData->GetRawAccMagAndGyr(rawAcc, rawMag, rawGyr);
  rotation->ComputeRotation(rawAcc);
  rotation->ComputeRotation(rawGyr);
  rotation->ComputeRotation(rawMag);
  imuData->SetRawAccMagAndGyr(rawAcc, rawMag, rawGyr);
}

GroupBox *Imu::GetGroupBox(void) const { return setupGroupbox; }

Layout *Imu::GetLayout(void) const { return sensorTab; }

void Imu::LockUserInterface(void) const {
  if (sensorTab == NULL) {
    Err("not applicable for simulation part.\n");
    return;
  }
  sensorTab->setEnabled(false);
}

void Imu::UnlockUserInterface(void) const {
  if (sensorTab == NULL) {
    Err("not applicable for simulation part.\n");
    return;
  }
  sensorTab->setEnabled(true);
}

void Imu::UseDefaultPlot(void) {
  if (tab == NULL) {
    Err("not applicable for simulation part.\n");
    return;
  }

  plotTab = new Tab(tab, "IMU");
  axPlot = new DataPlot1D(plotTab->NewRow(), "acc_x", -10, 10);
  axPlot->AddCurve(imuData->Element(ImuData::RawAx));
  ayPlot = new DataPlot1D(plotTab->LastRowLastCol(), "acc_y", -10, 10);
  ayPlot->AddCurve(imuData->Element(ImuData::RawAy));
  azPlot = new DataPlot1D(plotTab->LastRowLastCol(), "acc_z", -10, 10);
  azPlot->AddCurve(imuData->Element(ImuData::RawAz));

  if (plotTab == NULL)
    plotTab = new Tab(tab, "IMU");
  gxPlot = new DataPlot1D(plotTab->NewRow(), "gyr_x", -500, 500);
  gxPlot->AddCurve(imuData->Element(ImuData::RawGxDeg));
  gyPlot = new DataPlot1D(plotTab->LastRowLastCol(), "gyr_y", -500, 500);
  gyPlot->AddCurve(imuData->Element(ImuData::RawGyDeg));
  gzPlot = new DataPlot1D(plotTab->LastRowLastCol(), "gyr_z", -500, 500);
  gzPlot->AddCurve(imuData->Element(ImuData::RawGzDeg));

  if (plotTab == NULL)
    plotTab = new Tab(tab, "IMU");
  mxPlot = new DataPlot1D(plotTab->NewRow(), "mag_x", -500, 500);
  mxPlot->AddCurve(imuData->Element(ImuData::RawMx));
  myPlot = new DataPlot1D(plotTab->LastRowLastCol(), "mag_y", -500, 500);
  myPlot->AddCurve(imuData->Element(ImuData::RawMy));
  mzPlot = new DataPlot1D(plotTab->LastRowLastCol(), "mag_z", -500, 500);
  mzPlot->AddCurve(imuData->Element(ImuData::RawMz));
}

Tab *Imu::GetPlotTab(void) const { return plotTab; }

} // end namespace sensor
} // end namespace flair
