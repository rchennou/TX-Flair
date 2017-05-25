// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2017/04/25
//  filename:   BebopImu.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    imu for bebop
//
//
/*********************************************************************/

#include "BebopImu.h"
#include <FrameworkManager.h>
#include <I2cPort.h>
#include <Vector3D.h>
#include <Euler.h>
#include <ImuData.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#define G 9.81

using std::string;
using namespace flair::core;

namespace flair {
namespace sensor {
  
BebopImu::BebopImu(string name,I2cPort* i2cPort,uint8_t priority): Imu(name),Thread(getFrameworkManager(), name, priority) {
  I2Cdev::initialize(i2cPort);
  mpu=new MPU6050();
  mpu->initialize();
  if(!mpu->testConnection()) Thread::Err("MPU6050 did not respond\n");
  mpu->setDLPFMode(0);
  Printf("dlpf %i fifo %i fifo_count %i fifo_en %i\n",mpu->getDLPFMode(),mpu->getFIFOEnabled(),mpu->getFIFOCount(),mpu->getXGyroFIFOEnabled());
 // mpu->dmpInitialize();
}

       
BebopImu::~BebopImu() {
  
}

void BebopImu::Run(void) {
  static int32_t accs_offset[3]={0,0,0};
  static int32_t gyrs_offset[3]={0,0,0};
  static int cpt=0;
  Vector3Df scaledAcc,scaledMag,scaledGyr;
  int16_t rawAx,rawAy,rawAz,rawGx,rawGy,rawGz;
  ImuData *imuData;
  GetDatas(&imuData);
  
  float gyros_gain = 0;
  float acc_gain=0;
  switch(mpu->getFullScaleAccelRange()) {
    case 0:
      acc_gain=1/16384.*G;
      break;
    case 1:
      acc_gain=1/8192.*G;
      break;
    case 2:
      acc_gain=1/4096.*G;
      break;
    case 3:
      acc_gain=1/2048.*G;
      break;
    default:
      Thread::Err("invalid AccelRange\n");
  }
  
  switch(mpu->getFullScaleGyroRange()) {
    case 0:
      gyros_gain=1/131.;
      break;
    case 1:
      gyros_gain=1/65.5;
      break;
    case 2:
      gyros_gain=1/32.8;
      break;
    case 3:
      gyros_gain=1/16.4;
      break;
    default:
      Thread::Err("invalid GyroRange\n");
  }
  gyros_gain = Euler::ToRadian(gyros_gain);
  
        
  SetPeriodMS(5);
  
  while(!ToBeStopped()) {
    mpu->getMotion6(&rawAx, &rawAy, &rawAz, &rawGx, &rawGy, &rawGz);
    
    if(cpt==0) Printf("BebopImu::calibrating offsets, do not move imu\n");
    
    if(cpt<2000) { //init offsets
        accs_offset[0]+=rawAx;
        accs_offset[1]+=rawAy;
        accs_offset[2]+=rawAz;
        gyrs_offset[0]+=rawGx;
        gyrs_offset[1]+=rawGy;
        gyrs_offset[2]+=rawGz;
        
        if(cpt==1999) {
          SetIsReady(true);
          Printf("BebopImu::calibration done\n");
        }
        cpt++;
        scaledAcc.x=0;
        scaledAcc.y=0;
        scaledAcc.z=0;
        scaledGyr.x=0;
        scaledGyr.y=0;
        scaledGyr.z=0;
      
    } else {
      scaledAcc.x=acc_gain*(rawAx-accs_offset[0]/cpt);
      scaledAcc.y=acc_gain*(rawAy-accs_offset[1]/cpt);
      scaledAcc.z=acc_gain*((rawAz-accs_offset[2]/cpt));
      scaledMag.x=0;
      scaledMag.y=0;
      scaledMag.z=0;
      scaledGyr.x=gyros_gain*(rawGx-gyrs_offset[0]/cpt);
      scaledGyr.y=gyros_gain*(rawGy-gyrs_offset[1]/cpt);
      scaledGyr.z=gyros_gain*(rawGz-gyrs_offset[2]/cpt);
    }
    
    ApplyRotation(scaledAcc);
    scaledAcc.z-=G;
    ApplyRotation(scaledMag);
    ApplyRotation(scaledGyr);
    imuData->SetRawAccMagAndGyr(scaledAcc,scaledMag,scaledGyr);
    imuData->SetDataTime(GetTime());
    ProcessUpdate(imuData);
    WaitPeriod();
  }
}



} // end namespace sensor
} // end namespace flair