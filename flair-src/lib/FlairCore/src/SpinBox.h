// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SpinBox.h
 * \brief Class displaying a QSpinBox on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef SPINBOX_H
#define SPINBOX_H

#include <Box.h>

namespace flair {
namespace gui {

class LayoutPosition;

/*! \class SpinBox
*
* \brief Class displaying a QSpinBox on the ground station
*
*/
class SpinBox : public Box {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QSpinBox at given position. \n
  * The QSpinBox is saturated to min and max values.
  *
  * \param position position to display the QSpinBox
  * \param name name
  * \param min minimum value
  * \param max maximum value
  * \param step step
  * \param default_value default value if not in the xml config file
  */
  SpinBox(const LayoutPosition *position, std::string name, int min, int max,
          int step, int default_value = 0); /*!

* \brief Constructor
*
* Construct a QSpinBox at given position. \n
* The QSpinBox is saturated to min and max values.
*
* \param position position to display the QSpinBox
* \param name name
* \param suffix suffix for the value (eg unit)
* \param min minimum value
* \param max maximum value
* \param step step
* \param default_value default value if not in the xml config file
*/
  SpinBox(const LayoutPosition *position, std::string name, std::string suffix,
          int min, int max, int step, int default_value = 0);

  /*!
  * \brief Destructor
  *
  */
  ~SpinBox();

  /*!
   * \brief Value
   *
   * \return value
   */
  int Value(void) const;

private:
  /*!
  * \brief XmlEvent from ground station
  *
  * Reimplemented from Widget.
  *
  */
  void XmlEvent(void);

  int box_value;
};

} // end namespace gui
} // end namespace flair

#endif // SPINBOX_H
