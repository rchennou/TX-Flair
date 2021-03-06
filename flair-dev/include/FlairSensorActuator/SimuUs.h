// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuUs.h
 * \brief Class for a simulation UsRangeFinder
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/07
 * \version 4.0
 */

#ifndef SIMUUS_H
#define SIMUUS_H

#include <UsRangeFinder.h>
#include <Thread.h>

namespace flair {
namespace core {
class SharedMem;
}
namespace gui {
class SpinBox;
}
}

namespace flair {
namespace sensor {
/*! \class SimuUs
*
* \brief Class for a simulation UsRangeFinder
*/
class SimuUs : public core::Thread, public UsRangeFinder {
public:
  /*!
  * \brief Constructor
  *
  * Construct a SimuUs. Control part.
  *
  * \param parent parent
  * \param name name
  * \param dev_id device id
  * \param priority priority of the Thread
  */
  SimuUs(const core::FrameworkManager *parent, std::string name,
         uint32_t dev_id, uint8_t priority);

  /*!
  * \brief Constructor
  *
  * Construct a SimuUs. Simulation part.\n
  * The Thread of this class should not be run.
  *
  * \param parent parent
  * \param name name
  * \param dev_id device id
  */
  SimuUs(const core::IODevice *parent, std::string name, uint32_t dev_id);

  /*!
  * \brief Destructor
  *
  */
  ~SimuUs();

protected:
  /*!
  * \brief SharedMem to access datas
  *
  */
  core::SharedMem *shmem;

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

  gui::SpinBox *data_rate;
};
} // end namespace sensor
} // end namespace flair
#endif // SIMUUS_H
