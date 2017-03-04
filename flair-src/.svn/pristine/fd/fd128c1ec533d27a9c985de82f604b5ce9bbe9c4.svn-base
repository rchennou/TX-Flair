// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file GroupBox.h
 * \brief Class displaying a QGroupBox on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <Layout.h>

namespace flair {
namespace gui {
class LayoutPosition;

/*! \class GroupBox
*
* \brief Class displaying a QGroupBox on the ground station
*
*/
class GroupBox : public Layout {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QGroupBox at given position. \n
  * The GroupBox will automatically be child of position->getLayout() Layout.
  *After calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param position position
  * \param name name
  */
  GroupBox(const LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~GroupBox();

private:
};

} // end namespace gui
} // end namespace flair

#endif // GROUPBOX_H
