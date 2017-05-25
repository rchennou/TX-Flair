//  created:    2017/02/10
//  filename:   ApriltagFollower.cpp
//
//  author:     Thomas Fuhrmann
//              Osamah Saif
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Following an Apriltag
//              Based on the CircleFollower demo
//
//
/*********************************************************************/

#include "ApriltagFollower.h"
#include <TargetController.h>
#include <Uav.h>
#include <GridLayout.h>
#include <PushButton.h>
#include <GroupBox.h>
#include <DataPlot1D.h>
#include <FrameworkManager.h>
#include <cvmatrix.h>
#include <Tab.h>
#include <Pid.h>
#include <Ahrs.h>
#include <AhrsData.h>
#include <Camera.h>
#include <DoubleSpinBox.h>
#include <EulerDerivative.h>
#include <CvtColor.h>
#include <OpticalFlow.h>
#include <OpticalFlowSpeed.h>
#include <LowPassFilter.h>
#include <ButterworthLowPass.h>
#include <MetaDualShock3.h>

#include "Streaming.h"

using namespace std;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;
using namespace flair::filter;
using namespace flair::meta;

#define STREAM_MISSED_MAX 10

ApriltagFollower::ApriltagFollower(TargetController *controller, const string streaminIp) : UavStateMachine(controller),
                                                                                            behaviourMode(BehaviourMode_t::Default) {
  Uav *uav = GetUav();

  startTracking = new PushButton(GetButtonsLayout()->NewRow(), "start tracking");
  startPositionHold = new PushButton(GetButtonsLayout()->LastRowLastCol(), "start position hold");

  uX = new Pid(setupLawTab->At(1, 0), "u_x");
  uX->UseDefaultPlot(graphLawTab->NewRow());
  uY = new Pid(setupLawTab->At(1, 1), "u_y");
  uY->UseDefaultPlot(graphLawTab->LastRowLastCol());

  customReferenceOrientation = new AhrsData(this, "reference");
  uav->GetAhrs()->AddPlot(customReferenceOrientation, DataPlot::Green);
  AddDataToControlLawLog(customReferenceOrientation);

  customOrientation = new AhrsData(this, "orientation");
  getFrameworkManager()->AddDeviceToLog(uav->GetVerticalCamera());

  desiredDepthApriltag = new DoubleSpinBox(GetButtonsLayout()->NewRow(), "Desired Depth Apriltag", 0, 5, 0.10, 2, 1.0);
  desiredYApriltag = new DoubleSpinBox(GetButtonsLayout()->LastRowLastCol(), "Desired Y Apriltag", 0, 5, 0.10, 2, 0.0);

  // Streaming of the video and reception of the computed data
#ifdef STREAMING
  stream = new ::Streaming(streaminIp);
  getFrameworkManager()->AddDeviceToLog(stream);
#ifdef SIMU
  stream->Start();
#endif
#endif

  cvmatrix_descriptor *descVel = new cvmatrix_descriptor(3, 1);
  descVel->SetElementName(0, 0, "x_vel");
  descVel->SetElementName(1, 0, "y_vel");
  descVel->SetElementName(2, 0, "yaw_vel");
  cvmatrix *matrixVel = new cvmatrix(this, descVel, floatType, "EulerDeriv");
  delete descVel;
  eulerVel = new EulerDerivative(stream, GetButtonsLayout()->NewRow(), "AF_vel", matrixVel);
  delete matrixVel;
  
  cvmatrix_descriptor *descFilter = new cvmatrix_descriptor(3, 1);
  cvmatrix *prev_value = new cvmatrix(this, descFilter, floatType);
  delete descFilter;
  filterVel = new LowPassFilter(eulerVel, GetButtonsLayout()->NewRow(), "vel filter", prev_value);
  delete prev_value;
  
  filterVel2 =new ButterworthLowPass(eulerVel, GetButtonsLayout()->NewRow(), "vel filter2", 3,3,1);
  
  DataPlot1D* vx_plot = new DataPlot1D(stream->graphGroupBox->NewRow(), "vx", -1, 1);
  DataPlot1D* vy_plot = new DataPlot1D(stream->graphGroupBox->LastRowLastCol(), "vy", -1, 1);
  DataPlot1D* wz_plot = new DataPlot1D(stream->graphGroupBox->LastRowLastCol(), "wz", -1, 1);
  vx_plot->AddCurve(eulerVel->Matrix()->Element(0));
  vx_plot->AddCurve(filterVel->Matrix()->Element(0),DataPlot::Blue);
  vx_plot->AddCurve(filterVel2->Matrix()->Element(0),DataPlot::Green);
  vy_plot->AddCurve(eulerVel->Matrix()->Element(1));
  vy_plot->AddCurve(filterVel->Matrix()->Element(1),DataPlot::Blue);
  vy_plot->AddCurve(filterVel2->Matrix()->Element(1),DataPlot::Green);
  wz_plot->AddCurve(eulerVel->Matrix()->Element(2));
  wz_plot->AddCurve(filterVel->Matrix()->Element(2),DataPlot::Blue);
  wz_plot->AddCurve(filterVel2->Matrix()->Element(2),DataPlot::Green);
  
  uav->GetAhrs()->YawPlot()->AddCurve(stream->graphCvMatrix->Element(5),DataPlot::Black);
  uav->GetAhrs()->WZPlot()->AddCurve(eulerVel->Matrix()->Element(2),DataPlot::Black);
  /*
  CvtColor *greyCameraImage=new CvtColor(uav->GetVerticalCamera(),"gray",CvtColor::Conversion_t::ToGray);

	uav->GetVerticalCamera()->UseDefaultPlot(greyCameraImage->Output()); // Le defaultPlot de la caméra peut afficher n'importe quoi?

	//optical flow stack
  //opticalFlow= matrice de déplacements en pixels entre 2 images consécutives
  OpticalFlow *opticalFlow=new OpticalFlow(greyCameraImage,uav->GetVerticalCamera()->GetLayout()->NewRow(),"flux optique");
  //opticalFlowCompensated=new OpticalFlowCompensated(opticalFlow,uav->GetAhrs(),uav->GetVerticalCamera()->GetLayout()->NewRow(),"flux optique compense");
  OpticalFlowSpeed *opticalFlowSpeedRaw=new OpticalFlowSpeed(opticalFlow,"vitesse du flux optique");
  //opticalFlowSpeed=vitesse de déplacement en pixels par seconde (moyenne sur tous les points et division par le delta T)
  cvmatrix* twoByOneOFS=new cvmatrix((const Thread*)this,2,1,floatType);
  opticalFlowSpeed=new LowPassFilter(opticalFlowSpeedRaw,uav->GetVerticalCamera()->GetLayout()->NewRow(),"Speed lowPass",twoByOneOFS);
  
  Tab* opticalFlowRealTab=new Tab(getFrameworkManager()->GetTabWidget(),"real speed");
  opticalFlowRealSpeed=new cvmatrix((const Thread*)this,2,1,floatType);
  DataPlot1D* xRealVelocityPlot=new DataPlot1D(opticalFlowRealTab->NewRow(),"x speed (m/s)",-2,2);
  DataPlot1D* yRealVelocityPlot=new DataPlot1D(opticalFlowRealTab->LastRowLastCol(),"y speed (m/s)",-2,2);
  xRealVelocityPlot->AddCurve(opticalFlowRealSpeed->Element(0));
  yRealVelocityPlot->AddCurve(opticalFlowRealSpeed->Element(1));*/
}

