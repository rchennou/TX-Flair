// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/07/05
//  filename:   main.cpp
//
//  author:     Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    main for the mavlink controller
//
//
/*********************************************************************/

#include "FrameworkManager.h"
#include <stdio.h>
#include <tclap/CmdLine.h>

#include "GuiFlair.h"
#include "GuiGcs.h"
#include "Forwarder.h"

//todo remove for tests
#include <iostream>

using namespace TCLAP;
using namespace std;
using namespace flair::core;

string xmlFile;
string mode;
string inputAddress;
int inputPort;
string outputAddress;
int outputPort;
string flairAddress;
int flairPort;

void parseOptions(int argc, char **argv);

int main(int argc, char *argv[]) {
  std::cout << "avant parseOptions" << std::endl;
  parseOptions(argc, argv);

  std::cout << "parseOptions ok" << std::endl;

  FrameworkManager *manager;
  manager = new FrameworkManager("MavPlanner");
  manager->SetupConnection(flairAddress, flairPort);
  manager->SetupUserInterface(xmlFile);

  std::cout << "MavPlanner mode : " << mode << std::endl;

  if(mode == "forward") {
    Forwarder *guiForwarder = new Forwarder(manager, "Forwarder",
                                           inputAddress, inputPort,
                                           outputAddress, outputPort);
    if (!manager->ErrorOccured()) {
      guiForwarder->Start();
      guiForwarder->Join();
    }
  } else {
    GuiInterface *guiHandler;
    if(mode == "flair") {
      guiHandler = new GuiFlair(manager, "GuiFlair");
    } else if (mode == "gcs") {
      guiHandler = new GuiGcs(manager, "GuiGcs", outputAddress, outputPort);
    } else {
      //ERROR
    }
    if (!manager->ErrorOccured()) {
      guiHandler->Start();
      guiHandler->Join();
    }
  }

  delete manager;
}

void parseOptions(int argc, char **argv) {
  try {
    CmdLine cmd("Command description message", ' ', "0.1");

    ValueArg<string> inputAddressArg("", "inputAddress",
                                "input IP address", false,
                                "127.0.0.1", "string");
    cmd.add(inputAddressArg);

    ValueArg<int> inputPortArg("", "inputPort",
                          "input IP port", false,
                          9000, "int");
    cmd.add(inputPortArg);

    ValueArg<string> outputAddressArg("", "outputAddress",
                                      "output IP address", false,
                                      "127.0.0.1", "string");
    cmd.add(outputAddressArg);

    ValueArg<int> outputPortArg("", "outputPort",
                               "output IP port", false,
                               9000, "int");
    cmd.add(outputPortArg);

    ValueArg<string> flairAddressArg("a", "flairAddress",
                                      "flair IP address", true,
                                      "127.0.0.1", "string");
    cmd.add(flairAddressArg);

    ValueArg<int> flairPortArg("p", "flairPort",
                               "flair IP port", true,
                               9000, "int");
    cmd.add(flairPortArg);

    ValueArg<string> xmlArg("x", "xml", "xml file", true, "./settings.xml",
                            "string");
    cmd.add(xmlArg);

    ValueArg<string> modeArg("m", "mode", "application mode (forward, flair, gcs)",
                             true, "flair", "string");
    cmd.add(modeArg);

    cmd.parse(argc, argv);

    // string receiverAddressWithPort = inputAddressArg.getValue();
    // int semiColonPosition = receiverAddressWithPort.find(":");
    // receiverAddress = receiverAddressWithPort.substr(0, semiColonPosition);
    // receiverPort =
    //     atoi(receiverAddressWithPort.substr(semiColonPosition + 1).c_str());
    
    // Get the value parsed by each arg.
    inputAddress = inputAddressArg.getValue();
    inputPort = inputPortArg.getValue();
    outputAddress = outputAddressArg.getValue();
    outputPort = outputPortArg.getValue();
    flairAddress = flairAddressArg.getValue();
    flairPort = flairPortArg.getValue();
    xmlFile = xmlArg.getValue();
    mode = modeArg.getValue();

  } catch (ArgException &e) { // catch any exceptions
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
}
