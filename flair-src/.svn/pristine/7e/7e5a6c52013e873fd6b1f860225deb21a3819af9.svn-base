// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/14
//  filename:   Ahrs_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Virtual class for Ahrs_impl
//
//
/*********************************************************************/

#include "Ahrs_impl.h"
#include "Ahrs.h"
#include <Imu.h>
#include <Tab.h>
#include <TabWidget.h>
#include <DataPlot1D.h>
#include <AhrsData.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;
using namespace flair::sensor;

Ahrs_impl::Ahrs_impl(Ahrs *inSelf) : self(inSelf) {
  rollPlot = NULL;
  pitchPlot = NULL;
  yawPlot = NULL;
  wXPlot = NULL;
  wYPlot = NULL;
  wZPlot = NULL;
  q0Plot = NULL;
  q1Plot = NULL;
  q2Plot = NULL;
  q3Plot = NULL;

  eulerTab = NULL;
  quaternionTab = NULL;

  ahrsData = new AhrsData(self);
}

Ahrs_impl::~Ahrs_impl() {}

void Ahrs_impl::UseDefaultPlot(void) {

  eulerTab = new Tab(((Imu *)(self->Parent()))->tab, "AHRS");
  rollPlot = new DataPlot1D(eulerTab->NewRow(), "roll", -30, 30);
  rollPlot->AddCurve(ahrsData->Element(AhrsData::RollDeg));
  pitchPlot = new DataPlot1D(eulerTab->LastRowLastCol(), "pitch", -30, 30);
  pitchPlot->AddCurve(ahrsData->Element(AhrsData::PitchDeg));
  yawPlot = new DataPlot1D(eulerTab->LastRowLastCol(), "yaw", -180, 180);
  yawPlot->AddCurve(ahrsData->Element(AhrsData::YawDeg));

  wXPlot = new DataPlot1D(eulerTab->NewRow(), "w_x", -200, 200);
  wXPlot->AddCurve(ahrsData->Element(AhrsData::WxDeg));
  wYPlot = new DataPlot1D(eulerTab->LastRowLastCol(), "w_y", -200, 200);
  wYPlot->AddCurve(ahrsData->Element(AhrsData::WyDeg));
  wZPlot = new DataPlot1D(eulerTab->LastRowLastCol(), "w_z", -200, 200);
  wZPlot->AddCurve(ahrsData->Element(AhrsData::WzDeg));

  quaternionTab = new Tab(((Imu *)(self->Parent()))->tab, "Quaternion");
  q0Plot = new DataPlot1D(quaternionTab->NewRow(), "q0", -1, 1);
  q0Plot->AddCurve(ahrsData->Element(AhrsData::Q0));
  q1Plot = new DataPlot1D(quaternionTab->NewRow(), "q1", -1, 1);
  q1Plot->AddCurve(ahrsData->Element(AhrsData::Q1));
  q2Plot = new DataPlot1D(quaternionTab->LastRowLastCol(), "q2", -1, 1);
  q2Plot->AddCurve(ahrsData->Element(AhrsData::Q2));
  q3Plot = new DataPlot1D(quaternionTab->LastRowLastCol(), "q3", -1, 1);
  q3Plot->AddCurve(ahrsData->Element(AhrsData::Q3));
}

void Ahrs_impl::AddPlot(const AhrsData *ahrsData, DataPlot::Color_t color) {
  if (rollPlot != NULL) {
    rollPlot->AddCurve(ahrsData->Element(AhrsData::RollDeg), color);
    pitchPlot->AddCurve(ahrsData->Element(AhrsData::PitchDeg), color);
    yawPlot->AddCurve(ahrsData->Element(AhrsData::YawDeg), color);
  }
  if (wXPlot != NULL) {
    wXPlot->AddCurve(ahrsData->Element(AhrsData::WxDeg), color);
    wYPlot->AddCurve(ahrsData->Element(AhrsData::WyDeg), color);
    wZPlot->AddCurve(ahrsData->Element(AhrsData::WzDeg), color);
  }
  if (quaternionTab != NULL) {
    q0Plot->AddCurve(ahrsData->Element(AhrsData::Q0), color);
    q1Plot->AddCurve(ahrsData->Element(AhrsData::Q1), color);
    q2Plot->AddCurve(ahrsData->Element(AhrsData::Q2), color);
    q3Plot->AddCurve(ahrsData->Element(AhrsData::Q3), color);
  }
}
