//  created:    2016/06/01
//  filename:   main.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    exemple de code x4
//
//
/*********************************************************************/

#include "PidUav.h"
#include <UavFactory.h>
#include <FrameworkManager.h>
#include <stdio.h>
#include <tclap/CmdLine.h>
#include <TargetEthController.h>
#include <EmulatedController.h>

using namespace TCLAP;
using namespace std;
using namespace flair::core;
using namespace flair::meta;
using namespace flair::sensor;

string uav_type;
string dsp_file;
string log_path;
bool headless;
int port;
string xml_file;
string name;
string address;

void parseOptions(int argc, char **argv);

int main(int argc, char *argv[]) {
  parseOptions(argc, argv);

  FrameworkManager *manager;
  manager = new FrameworkManager(name);
  if (!headless) {
    manager->SetupConnection(address, port);
  }
  manager->SetupUserInterface(xml_file);
  manager->SetupLogger(log_path);

  Uav *drone = CreateUav(manager, name, uav_type);
  TargetEthController *controller =
      new TargetEthController(manager, "Dualshock3", 20000);
  // EmulatedController *controller=new EmulatedController(manager,"Emulated
  // Controller");
  //    controller->AddStep(10000,"Waiting for AHRS
  //    stabilization",0,0.,0.,0.,0.);
  //    controller->AddStep(500,"Takeoff",(uint16_t)EmulatedController::ButtonType::start,0.,0.,0.,0.);
  //    controller->AddStep(3000,"Waiting for flight
  //    stabilization",0,0.,0.,0.,0.);
  /*    controller->AddStep(2000,"fly left",0,-0.3,0.,0.,0.);
      controller->AddStep(1000,"fly right",0,0.3,0.,0.,0.);*/
  //    controller->AddStep(500,"Land",(uint16_t)EmulatedController::ButtonType::start,0.,0.,0.,0.);
  //    controller->AddStep(3000,"Waiting for landing",0,0.,0.,0.,0.);
  //    controller->AddStep(500,"Stop",(uint16_t)EmulatedController::ButtonType::select,0.,0.,0.,0.);
  PidUav *app = new PidUav(drone, controller);

  app->Start();
  app->Join();

  delete manager;
}

void parseOptions(int argc, char **argv) {
  try {

    CmdLine cmd("Command description message", ' ', "0.1");

    ValueArg<string> nameArg("n", "name", "uav name", true, "x4", "string");
    cmd.add(nameArg);

    ValueArg<string> typeArg(
        "t", "type", "uav type: ardrone2, hds_x4, hds_x8, hds_xufo, hds_simu "
                     "or hds_simux (with x the number of the simulated uav)",
        true, "hds_x4", "string");
    cmd.add(typeArg);

    ValueArg<string> xmlArg("x", "xml", "fichier xml", true, "./reglages.xml",
                            "string");
    cmd.add(xmlArg);

    ValueArg<string> logsArg("l", "logs", "repertoire des logs", true,
                             "/media/ram", "string");
    cmd.add(logsArg);

    ValueArg<int> portArg("p", "port", "port pour station sol", true, 9000,
                          "int");
    cmd.add(portArg);

    ValueArg<string> addressArg("a", "address", "addresse station sol", true,
                                "127.0.0.1", "string");
    cmd.add(addressArg);

    SwitchArg headlessArg("e", "headless", "headless mode", false);
    cmd.add(headlessArg);

    cmd.parse(argc, argv);

    // Get the value parsed by each arg.
    uav_type = typeArg.getValue();
    log_path = logsArg.getValue();
    port = portArg.getValue();
    xml_file = xmlArg.getValue();
    name = nameArg.getValue();
    address = addressArg.getValue();
    headless = headlessArg.getValue();

  } catch (ArgException &e) // catch any exceptions
  {
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
}
