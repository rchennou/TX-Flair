// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/25
//  filename:   Unix_SerialPort.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for unix serial port
//
//
/*********************************************************************/

#include "Unix_SerialPort.h"
#include <fcntl.h> /* File control definitions */
#include <unistd.h>

using std::string;

namespace flair {
namespace core {

Unix_SerialPort::Unix_SerialPort(const Object *parent, string name,
                                 string device)
    : SerialPort(parent, name) {
  // open port
  fd = open(device.c_str(), O_RDWR | O_NOCTTY); // |O_NDELAY|O_NONBLOCK);
  if (fd == -1) {
    Err("open_port: Unable to open %s\n", device.c_str());
  }
  // fcntl(fd, F_SETFL, 0); //read calls are non blocking

  // Get the current options for the port

  tcgetattr(fd, &options);
  // Set the baud rates to 115200
  cfsetispeed(&options, B115200);
  cfsetospeed(&options, B115200);

  options.c_cflag |= (CLOCAL | CREAD); // Enable the receiver and set local mode
  options.c_iflag = 0;                 // clear input options
  options.c_lflag = 0;                 // clear local options
  options.c_oflag &= ~OPOST;           // clear output options (raw output)

  // Set the new options for the port
  options.c_cc[VTIME] = 0;
  options.c_cc[VMIN] = 1;
  FlushInput();
  tcsetattr(fd, TCSANOW, &options);
}

Unix_SerialPort::~Unix_SerialPort() { close(fd); }

void Unix_SerialPort::SetBaudrate(int baudrate) {
  // set port options
  struct termios options;
  // Get the current options for the port
  tcgetattr(fd, &options);
  // Set the baud rates to 115200

  switch (baudrate) {
  case 1200:
    cfsetispeed(&options, B1200);
    cfsetospeed(&options, B1200);
    break;
  case 2400:
    cfsetispeed(&options, B2400);
    cfsetospeed(&options, B2400);
    break;
  case 4800:
    cfsetispeed(&options, B4800);
    cfsetospeed(&options, B4800);
    break;
  case 9600:
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    break;
  case 19200:
    cfsetispeed(&options, B19200);
    cfsetospeed(&options, B19200);
    break;
  case 38400:
    cfsetispeed(&options, B38400);
    cfsetospeed(&options, B38400);
    break;
  case 115200:
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
    break;
  case 460800:
    cfsetispeed(&options, B460800);
    cfsetospeed(&options, B460800);
    break;
  case 921600:
    cfsetispeed(&options, B921600);
    cfsetospeed(&options, B921600);
    break;
  default:
    Err("unsupported baudrate\n");
  }
  tcsetattr(fd, TCSANOW, &options);
  FlushInput();
}

void Unix_SerialPort::SetRxTimeout(core::Time timeout_ns) {}

void Unix_SerialPort::FlushInput(void) { tcflush(fd, TCIFLUSH); }

ssize_t Unix_SerialPort::Write(const void *buf, size_t nbyte) {
  return write(fd, buf, nbyte);
}

ssize_t Unix_SerialPort::Read(void *buf, size_t nbyte) {
  if (options.c_cc[VMIN] != nbyte) {
    tcgetattr(fd, &options); // bug if not called?
    options.c_cc[VTIME] = 0;
    options.c_cc[VMIN] = nbyte;
    tcsetattr(fd, TCSANOW, &options);
  }

  return read(fd, buf, nbyte);
}

} // end namespace core
} // end namespace flair
