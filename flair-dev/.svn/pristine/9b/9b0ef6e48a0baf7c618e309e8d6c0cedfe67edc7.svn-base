// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file CheckBox.h
 * \brief Class displaying a QCheckBox on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <Box.h>

namespace flair {
namespace gui {

class LayoutPosition;

/*! \class CheckBox
*
* \brief Class displaying a QCheckBox on the ground station
*
*/
class CheckBox : public Box {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QCheckBox at given position.
  *
  * \param position position to display the QCheckBox
  * \param name name
  * \param default_value default value if not in the xml config file
  */
  CheckBox(const LayoutPosition *position, std::string name,
           bool default_value = true);

  /*!
  * \brief Destructor
  *
  */
  ~CheckBox();

  /*!
  * \brief Is checked?
  *
  * \return true if checked
  */
  bool IsChecked(void) const;

  /*!
  * \brief Value
  *
  * \return 1 if checked, 0 otherwise
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

  bool box_value;
};

} // end namespace gui
} // end namespace flair

#endif // CHECKBOX_H
