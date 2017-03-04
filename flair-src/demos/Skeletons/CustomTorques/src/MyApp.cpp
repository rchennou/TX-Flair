//  created:    2015/10/29
//  filename:   Uav.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    skeleton to use UavStateMachine with custom torques only
//
//
/*********************************************************************/

//include files, add yours
#include "MyApp.h"
#include <GridLayout.h>
#include <PushButton.h>
#include <MetaDualShock3.h>
#include <FrameworkManager.h>

//namespaces, add others if necessary (filter, sensor, actuator)
using namespace std;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::meta;
using namespace flair::sensor;

MyApp::MyApp(Uav* uav,TargetController *controller): UavStateMachine(uav,controller), behaviourMode(BehaviourMode_t::Default) {
    start_CustomTorques=new PushButton(GetButtonsLayout()->NewRow(),"start CustomTorques");
    stop_CustomTorques=new PushButton(GetButtonsLayout()->NewRow(),"stop CustomTorques");
}

MyApp::~MyApp() {
}

//this method is called by UavStateMachine::Run (main loop) when TorqueMode is Custom
void MyApp::ComputeCustomTorques(Euler &torques) {
    //compute the torques, with your own control laws

    //torques.roll=;
    //torques.pitch=;
    //torques.yaw=;
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
        Thread::Info("CustomTorques: stop\n");
        behaviourMode=BehaviourMode_t::Default;
        break;
    }
}

void MyApp::ExtraCheckPushButton(void) {
    if(start_CustomTorques->Clicked() && (behaviourMode!=BehaviourMode_t::CustomTorques)) {
        StartCustomTorques();
    }

    if(stop_CustomTorques->Clicked() && (behaviourMode==BehaviourMode_t::CustomTorques)) {
        StopCustomTorques();
    }
}

void MyApp::ExtraCheckJoystick(void) {
    //R1
    if(GetJoystick()->IsButtonPressed(9) && (behaviourMode!=BehaviourMode_t::CustomTorques)) {
        StartCustomTorques();
    }

    //stop is not managed here, it is done in UavStateMachine with cross button
    //pushing cross button will enter fail safe mode and signal the EnteringFailSafeMode event
}

void MyApp::StartCustomTorques(void) {
    //ask UavStateMachine to enter in custom torques
    if (SetTorqueMode(TorqueMode_t::Custom)) {
        Thread::Info("CustomTorques: start\n");
    } else {
        Thread::Warn("CustomTorques: could not start\n");
        return;
    }

    behaviourMode=BehaviourMode_t::CustomTorques;
}

void MyApp::StopCustomTorques(void) {
    //just ask to enter fail safe mode
    EnterFailSafeMode();
}
