// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file BebopUs.h
 * \brief Class for bebop ultra sonic sensor
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/07/25
 * \version 4.0
 */

#ifndef BEBOPUS_H
#define BEBOPUS_H

#include <Thread.h>
#include <UsRangeFinder.h>

namespace flair {
namespace core {
class FrameworkManager;
class I2cPort;
class cvmatrix;
}
namespace gui {
class SpinBox;
}
}

namespace flair {
namespace sensor {
/*! \class BebopUs
*
* \brief Class for bebop ultra sonic sensor
*/
class BebopUs : public core::Thread, public UsRangeFinder {

public:
  /*!
  * \brief Constructor
  *
  * Construct a bebop ultra sonic sensor
  *
  * \param name name
  * \param priority priority of the Thread
  */
  BebopUs(std::string name,uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~BebopUs();

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);

  void SpiInit(void);
  void AdcInit(void);
  void AdcRead(void);
  void AdcEnable(bool enable);
  int spiFd,adcFd;
  core::cvmatrix* samples;
};
} // end namespace sensor
} // end namespace flair
#endif // BEBOPUS_H
