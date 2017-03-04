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

#ifndef SIMUUSGL_H
#define SIMUUSGL_H

#include <SimuUs.h>
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
class SimuUsGL : public SimuUs, public SensorGL {
public:
  SimuUsGL(const simulator::Model *parent, std::string name, int dev_id);
  ~SimuUsGL();

private:
  void UpdateFrom(const core::io_data *data);
  gui::DoubleSpinBox *range;
  gui::Vector3DSpinBox *position, *direction;
};
} // end namespace sensor
} // end namespace flair
#endif // SIMUUSGL_H
