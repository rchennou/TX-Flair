//  created:    2011/05/01
//  filename:   SquareFollower.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    demo cercle avec optitrack
//
//
/*********************************************************************/

#include "SquareFollower.h"
#include <TargetController.h>
#include <Uav.h>
#include <GridLayout.h>
#include <PushButton.h>
#include <DataPlot1D.h>
#include <DataPlot2D.h>
#include <MetaDualShock3.h>
#include <FrameworkManager.h>
#include <VrpnClient.h>
#include <MetaVrpnObject.h>
#include <TrajectoryGenerator2DSquare.h>
#include <cvmatrix.h>
#include <cmath>
#include <Tab.h>
#include <Pid.h>
#include <Ahrs.h>
#include <AhrsData.h>

using namespace std;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;
using namespace flair::filter;
using namespace flair::meta;

SquareFollower::SquareFollower(Uav* uav,TargetController *controller): UavStateMachine(uav,controller), behaviourMode(BehaviourMode_t::Default), vrpnLost(false) {

    uav->SetupVRPNAutoIP(uav->ObjectName());

    startSquare=new PushButton(GetButtonsLayout()->NewRow(),"start_square");
    stopSquare=new PushButton(GetButtonsLayout()->LastRowLastCol(),"stop_square");

    if(uav->GetVrpnClient()->UseXbee()==true) {
        targetVrpn=new MetaVrpnObject(uav->GetVrpnClient(),"target",1);
    } else {
        targetVrpn=new MetaVrpnObject(uav->GetVrpnClient(),"target");
    }

    getFrameworkManager()->AddDeviceToLog(targetVrpn);

    square=new TrajectoryGenerator2DSquare(uav->GetVrpnClient()->GetLayout()->NewRow(),"square");
    uav->GetVrpnObject()->xPlot()->AddCurve(square->Matrix()->Element(0,0),DataPlot::Blue);
    uav->GetVrpnObject()->yPlot()->AddCurve(square->Matrix()->Element(0,1),DataPlot::Blue);
    uav->GetVrpnObject()->VxPlot()->AddCurve(square->Matrix()->Element(1,0),DataPlot::Blue);
    uav->GetVrpnObject()->VyPlot()->AddCurve(square->Matrix()->Element(1,1),DataPlot::Blue);
    uav->GetVrpnObject()->XyPlot()->AddCurve(square->Matrix()->Element(0,1),square->Matrix()->Element(0,0),DataPlot::Blue,"square");

    uX=new Pid(setupLawTab->At(1,0),"u_x");
    uX->UseDefaultPlot(graphLawTab->NewRow());
    uY=new Pid(setupLawTab->At(1,1),"u_y");
    uY->UseDefaultPlot(graphLawTab->LastRowLastCol());

    customReferenceOrientation= new AhrsData(this,"reference");
    uav->GetAhrs()->AddPlot(customReferenceOrientation,DataPlot::Yellow);
    AddDataToControlLawLog(customReferenceOrientation);

    customOrientation=new AhrsData(this,"orientation");
}

SquareFollower::~SquareFollower() {
}

const AhrsData *SquareFollower::GetOrientation(void) const {
    //get yaw from vrpn
    Euler vrpnEuler;
    GetUav()->GetVrpnObject()->GetEuler(vrpnEuler);

    //get roll, pitch and w from imu
    Quaternion ahrsQuaternion;
    Vector3D ahrsAngularSpeed;
    GetDefaultOrientation()->GetQuaternionAndAngularRates(ahrsQuaternion, ahrsAngularSpeed);

    Euler ahrsEuler=ahrsQuaternion.ToEuler();
    ahrsEuler.yaw=vrpnEuler.yaw;
    Quaternion mixQuaternion=ahrsEuler.ToQuaternion();

    customOrientation->SetQuaternionAndAngularRates(mixQuaternion,ahrsAngularSpeed);

    return customOrientation;
}

void SquareFollower::AltitudeValues(float &z,float &dz) {
    Vector3D uav_pos,uav_vel;

    GetUav()->GetVrpnObject()->GetPosition(uav_pos);
    GetUav()->GetVrpnObject()->GetSpeed(uav_vel);
    //z and dz must be in uav's frame
    z=-uav_pos.z;
    dz=-uav_vel.z;
}

