// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Layout.h
 * \brief Abstract class to display a layout on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#include <Widget.h>
#include <Mutex.h>

namespace flair {
namespace gui {
class LayoutPosition;

/*! \class Layout
*
* \brief Abstract class to display a layout on the ground station
*
* This is an abstract class to display layouts (like GridLayout, GroupBox, etc).
*\n
* A layout can contains Widgets (Box, DataPlot, Picture, etc). \n
* Layout holds a Mutex, which can be used to protect access to Box's value for
*example.
*/
class Layout : public Widget {
  friend class Box;

public:
  /*!
  * \brief Constructor
  *
  * Construct a Layout. Type is a predifined one, and will be
  * interpreted by the ground station.
  *
  * \param parent parent
  * \param name name
  * \param type type of layout
  */
  Layout(const Widget *parent, std::string name, std::string type);

  /*!
  * \brief Destructor
  *
  */
  ~Layout();

  /*!
  * \brief Last Row and Col LayoutPosition
  *
  * Get a LayoutPosition at the last row and col.
  *
  * \return the LayoutPosition
  */
  LayoutPosition *LastRowLastCol(void) const;

  /*!
  * \brief New Row LayoutPosition
  *
  * Get a LayoutPosition at a new row and first col. This new row will be at the
  *last position.
  *
  * \return the LayoutPosition
  */
  LayoutPosition *NewRow(void) const;

  /*!
  * \brief LayoutPosition at specified position
  *
  * Get a LayoutPosition at specified row and col.
  *
  * \param row row
  * \param col col
  *
  * \return the LayoutPosition
  */
  LayoutPosition *At(uint16_t row, uint16_t col) const;

private:
  /*!
  * \brief Mutex
  *
  * This Mutex can be used by friends class like Box to protect access
  * to Box's value.
  */
  core::Mutex *mutex;
};

} // end namespace gui
} // end namespace flair

#endif // LAYOUT_H
