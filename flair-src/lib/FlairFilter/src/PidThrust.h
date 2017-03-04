// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file PidThrust.h
 * \brief Class defining a Pid for Thrust
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/11/07
 * \version 4.0
 */

#ifndef PIDTHRUST_H
#define PIDTHRUST_H

#include <ControlLaw.h>

namespace flair {
namespace gui {
class LayoutPosition;
}
}

class PidThrust_impl;

namespace flair {
namespace filter {
/*! \class PidThrust
*
* \brief Class defining a Pid for Thrust.\n
* This Pid as an extra offset for compensating gravity.
*/
class PidThrust : public ControlLaw {
  friend class ::PidThrust_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a PidThrust at given position
  * The PidThrust will automatically be child of position->getLayout() Layout.
  *After calling this function,
  * position will be deleted as it is no longer usefull. \n
  *
  * \param position position to display settings
  * \param name name
  */
  PidThrust(const gui::LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~PidThrust();

  /*!
  * \brief Reset integral and offset to 0
  *
  */
  void Reset(void);

  /*!
  * \brief Reset integral to 0
  *
  */
  void ResetI(void);

  /*!
  * \brief Reset offset to 0
  *
  */
  void ResetOffset(void);

  /*!
  * \brief Set offset to specified value in ground station
  *
  */
  void SetOffset(void);

  /*!
  * \brief Get offset
  *
  * \return current offset
  */
  float GetOffset(void);

  /*!
  * \brief Step up the offset according to specified value in ground station
  *
  * \return false if offset is at its maximum (1) value, true otherwise
  */
  bool OffsetStepUp(void);

  /*!
  * \brief Step down the offset according to specified value in ground station
  *
  * \return false if offset is at its minimum (specified in ground station)
  *value, true otherwise
  */
  bool OffsetStepDown(void);

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

  PidThrust_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // PIDTHRUST_H
