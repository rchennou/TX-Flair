//  created:    2015/10/27
//  filename:   MyApp.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    skeleton to use UavStateMachine with custom reference angles only
//
//
/*********************************************************************/

//include files, add yours
#include "MyApp.h"
#include <GridLayout.h>
#include <PushButton.h>
#include <MetaDualShock3.h>
#include <FrameworkManager.h>
#include <AhrsData.h>
#include <Ahrs.h>
#include <Uav.h>

//namespaces, add others if necessary (filter, sensor, actuator)
using namespace std;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::meta;
using namespace flair::sensor;

MyApp::MyApp(Uav* uav,TargetController *controller): UavStateMachine(uav,controller), behaviourMode(BehaviourMode_t::Default) {
    start_CustomAngles=new PushButton(GetButtonsLayout()->NewRow(),"start CustomReferenceAngles");
    stop_CustomAngles=new PushButton(GetButtonsLayout()->NewRow(),"stop CustomReferenceAngles");

    customReferenceOrientation= new AhrsData(this,"reference");
    uav->GetAhrs()->AddPlot(customReferenceOrientation,DataPlot::Yellow);
    AddDataToControlLawLog(customReferenceOrientation);
}

MyApp::~MyApp() {
}

//this method is called by UavStateMachine::Run (main loop) when OrientationMode is Custom
AhrsData *MyApp::GetReferenceOrientation(void) {
    //compute the reference angles (for example depending on a position error)
    //reference angular speed is set to 0

    Euler refAngles;
    //refAngles.roll=;
    //refAngles.pitch=;
    //refAngles.yaw=;

    customReferenceOrientation->SetQuaternionAndAngularRates(refAngles.ToQuaternion(),Vector3D(0,0,0));

    return customReferenceOrientation;
}

void MyApp::SignalEvent(Event_t event) {
    UavStateMachine::SignalEvent(event);
    switch(event) {
    case Event_t::TakingOff:
        //always take off in default mode
        behaviourMode=BehaviourMode_t::Default;
        break;
    case Event_t::EnteringFailSafeMode:
        //return to default mode
        Thread::Info("CustomReferenceAngles: stop\n");
        behaviourMode=BehaviourMode_t::Default;
        break;
    }
}

void MyApp::ExtraCheckPushButton(void) {
    if(start_CustomAngles->Clicked() && (behaviourMode!=BehaviourMode_t::CustomReferenceAngles)) {
        StartCustomAngles();
    }

    if(stop_CustomAngles->Clicked() && (behaviourMode==BehaviourMode_t::CustomReferenceAngles)) {
        StopCustomAngles();
    }
}

void MyApp::ExtraCheckJoystick(void) {
    //R1
    if(GetJoystick()->IsButtonPressed(9) && (behaviourMode!=BehaviourMode_t::CustomReferenceAngles)) {
        StartCustomAngles();
    }

    //stop is not managed here, it is done in UavStateMachine with cross button
    //pushing cross button will enter fail safe mode and signal the EnteringFailSafeMode event
}

void MyApp::StartCustomAngles(void) {
    //ask UavStateMachine to enter in custom orientation mode
    if (SetOrientationMode(OrientationMode_t::Custom)) {
        Thread::Info("CustomReferenceAngles: start\n");
    } else {
        Thread::Warn("CustomReferenceAngles: could not start\n");
        return;
    }

    behaviourMode=BehaviourMode_t::CustomReferenceAngles;
}

void MyApp::StopCustomAngles(void) {
    //just ask to enter fail safe mode
    EnterFailSafeMode();
}
