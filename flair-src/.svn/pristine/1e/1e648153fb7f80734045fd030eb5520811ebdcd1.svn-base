// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuX4.h
 * \brief Class defining a simulation x4 uav
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/02/08
 * \version 4.0
 */

#ifndef SIMUX4_H
#define SIMUX4_H

#include "Uav.h"

namespace flair {
namespace meta {
/*! \class SimuX4
*
* \brief Class defining a simulation x4 uav
*/
class SimuX4 : public Uav {
public:
  // simu_id: 0 if simulating only one UAV
  //>0 otherwise
  SimuX4(core::FrameworkManager *parent, std::string uav_name, int simu_id = 0,
         filter::UavMultiplex *multiplex = NULL);
  ~SimuX4();
  void StartSensors(void);
  void SetupVRPNAutoIP(std::string name);
};
} // end namespace meta
} // end namespace flair
#endif // SIMUX4_H
