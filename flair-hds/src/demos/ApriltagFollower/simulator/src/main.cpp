//  created:    2017/02/10
//  filename:   main.cpp
//
//  author:     Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    main simulateur
//
//
/*********************************************************************/

#include <tclap/CmdLine.h>
#include <Simulator.h>
#include "X4WithTag.h"
#include <X4.h>
#include <SimuImu.h>
#include <SimuCameraGL.h>
#include <Parser.h>
#include <SimuUsGL.h>

using namespace TCLAP;
using namespace std;
using namespace flair::simulator;
using namespace flair::sensor;

int port;
int opti_time;
string xml_file;
string media_path;
string scene_file;
string address;

void createUavWithTag(uint32_t modelId);
void createUavFollowingTheTag(uint32_t modelId);

void parseOptions(int argc, char** argv) {
  try {
    CmdLine cmd("Command description message", ' ', "0.1");

    ValueArg<string> xmlArg("x", "xml", "xml file", true, "./reglages.xml", "string");
    cmd.add(xmlArg);

    ValueArg<int> portArg("p", "port", "ground station port", true, 9002, "int");
    cmd.add(portArg);

    ValueArg<string> addressArg("a", "address", "ground station address", true, "127.0.0.1", "string");
    cmd.add(addressArg);

    ValueArg<int> optiArg("o", "opti", "optitrack time ms", false, 0, "int");
    cmd.add(optiArg);

    ValueArg<string> mediaArg("m", "media", "path to media files", true, "./", "string");
    cmd.add(mediaArg);

    ValueArg<string> sceneArg("s", "scene", "path to scene file", true, "./voliere.xml", "string");
    cmd.add(sceneArg);

    cmd.parse(argc, argv);

    // Get the value parsed by each arg.
    port = portArg.getValue();
    xml_file = xmlArg.getValue();
    opti_time = optiArg.getValue();
    address = addressArg.getValue();
    media_path = mediaArg.getValue();
    scene_file = sceneArg.getValue();
  } catch(ArgException& e) // catch any exceptions
  {
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
}

int main(int argc, char* argv[]) {
  parseOptions(argc, argv);

  Simulator* simu = new Simulator("simulator", opti_time, 90);
  simu->SetupConnection(address, port);
  simu->SetupUserInterface(xml_file);

  Parser* gui = new Parser(1200, 660, 880, 660, media_path, scene_file);

  createUavWithTag(0);
  createUavFollowingTheTag(1);

  simu->RunSimu();

  delete simu;

  return 0;
}

void createUavWithTag(uint32_t modelId) {
  Model* uav = new X4WithTag("UavWithTag", modelId);
  SimuImu* imu = new SimuImu(uav, "imu", modelId, 0);
  SimuUsGL* us_gl = new SimuUsGL(uav, "us", modelId, 0);
  SimuCameraGL* cam_bas = new SimuCameraGL(uav, "bottom camera", 320, 240, 880, 0, modelId, 0);
}

void createUavFollowingTheTag(uint32_t modelId) {
  Model* uav = new X4("UavFollowingTheTag", modelId);
  SimuImu* imu = new SimuImu(uav, "imu", modelId, 0);
  SimuUsGL* us_gl = new SimuUsGL(uav, "us", modelId, 0);
  SimuCameraGL* cam_bas = new SimuCameraGL(uav, "bottom camera", 320, 240, 880, 240, modelId, 0);
  SimuCameraGL* cam_hor = new SimuCameraGL(uav, "horizontal camera", 320, 180, 880, 480, modelId, 1);
}