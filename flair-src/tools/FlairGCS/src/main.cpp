// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include <QApplication>
#include <QCleanlooksStyle>
#include <QLocale>
#include <qmetatype.h>
#include <tclap/CmdLine.h>

#include "Manager.h"
#include "unexported/compile_info.h"

using namespace TCLAP;
using namespace std;

string name;
int port;

void parseOptions(int argc, char **argv) {
  try {
    CmdLine cmd("Command description message", ' ', "0.1");

    ValueArg<string> nameArg("n", "name", "uav name", false, "x4-0", "string");
    cmd.add(nameArg);

    ValueArg<int> portArg("p", "port", "port number", false, 9000, "int");
    cmd.add(portArg);

    cmd.parse(argc, argv);

    // Get the value parsed by each arg.
    name = nameArg.getValue();
    port = portArg.getValue();

  } catch (ArgException &e) { // catch any exceptions
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
}

int main(int argc, char *argv[]) {

  union {
    uint32_t i;
    char c[4];
  } bint = {0x01020304};

  if (bint.c[0] == 1) {
    printf("error, ground station is only compatible with little endian\n");
    return -1;
  }

  compile_info("FlairGCS");

  parseOptions(argc, argv);
  printf("listening on port %i\n", port);

  qRegisterMetaType<const char *>("const char*");
  QLocale::setDefault(QLocale::C);
  QApplication app(argc, argv);
  app.setStyle(new QCleanlooksStyle);

  Manager manager(QString::fromStdString(name), port);

  manager.show();

  app.exec();
}
