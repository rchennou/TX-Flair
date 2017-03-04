// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuAhrs.h
 * \brief Class for a simulation Ahrs
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/07
 * \version 4.0
 */

#ifndef SIMUAHRS_H
#define SIMUAHRS_H

#include <Ahrs.h>
#include <stdint.h>

namespace flair {
namespace filter {
/*! \class SimuAhrs
*
* \brief Class for a simulation Ahrs
*
* This class constructs a SimuImu as Imu of this Ahrs.
*/
class SimuAhrs : public filter::Ahrs {
public:
  /*!
  * \brief Constructor
  *
  * Construct a simulation Ahrs.
  *
  * \param parent parent
  * \param name name
  * \param dev_id number id of the simulated Ahrs
  * \param priority priority of the SimuImu Thread
  */
  SimuAhrs(const core::FrameworkManager *parent, std::string name,
           uint32_t dev_id, uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~SimuAhrs();

  /*!
 * \brief Start SimuImu Thread
 *
 */
  void Start(void);

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);
};
} // end namespace filter
} // end namespace flair
#endif // SIMUAHRS_H
