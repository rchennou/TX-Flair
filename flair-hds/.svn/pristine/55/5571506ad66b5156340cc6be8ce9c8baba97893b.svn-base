//  created:    2017/02/02
//  filename:   Streaming.cpp
//
//  author:     Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    streams data and receives computed information
//
//
/*********************************************************************/

#include "Streaming.h"

#include <Uav.h>
#include <Camera.h>
#include <CvtColor.h>
#include <GridLayout.h>
#include <Label.h>
#include <Tab.h>
#include <GroupBox.h>
#include <DataPlot1D.h>
#include <FrameworkManager.h>
#include <cvmatrix.h>
#include <Euler.h>
#include <Mutex.h>
#include <TcpSocket.h>
#include <OneAxisRotation.h>

#include "StreamingFilter.h"

#include <cmath>

using namespace std;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;
using namespace flair::meta;
using namespace flair::sensor;

Streaming::Streaming(const std::string streamIp)
    : Thread(getFrameworkManager(), "Streaming", 6)
    , IODevice(getFrameworkManager(), "StreamIO")
    , recvDataFlag(false) {
  Uav* uav = GetUav();
  if(uav->GetHorizontalCamera() == NULL) {
    Printf("Exiting because no horizontal camera has been found...\n");
    exit(1);
  }

  // Build GUI in a new Tab
  Tab* mainTab = new Tab(getFrameworkManager()->GetTabWidget(), "Streaming");
  fps = new Label(mainTab->NewRow(), "fps");
  rotation_1 = new OneAxisRotation(mainTab->NewRow(), "post rotation 1");
  rotation_2 = new OneAxisRotation(mainTab->NewRow(), "post rotation 2");
  graphGroupBox = new GroupBox(mainTab->NewRow(), "Graphs");

  // Descriptor for plotting data
  cvmatrix_descriptor* desc = new cvmatrix_descriptor(3, 1);
  desc->SetElementName(0, 0, "x_tag");
  desc->SetElementName(1, 0, "y_tag");
  desc->SetElementName(2, 0, "yaw_tag");
  outputCvMatrix = new cvmatrix((IODevice*)this, desc, floatType);
  delete desc;

  cvmatrix_descriptor* descGraph = new cvmatrix_descriptor(6, 1);
  descGraph->SetElementName(0, 0, "x_tag");
  descGraph->SetElementName(1, 0, "y_tag");
  descGraph->SetElementName(2, 0, "z_tag");
  descGraph->SetElementName(3, 0, "roll_tag");
  descGraph->SetElementName(4, 0, "pitch_tag");
  descGraph->SetElementName(5, 0, "yaw_tag");
  graphCvMatrix = new cvmatrix((IODevice*)this, descGraph, floatType);
  delete descGraph;

  cvmatrix_descriptor* descLog = new cvmatrix_descriptor(7, 1);
  descLog->SetElementName(0, 0, "x");
  descLog->SetElementName(1, 0, "y");
  descLog->SetElementName(2, 0, "z");
  descLog->SetElementName(3, 0, "q1");
  descLog->SetElementName(4, 0, "q2");
  descLog->SetElementName(5, 0, "q3");
  descLog->SetElementName(6, 0, "q4");
  savingMatrix = new cvmatrix((IODevice*)this, descLog, floatType);
  delete descLog;
  AddDataToLog(savingMatrix);

  // Create the GUi for plotting data
  DataPlot1D* roll_plot = new DataPlot1D(graphGroupBox->NewRow(), "roll", -180, 180);
  DataPlot1D* pitch_plot = new DataPlot1D(graphGroupBox->LastRowLastCol(), "pitch", -180, 180);
  DataPlot1D* yaw_plot = new DataPlot1D(graphGroupBox->LastRowLastCol(), "yaw", -60, 60);
  DataPlot1D* x_plot = new DataPlot1D(graphGroupBox->NewRow(), "x", -1, 1);
  DataPlot1D* y_plot = new DataPlot1D(graphGroupBox->LastRowLastCol(), "y", -1, 1);
  DataPlot1D* z_plot = new DataPlot1D(graphGroupBox->LastRowLastCol(), "z", 0, 2);

  // Add received data
  x_plot->AddCurve(graphCvMatrix->Element(0));
  y_plot->AddCurve(graphCvMatrix->Element(1));
  z_plot->AddCurve(graphCvMatrix->Element(2));
  roll_plot->AddCurve(graphCvMatrix->Element(3));
  pitch_plot->AddCurve(graphCvMatrix->Element(4));
  yaw_plot->AddCurve(graphCvMatrix->Element(5));

  // Init variables
  isTagDetected = false;

  // Mutex to protect the access of the received data
  recvDataMutex = new Mutex(static_cast<Thread*>(this), "recvDataMutex");
  // Create filters, first convert image in gray and then send it over socket
  greyCameraImage = new CvtColor(uav->GetHorizontalCamera(), "gray", CvtColor::Conversion_t::ToGray);
#ifdef REAL
  streamingCameraImage = new StreamingFilter(greyCameraImage, "stream", streamIp, 5000);
#endif
// Create the socket to send processed data
#ifdef SIMU
  receivingSocket = new TcpSocket(getFrameworkManager(), "RcvSkt", false, true);
  if(!receivingSocket->Connect(5001, streamIp)) {
    Thread::Err("receivingSocket connect failed\n");
  }
#endif
  // Add the plot of camera picture
  uav->GetHorizontalCamera()->UseDefaultPlot(greyCameraImage->Output());
}

