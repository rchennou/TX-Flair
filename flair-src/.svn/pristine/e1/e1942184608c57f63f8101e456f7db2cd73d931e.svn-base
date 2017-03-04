// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file XBldc.h
 * \brief Class for Xufo Bldc
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/11/13
 * \version 4.0
 */

#ifndef XBLDC_H
#define XBLDC_H

#include "Bldc.h"

namespace flair {
namespace core {
class IODevice;
class I2cPort;
}
namespace gui {
class Layout;
}
}

class XBldc_impl;

namespace flair {
namespace actuator {
/*! \class XBldc
*
* \brief Class for Xufo Bldc
*/
class XBldc : public Bldc {
public:
  /*!
  * \brief Constructor
  *
  * Construct a XBldc.
  *
  * \param parent parent
  * \param layout layout
  * \param name name
  * \param i2cport i2cport
  */
  XBldc(const core::IODevice *parent, gui::Layout *layout, std::string name,
        core::I2cPort *i2cport);

  /*!
  * \brief Destructor
  *
  */
  ~XBldc();

  /*!
  * \brief Has speed measurement
  *
  * Reimplemented from Bldc. \n
  *
  * \return true if it has speed measurement
  */
  bool HasSpeedMeasurement(void) const { return false; };

  /*!
  * \brief Has current measurement
  *
  * Reimplemented from Bldc. \n
  *
  * \return true if it has current measurement
  */
  bool HasCurrentMeasurement(void) const { return false; };

private:
  /*!
  * \brief Set motors values
  *
  * Reimplemented from Bldc. \n
  * Values size must be the same as MotorsCount()
  *
  * \param values motor values
  */
  void SetMotors(float *value);

  class XBldc_impl *pimpl_;
};
} // end namespace actuator
} // end namespace flair
#endif // XBLDC_H
