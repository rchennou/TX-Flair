// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}

//  created:    2013/08/23
//  filename:   HokuyoUTM30Lx.cpp
//
//  author:     Cesar Richard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe intégrant le telemetre laser Hokuyo UTM 30lx
//
//
/*********************************************************************/

#include "HokuyoUTM30Lx.h"
#include <SerialPort.h>
#include <FrameworkManager.h>
#include <RangeFinderPlot.h>
#include <cvmatrix.h>
#include <Tab.h>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <iostream>

using namespace std;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

HokuyoUTM30Lx::HokuyoUTM30Lx(const FrameworkManager *parent, string name,
                             SerialPort *serialport, uint8_t priority)
    : LaserRangeFinder(parent, name), Thread(parent, name, priority) {
  main_tab = new Tab(parent->GetTabWidget(), name);
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(1081, 1);
  output = new cvmatrix((IODevice *)this, desc, SignedIntegerType(16));

  bufRetMut =
      new Mutex(reinterpret_cast<Object *>(this), (string)name + "BufRetMut");
  sendingCmdMut = new Mutex(reinterpret_cast<Object *>(this),
                            (string)name + "SendingCmdMut");

  this->serialport = serialport;
  serialport->SetRxTimeout(100000000);
}

HokuyoUTM30Lx::~HokuyoUTM30Lx() {
  delete main_tab;
  SafeStop();
  Join();
}

void HokuyoUTM30Lx::Run(void) {
  /** Debut init **/
  char c, lastC;
  int startStep;
  bool mustDecode = false;
  stringstream ss;
  vector<string> ret;
  lastC = c = 0;

  /** Fin init **/
  resetConfig();
  startLaser();
  Printf("Laser started\r\n");

  /** Debut running loop **/
  WarnUponSwitches(true);

  while (!ToBeStopped()) {
    ss.clear();
    ss.str("");
    do {
      lastC = c;
      serialport->Read(&c, 1);
      ss << c;
    } while (!(c == '\n' && lastC == '\n'));
    ret = explode(ss.str(), '\n');
    if (!checkSum(ret.at(1)))
      perror("Bad Checksum !");
    if (ret.at(0).substr(0, 2) == "MD")
      mustDecode = true;

    startStep = atoi(ret.at(0).substr(2, 4).c_str());
    ret.erase(ret.begin());
    bufRetMut->GetMutex();
    bufRet.push(ret.at(0).substr(0, 2));
    bufRetMut->ReleaseMutex();
    if (mustDecode) {
      mustDecode = false;
      ss.clear();
      ss.str("");
      do {
        lastC = c;
        serialport->Read(&c, 1);
        ss << c;
      } while (!(c == '\n' && lastC == '\n'));
      ret = explode(ss.str(), '\n');
      ret.erase(ret.begin());
      ret.erase(ret.begin());
      if (ret.at(0).size() == 5)
        if (!checkSum(ret.at(0)))
          perror("TimeStamp checksum error!");
      ret.erase(ret.begin());
      Printf("!post\r\n");
      ret.pop_back();
      decodeDatas(ret, startStep);
    }
  }
  /** fin running loop **/
  stopLaser();
  WarnUponSwitches(false);
}

void HokuyoUTM30Lx::decodeDatas(vector<string> datas, int startStep) {
  stringstream ss;
  for (unsigned i = 0; i < datas.size(); i++) {
    if (datas.at(i).size() != 0) {
      if (!checkSum(datas.at(i)))
        perror("Datas checksum error !");
      datas.at(i).erase(datas.at(i).end() - 1);
      ss << datas.at(i);
    }
  }
  output->GetMutex();
  for (unsigned i = 0; i < 1080; i++) {
    // TODO: remettre -1 pour les points non lus
    output->SetValueNoMutex(i, 0, 0);
  }
  for (unsigned i = 0; i < ss.str().size(); i += 3) {
    output->SetValueNoMutex(startStep + (i / 3), 0,
                            decode3car(ss.str().substr(i, 3).c_str()));
  }
  UpdateFrom(output);
  ProcessUpdate(output);
  output->ReleaseMutex();
}

