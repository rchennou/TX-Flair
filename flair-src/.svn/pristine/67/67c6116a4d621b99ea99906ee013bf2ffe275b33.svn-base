//  created:    2013/06/26
//  filename:   main.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//
//
/*********************************************************************/

#include "Loop.h"
#include <FrameworkManager.h>
#include <tclap/CmdLine.h>
#include <stdio.h>

// we use namespace std, to avoid writing for examlpe std::string
using namespace std;
// idem for TCLAP
using namespace TCLAP;
// idem for flair
using namespace flair::core;

// global variables for the command line arguments
string logPath; // path for logs
string address; // address for FlairGCS
int port; // port for FlairGCS
string xmlFile; // setup xml file
string name; // name

void parseOptions(int argc, char **argv);

int main(int argc, char *argv[]) {
  // get command line arguments (name,port,xml_file,log_path)
  parseOptions(argc, argv);

  // creation of FrameworkManager
  FrameworkManager *manager;
  manager = new FrameworkManager(name);
  manager->SetupConnection(address, port);
  manager->SetupUserInterface(xmlFile);
  manager->SetupLogger(logPath);

  // creation of the
  Loop *example = new Loop(manager, "Loop");

  // start loop
  example->Start();

  // wait for loop ends (with kill button)
  example->Join();

  delete manager;
}

void parseOptions(int argc, char **argv) {
  try {
    CmdLine cmd("Command description message", ' ', "0.1");

    // name of the FrameworkManager, Sinus by default
    ValueArg<string> nameArg("n", "name", "program name", false, "Sinus",
                             "string");
    cmd.add(nameArg);

    // setup xml file, ./Sinus.xml by default
    ValueArg<string> xmlArg("x", "xml", "xml file", false, "./Sinus.xml",
                            "string");
    cmd.add(xmlArg);

    // log path, ./ by defaults
    ValueArg<string> logArg("l", "log", "log path", false, "/tmp", "string");
    cmd.add(logArg);

    // address for FlairGCS
    ValueArg<string> addressArg("a", "address",
                                "address for FlairGCS station sol", false,
                                "127.0.0.1", "string");
    cmd.add(addressArg);

    // port for FlairGCS, 9000 by default
    ValueArg<int> portArg("p", "port", "port for FlairGCS", false, 9000, "int");
    cmd.add(portArg);

    cmd.parse(argc, argv);

    // Get the value parsed by each arg.
    logPath = logArg.getValue();
    port = portArg.getValue();
    xmlFile = xmlArg.getValue();
    name = nameArg.getValue();
    address = addressArg.getValue();

  } catch (ArgException &e) { // catch any exceptions
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
}
