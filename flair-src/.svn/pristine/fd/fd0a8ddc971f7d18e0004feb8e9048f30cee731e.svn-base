// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file TabWidget.h
 * \brief Class displaying a QTabWidget on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/07/30
 * \version 4.0
 */

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <Widget.h>

namespace flair {
namespace gui {
class LayoutPosition;

/*! \class TabWidget
*
* \brief Class displaying a QTabWidget on the ground station
*
* TabWidget contains Tabs.
*
*/
class TabWidget : public Widget {
public:
  /*!
  * \enum TabPosition_t
  * \brief Position of tabs
  */
  typedef enum {
    North /*! north */,
    South /*! south */,
    West /*! west */,
    East /*! east */
  } TabPosition_t;

  /*!
  * \brief Constructor
  *
  * Construct a QTabWidget at given position. \n
  * The TabWidget will automatically be child of position->getLayout() Layout.
  *After calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param position position
  * \param name name
  * \param tabPosition position of tabs
  */
  TabWidget(const LayoutPosition *position, std::string name,
            TabPosition_t tabPosition = TabWidget::West);

  /*!
  * \brief Destructor
  *
  */
  ~TabWidget();

private:
};

} // end namespace core
} // end namespace flair

#endif // TABWIDGET_H
