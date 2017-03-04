// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/09/02
//  filename:   Forwarder.h
//
//  authors:    Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Forward input data to output data, using sockets
//
//
/*********************************************************************/

#ifndef MAVPLANNER_FORWARDER_H
#define MAVPLANNER_FORWARDER_H

#include <string>

#include <Thread.h>

namespace flair {
namespace core {
  class FrameworkManager;
  class Socket;
}
}

class Forwarder : public flair::core::Thread {
public:

  Forwarder(const flair::core::FrameworkManager *parent, std::string name,
  			std::string &inputAddress, int inputPort,
  			std::string &outputAddress, int outputPort);
  ~Forwarder();

private:
  // reimplement the run of the Thread class
  void Run();

  flair::core::Socket *inputSocket;
  std::string inputAddress;
  int inputPort;
  char *inputBuffer;
  const int inputBufferSize = 200;

  flair::core::Socket *outputSocket;
  std::string outputAddress;
  int outputPort;

};

#endif // MAVPLANNER_FORWARDER_H
