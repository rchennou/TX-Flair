// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file OpticalFlowCompensated.h
 * \brief Compensate optical flow data for rotations
 * \author Gildas Bayard, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2017/02/17
 * \version 1.0
 */

#ifndef OPTICALFLOWCOMPENSATED_H_
#define OPTICALFLOWCOMPENSATED_H

#include <IODevice.h>
#include <Object.h>
#include <Vector3D.h>

namespace flair {
  namespace core {
    class io_data;
    class cvmatrix;
  }
  namespace gui {
    class LayoutPosition;
    class SpinBox;
    class DoubleSpinBox;
  }
  namespace filter {
    class Ahrs;
    class OpticalFlow;
    class OpticalFlowData;
  }
}

namespace flair { namespace filter {

/*! \class OpticalFlowCompensated
*
* \brief Compensate optical flow data for rotations
*
*/
class OpticalFlowCompensated : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct an optical flow compensated filter
  *
  * \param parent parent
  * \param name name
  * \param ahrs ahrs object used to get rotational speed
  */
  OpticalFlowCompensated(const filter::OpticalFlow *parent, const filter::Ahrs *ahrs, const gui::LayoutPosition* position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~OpticalFlowCompensated();

  void UpdateFrom(const core::io_data *data);

  core::cvmatrix *GetFirstPointDisplacement() const;
private:
  OpticalFlowData *output;
  core::Time previousTime;
  const Ahrs *ahrs;
  core::cvmatrix *firstPointDisplacement;
  core::Vector3Df **previousStepsAngularRates;
  unsigned int previousStepsAngularRatesIndex;
  gui::SpinBox *gyroDelay;
  gui::DoubleSpinBox *gyroGain;
};

}} // end namespace flair::filter
#endif // OPTICALFLOWCOMPENSATED_H
