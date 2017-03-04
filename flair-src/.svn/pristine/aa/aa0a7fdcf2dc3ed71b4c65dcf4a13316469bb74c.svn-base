// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/08/28
//  filename:   Unix_I2cPort.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for unix i2c port
//
//
/*********************************************************************/

#include "Unix_I2cPort.h"
#include <errno.h>
#include <fcntl.h> /* File control definitions */
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

using std::string;

namespace flair {
namespace core {

Unix_I2cPort::Unix_I2cPort(const Object *parent, string name, string device)
    : I2cPort(parent, name) {
  // open port
  fd = open(device.c_str(), O_RDWR);
  if (fd == -1) {
    Err("open_port: Unable to open %s\n", device.c_str());
  }
}

Unix_I2cPort::~Unix_I2cPort() { close(fd); }

void Unix_I2cPort::SetRxTimeout(core::Time timeout_ns) {
  Warn("not implemented\n");
}

void Unix_I2cPort::SetTxTimeout(core::Time timeout_ns) {
  Warn("not implemented\n");
}

int Unix_I2cPort::SetSlave(uint16_t address) {
  int err = ioctl(fd, I2C_SLAVE_FORCE, address);
  if (err < 0) {
    Err("Failed to set slave address\n");
  }

  return err;
}

ssize_t Unix_I2cPort::Write(const void *buf, size_t nbyte) {
  return write(fd, buf, nbyte);
}

ssize_t Unix_I2cPort::Read(void *buf, size_t nbyte) {
  return read(fd, buf, nbyte);
}

} // end namespace core
} // end namespace flair
