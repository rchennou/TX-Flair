// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ArDrone2Bldc.h
 * \brief Class for Ardrone 2 Bldc
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/12/19
 * \version 4.0
 */

#ifndef ARDRONE2BLDC_H
#define ARDRONE2BLDC_H

#include "Bldc.h"

namespace flair {
  namespace core {
    class SerialPort;
  }
  namespace gui {
    class Layout;
  }
  namespace actuator {
    class ArDrone2Gpio;
  }
}

class ArDrone2Bldc_impl;

namespace flair {
namespace actuator {
/*! \class ArDrone2Bldc
*
* \brief Class for Ardrone 2 Bldc
*/
class ArDrone2Bldc : public Bldc {
public:
    /*!
    * \brief Constructor
    *
    * Construct a ArDrone2Bldc.
    *
    * \param parent parent
    * \param layout layout
    * \param name name
    * \param serialport serialport
    * \param gpio gpio
    */
    ArDrone2Bldc(const core::IODevice* parent,gui::Layout* layout,std::string name,core::SerialPort* serialport,actuator::ArDrone2Gpio* gpio);

    /*!
    * \brief Destructor
    *
    */
    ~ArDrone2Bldc();

    /*!
    * \brief Has speed measurement
    *
    * Reimplemented from Bldc. \n
    *
    * \return true if it has speed measurement
    */
    bool HasSpeedMeasurement(void) const {
        return false;
    };

    /*!
    * \brief Has current measurement
    *
    * Reimplemented from Bldc. \n
    *
    * \return true if it has current measurement
    */
    bool HasCurrentMeasurement(void) const {
        return false;
    };

private:
    /*!
    * \brief Set motors values
    *
    * Reimplemented from Bldc. \n
    * Values size must be the same as MotorsCount()
    *
    * \param values motor values
    */
    void SetMotors(float* value);

    class ArDrone2Bldc_impl* pimpl_;
};
} // end namespace actuator
} // end namespace framewor
#endif // ARDRONE2BLDC_H
