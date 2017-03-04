// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Box.h
 * \brief Abstract class to display a box on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/28
 * \version 4.0
 */

#ifndef BOX_H
#define BOX_H

#include <Widget.h>

namespace flair {
namespace gui {

class Layout;
class LayoutPosition;

/*! \class Box
*
* \brief Abstract class to display a box on the ground station
*
* This is an abstract class to display boxes (like CheckBox, SpinBox, etc). \n
* To access reimplemented box's value, use Box::GetMutex and Box::ReleaseMutex.
*\n
* Note that this mutex is in reality the one from the parent Layout. To minimize
*memory
* footprint, each Box does not have its own Mutex.
*/
class Box : public Widget {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Box. \n
  * Type must agree with predifined (hard coded) types
  * in ground station code. \n
  * The Box will automatically be child of position->getLayout() Layout. After
  *calling this method,
  * position will be deleted as it is no longer usefull.
  *
  * \param position position
  * \param name name
  * \param type type
  */
  Box(const LayoutPosition *position, std::string name, std::string type);

  /*!
  * \brief Destructor
  *
  */
  ~Box();

  /*!
  * \brief Has the value changed since last call?
  *
  * This method returns the value of an internal flag
  * which is set through SetValueChanged(). \n
  * After calling this method, the internal flag is
  * set to false.
  *
  * \return true is valued has changed since last call
  */
  bool ValueChanged(void);

protected:
  /*!
  * \brief Set the value changed flag
  *
  * The reimplemented class must call this method when Box's value is changed.
  *\n
  * This method must be called with Mutex locked. Indeed, as reimplemented class
  * also has to lock the Mutex to change the Box value, this mecanism avoid two
  *successives
  * lock and unlock.
  *
  */
  void SetValueChanged(void);

  /*!
  * \brief Get Mutex
  *
  * This method must be called before changing Box's value or
  * calling SetValueChanged().
  *
  */
  void GetMutex(void) const;

  /*!
  * \brief Release Mutex
  *
   * This method must be called after changing Box's value or
  *  calling SetValueChanged().
  *
  */
  void ReleaseMutex(void) const;

private:
  bool value_changed;
};

} // end namespace gui
} // end namespace flair

#endif // BOX_H
