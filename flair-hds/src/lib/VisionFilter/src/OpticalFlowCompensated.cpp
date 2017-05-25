// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/14
//  filename:   OpticalFlowCompensated.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Compensate optical flow data for rotations
//
//
/*********************************************************************/
#include "OpticalFlowCompensated.h"
#include <io_data.h>
#include <Ahrs.h>
#include <AhrsData.h>
#include <OpticalFlow.h>
#include <OpticalFlowData.h>
#include <Euler.h>
#include <cvmatrix.h>
#include <Layout.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <DoubleSpinBox.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

OpticalFlowCompensated::OpticalFlowCompensated(const OpticalFlow *parent, const Ahrs *ahrs, const LayoutPosition* position, string name) : IODevice(parent, name), ahrs(ahrs), output(NULL) {
  cvmatrix_descriptor* desc=new cvmatrix_descriptor(3,2);
  desc->SetElementName(0,0,"raw displacement X");
  desc->SetElementName(0,1,"raw displacement Y");
  desc->SetElementName(1,0,"compensation X");
  desc->SetElementName(1,1,"compensation Y");
  desc->SetElementName(2,0,"displacement with compensation X");
  desc->SetElementName(2,0,"displacement with compensation Y");
  firstPointDisplacement=new cvmatrix(this,desc,floatType,name);
  delete desc;
  previousStepsAngularRates=new Vector3Df*[10];
  for (int i=0; i<10; i++) previousStepsAngularRates[i]=NULL;
  previousStepsAngularRatesIndex=0;

  GroupBox* reglages_groupbox=new GroupBox(position,name);
  //TODO: the gyroDelay is set to compensate for the time difference between image snapshot et gyro measurements
//it is equal to the time between 2 images (because optical flow always lags 1 frame) + the time to compute optical flow
//here it is approximated by 2 video frames
  gyroDelay=new SpinBox(reglages_groupbox->NewRow(),"gyro delay (in video frames):",0,10,1,2);
  gyroGain=new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),"gyro gain:",0.,500.,10.,2,300.);

}

OpticalFlowCompensated::~OpticalFlowCompensated() {
  delete output;
}

void OpticalFlowCompensated::UpdateFrom(const io_data *data) {
  OpticalFlowData *input=(OpticalFlowData *)data;
  if (!output) { //first pass
    output=new OpticalFlowData(this,input->MaxFeatures(),input->ObjectName()+"_filtered");
    previousTime=input->DataTime();
    return;
  }
//  float kX=320/Euler::ToRadian(70); //TEST: only for default simuCameraGL. fov=70° and image width=320 => k=320*180/(70*pi)
//  float kY=240/Euler::ToRadian(70); //TEST: only for default simuCameraGL. fov=70° and image height=240
  float kX=gyroGain->Value();
  float kY=gyroGain->Value();
  float deltaT=(input->DataTime()-previousTime)/(1000*1000*1000.);
  previousTime=input->DataTime();

  int delayedIndex=previousStepsAngularRatesIndex-gyroDelay->Value(); // Ahhh décalage, esprit canal...
  if (delayedIndex<0) delayedIndex+=10;

  if (!previousStepsAngularRates[previousStepsAngularRatesIndex]) {
    previousStepsAngularRates[previousStepsAngularRatesIndex]=new Vector3Df();
  }
  *previousStepsAngularRates[previousStepsAngularRatesIndex++]=ahrs->GetDatas()->GetAngularRates();

  if (!previousStepsAngularRates[delayedIndex]) return;
  float rotationFlowX=previousStepsAngularRates[delayedIndex]->y*deltaT*kY;
  float rotationFlowY=-previousStepsAngularRates[delayedIndex]->x*deltaT*kX;
  if (previousStepsAngularRatesIndex==10) previousStepsAngularRatesIndex=0;
  input->GetMutex();
  output->GetMutex();

  for (int i=0; i<input->NbFeatures(); i++) {
    if (!i) {
      firstPointDisplacement->SetValue(0,0,input->PointsB()[i].x-input->PointsA()[i].x);
      firstPointDisplacement->SetValue(0,1,input->PointsB()[i].y-input->PointsA()[i].y);
      firstPointDisplacement->SetValue(1,0,-rotationFlowX);
      firstPointDisplacement->SetValue(1,1,-rotationFlowY);
      firstPointDisplacement->SetValue(2,0,input->PointsB()[i].x-input->PointsA()[i].x-rotationFlowX);
      firstPointDisplacement->SetValue(2,1,input->PointsB()[i].y-input->PointsA()[i].y-rotationFlowY);
    }
    output->PointsA()[i].x=input->PointsA()[i].x;
    output->PointsA()[i].y=input->PointsA()[i].y;
    output->PointsB()[i].x=input->PointsB()[i].x-rotationFlowX;
    output->PointsB()[i].y=input->PointsB()[i].y-rotationFlowY;
  }
  output->SetNbFeatures(input->NbFeatures());
  output->SetFoundFeature(input->FoundFeature());
  output->SetFeatureError(input->FeatureError());

  output->ReleaseMutex();
  input->ReleaseMutex();

  output->SetDataTime(input->DataTime());
  ProcessUpdate(output);
}

  cvmatrix *OpticalFlowCompensated::GetFirstPointDisplacement() const {
    return firstPointDisplacement;
  }

} // end namespace filter
} // end namespace flair
