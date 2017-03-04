// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuBldc.h
 * \brief Class for a simulation bldc
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/07
 * \version 4.0
 */

#ifndef SIMUBLDC_H
#define SIMUBLDC_H

#include <Bldc.h>

namespace flair {
namespace core {
class SharedMem;
class IODevice;
class cvmatrix;
}
namespace gui {
class DoubleSpinBox;
class Layout;
}
}

namespace flair {
namespace actuator {
/*! \class SimuBldc
*
* \brief Class for a simulation bldc
*
*/
class SimuBldc : public Bldc {
public:
  /*!
  * \brief Constructor
  *
  * Construct a SimuBldc. Control part.
  *
  * \param parent parent
  * \param layout layout
  * \param name name
  * \param motors_count number of motors
  * \param dev_id device id
  */
  SimuBldc(const core::IODevice *parent, gui::Layout *layout, std::string name,
           uint8_t motors_count, uint32_t dev_id);

  /*!
  * \brief Constructor
  *
  * Construct a SimuBldc. Simulation part.
  *
  * \param parent parent
  * \param name name
  * \param motors_count number of motors
  * \param dev_id device id
  */
  SimuBldc(const core::Object *parent, std::string name, uint8_t motors_count,
           uint32_t dev_id);

  /*!
  * \brief Destructor
  *
  */
  ~SimuBldc();

  /*!
  * \brief Get motors speeds.
  *
  * This function should only be used for the simulation part.
  *
  * \param value array to store motors speeds
  */
  void GetSpeeds(float *value) const;

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

  core::SharedMem *shmem;
  gui::DoubleSpinBox *k;
};
} // end namespace actuator
} // end namespace flair
#endif // SIMUBLDC_H
