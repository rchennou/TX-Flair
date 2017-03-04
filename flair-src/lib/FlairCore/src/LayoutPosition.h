// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file LayoutPosition.h
 * \brief Class to define a position in a layout on the ground station.
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/12/04
 * \version 4.0
 */

#ifndef LAYOUTPOSITION_H
#define LAYOUTPOSITION_H

#include <stdint.h>

namespace flair {
namespace gui {
class Layout;

/*! \class LayoutPosition
*
* \brief Class to define a position in a layout on the ground station.
*

*/
class LayoutPosition {
public:
  /*!
  * \brief Constructor
  *
  * Construct a LayoutPosition, in given Layout at given place.
  *
  * \param layout layout
  * \param row row position
  * \param col col position
  */
  LayoutPosition(const Layout *layout, int16_t row, int16_t col);

  /*!
  * \brief Destructor
  *
  */
  ~LayoutPosition();

  /*!
  * \brief get Layout
  *
  * \return the parent Layout
  */
  const Layout *getLayout(void) const;

  /*!
  * \brief get row
  *
  * \return row position
  */
  int16_t Row(void) const;

  /*!
  * \brief get col
  *
  * \return col position
  */
  int16_t Col(void) const;

private:
  const Layout *layout;
  int16_t row, col;
};

} // end namespace gui
} // end namespace flair

#endif // LAYOUTPOSITION_H
