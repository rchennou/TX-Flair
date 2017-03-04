// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Vector3DSpinBox.h
 * \brief Class displaying 3 QDoubleSpinBox for x,y,z on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef VECTOR3DSPINBOX_H
#define VECTOR3DSPINBOX_H

#include <Box.h>
#include <Vector3D.h>

namespace flair {
namespace gui {
class Layout;

/*! \class Vector3DSpinBox
*
* \brief Class displaying 3 QDoubleSpinBox for x,y,z on the ground station
*
*/
class Vector3DSpinBox : public Box {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Vector3DSpinBox at given position. \n
  * Each DoubleSpinBox is saturated to min and max values.
  *
  * \param position position to display the Vector3DSpinBox
  * \param name name
  * \param min minimum value
  * \param max maximum value
  * \param step step
  * \param decimals number of decimals
  * \param default_value default value if not in the xml config file
  */
  Vector3DSpinBox(const LayoutPosition *position, std::string name, double min,
                  double max, double step, int decimals = 2,
                  core::Vector3D default_value = core::Vector3D(0, 0, 0));

  /*!
  * \brief Destructor
  *
  */
  ~Vector3DSpinBox();

  /*!
  * \brief Value
  *
  * \return value
  */
  core::Vector3D Value(void) const;
  // operator core::Vector3D() const;
private:
  /*!
  * \brief XmlEvent from ground station
  *
  * Reimplemented from Widget.
  *
  */
  void XmlEvent(void);

  core::Vector3D box_value;
};

} // end namespace gui
} // end namespace flair

#endif // VECTOR3DSPINBOX_H
