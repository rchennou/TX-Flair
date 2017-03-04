// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuImu.h
 * \brief Class for a simulation Imu
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/07
 * \version 4.0
 */

#ifndef SIMUIMU_H
#define SIMUIMU_H

#include <Imu.h>
#include <Thread.h>

namespace flair {
  namespace core {
    class SharedMem;
    class AhrsData;
  }
  namespace gui {
    class SpinBox;
  }
}

namespace flair {
namespace sensor {
/*! \class SimuImu
*
* \brief Class for a simulation Imu
*/
class SimuImu : public Imu, public core::Thread {
public:
  /*!
  * \brief Constructor
  *
  * Construct a SimuImu. Control part.
  *
  * \param parent parent
  * \param name name
  * \param dev_id device id
  * \param priority priority of the Thread
  */
  SimuImu(const core::FrameworkManager *parent, std::string name,
          uint32_t dev_id, uint8_t priority);

  /*!
  * \brief Constructor
  *
  * Construct a SimuImu. Simulation part.\n
  * The Thread of this class should not be run.
  *
  * \param parent parent
  * \param name name
  * \param dev_id device id
  */
  SimuImu(const core::IODevice *parent, std::string name, uint32_t dev_id);

  /*!
  * \brief Destructor
  *
  */
  ~SimuImu();

private:
  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);

  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

  typedef struct {
    float q0;
    float q1;
    float q2;
    float q3;
    float wx;
    float wy;
    float wz;
  } imu_states_t;

  gui::SpinBox *dataRate;
  core::SharedMem *shmem;
  core::AhrsData *ahrsData;
};
} // end namespace sensor
} // end namespace flair
#endif // SIMUIMU_H
