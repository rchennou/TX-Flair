// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/07/25
//  filename:   BebopUs.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class for bebop ultra sonic sensor
//
//
/*********************************************************************/

#include "BebopUs.h"
#include <FrameworkManager.h>
#include <cvmatrix.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace sensor {

BebopUs::BebopUs(string name, uint8_t priority)
    : Thread(getFrameworkManager(),name, priority), UsRangeFinder(name) {

  SpiInit();
  AdcInit();

  //samples = new cvmatrix((Thread *)this, 8192, 1, floatType);
  //AddDataToLog(samples);
}

BebopUs::~BebopUs() {
  SafeStop();
  AdcEnable(false);
  close(spiFd);
  close(adcFd);
  Join();
}

void BebopUs::SpiInit(void) {
  spiFd = open("/dev/spidev1.0", O_RDWR);
  if (spiFd < 0) {
    Thread::Err("error openning spidev\n");
  }

  uint8_t spiMode = 0;
  if (ioctl(spiFd, SPI_IOC_WR_MODE, &spiMode) < 0) {
    Thread::Err("error cannot set spi mode");
  }

  uint8_t spiOrder = 0;
  if (ioctl(spiFd, SPI_IOC_WR_LSB_FIRST, &spiOrder) < 0) {
    Thread::Err("error cannot set spi bit justification");
  }

  uint8_t spiBitsPerWord = 8;
  if (ioctl(spiFd, SPI_IOC_WR_BITS_PER_WORD, &spiBitsPerWord) < 0) {
    Thread::Err("error cannot set bits per word");
  }

  uint32_t spiSpeed = 320000;
  if (ioctl(spiFd, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed) < 0) {
    Thread::Err("error cannot set max speed hz");
  }
}

void BebopUs::AdcInit(void) {
  AdcEnable(false);

  // enable channel
  int result =
      system("echo 1 > /sys/bus/iio/devices/iio:device0/scan_elements/in_voltage2_en");
  if (result < 0) {
    Thread::Err("error system command %s\n", strerror(-result));
  }

  // Set the buffer length
  result =
      system("echo 8192 > /sys/bus/iio/devices/iio:device0/buffer/length");
  if (result < 0) {
    Thread::Err("error system command %s\n", strerror(-result));
  }
  
  char *temp;
  if (asprintf(&temp, "/dev/iio:device0") < 0) {
    Thread::Err("error openning adc\n");
    return;
  }
  
  adcFd = open(temp, O_RDONLY);//blocking read
  free(temp);

  if (adcFd < 0) {
    Thread::Err("error openning adc\n");
  }
  
  AdcEnable(true);
  
}

void BebopUs::AdcEnable(bool enable) {
  int result;
  if (enable) {
    result = system("echo 1 > /sys/bus/iio/devices/iio:device0/buffer/enable");
  } else {
    result = system("echo 0 > /sys/bus/iio/devices/iio:device0/buffer/enable");
  }

  if (result < 0) {
    Thread::Err("error system command %s\n", strerror(-result));
  }
}

void BebopUs::AdcRead(void) {
  uint16_t values[8192];

  int ret = read(adcFd, values, 8192);

  uint16_t firstPeakStart = 0;
  uint16_t firstPeakEnd = 0;
  uint16_t lowestValue = 60000;
  uint16_t maximumValue = 0;
  uint16_t maximumValueId = 0;
  
  typedef enum {
    searchFirstPeakStart,
    searchFirstPeakEnd,
    searchSecondPeakStart,
    searchMaximumPeak
  } state_t;
  
  state_t state=searchFirstPeakStart;
  
  for(int i=0;i<7000;i++) {
    switch(state) {
      case searchFirstPeakStart:
        if(values[i]>60000) {
          state=searchFirstPeakEnd;
          firstPeakStart=i;
        }
        break;
      case searchFirstPeakEnd:
        if(values[i]<60000) {
          state=searchSecondPeakStart;
          firstPeakEnd=i-1;
        }
        break;
      case searchSecondPeakStart:
        if(values[i]<lowestValue) {
          lowestValue=values[i];
        }
        if(values[i]>lowestValue+5000) {
          state=searchMaximumPeak;
        }
        break;
      case searchMaximumPeak:
        if(values[i]>maximumValue) {
          maximumValue=values[i];
          maximumValueId=i;
        }
        break;
    }
  }

  float distance=((firstPeakEnd-firstPeakStart)/2+maximumValueId-firstPeakEnd)/1000.;

  if(firstPeakEnd-firstPeakStart<250 && distance>0.15) {
    output->SetValue(0, 0, distance);
  } else {
    output->SetValue(0, 0, 0);
  }
  output->SetDataTime(GetTime());
/*
samples->GetMutex();
  for (int i = 0; i < 8192; i++) {
    samples->SetValueNoMutex(i, 0, values[i]);
  }
samples->ReleaseMutex();*/
  ProcessUpdate(output);
}

void BebopUs::Run(void) {
  WarnUponSwitches(true);

  struct spi_ioc_transfer xfer;
  memset(&xfer, 0, sizeof xfer);
  uint8_t sonar_bebop_spi_d[16] = {0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00};

  xfer.tx_buf = (unsigned long)sonar_bebop_spi_d;
  xfer.len = sizeof(sonar_bebop_spi_d);
 
  SetPeriodMS(25);

  while (!ToBeStopped()) {
    //AdcEnable(true);
    int status = ioctl(spiFd, SPI_IOC_MESSAGE(1), &xfer);
    if (status < 0) {
      Thread::Err("SPI_IOC_MESSAGE");
    }
    AdcRead();
//AdcEnable(false);
    WaitPeriod();
  }

  WarnUponSwitches(false);
}

} // end namespace sensor
} // end namespace flair
