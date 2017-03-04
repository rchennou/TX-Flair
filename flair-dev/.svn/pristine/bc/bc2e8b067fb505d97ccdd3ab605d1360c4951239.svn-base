// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Ps3Eye.h
 * \brief Class for Ps3Eye camera
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/01/19
 * \version 4.0
 */

#ifndef PS3EYE_H
#define PS3EYE_H

#include "V4LCamera.h"

namespace flair {
namespace core {
class cvimage;
class FrameworkManager;
}
namespace gui {
class GridLayout;
class DoubleSpinBox;
class CheckBox;
}
}

namespace flair {
namespace sensor {
/*! \class Ps3Eye
*
* \brief Class for Ps3Eye camera
*/
class Ps3Eye : public V4LCamera {

public:
  /*!
  * \brief Constructor
  *
  * Construct a Ps3Eye.
  *
  * \param parent parent
  * \param name name
  * \param camera_index index of the camera, ie /dev/videox
  * \param priority priority of the Thread
  */
  Ps3Eye(const core::FrameworkManager *parent, std::string name,
         int camera_index, uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~Ps3Eye();

private:
};
} // end namespace sensor
} // end namespace flair

#endif // PS3EYE_H
