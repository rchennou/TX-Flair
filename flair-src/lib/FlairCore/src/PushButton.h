// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file PushButton.h
 * \brief Class displaying a QPushButton on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <Widget.h>

namespace flair {
namespace gui {

class LayoutPosition;

/*! \class PushButton
*
* \brief Class displaying a QPushButton on the ground station
*
*/
class PushButton : public Widget {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QPushButton at given position. \n
  * The PushButton will automatically be child of position->getLayout() Layout.
  *After calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param parent parent
  * \param name name
  */
  PushButton(const LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~PushButton();

  /*!
  * \brief Has been clicled?
  *
  * After calling this method, the internal flag
  * representing the state of the button is
  * automatically set to false.
  *
  * \return true if button was clicked
  */
  bool Clicked(void);

private:
  /*!
  * \brief XmlEvent from ground station
  *
  * Reimplemented from Widget.
  *
  */
  void XmlEvent(void);

  bool clicked;
};

} // end namespace gui
} // end namespace flair

#endif // PUSHBUTTON_H
