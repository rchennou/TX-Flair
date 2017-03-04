// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuCamera.h
 * \brief Class for a simulation camera
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/03/06
 * \version 4.0
 */

#ifndef SIMUCAMERA_H
#define SIMUCAMERA_H

#include <Camera.h>
#include <Thread.h>
#include <cxcore.h>

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
/*! \class SimuCamera
*
* \brief Class for a simulation camera
*/
class SimuCamera : public core::Thread, public Camera {
public:
  /*!
  * \brief Constructor
  *
  * Construct a SimuCamera. Control part.
  *
  * \param parent parent
  * \param name name
  * \param width width
  * \param height height
  * \param channels number of channels
  * \param dev_id device id
  * \param priority priority of the Thread
  */
  SimuCamera(const core::FrameworkManager *parent, std::string name,
             uint16_t width, uint16_t height, uint8_t channels, uint32_t dev_id,
             uint8_t priority);

  /*!
  * \brief Constructor
  *
  * Construct a SimuCamera. Simulation part.\n
  * The Thread of this class should not be run.
  *
  * \param parent parent
  * \param name name
  * \param width width
  * \param height height
  * \param channels number of channels
  * \param dev_id device id
  */
  SimuCamera(const core::IODevice *parent, std::string name, uint16_t width,
             uint16_t height, uint8_t channels, uint32_t dev_id);

  /*!
  * \brief Destructor
  *
  */
  ~SimuCamera();

protected:
  /*!
  * \brief SharedMem to access datas
  *
  */
  core::SharedMem *shmem;

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
  void UpdateFrom(const core::io_data *data){};

  gui::SpinBox *data_rate;
  size_t buf_size;
  IplImage *img;
};
} // end namespace sensor
} // end namespace flair
#endif // SIMUCAMERA_H
