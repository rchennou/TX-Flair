//  created:    2016/07/01
//  filename:   DemoGps.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    demo GPS
//
//
/*********************************************************************/

#include "DemoGps.h"
#include <TargetController.h>
#include <Uav.h>
#include <GridLayout.h>
#include <PushButton.h>
#include <DataPlot1D.h>
#include <DataPlot2D.h>
#include <MetaDualShock3.h>
#include <FrameworkManager.h>
#include <TrajectoryGenerator2DCircle.h>
#include <cvmatrix.h>
#include <cmath>
#include <Tab.h>
#include <Pid.h>
#include <Ahrs.h>
#include <AhrsData.h>
#include <RTDM_SerialPort.h>
#include <Mb800.h>
#include <SimuGps.h>

using namespace std;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;
using namespace flair::filter;
using namespace flair::meta;

DemoGps::DemoGps(Uav* uav,TargetController *controller): UavStateMachine(uav,controller), behaviourMode(BehaviourMode_t::Default) {

    startCircle=new PushButton(GetButtonsLayout()->NewRow(),"start_circle");
    stopCircle=new PushButton(GetButtonsLayout()->LastRowLastCol(),"stop_circle");

    //RTDM_SerialPort *serialport=new RTDM_SerialPort(getFrameworkManager(),"gps_serial","rtser2");
    //gps=new Mb800(getFrameworkManager(),"gps",serialport,(NmeaGps::NMEAFlags_t)(NmeaGps::GGA|NmeaGps::VTG),40);
    gps=new SimuGps(getFrameworkManager(),"gps",(NmeaGps::NMEAFlags_t)(NmeaGps::GGA|NmeaGps::VTG),0,40);
    gps->UseDefaultPlot();
    getFrameworkManager()->AddDeviceToLog(gps);
    //gps->Start();

    circle=new TrajectoryGenerator2DCircle(gps->GetLayout()->NewRow(),"circle");
    //todo: add graphs in gps plot
    /*
    uav->GetVrpnObject()->xPlot()->AddCurve(circle->Matrix()->Element(0,0),DataPlot::Blue);
    uav->GetVrpnObject()->yPlot()->AddCurve(circle->Matrix()->Element(0,1),DataPlot::Blue);
    uav->GetVrpnObject()->VxPlot()->AddCurve(circle->Matrix()->Element(1,0),DataPlot::Blue);
    uav->GetVrpnObject()->VyPlot()->AddCurve(circle->Matrix()->Element(1,1),DataPlot::Blue);
    uav->GetVrpnObject()->XyPlot()->AddCurve(circle->Matrix()->Element(0,1),circle->Matrix()->Element(0,0),DataPlot::Blue,"circle");*/

    uX=new Pid(setupLawTab->At(1,0),"u_x");
    uX->UseDefaultPlot(graphLawTab->NewRow());
    uY=new Pid(setupLawTab->At(1,1),"u_y");
    uY->UseDefaultPlot(graphLawTab->LastRowLastCol());

    customReferenceOrientation= new AhrsData(this,"reference");
    uav->GetAhrs()->AddPlot(customReferenceOrientation,DataPlot::Yellow);
    AddDataToControlLawLog(customReferenceOrientation);

    customOrientation=new AhrsData(this,"orientation");
}

DemoGps::~DemoGps() {
}

AhrsData *DemoGps::GetReferenceOrientation(void) {
    Vector2D pos_err, vel_err; // in Uav coordinate system
    float yaw_ref;
    Euler refAngles;

    PositionValues(pos_err, vel_err, yaw_ref);

    refAngles.yaw=yaw_ref;

    uX->SetValues(pos_err.x, vel_err.x);
    uX->Update(GetTime());
    refAngles.pitch=uX->Output();

    uY->SetValues(pos_err.y, vel_err.y);
    uY->Update(GetTime());
    refAngles.roll=-uY->Output();

    customReferenceOrientation->SetQuaternionAndAngularRates(refAngles.ToQuaternion(),Vector3D(0,0,0));

    return customReferenceOrientation;
}

