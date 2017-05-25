//  created:    2015/10/19
//  filename:   main.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    exemple de code x4
//
//
/*********************************************************************/

#include "DemoFollowLine.h"
#include <UavFactory.h>
#include <FrameworkManager.h>
#include <stdio.h>
#include <tclap/CmdLine.h>
#include <TargetEthController.h>
#include <VisionFilter.h>

using namespace TCLAP;
using namespace std;
using namespace flair::core;
using namespace flair::meta;
using namespace flair::sensor;

string uav_type;
string dsp_file;
string log_path;
int port;
int ds3port;
string xml_file;
string name;
string address;

void parseOptions(int argc, char** argv);

int main(int argc, char* argv[]) {
    parseOptions(argc,argv);
		
		if(!InitVisionFilter("file="+dsp_file)) {
			exit(1);
		}

    FrameworkManager *manager;
    manager= new FrameworkManager(name);
    manager->SetupConnection(address,port);
    manager->SetupUserInterface(xml_file);
    manager->SetupLogger(log_path);

    Uav* drone=CreateUav(name,uav_type);
    TargetEthController *controller=new TargetEthController("Dualshock3",ds3port);
    DemoFollowLine* demo=new DemoFollowLine(controller);

    demo->Start();
    demo->Join();

    delete manager;
		
		CloseVisionFilter();
}


void parseOptions(int argc, char** argv)
{
	try
	{

        CmdLine cmd("Command description message", ' ', "0.1");

        ValueArg<string> nameArg("n","name","uav name",true,"x4","string");
        cmd.add( nameArg );

        ValueArg<string> typeArg("t","type","uav type: ardrone2, hds_x4, hds_x8, hds_xufo, hds_simu or hds_simux (with x the number of the simulated uav)",true,"hds_x4","string");
        cmd.add( typeArg );

        ValueArg<string> dspArg("v","dsp","executable dsp",true,"./dspcv_dsp.out","string");
        cmd.add( dspArg );

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

        cmd.parse( argc, argv );

        // Get the value parsed by each arg.
        uav_type=typeArg.getValue();
        dsp_file = dspArg.getValue();
        log_path = logsArg.getValue();
        port=portArg.getValue();
				ds3port=ds3portArg.getValue();
        xml_file = xmlArg.getValue();
        name=nameArg.getValue();
        address=addressArg.getValue();

	} catch (ArgException &e)  // catch any exceptions
	{ cerr << "error: " << e.error() << " for arg " << e.argId() << endl; }
}
