//  created:    2015/03/30
//  filename:   EmulatedController.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class that emulate a remote control.
//              Typical use case: run a demo without any reliable communication channel
//
/*********************************************************************/
#include "EmulatedController.h"
#include <Controller.h>
#include <FrameworkManager.h>
#include <TcpSocket.h>
#include <Socket.h>
#include <cstring>
#include <string>
#include <cvmatrix.h>
#include <stdexcept>

#include <unistd.h> // for sleep (debug)

using namespace flair::core;
using namespace flair::gui;
using std::string;

namespace flair { namespace sensor {

EmulatedController::EmulatedController(const FrameworkManager* parent,string name,uint8_t priority) :
    TargetController(parent,name,priority) {
}

EmulatedController::~EmulatedController() {
    //TargetController calls TargetEthController methods in its run
    //we must stop the thread now
    SafeStop();
    Join();
}

bool EmulatedController::IsConnected() const {
    return true;
}

bool EmulatedController::IsDataFrameReady(){
    return true;
}

template<typename T> void EmulatedController::fillVectorNoMutex(cvmatrix &vector,T data[],unsigned int size) {
    for (unsigned int i=0; i<size; i++) {
        vector.SetValueNoMutex(i,0,data[i]);
    }
}

void EmulatedController::fillVectorNoMutex(cvmatrix &destination,cvmatrix &source,unsigned int size) {
    for (unsigned int i=0; i<size; i++) {
        destination.SetValueNoMutex(i,0,source.Value(i,0));
    }
}

void EmulatedController::StepData::Print() {
    Printf("<StepData %s, duration=%d, axisData={%f,%f,%f,%f}, buttonData={%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c} />\n",description.c_str(),durationMs,
      axisData->Value(0,0),axisData->Value(1,0),axisData->Value(2,0),axisData->Value(3,0),
      buttonData->Value(0,0)?'X':'-',buttonData->Value(1,0)?'X':'-',buttonData->Value(2,0)?'X':'-',buttonData->Value(3,0)?'X':'-',
      buttonData->Value(4,0)?'X':'-',buttonData->Value(5,0)?'X':'-',buttonData->Value(6,0)?'X':'-',buttonData->Value(7,0)?'X':'-',
      buttonData->Value(8,0)?'X':'-',buttonData->Value(9,0)?'X':'-',buttonData->Value(10,0)?'X':'-',buttonData->Value(11,0)?'X':'-',
      buttonData->Value(12,0)?'X':'-',buttonData->Value(13,0)?'X':'-',buttonData->Value(14,0)?'X':'-',buttonData->Value(15,0)?'X':'-'
    );
}

void EmulatedController::AddStep(unsigned int durationMs,string description,uint16_t buttonPressed, float leftAxisX, float leftAxisY, float rightAxisX, float rightAxisY) {
    cvmatrix *axisMatrix=new cvmatrix((IODevice *)this,4,1,floatType);
    axisMatrix->SetValueNoMutex(0,0,leftAxisX);
    axisMatrix->SetValueNoMutex(1,0,leftAxisY);
    axisMatrix->SetValueNoMutex(2,0,rightAxisX);
    axisMatrix->SetValueNoMutex(3,0,rightAxisY);

    cvmatrix *buttonMatrix=new cvmatrix((IODevice *)this,16,1,SignedIntegerType(8));
    if (buttonPressed&(uint16_t)ButtonType::start) buttonMatrix->SetValueNoMutex(0,0,1);
    if (buttonPressed&(uint16_t)ButtonType::select) buttonMatrix->SetValueNoMutex(1,0,1);
    if (buttonPressed&(uint16_t)ButtonType::square) buttonMatrix->SetValueNoMutex(2,0,1);
    if (buttonPressed&(uint16_t)ButtonType::triangle) buttonMatrix->SetValueNoMutex(3,0,1);
    if (buttonPressed&(uint16_t)ButtonType::circle) buttonMatrix->SetValueNoMutex(4,0,1);
    if (buttonPressed&(uint16_t)ButtonType::cross) buttonMatrix->SetValueNoMutex(5,0,1);
    if (buttonPressed&(uint16_t)ButtonType::left1) buttonMatrix->SetValueNoMutex(6,0,1);
    if (buttonPressed&(uint16_t)ButtonType::left2) buttonMatrix->SetValueNoMutex(7,0,1);
    if (buttonPressed&(uint16_t)ButtonType::left3) buttonMatrix->SetValueNoMutex(8,0,1);
    if (buttonPressed&(uint16_t)ButtonType::right1) buttonMatrix->SetValueNoMutex(9,0,1);
    if (buttonPressed&(uint16_t)ButtonType::right2) buttonMatrix->SetValueNoMutex(10,0,1);
    if (buttonPressed&(uint16_t)ButtonType::right3) buttonMatrix->SetValueNoMutex(11,0,1);
    if (buttonPressed&(uint16_t)ButtonType::up) buttonMatrix->SetValueNoMutex(12,0,1);
    if (buttonPressed&(uint16_t)ButtonType::down) buttonMatrix->SetValueNoMutex(13,0,1);
    if (buttonPressed&(uint16_t)ButtonType::left) buttonMatrix->SetValueNoMutex(14,0,1);
    if (buttonPressed&(uint16_t)ButtonType::right) buttonMatrix->SetValueNoMutex(15,0,1);

    StepData step={durationMs,axisMatrix,buttonMatrix,description};
    //step.Print();
    steps.push_back(step);
}

void EmulatedController::ComputeControllerData(DataType dataType, cvmatrix &data) {
    static Time startStepTime=GetTime();

    Time now=GetTime();

    axis->GetMutex();
    button->GetMutex();

    if (steps.empty()) {
        if (dataType==DataType::axis) {
            float values[]={0.,0.,0.,0.};
            fillVectorNoMutex(data,values,4);
        }
        if (dataType==DataType::button) {
            int values[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            fillVectorNoMutex(data,values,16);
        }
    } else {
        StepData currentStep=steps.front();
        if (dataType==DataType::axis) fillVectorNoMutex(data,*(currentStep.axisData),4);
        if (dataType==DataType::button) fillVectorNoMutex(data,*(currentStep.buttonData),16);
        if (now-startStepTime>(Time)currentStep.durationMs*1000*1000) {
            Thread::Info("Step '%s' done\n",currentStep.description.c_str());
            startStepTime=now;
            steps.pop_front();
        }
    }

    button->ReleaseMutex();
    axis->ReleaseMutex();
}

void EmulatedController::AcquireAxisData(core::cvmatrix &axis) {
    ComputeControllerData(DataType::axis,axis);
}

void EmulatedController::AcquireButtonData(core::cvmatrix &button) {
    ComputeControllerData(DataType::button,button);
}

bool EmulatedController::ProcessMessage(Message *msg) {
    return false;
}

bool EmulatedController::ControllerInitialization() {
    axisNumber=4;
    buttonNumber=16;
    return true;
}

} // end namespace sensor
} // end namespace flair