AhrsData *SquareFollower::GetReferenceOrientation(void) {
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

void SquareFollower::PositionValues(Vector2D &pos_error,Vector2D &vel_error,float &yaw_ref) {
    Vector3D uav_pos,uav_vel; // in VRPN coordinate system
    Vector2D uav_2Dpos,uav_2Dvel; // in VRPN coordinate system

    GetUav()->GetVrpnObject()->GetPosition(uav_pos);
    GetUav()->GetVrpnObject()->GetSpeed(uav_vel);

    uav_pos.To2Dxy(uav_2Dpos);
    uav_vel.To2Dxy(uav_2Dvel);

    if (behaviourMode==BehaviourMode_t::PositionHold) {
        pos_error=uav_2Dpos-posHold;
        vel_error=uav_2Dvel;
        yaw_ref=yawHold;
    } else { //square
        Vector3D target_pos;
        Vector2D square_pos,square_vel;
        Vector2D target_2Dpos;

        targetVrpn->GetPosition(target_pos);
        target_pos.To2Dxy(target_2Dpos);
        square->SetCenter(target_2Dpos);

        //square reference
        square->Update(GetTime());
        square->GetPosition(square_pos);
        square->GetSpeed(square_vel);

        //error in optitrack frame
        pos_error=uav_2Dpos-square_pos;
        vel_error=uav_2Dvel-square_vel;
        yaw_ref=atan2(target_pos.y-uav_pos.y,target_pos.x-uav_pos.x);
    }

    //error in uav frame
    Quaternion currentQuaternion=GetCurrentQuaternion();
    Euler currentAngles;//in vrpn frame
    currentQuaternion.ToEuler(currentAngles);
    pos_error.Rotate(-currentAngles.yaw);
    vel_error.Rotate(-currentAngles.yaw);
}

void SquareFollower::SignalEvent(Event_t event) {
    UavStateMachine::SignalEvent(event);
    switch(event) {
    case Event_t::TakingOff:
        behaviourMode=BehaviourMode_t::Default;
        vrpnLost=false;
        break;
    case Event_t::EnteringControlLoop:
        if ((behaviourMode==BehaviourMode_t::Square) && (!square->IsRunning())) {
            VrpnPositionHold();
        }
        break;
    case Event_t::EnteringFailSafeMode:
        behaviourMode=BehaviourMode_t::Default;
        break;
    }
}

void SquareFollower::ExtraSecurityCheck(void) {
    if ((!vrpnLost) && ((behaviourMode==BehaviourMode_t::Square) || (behaviourMode==BehaviourMode_t::PositionHold))) {
        if (!targetVrpn->IsTracked(500)) {
            Thread::Err("VRPN, target lost\n");
            vrpnLost=true;
            EnterFailSafeMode();
            Land();
        }
        if (!GetUav()->GetVrpnObject()->IsTracked(500)) {
            Thread::Err("VRPN, uav lost\n");
            vrpnLost=true;
            EnterFailSafeMode();
            Land();
        }
    }
}

void SquareFollower::ExtraCheckPushButton(void) {
    if(startSquare->Clicked() && (behaviourMode!=BehaviourMode_t::Square)) {
        StartSquare();
    }
    if(stopSquare->Clicked() && (behaviourMode==BehaviourMode_t::Square)) {
        StopSquare();
    }
}

void SquareFollower::ExtraCheckJoystick(void) {
    //R1 and Square
    if(GetJoystick()->IsButtonPressed(9) && GetJoystick()->IsButtonPressed(4) && (behaviourMode!=BehaviourMode_t::Square)) {
        StartSquare();
    }

    //R1 and Cross
    if(GetJoystick()->IsButtonPressed(9) && GetJoystick()->IsButtonPressed(5) && (behaviourMode==BehaviourMode_t::Square)) {
        StopSquare();
    }
}

void SquareFollower::StartSquare(void) {
    if (SetOrientationMode(OrientationMode_t::Custom)) {
        Thread::Info("SquareFollower: start square\n");
    } else {
        Thread::Warn("SquareFollower: could not start square\n");
        return;
    }
    Vector3D uav_pos,target_pos;
    Vector2D uav_2Dpos,target_2Dpos;

    targetVrpn->GetPosition(target_pos);
    target_pos.To2Dxy(target_2Dpos);
    square->SetCenter(target_2Dpos);

    GetUav()->GetVrpnObject()->GetPosition(uav_pos);
    uav_pos.To2Dxy(uav_2Dpos);
    square->StartTraj(uav_2Dpos);

    uX->Reset();
    uY->Reset();
    behaviourMode=BehaviourMode_t::Square;
}

void SquareFollower::StopSquare(void) {
    square->StopTraj();
    //GetJoystick()->Rumble(0x70);
    Thread::Info("SquareFollower: finishing square\n");
}

void SquareFollower::VrpnPositionHold(void) {
    Euler vrpn_euler;
    Vector3D vrpn_pos;

    GetUav()->GetVrpnObject()->GetEuler(vrpn_euler);
    yawHold=vrpn_euler.yaw;

    GetUav()->GetVrpnObject()->GetPosition(vrpn_pos);
    vrpn_pos.To2Dxy(posHold);

    uX->Reset();
    uY->Reset();
    behaviourMode=BehaviourMode_t::PositionHold;
    SetOrientationMode(OrientationMode_t::Custom);
    Thread::Info("SquareFollower: holding position\n");
}
