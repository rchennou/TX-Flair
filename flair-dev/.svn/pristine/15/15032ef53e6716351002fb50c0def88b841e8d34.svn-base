// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file DoubleSpinBox.h
 * \brief Class displaying a QDoubleSpinBox on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <Box.h>

namespace flair {
namespace gui {

class Layout;

/*! \class DoubleSpinBox
*
* \brief Class displaying a QDoubleSpinBox on the ground station
*
*/
class DoubleSpinBox : public Box {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QDoubleSpinBox at given position. \n
  * The QDoubleSpinBox is saturated to min and max values.
  *
  * \param position position to display the QDoubleSpinBox
  * \param name name
  * \param min minimum value
  * \param max maximum value
  * \param step step
  * \param decimals number of decimals
  * \param default_value default value if not in the xml config file
  */
  DoubleSpinBox(const LayoutPosition *position, std::string name, double min,
                double max, double step, int decimals = 2,
                double default_value = 0);

  /*!
  * \brief Constructor
  *
  * Construct a QDoubleSpinBox at given position. \n
  * The QDoubleSpinBox is saturated to min and max values.
  *
  * \param position position to display the QDoubleSpinBox
  * \param name name
  * \param suffix suffix for the value (eg unit)
  * \param min minimum value
  * \param max maximum value
  * \param step step
  * \param decimals number of decimals
  * \param default_value default value if not in the xml config file
  */
  DoubleSpinBox(const LayoutPosition *position, std::string name,
                std::string suffix, double min, double max, double step,
                int decimals = 2, double default_value = 0);

  /*!
  * \brief Destructor
  *
  */
  ~DoubleSpinBox();

  /*!
  * \brief Value
  *
  * \return value
  */
  double Value(void) const;

private:
  /*!
  * \brief XmlEvent from ground station
  *
  * Reimplemented from Widget.
  *
  */
  void XmlEvent(void);

  double box_value;
};

} // end namespace gui
} // end namespace flair

#endif // DOUBLESPINBOX_H
