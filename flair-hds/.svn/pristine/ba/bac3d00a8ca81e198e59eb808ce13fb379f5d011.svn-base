//  created:    2015/10/19
//  filename:   DemoFollowLine.cpp
//
//  author:     Gildas Bayard, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    demo follow line
//
//
/*********************************************************************/

#include "DemoFollowLine.h"
#include <Uav.h>
#include <Camera.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <cvmatrix.h>
#include <MetaDualShock3.h>
#include <LowPassFilter.h>
#include <Pid.h>
#include <Sobel.h>
#include <ImgThreshold.h>
#include <Tab.h>
#include <GridLayout.h>
#include <CvtColor.h>
#include <Picture.h>
#include <HoughLines.h>
#include <DataPlot1D.h>
#include <Ahrs.h>
#include <AhrsData.h>
#include <V4LCamera.h>

using namespace std;
using namespace flair::core;
using namespace flair::sensor;
using namespace flair::gui;
using namespace flair::filter;
using namespace flair::meta;

DemoFollowLine::DemoFollowLine(TargetController *controller): DemoOpticalFlow(controller) {
	Uav* uav=GetUav();
	
    //We disabled the X and Y optical flow max speed parameters
    maxXSpeed->setEnabled(false);
    maxYSpeed->setEnabled(false);
    //We add a speed along the line step parameter
    speedStep=new DoubleSpinBox(opticalFlowGroupBox->NewRow(),"speed step"," m/s",-5,5,0.1,1);

    Sobel *sobelAlongX=new Sobel(greyCameraImage,uav->GetVerticalCamera()->GetLayout()->NewRow(),"sobel along x");
    ImgThreshold *threshold=new ImgThreshold(sobelAlongX,uav->GetVerticalCamera()->GetLayout()->NewRow(),"threshold");
    houghLines=new HoughLines(threshold,uav->GetVerticalCamera()->GetLayout()->NewRow(),"houghlines");

    Picture* sobelPlot=new Picture(uav->GetVerticalCamera()->GetPlotTab()->LastRowLastCol(),sobelAlongX->ObjectName(),sobelAlongX->Output());
    Picture* threshPlot=new Picture(uav->GetVerticalCamera()->GetPlotTab()->LastRowLastCol(),threshold->ObjectName(),threshold->Output());

    DataPlot1D *plotDistance=new DataPlot1D(uav->GetVerticalCamera()->GetPlotTab()->NewRow(),"distance",-20,20);
            plotDistance->AddCurve(houghLines->Output()->Element(0));
    DataPlot1D *plotOrientation=new DataPlot1D(uav->GetVerticalCamera()->GetPlotTab()->LastRowLastCol(),"orientation",-90,90);
            plotOrientation->AddCurve(houghLines->Output()->Element(2));
    DataPlot1D *plotLineDetected=new DataPlot1D(uav->GetVerticalCamera()->GetPlotTab()->LastRowLastCol(),"line detected",0,1.1);
            plotLineDetected->AddCurve(houghLines->Output()->Element(3));

    customOrientation=new AhrsData(this,"orientation");
    speedAlongLine=0;
    flagCameraLost=false;
}

void DemoFollowLine::SignalEvent(Event_t event) {
    DemoOpticalFlow::SignalEvent(event);
    switch(event) {
    case Event_t::EnteringFailSafeMode:
        //We shall reset speed along line value
        speedAlongLine=0;
        //enable speedStep
        speedStep->setEnabled(true);
        break;
    }
}

