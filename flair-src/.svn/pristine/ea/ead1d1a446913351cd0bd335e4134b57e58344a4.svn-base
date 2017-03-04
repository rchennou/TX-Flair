// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/09/04
//  filename:   RTDM_RTDM_I2cPort.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for real time i2c port using RTDM
//
//
/*********************************************************************/

#include "RTDM_I2cPort.h"

#ifdef __XENO__

#include <rtdm/rti2c.h>
#include <errno.h>
#include <cstring>

using std::string;

namespace flair {
namespace core {

RTDM_I2cPort::RTDM_I2cPort(const Object *parent, string name, string device)
    : I2cPort(parent, name) {
  int err = 0;
  struct rti2c_config write_config;

  // printf("i2c integer le mutex dans le driver, avec acces ioctl\n");
  fd = rt_dev_open(device.c_str(), 0);
  if (fd < 0) {
    Err("rt_dev_open (%s)\n", ObjectName().c_str(), strerror(-fd));
  }

  write_config.config_mask =
      RTI2C_SET_BAUD | RTI2C_SET_TIMEOUT_RX | RTI2C_SET_TIMEOUT_TX;
  write_config.baud_rate = 400000;
  write_config.rx_timeout = 500000;
  write_config.tx_timeout = 1000000; // 5ms pour les xbldc, normalement 1ms
  // the rest implicitely remains default

  // config
  err = rt_dev_ioctl(fd, RTI2C_RTIOC_SET_CONFIG, &write_config);
  if (err) {
    Err("rt_dev_ioctl RTI2C_RTIOC_SET_CONFIG error (%s)\n",
        ObjectName().c_str(), strerror(-err));
  }
}

RTDM_I2cPort::~RTDM_I2cPort() { rt_dev_close(fd); }

int RTDM_I2cPort::SetSlave(uint16_t address) {
  int err = rt_dev_ioctl(fd, RTI2C_RTIOC_SET_SLAVE, &address);
  if (err) {
    Err("rt_dev_ioctl RTI2C_RTIOC_SET_SLAVE error (%s)\n", strerror(-err));
  }

  return err;
}

void RTDM_I2cPort::SetRxTimeout(Time timeout_ns) {
  struct rti2c_config write_config;

  write_config.config_mask = RTI2C_SET_TIMEOUT_RX;
  write_config.rx_timeout = timeout_ns;

  int err = rt_dev_ioctl(fd, RTI2C_RTIOC_SET_CONFIG, &write_config);
  if (err) {
    Err("rt_dev_ioctl RTI2C_RTIOC_SET_CONFIG (%s)\n", ObjectName().c_str(),
        strerror(-err));
  }
}

void RTDM_I2cPort::SetTxTimeout(Time timeout_ns) {
  struct rti2c_config write_config;

  write_config.config_mask = RTI2C_SET_TIMEOUT_TX;
  write_config.tx_timeout = timeout_ns;

  int err = rt_dev_ioctl(fd, RTI2C_RTIOC_SET_CONFIG, &write_config);
  if (err) {
    Err("rt_dev_ioctl RTI2C_RTIOC_SET_CONFIG (%s)\n", ObjectName().c_str(),
        strerror(-err));
  }
}

ssize_t RTDM_I2cPort::Write(const void *buf, size_t nbyte) {
  return rt_dev_write(fd, buf, nbyte);
}

ssize_t RTDM_I2cPort::Read(void *buf, size_t nbyte) {
  return rt_dev_read(fd, buf, nbyte);
}

} // end namespace core
} // end namespace flair

#else //__XENO__

using std::string;
using namespace flair::core;

namespace flair {
namespace core {

RTDM_I2cPort::RTDM_I2cPort(const Object *parent, string name, string device)
    : I2cPort(parent, name) {
  Err("not available in non real time\n");
}

RTDM_I2cPort::~RTDM_I2cPort() {}

int RTDM_I2cPort::SetSlave(uint16_t address) { return -1; }

void RTDM_I2cPort::SetRxTimeout(Time timeout_ns) {}

void RTDM_I2cPort::SetTxTimeout(Time timeout_ns) {}

ssize_t RTDM_I2cPort::Write(const void *buf, size_t nbyte) { return -1; }

ssize_t RTDM_I2cPort::Read(void *buf, size_t nbyte) { return -1; }

} // end namespace core
} // end namespace flair

#endif
