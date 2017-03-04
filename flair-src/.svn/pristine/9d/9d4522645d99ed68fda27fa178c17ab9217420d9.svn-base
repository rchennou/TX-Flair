// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Tab.h
 * \brief Class displaying a QTab on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef TAB_H
#define TAB_H

#include <Layout.h>

namespace flair {
namespace gui {

class TabWidget;

/*! \class Tab
*
* \brief Class displaying a QTab on the ground station
*
* Tabs are displayed in a TabWidget.
*/
class Tab : public Layout {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Tab in the TabWidget.
  *
  * \param parent parent
  * \param name name
  * \param position tab position, -1 to put at the last position
  */
  Tab(const TabWidget *parent, std::string name, int position = -1);

  /*!
  * \brief Destructor
  *
  */
  ~Tab();

private:
};

} // end namespace gui
} // end namespace flair

#endif // TAB_H