void DemoFollowLine::ExtraCheckJoystick(void) {
    DemoOpticalFlow::ExtraCheckJoystick();

    static bool wasFollowLineModeButtonPressed=false;
    static bool wasIncreaseSpeedButtonPressed=false;
    static bool wasDecreaseSpeedButtonPressed=false;
    // controller button R1 enters follow the line mode

    if(GetJoystick()->IsButtonPressed(9)) { // R1
        if (!wasFollowLineModeButtonPressed) {
            wasFollowLineModeButtonPressed=true;
            if (SetOrientationMode(OrientationMode_t::Custom)) {
                Thread::Info("(Re)entering follow line mode\n");
                //disable speedStep to have consistent increment/decrement of opticalFlowReference
                speedStep->setEnabled(false);
            } else {
                Thread::Warn("Could not enter follow line mode\n");
            }
        }
    } else {
        wasFollowLineModeButtonPressed=false;
    }

    // if we are in follow the line mode, we care about up and down buttons
    if (GetOrientationMode()==OrientationMode_t::Custom) {
        // controller button up increases speed along line
        if(GetJoystick()->IsButtonPressed(12)) { // UP
            if (!wasIncreaseSpeedButtonPressed) {
                wasIncreaseSpeedButtonPressed=true;
                speedAlongLine+=speedStep->Value();
                Thread::Info("Increasing speed along line. Speed is now %f\n", speedAlongLine);
            }
        } else {
            wasIncreaseSpeedButtonPressed=false;
        }

        // controller button down decreases speed along line
        if(GetJoystick()->IsButtonPressed(13)) { // DOWN
            if (!wasDecreaseSpeedButtonPressed) {
                wasDecreaseSpeedButtonPressed=true;
                speedAlongLine-=speedStep->Value();
                Thread::Info("Decreasing speed along line. Speed is now %f\n", speedAlongLine);
            }
        } else {
            wasDecreaseSpeedButtonPressed=false;
        }
    }
}

const AhrsData *DemoFollowLine::GetReferenceOrientation(void) {
    //ne pas mettre en static?
    //pour pouvoir maitriser le reset quand on passe en suivi de ligne
    static float error_lateralPosition;
    Euler refAngles;

    //Yaw angle
    Quaternion currentQuaternion=GetCurrentQuaternion();
    Euler currentAngles;//in vrpn frame
    currentQuaternion.ToEuler(currentAngles);
    if (houghLines->isLineDetected()) {
        refAngles.yaw=0;
    } else {
        refAngles.yaw=currentAngles.yaw;
    }

    float focal=271.76;
    float z,dz;
    AltitudeValues(z, dz);
    float scale=z/focal;    

    // Forward speed (in pixel/s)
    if (houghLines->isLineDetected()) {
        float error_speedAlongLine=opticalFlowRealSpeed->Value(0,0)-speedAlongLine;
        float errorVariation_speedAlongLine=opticalFlowRealAcceleration->Value(0,0);
        u_x->SetValues(error_speedAlongLine, errorVariation_speedAlongLine);
        u_x->Update(GetTime());
        refAngles.pitch=u_x->Output();
    } else {
        refAngles.pitch=0;
    }

    // lateral distance to the line
//    if (houghLines->isLineDetected()) {
        error_lateralPosition=-houghLines->GetDistance()*scale;
/*    } else {
        error_lateralPosition+=opticalFlowSpeed->Output(1,0)*scale;
    }*/
    float errorVariation_lateralPosition=opticalFlowRealSpeed->Value(1,0);

    u_y->SetValues(error_lateralPosition, errorVariation_lateralPosition);
    u_y->Update(GetTime());
    refAngles.roll=-u_y->Output();

    customReferenceOrientation->SetQuaternionAndAngularRates(refAngles.ToQuaternion(),Vector3Df(0,0,0));

    return customReferenceOrientation;
}

const AhrsData *DemoFollowLine::GetOrientation(void) const {
    Quaternion ahrsQuaternion;
    Vector3Df ahrsAngularSpeed;
    GetDefaultOrientation()->GetQuaternionAndAngularRates(ahrsQuaternion, ahrsAngularSpeed);

    //yaw from line if available
    if (houghLines->isLineDetected()) {
        Euler ahrsEuler=ahrsQuaternion.ToEuler();
        ahrsEuler.yaw=-houghLines->GetOrientation();
        Quaternion mixQuaternion=ahrsEuler.ToQuaternion();

        customOrientation->SetQuaternionAndAngularRates(mixQuaternion,ahrsAngularSpeed);
    } else {
        customOrientation->SetQuaternionAndAngularRates(ahrsQuaternion,ahrsAngularSpeed);
    }

    return customOrientation;
}

void DemoFollowLine::ExtraSecurityCheck(void) {
  if(GetUav()->GetType()=="hds_x8") {
    if(((V4LCamera*)GetUav()->GetVerticalCamera())->HasProblems() && !flagCameraLost) {
      flagCameraLost = true;
      Thread::Err("Camera lost\n");
      SafeStop();
      Land();
    }
  }
}

DemoFollowLine::~DemoFollowLine() {
}
