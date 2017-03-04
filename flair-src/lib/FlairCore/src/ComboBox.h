// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ComboBox.h
 * \brief Class displaying a QComboBox on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <Box.h>

namespace flair {
namespace gui {

class LayoutPosition;

/*! \class ComboBox
*
* \brief Class displaying a QComboBox on the ground station
*
*/
class ComboBox : public Box {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QComboBox at given position.
  *
  * \param position position to display the QComboBox
  * \param name name
  */
  ComboBox(const LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~ComboBox();

  /*!
 * \brief Add an item
 *
 * Add an item to the end of the list.
 *
 * \param name item nam
 */
  void AddItem(std::string name);

  /*!
  * \brief Currend index
  *
  * Index of the currently selected item. Items are numbered starting to 0.
  *
  * \return index number
  */
  int CurrentIndex(void) const;

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

#endif // COMBOBOX_H
