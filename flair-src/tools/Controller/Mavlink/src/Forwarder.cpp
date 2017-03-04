// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/02
//  filename:   Forwarder.cpp
//
//  authors:    Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Forward input data to output data, using sockets
//
//
/*********************************************************************/

#include "Forwarder.h"

#include <Socket.h>
#include <Thread.h>
#include <FrameworkManager.h>

//todo remove for tests
#include <iostream>

using namespace std;
using namespace flair::core;

Forwarder::Forwarder(const FrameworkManager *parent, string name, string &inputAddress,
					 int inputPort, string &outputAddress, int outputPort):
					 Thread(parent, name, 6), inputAddress(inputAddress), 
					 inputPort(inputPort), outputAddress(outputAddress),
					 outputPort(outputPort) {
  cout << "MavPlanner Forwarder constructor" << endl;

  // string tmpOutput = outputAddress + ":" + to_string(outputPort);
  // cout << "MavPlanner Forwarder output address : " << tmpOutput << endl;

  // cout << "input socket : " << inputAddress + ":" + to_string(inputPort) << endl;
  // cout << "output socket : " << outputAddress + ":" + to_string(outputPort) << endl;

  inputSocket = new Socket((Thread *)this, "input socket", inputPort);
  outputSocket = new Socket((Thread *)this, "output socket", outputAddress + ":" + to_string(outputPort));
}

Forwarder::~Forwarder() {

}

void Forwarder::Run() {
  if (getFrameworkManager()->ErrorOccured()) {
    SafeStop();
    Thread::Err("An error occurred, we don't launch the Run loop.\n");
  }
  int recvDataSize = 0;
  char inputBuffer[200];
  while (!ToBeStopped()) {
    recvDataSize = inputSocket->RecvMessage(inputBuffer, 200, 1000000000);
	  outputSocket->SendMessage(inputBuffer, recvDataSize);
  }
}