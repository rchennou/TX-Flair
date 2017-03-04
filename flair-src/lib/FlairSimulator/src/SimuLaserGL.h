// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuUsGL.h
 * \brief Class for a simulation us
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/07
 * \version 3.4
 */

#ifndef SIMULASERGL_H
#define SIMULASERGL_H

#include <SimuLaser.h>
#include <SensorGL.h>

namespace flair {
namespace gui {
class DoubleSpinBox;
class Vector3DSpinBox;
}
}

namespace flair {
namespace simulator {
class Model;
}
}

namespace flair {
namespace sensor {
/*! \class SimuUsGL
* \brief Class for a simulation us
*
*/
class SimuLaserGL : public SimuLaser, public SensorGL {
public:
  SimuLaserGL(const simulator::Model *parent, std::string name, int dev_id);
  ~SimuLaserGL();

private:
  void UpdateFrom(const core::io_data *data);
  gui::DoubleSpinBox *range;
  gui::Vector3DSpinBox *position, *direction;
};
} // end namespace sensor
} // end namespace flair
#endif // SIMULASERGL_H