ApriltagFollower::~ApriltagFollower() {
}

const AhrsData *ApriltagFollower::GetOrientation(void) const {
  if (behaviourMode == BehaviourMode_t::Tracking) {
    if(trackingDetection) {
      //get roll, pitch and w from imu; yaw from tag
      Quaternion ahrsQuaternion;
      Vector3Df ahrsAngularSpeed;
      GetDefaultOrientation()->GetQuaternionAndAngularRates(ahrsQuaternion, ahrsAngularSpeed);

      Euler ahrsEuler = ahrsQuaternion.ToEuler();
      //delta=line from uav center to tag enter
      //yaw=angle from delta to x_uav
      //we want to stabilize this angle to 0 (uav looking to tag)
      ahrsEuler.yaw =  -atan2(trackingPosition.y,trackingPosition.x);
      Quaternion mixQuaternion = ahrsEuler.ToQuaternion();

      customOrientation->SetQuaternionAndAngularRates(mixQuaternion, ahrsAngularSpeed);

      return customOrientation;
    }else {
      return GetDefaultOrientation();
    }
  } else if (behaviourMode == BehaviourMode_t::PositionHold) {
    return GetDefaultOrientation();
  } else {
    Warn("unknown state\n");
  }
}

//go in this function in cutom mode and does not take in account the dualshock
AhrsData *ApriltagFollower::GetReferenceOrientation(void) {
  if (behaviourMode == BehaviourMode_t::Tracking) {
    ComputeTrackingReferenceOrientation();
  } else if (behaviourMode == BehaviourMode_t::PositionHold) {
    ComputePositionHoldReferenceOrientation();
  } else {
    Warn("unknown state\n");
  }

  return customReferenceOrientation;
}

