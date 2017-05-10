//  created:    2011/05/01
//  filename:   main.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    exemple de code uav
//
//
/*********************************************************************/

#include "SquareFleet.h"
#include <FrameworkManager.h>
#include <UavFactory.h>
#include <stdio.h>
#include <tclap/CmdLine.h>
#include <TargetEthController.h>

using namespace TCLAP;
using namespace std;
using namespace flair::core;
using namespace flair::meta;
using namespace flair::sensor;

string uav_type;
string log_path;
int port;
int ds3port;
string xml_file;
string name;
string broadcast;
string address;

void parseOptions(int argc, char** argv);


int main(int argc, char* argv[]) {
    parseOptions(argc,argv);

    FrameworkManager *manager;
    manager= new FrameworkManager(name);
    manager->SetupLogger(log_path);
    manager->SetupConnection(address,port);
    manager->SetupUserInterface(xml_file);

    Uav* drone=CreateUav(manager,name,uav_type);
    TargetEthController *controller=new TargetEthController(manager,"Dualshock3",ds3port);
    SquareFleet* demo=new SquareFleet(drone,broadcast,controller);

    demo->Start();
    demo->Join();

    delete manager;
}


void parseOptions(int argc, char** argv) {
	try {

        CmdLine cmd("Command description message", ' ', "0.1");

        ValueArg<string> nameArg("n","name","uav name, also used for vrpn",true,"x4","string");
        cmd.add( nameArg );

        ValueArg<string> typeArg("t","type","uav type: ardrone2, hds_x4, hds_x8, hds_xufo, x4_simu, x8_simu or x4_simux (with x the number of the simulated uav)",true,"hds_x4","string");
        cmd.add( typeArg );

        ValueArg<string> xmlArg("x","xml","fichier xml",true,"./reglages.xml","string");
        cmd.add( xmlArg );

        ValueArg<string> logsArg("l","logs","repertoire des logs",true,"/media/ram","string");
        cmd.add( logsArg );

        ValueArg<int> portArg("p","port","port pour station sol",true,9000,"int");
        cmd.add( portArg );

        ValueArg<string> addressArg("a","address","addresse station sol",true,"127.0.0.1","string");
        cmd.add( addressArg );

        ValueArg<int> ds3portArg("d","ds3_port","port pour ds3",false,20000,"int");
        cmd.add( ds3portArg );

        ValueArg<string> broadcastArg("b","broadcast","broadcast ip address and port,",true,"127.255.255.255:20001","string");
        cmd.add( broadcastArg );

        cmd.parse( argc, argv );

        // Get the value parsed by each arg.
        log_path = logsArg.getValue();
        port=portArg.getValue();
        ds3port=ds3portArg.getValue();
        xml_file = xmlArg.getValue();
        name=nameArg.getValue();
        broadcast=broadcastArg.getValue();
        uav_type=typeArg.getValue();
        address=addressArg.getValue();

	} catch (ArgException &e) { // catch any exceptions
        cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
	}
}