Streaming::~Streaming() {
}

bool Streaming::GetComputedData(Vector3Df& position, Euler& rotation, bool& detection) {
  bool toReturn;
  recvDataMutex->GetMutex();
  toReturn = recvDataFlag;
  position = recvPosition;
  rotation = recvQuaternion.ToEuler();
  detection = isTagDetected;
  recvDataFlag = false;
  recvDataMutex->ReleaseMutex();
  return toReturn;
}

void Streaming::Run() {
  if(getFrameworkManager()->ErrorOccured()) {
    SafeStop();
    Thread::Err("An error occurred, we don't launch the Run loop.\n");
  }
  long bytesReceived;
  tagData receivedData;
  Time fpsNow, fpsPrev;
  int fpsCounter = 0;
  start = std::chrono::system_clock::now();
  fpsPrev = GetTime();
  Euler recvEuler;
  float prevYaw=0;
  while(!ToBeStopped()) {
    if((bytesReceived = receivingSocket->RecvMessage((char*)&receivedData, sizeof(tagData))) == -1) {
      Thread::Err("RecvMessage failed, received bytes = %d\n", bytesReceived);
    } else {
      end = std::chrono::system_clock::now();
      elapsedSeconds = end - start;
      // Fps counter
      // todo more accurate fps counter ?
      fpsCounter++;
      if(fpsCounter == 10) {
        fpsNow = GetTime();
        fps->SetText("fps: %.1f", fpsCounter / ((float)(fpsNow - fpsPrev) / 1000000000.));
        fpsCounter = 0;
        fpsPrev = fpsNow;
      }
      recvDataMutex->GetMutex();
      recvDataFlag = true;
      isTagDetected = receivedData.nbDetect > 0;
      recvQuaternion = Quaternion(receivedData.q0, receivedData.q1, receivedData.q2, receivedData.q3);
      recvQuaternion.Normalize();
      recvPosition = Vector3Df(receivedData.x, receivedData.y, receivedData.z);
      ComputeRotations(recvQuaternion);
      ComputeRotations(recvPosition);
      recvDataMutex->ReleaseMutex();

      recvEuler = recvQuaternion.ToEuler();

      // Update the data from the camera frame to the uav frame
      outputCvMatrix->GetMutex();
      outputCvMatrix->SetValueNoMutex(0, 0, recvPosition.x);
      outputCvMatrix->SetValueNoMutex(1, 0, recvPosition.y);
      //hack to get yaw derivative
      if(recvEuler.yaw-prevYaw>CV_PI) recvEuler.yaw-=2*CV_PI;
      if(recvEuler.yaw-prevYaw<-CV_PI) recvEuler.yaw+=2*CV_PI;
      outputCvMatrix->SetValueNoMutex(2, 0, recvEuler.yaw);
      prevYaw=recvEuler.yaw;
      outputCvMatrix->ReleaseMutex();
      // for graph in degree
      graphCvMatrix->GetMutex();
      graphCvMatrix->SetValueNoMutex(0, 0, recvPosition.x);
      graphCvMatrix->SetValueNoMutex(1, 0, recvPosition.y);
      graphCvMatrix->SetValueNoMutex(2, 0, recvPosition.z);
      graphCvMatrix->SetValueNoMutex(3, 0, Euler::ToDegree(recvEuler.roll));
      graphCvMatrix->SetValueNoMutex(4, 0, Euler::ToDegree(recvEuler.pitch));
      graphCvMatrix->SetValueNoMutex(5, 0, Euler::ToDegree(recvEuler.yaw));
      graphCvMatrix->ReleaseMutex();
      // Save the data (log)
      savingMatrix->GetMutex();
      savingMatrix->SetValueNoMutex(0, 0, recvPosition.x);
      savingMatrix->SetValueNoMutex(1, 0, recvPosition.y);
      savingMatrix->SetValueNoMutex(2, 0, recvPosition.z);
      savingMatrix->SetValueNoMutex(3, 0, recvQuaternion.q0);
      savingMatrix->SetValueNoMutex(4, 0, recvQuaternion.q1);
      savingMatrix->SetValueNoMutex(5, 0, recvQuaternion.q2);
      savingMatrix->SetValueNoMutex(6, 0, recvQuaternion.q3);
      savingMatrix->ReleaseMutex();
      savingMatrix->SetDataTime(receivedData.time);

      start = std::chrono::system_clock::now();
      if(isTagDetected) {
        // Thread::Info("Tag detected, %f, %lld\n", recvPosition.z, GetTime());
        outputCvMatrix->SetDataTime(receivedData.time);
        ProcessUpdate(outputCvMatrix);
      }
    }
  }
}

// nothing because Streaming has no IO parent
void Streaming::UpdateFrom(const io_data* data) {
}

void Streaming::ComputeRotations(Vector3Df& point) {
  rotation_1->ComputeRotation(point);
  rotation_2->ComputeRotation(point);
}

void Streaming::ComputeRotations(Quaternion& quat) {
  rotation_1->ComputeRotation(quat);
  rotation_2->ComputeRotation(quat);
}