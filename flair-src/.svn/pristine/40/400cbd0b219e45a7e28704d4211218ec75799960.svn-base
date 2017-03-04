// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/02
//  filename:   GuiFlair.cpp
//
//  authors:    Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Implementation of GuiInterface using Flair
//  			communication mechanism
//
//
/*********************************************************************/

#include "GuiFlair.h"
#include "GuiInterface.h"

#include <FrameworkManager.h>
#include <Socket.h>

//todo remove for tests
#include <iostream>


using namespace std;
using namespace flair::core;
using namespace flair::gui;

GuiFlair::GuiFlair(const FrameworkManager *parent, string name):
				   GuiInterface(parent, name) {
	cout << "MavPlanner GuiFlair constructor" << endl;

	outputSocket = new Socket((Thread *)this, "output socket", "127.0.0.1:5036");

	// outputSocket = new Socket(parent, "output socket", "127.255.255.255:9001", true);
	inputSocket = new Socket((Thread *)this, "input socket", 9001);
}

GuiFlair::~GuiFlair() {

}

void GuiFlair::MissionStart() {
	cout << "MavPlanner GuiFlair MissionStart" << endl;

	int received = 0;
	char receiveFrameBuffer[200];

	std::string message_to_send("Test of sending a message");

	//fonctionne en récéption si on prend un broadcast pour la création du socket
	// outputSocket->SendMessage(message_to_send);

	do {
		// cout << "." << endl;
		received=inputSocket->RecvMessage(receiveFrameBuffer,200, TIME_NONBLOCK);
		// cout << "." << endl;
		if (received > 0) {
		   cout << "MavPlanner GuiFlair MissionStart data received : " << receiveFrameBuffer << endl;
		   outputSocket->SendMessage(receiveFrameBuffer, received);
		}
	} while (received != 0);
}

void GuiFlair::MissionStop() {
	cout << "MavPlanner GuiFlair MissionStop" << endl;
}

void GuiFlair::MissionPause() {
	cout << "MavPlanner GuiFlair MissionResume" << endl;
}

void GuiFlair::MissionSend() {
	cout << "MavPlanner GuiFlair MissionSend" << endl;
}
