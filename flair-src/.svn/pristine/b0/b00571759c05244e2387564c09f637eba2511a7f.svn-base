// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuGps.h
 * \brief Class for a simulation GPS
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/08/23
 * \version 4.0
 */

#ifndef SIMUGPS_H
#define SIMUGPS_H

#include <Thread.h>
#include <NmeaGps.h>

namespace flair {
  namespace core {
    class FrameworkManager;
    class SharedMem;
  }
  namespace gui {
    class SpinBox;
    class DoubleSpinBox;
  }
}

namespace flair {
namespace sensor {
/*! \class SimuGps
*
* \brief Class for a simulation GPS
*/
class SimuGps : public core::Thread, public NmeaGps {
public:
  /*!
  * \brief Constructor
  *
  * Construct a simulation GPS. Control part.
  *
  * \param parent parent
  * \param name name
  * \param NMEAFlags NMEA sentances to enable
  * \param deviceId device id
  * \param priority priority of the Thread
  */
  SimuGps(const core::FrameworkManager *parent, std::string name,
          NmeaGps::NMEAFlags_t NMEAFlags, uint32_t deviceId,uint8_t priority);

  /*!
  * \brief Constructor
  *
  * Construct a simulation GPS. Simulation part.\n
  * The Thread of this class should not be run.
  *
  * \param parent parent
  * \param name name
  * \param deviceId device id
  */
  SimuGps(const core::IODevice *parent, std::string name, uint32_t deviceId);

  /*!
  * \brief Destructor
  *
  */
  ~SimuGps();

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);

  typedef struct {
    float e;
    float n;
    float u;
    float ve;
    float vn;
  } gps_states_t;

  core::SharedMem *shmem;
  gui::SpinBox *dataRate,*fixQuality,*numberOfSatellites;
  gui::DoubleSpinBox *latitudeRef,*longitudeRef,*altitudeRef;
};
} // end namespace sensor
} // end namespace framewor
#endif // SIMUGPS_H
