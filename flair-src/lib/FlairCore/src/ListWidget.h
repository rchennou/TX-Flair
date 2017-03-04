// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ListWidget.h
 * \brief Class displaying a QListWidget on the ground station
 * \author Thomas Fuhrmann, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/07/26
 * \version 1.0
 */

#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <Widget.h>

namespace flair {
namespace gui {

class LayoutPosition;

/*! \class ListWidget
 *
 * \brief Class displaying a QListWidget on the ground station
 *  
 *  The internal list (called items) contains the same elements
 *  as the list of the QListWidget on the ground station.
 *  To do that, each action done on the ground station has to
 *  applied thanks to a click on the "apply" button.
 *
 */
class ListWidget : public Widget {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QListWidget at given position.
  *
  * \param position position to display the QListWidget
  * \param name name
  */
  ListWidget(const LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~ListWidget();

  /*!
 * \brief Add an item
 *
 * Add an item to the end of the list.
 *
 * \param name item nam
 */
  void AddItem(std::string name);

  /*!
  * \brief Remove an item
  *
  * Remove the currently selected item.
  * The item is not removed from the internal xml file,
  * because the xml is override by the GUI.
  */
  void RemoveItem(void);

  const std::vector<std::string> &GetItemList() const;

private:
  /*!
  * \brief XmlEvent from ground station
  *
  * Reimplemented from Widget.
  *
  */
  void XmlEvent(void);

  /**
   * List of items displayed in the ground station.
   */
  std::vector<std::string> items;
  /**
   * Row of the item currently selected in the list.
   */
  uint16_t selectedItemRow;
  /**
   * Flag to know if the selected item has changed.
   */
  bool selectedItemChanged;
};

} // end namespace gui
} // end namespace flair

#endif // LISTWIDGET_H
