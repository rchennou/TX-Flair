// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Srf08.h
 * \brief Class for ultra sonic SRF08
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef SRF08_H
#define SRF08_H

#include <Thread.h>
#include <UsRangeFinder.h>

namespace flair {
namespace core {
class FrameworkManager;
class I2cPort;
}
namespace gui {
class SpinBox;
;
}
}

namespace flair {
namespace sensor {
/*! \class Srf08
*
* \brief Class for ultra sonic SRF08
*/
class Srf08 : public core::Thread, public UsRangeFinder {

public:
  /*!
  * \brief Constructor
  *
  * Construct a SRF08 sensor
  *
  * \param parent parent
  * \param name name
  * \param i2cport i2c port
  * \param address i2c slave address
  * \param priority priority of the Thread
  */
  Srf08(const core::FrameworkManager *parent, std::string name,
        core::I2cPort *i2cport, uint16_t address, uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~Srf08();

  /*!
  * \brief Set Range
  *
  * check datasheet for values
  */
  void SetRange(void);

  /*!
  * \brief Set Max Gain
  *
  * check datasheet for values
  */
  void SetMaxGain(void);

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

  void SendEcho(void);
  void GetEcho(void);

  bool is_init;
  core::Time echo_time;
  float z_1, z_2;
  gui::SpinBox *gain, *range;
  uint16_t address;
  core::I2cPort *i2cport;
};
} // end namespace sensor
} // end namespace flair
#endif // SRF08_H
