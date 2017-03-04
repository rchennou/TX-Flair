// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/10/20
//  filename:   main.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: $
//
//  purpose:    main dual shock 3
//
//
/*********************************************************************/

#include "FrameworkManager.h"
#include "DualShock3.h"
#include <stdio.h>
#include <tclap/CmdLine.h>

using namespace TCLAP;
using namespace std;
using namespace flair::core;
using namespace flair::sensor;

string receiverAddress;
int receiverPort;
string connection;
int port;
uint32_t period;
string xml_file;

void parseOptions(int argc, char **argv);

int main(int argc, char *argv[]) {
  parseOptions(argc, argv);

  DualShock3 *joystick;
  FrameworkManager *manager;

  manager = new FrameworkManager("dualshock3");
  manager->SetupConnection("127.0.0.1", port);
  manager->SetupUserInterface(xml_file);

  if (connection == "usb") {
    //        manager->Warn("!! adresse = %s !!\n", address.c_str());
    joystick = new DualShock3(manager, "dualshock3", receiverAddress,
                              receiverPort, DualShock3::Usb, period, 6);
  } else {
    joystick = new DualShock3(manager, "dualshock3", receiverAddress,
                              receiverPort, DualShock3::Bluetooth, period, 6);
  }

  joystick->DrawUserInterface();

  if (!manager->ErrorOccured()) {
    joystick->Start();
    joystick->Join();
  }

  delete manager;
}

void parseOptions(int argc, char **argv) {
  try {
    CmdLine cmd("Command description message", ' ', "0.1");

    ValueArg<string> addressArg("a", "address",
                                "data receiver address (ex: uav)", true,
                                "127.0.0.1:20000", "string");
    cmd.add(addressArg);

    ValueArg<string> connectionArg("c", "connection",
                                   "connection type (usb or bluetooth)", false,
                                   "bluetooth", "string");
    cmd.add(connectionArg);

    ValueArg<int> portArg("p", "port",
                          "local port used to connect to the ground station",
                          false, 9000, "int");
    cmd.add(portArg);

    ValueArg<int> periodArg("t", "period", "sending data period", false, 10,
                            "int");
    cmd.add(periodArg);

    ValueArg<string> xmlArg("x", "xml", "xml file", true, "./settings.xml",
                            "string");
    cmd.add(xmlArg);

    cmd.parse(argc, argv);

    // Get the value parsed by each arg.
    string receiverAddressWithPort = addressArg.getValue();
    int semiColonPosition = receiverAddressWithPort.find(":");
    receiverAddress = receiverAddressWithPort.substr(0, semiColonPosition);
    receiverPort =
        atoi(receiverAddressWithPort.substr(semiColonPosition + 1).c_str());
    connection = connectionArg.getValue();
    port = portArg.getValue();
    period = periodArg.getValue();
    xml_file = xmlArg.getValue();

  } catch (ArgException &e) { // catch any exceptions
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
}
