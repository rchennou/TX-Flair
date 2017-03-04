// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/25
//  filename:   RTDM_SerialPort.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    port serie temps reel
//
//
/*********************************************************************/

#include "RTDM_SerialPort.h"

#ifdef __XENO__

#include <rtdm/rtserial.h>
#include <errno.h>
#include <cstring>

using std::string;

namespace flair {
namespace core {

RTDM_SerialPort::RTDM_SerialPort(const Object *parent, string name,
                                 string device)
    : SerialPort(parent, name) {
  struct rtser_config write_config;

  write_config.config_mask = RTSER_SET_BAUD | RTSER_SET_TIMESTAMP_HISTORY,
  write_config.baud_rate = 115200,
  write_config.timestamp_history = RTSER_DEF_TIMESTAMP_HISTORY,
  // the rest implicitely remains default

      fd = rt_dev_open(device.c_str(), 0);
  if (fd < 0) {
    Err("erreur rt_dev_open (%s)\n", strerror(-fd));
  }

  // config
  int err = rt_dev_ioctl(fd, RTSER_RTIOC_SET_CONFIG, &write_config);
  if (err) {
    Err("erreur rt_dev_ioctl RTSER_RTIOC_SET_CONFIG (%s)\n", strerror(-err));
  }
}

RTDM_SerialPort::~RTDM_SerialPort() { rt_dev_close(fd); }

void RTDM_SerialPort::SetBaudrate(int baudrate) {
  struct rtser_config write_config;

  write_config.config_mask = RTSER_SET_BAUD;
  write_config.baud_rate = baudrate;
  // the rest implicitely remains default

  // config
  int err = rt_dev_ioctl(fd, RTSER_RTIOC_SET_CONFIG, &write_config);
  if (err) {
    Err("erreur rt_dev_ioctl RTSER_RTIOC_SET_CONFIG (%s)\n", strerror(-err));
  }
}

void RTDM_SerialPort::SetRxTimeout(core::Time timeout_ns) {
  struct rtser_config write_config;

  write_config.config_mask = RTSER_SET_TIMEOUT_RX;
  write_config.rx_timeout = timeout_ns;
  // the rest implicitely remains default

  // config
  int err = rt_dev_ioctl(fd, RTSER_RTIOC_SET_CONFIG, &write_config);
  if (err) {
    Err("erreur rt_dev_ioctl RTSER_RTIOC_SET_CONFIG (%s)\n", strerror(-err));
  }
}

void RTDM_SerialPort::FlushInput(void) {
  char tmp;

  SetRxTimeout(1000000);
  while (rt_dev_read(fd, &tmp, 1) == 1)
    ;
  SetRxTimeout(TIME_INFINITE);
}

ssize_t RTDM_SerialPort::Write(const void *buf, size_t nbyte) {
  return rt_dev_write(fd, buf, nbyte);
}

ssize_t RTDM_SerialPort::Read(void *buf, size_t nbyte) {
  return rt_dev_read(fd, buf, nbyte);
}

} // end namespace core
} // end namespace flair

#else //__XENO__

using std::string;
using namespace flair::core;

namespace flair {
namespace core {

RTDM_SerialPort::RTDM_SerialPort(const Object *parent, string name,
                                 string device)
    : SerialPort(parent, name) {
  Err("not available in non real time\n");
}

RTDM_SerialPort::~RTDM_SerialPort() {}

ssize_t RTDM_SerialPort::Write(const void *buf, size_t nbyte) { return -1; }

ssize_t RTDM_SerialPort::Read(void *buf, size_t nbyte) { return -1; }

void RTDM_SerialPort::SetBaudrate(int baudrate) {}

void RTDM_SerialPort::SetRxTimeout(core::Time timeout_ns) {}

void RTDM_SerialPort::FlushInput(void) {}

} // end namespace core
} // end namespace flair

#endif