void ApriltagFollower::ComputePositionHoldReferenceOrientation(void) {
 
}

void ApriltagFollower::ComputeTrackingReferenceOrientation(void) {
  Vector2Df pos_err, vel_err; // in Uav coordinate system
  float yaw_ref;
  Euler refAngles;

  if(trackingDetection) {
    PositionValues(pos_err, vel_err, yaw_ref);

    refAngles.yaw = yaw_ref;

    uX->SetValues(pos_err.x, vel_err.x);
    uX->Update(GetTime());
    refAngles.pitch = uX->Output();
    uY->SetValues(pos_err.y, vel_err.y);
    uY->Update(GetTime());
    refAngles.roll = -uY->Output();
    
    customReferenceOrientation->SetQuaternionAndAngularRates(refAngles.ToQuaternion(), Vector3Df(0, 0, 0));
    wasLost=false;
  } else {
    Quaternion currentQuaternion;
    Vector3Df currentAngularSpeed;
    if(!wasLost) {
      GetDefaultOrientation()->GetQuaternionAndAngularRates(currentQuaternion,currentAngularSpeed);
      joy->SetYawRef(currentQuaternion);
      wasLost=true;
    }
    GetDefaultReferenceOrientation()->GetQuaternionAndAngularRates(currentQuaternion,currentAngularSpeed);
    customReferenceOrientation->SetQuaternionAndAngularRates(currentQuaternion,currentAngularSpeed);
  }
}

void ApriltagFollower::PositionValues(Vector2Df &pos_error, Vector2Df &vel_error, float &yaw_ref) {
  static Vector2Df savedPosError;
  static Vector2Df savedVelError;
  static float savedYaw;

  if (trackingNewData) {
    Vector2Df referencePoint;
    //in tag frame
    referencePoint.x=desiredDepthApriltag->Value();
    referencePoint.y=desiredYApriltag->Value();
    //in uav frame
    referencePoint.Rotate(trackingRotation.yaw);
    referencePoint+=trackingPosition.To2Dxy();
    pos_error = -referencePoint;

    Vector2Df velReferencePoint;
    //in tag frame
    velReferencePoint.x=-desiredYApriltag->Value()*eulerVel->Output(2,0);
    velReferencePoint.y=desiredDepthApriltag->Value()*eulerVel->Output(2,0);
    //in uav frame
    velReferencePoint.Rotate(trackingRotation.yaw);
    velReferencePoint.x=eulerVel->Output(0,0)+velReferencePoint.x;
    velReferencePoint.y=eulerVel->Output(1,0)+velReferencePoint.y;
    vel_error=-velReferencePoint;
    
    //vel_error.x=opticalFlowRealSpeed->Value(0,0);
    //vel_error.y=opticalFlowRealSpeed->Value(1,0);
    
    //pos_error.x = desiredDepthApriltag->Value()-trackingPosition.x ;
    //pos_error.y = desiredYApriltag->Value()-trackingPosition.y;
    
    // Get the velocity from EulerDerivative
    //ok if uav's yaw is not changing! (for y)
    //vel_error.x = -eulerVel->Output(0,0);
    //vel_error.y = -eulerVel->Output(1,0);

    //todo: change this to a parameter
    yaw_ref =0;//looking to tag

    savedPosError = pos_error;
    savedVelError = vel_error;
    savedYaw = yaw_ref;
  } else {
    pos_error = savedPosError;
    vel_error = savedVelError;
    yaw_ref = savedYaw;
  }
}