bool HokuyoUTM30Lx::checkSum(string data) {
  return (char)encodeSum(data.substr(0, data.size() - 1).c_str(),
                         data.size() - 1) == data.at(data.size() - 1);
}

void HokuyoUTM30Lx::startLaser() {
  string ret = sendCommand("BM");
#ifdef VERBOSE
  if (ret == "00") {
    cout << "BM: Alright !" << endl;
  } else if (ret == "01") {
    cout << "BM: Laser malfunction !" << endl;
  } else if (ret == "02") {
    cout << "BM: Laser already started !" << endl;
  }
#endif
}

void HokuyoUTM30Lx::stopLaser() { sendCommand("QT"); }

void HokuyoUTM30Lx::resetConfig() { sendCommand("RS"); }

vector<string> HokuyoUTM30Lx::explode(const string str, char delimiter) {
  istringstream split(str);
  vector<string> tokens;
  for (string each; getline(split, each, delimiter); tokens.push_back(each))
    ;
  return tokens;
}

int HokuyoUTM30Lx::encodeSum(const char *code, int byte) {
  unsigned char value = 0;
  int i;
  for (i = 0; i < byte; ++i) {
    value += code[i];
  }
  value &= 0x3f;
  value += 0x30;
  return value;
}

float HokuyoUTM30Lx::decode2car(const char *data) {
  return ((data[0] - 0x30) << 6) | ((data[1] - 0x30));
}
float HokuyoUTM30Lx::decode3car(const char *data) {
  return ((data[0] - 0x30) << 12) | ((data[1] - 0x30) << 6) |
         ((data[2] - 0x30));
}
float HokuyoUTM30Lx::decode4car(const char *data) {
  return ((data[0] - 0x30) << 18) | ((data[1] - 0x30) << 12) |
         ((data[2] - 0x30) << 6) | ((data[3] - 0x30));
}

string HokuyoUTM30Lx::sendCommand(string command) {
  char c;
  string ret = "00";
  c = '\n';
  sendingCmdMut->GetMutex();
  serialport->Write(command.c_str(), command.size());
  serialport->Write(&c, 1);
  sendingCmdMut->ReleaseMutex();
  return ret;
}

void HokuyoUTM30Lx::getMesure(int startStep, int endStep, int clusterCount,
                              int interval, int scanNumber) {
  stringstream ss;
  string ret;
  ss << "MD" << std::setfill('0') << std::setw(4) << startStep << std::setw(4)
     << endStep << std::setw(2) << clusterCount << std::setw(1) << interval
     << std::setw(2) << scanNumber;
  ret = sendCommand(ss.str());
#ifdef VERBOSE
  if (ret == "00") {
    cout << "MD: Alright !" << endl;
  } else if (ret == "01") {
    cout << "MD: Laser malfunction !" << endl;
  } else if (ret == "02") {
    cout << "MD: End Step has non-numeric value !" << endl;
  } else if (ret == "03") {
    cout << "MD: Cluster Count has non-numeric value !" << endl;
  } else if (ret == "04") {
    cout << "MD: End Step is out of range !" << endl;
  } else if (ret == "05") {
    cout << "MD: End Step is smaller than Starting Step !" << endl;
  } else if (ret == "06") {
    cout << "MD: Scan Interval has non-numeric value !" << endl;
  } else if (ret == "07") {
    cout << "MD: Number of Scan has non-numeric value !" << endl;
  } else if (ret == "98") {
    cout << "MD: Resumption of process after confirming normal HokuyoUTM30Lx "
            "operation." << endl;
  } else {
    /* Concerne :
    21~49 --- Processing stopped to verify the error.
    50~97 --- Hardware trouble (such as laser, motor malfunctions etc.)*/
    cout << "MD: Malfunction !" << endl;
  }
#endif
}
cvmatrix *HokuyoUTM30Lx::getDatas() { return output; }

void HokuyoUTM30Lx::UseDefaultPlot(void) {
  plot = new RangeFinderPlot(main_tab->NewRow(), "plot", "x", -100, 100, "y",
                             -0, 100, output, -45, 225, output->Rows());
}

} // end namespace sensor
} // end namespace framewor
