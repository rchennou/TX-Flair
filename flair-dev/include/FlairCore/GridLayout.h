// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file GridLayout.h
 * \brief Class displaying a QGridLayout on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include <Layout.h>

namespace flair {
namespace gui {
class LayoutPosition;

/*! \class GridLayout
*
* \brief Class displaying a QGridLayout on the ground station
*
*/
class GridLayout : public Layout {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QCheckBox at given position. \n
  * The GridLayout will automatically be child of position->getLayout() Layout.
  After calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param parent parent
  * \param name name

  */
  GridLayout(const LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~GridLayout();

private:
};

} // end namespace gui
} // end namespace flair

#endif // GRIDLAYOUT_H