void ApriltagFollower::SignalEvent(Event_t event) {
  UavStateMachine::SignalEvent(event);
  switch (event) {
    case Event_t::TakingOff:
      behaviourMode = BehaviourMode_t::Default;
      //change to position hold when optical flow ready
      //StartPositionHold();
      break;
    case Event_t::EnteringControlLoop: {
      //to debug when not flying:
      if (behaviourMode == BehaviourMode_t::Default) ComputeTrackingReferenceOrientation();
      /*
      float focal=271.76;
      float z,dz;
      AltitudeValues(z, dz);
      float scale=z/focal;
      opticalFlowRealSpeed->SetValue(0,0,opticalFlowSpeed->Output(0,0)*scale);
      opticalFlowRealSpeed->SetValue(1,0,opticalFlowSpeed->Output(1,0)*scale);*/
      break;
    }
    case Event_t::EnteringFailSafeMode:
      behaviourMode = BehaviourMode_t::Default;
      break;
  }
}

void ApriltagFollower::ExtraCheckPushButton(void) {
  if (startTracking->Clicked() && (behaviourMode != BehaviourMode_t::Tracking)) {
    StartTracking();
  }
  /*
  if (startPositionHold->Clicked() && (behaviourMode != BehaviourMode_t::PositionHold)) {
    StartPositionHold();
  }*/
}

void ApriltagFollower::ExtraCheckJoystick(void) {
  //Square
  if (GetJoystick()->IsButtonPressed(2) && (behaviourMode!=BehaviourMode_t::Tracking)) {
    StartTracking();
  }
  //Circle
  /*
  if (GetJoystick()->IsButtonPressed(4) && (behaviourMode!=BehaviourMode_t::PositionHold)) { 
    StartPositionHold();
  }*/
}

void ApriltagFollower::ExtraSecurityCheck(void) {
  static int streamMissedCounter = 0;

  //get tracking datas as soon as possible in the control loop
  trackingNewData=stream->GetComputedData(trackingPosition, trackingRotation, trackingDetection);
  /*
  //if(trackingNewData && trackingDetection) printf("%f\n",Euler::ToDegree(dYaw));
  //if(trackingNewData && trackingDetection) printf("%f\n",Euler::ToDegree(eulerVel->Output(2,0)));
  if (trackingNewData && (behaviourMode==BehaviourMode_t::Tracking)) {
    if (!trackingDetection) {
      streamMissedCounter++;
      if (streamMissedCounter > STREAM_MISSED_MAX) {
        // To much stream missed, so hold the uav position
        Thread::Warn("Too much apriltag detection miss, activate position hold.\n");
        //todo: position hold when optical flow ready
        //StartPositionHold();
        EnterFailSafeMode();
      }
    } else {
      streamMissedCounter = 0;
    }
  }
  */
}

void ApriltagFollower::StartTracking(void) {
  if(!trackingDetection) {
    Thread::Warn("No tag found, not entering tracking mode\n");
    return;
  }
  if (SetOrientationMode(OrientationMode_t::Custom)) {
    Thread::Info("(Re)entering tracking mode\n");
    uX->Reset();
    uY->Reset();
    behaviourMode=BehaviourMode_t::Tracking;
    wasLost=false;
	} else {
    Thread::Warn("Could not enter tracking mode\n");
	}
}

void ApriltagFollower::StartPositionHold(void) {
  if (SetOrientationMode(OrientationMode_t::Custom)) {
    Thread::Info("(Re)entering optical flow mode (position hold)\n");
    uX->Reset();
    uY->Reset();
    behaviourMode = BehaviourMode_t::PositionHold;
    yawHold=GetDefaultOrientation()->GetQuaternion().ToEuler().yaw;
	} else {
    Thread::Warn("Could not enter optical flow mode (position hold)\n");
	}
}
