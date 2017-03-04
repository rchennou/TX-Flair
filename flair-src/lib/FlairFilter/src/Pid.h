// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Pid.h
 * \brief Class defining a PID
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef PID_H
#define PID_H

#include <ControlLaw.h>

namespace flair {
namespace gui {
class LayoutPosition;
}
}

class Pid_impl;

namespace flair {
namespace filter {
/*! \class Pid
*
* \brief Class defining a PID
*/
class Pid : public ControlLaw {
  friend class ::Pid_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a PID at given position. \n
  * The PID will automatically be child of position->getLayout() Layout. After
  *calling this function,
  * position will be deleted as it is no longer usefull. \n
  *
  * \param position position to display settings
  * \param name name
  */
  Pid(const gui::LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~Pid();

  /*!
  * \brief Reset integral
  *
  */
  void Reset(void);

  /*!
  * \brief Set input values
  *
  * \param p proportional value
  * \param d derivative value
  */
  void SetValues(float p, float d);

  /*!
  * \brief Use default plot
  *
  * Plot the output values at position. \n
  * Plot consists of 4 curves: proportional part,
  * derivative part, integral part and
  * the sum of the three. \n
  * After calling this function, position will be deleted as it is no longer
  *usefull. \n
  *
  * \param position position to display plot
  */
  void UseDefaultPlot(const gui::LayoutPosition *position);

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

  Pid_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // PID_H