void DemoGps::PositionValues(Vector2D &pos_error,Vector2D &vel_error,float &yaw_ref) {
    Vector3D uav_pos,uav_vel;
    Vector2D uav_2Dpos,uav_2Dvel;

//TODO GPS position and circle center
   // GetUav()->GetVrpnObject()->GetPosition(uav_pos);
    //GetUav()->GetVrpnObject()->GetSpeed(uav_vel);

    uav_pos.To2Dxy(uav_2Dpos);
    uav_vel.To2Dxy(uav_2Dvel);

    if (behaviourMode==BehaviourMode_t::PositionHold) {
        pos_error=uav_2Dpos-posHold;
        vel_error=uav_2Dvel;
        yaw_ref=yawHold;
    } else { //Circle
        Vector2D circle_pos,circle_vel;
        Vector2D target_2Dpos;

        circle->SetCenter(target_2Dpos);

        //circle reference
        circle->Update(GetTime());
        circle->GetPosition(circle_pos);
        circle->GetSpeed(circle_vel);

        //error in optitrack frame
        pos_error=uav_2Dpos-circle_pos;
        vel_error=uav_2Dvel-circle_vel;
        yaw_ref=atan2(target_2Dpos.y-uav_pos.y,target_2Dpos.x-uav_pos.x);
    }

    //error in uav frame
    Quaternion currentQuaternion=GetCurrentQuaternion();
    Euler currentAngles;//in vrpn frame
    currentQuaternion.ToEuler(currentAngles);
    pos_error.Rotate(-currentAngles.yaw);
    vel_error.Rotate(-currentAngles.yaw);
}

void DemoGps::SignalEvent(Event_t event) {
    UavStateMachine::SignalEvent(event);
    switch(event) {
    case Event_t::TakingOff:
        behaviourMode=BehaviourMode_t::Default;
        break;
    case Event_t::EnteringControlLoop:
        if ((behaviourMode==BehaviourMode_t::Circle) && (!circle->IsRunning())) {
            GpsPositionHold();
        }
        break;
    case Event_t::EnteringFailSafeMode:
        behaviourMode=BehaviourMode_t::Default;
        break;
    }
}

void DemoGps::ExtraSecurityCheck(void) {

}

void DemoGps::ExtraCheckPushButton(void) {
    if(startCircle->Clicked() && (behaviourMode!=BehaviourMode_t::Circle)) {
        StartCircle();
    }
    if(stopCircle->Clicked() && (behaviourMode==BehaviourMode_t::Circle)) {
        StopCircle();
    }
}

void DemoGps::ExtraCheckJoystick(void) {
    //R1 and Circle
    if(GetJoystick()->IsButtonPressed(9) && GetJoystick()->IsButtonPressed(4) && (behaviourMode!=BehaviourMode_t::Circle)) {
        StartCircle();
    }

    //R1 and Cross
    if(GetJoystick()->IsButtonPressed(9) && GetJoystick()->IsButtonPressed(5) && (behaviourMode==BehaviourMode_t::Circle)) {
        StopCircle();
    }
}

void DemoGps::StartCircle(void) {
    if (SetOrientationMode(OrientationMode_t::Custom)) {
        Thread::Info("DemoGps: start circle\n");
    } else {
        Thread::Warn("DemoGps: could not start circle\n");
        return;
    }
    Vector3D uav_pos;
    Vector2D uav_2Dpos,target_2Dpos;

    circle->SetCenter(target_2Dpos);

    //todo get uav and circle pos by gps
    uav_pos.To2Dxy(uav_2Dpos);
    circle->StartTraj(uav_2Dpos);

    uX->Reset();
    uY->Reset();
    behaviourMode=BehaviourMode_t::Circle;
}

void DemoGps::StopCircle(void) {
    circle->FinishTraj();
    //GetJoystick()->Rumble(0x70);
    Thread::Info("DemoGps: finishing circle\n");
}

void DemoGps::GpsPositionHold(void) {


//tood set yawHold and posHold


    uX->Reset();
    uY->Reset();
    behaviourMode=BehaviourMode_t::PositionHold;
    SetOrientationMode(OrientationMode_t::Custom);
    Thread::Info("DemoGps: holding position\n");
}
