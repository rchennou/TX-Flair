// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file NestedSat.h
 * \brief  Class defining a PID with saturations
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/15
 * \version 4.0
 */

#ifndef NESTEDSAT_H
#define NESTEDSAT_H

#include <ControlLaw.h>

namespace flair {
namespace gui {
class Layout;
class LayoutPosition;
}
}

class NestedSat_impl;

namespace flair {
namespace filter {
/*! \class NestedSat
*
* \brief  Class defining a PID with saturations
*
* The output of this control law is calculated
* as follows: \n
* p_ref=Sat(p_ref,k*sat_ref) \n
* d_ref=Sat[(p_ref-p)*kp,k*sat_dref] \n
* law=Sat[(d-d_ref)*kd,sat_u] \n
* where p, p_ref and d are input values (see SetValues()), \n
* where sat_ref, sat_dref and sat_u are settings availables on the ground
*station, \n
* where k is a conversion factor (see ConvertSatFromDegToRad()).
*/
class NestedSat : public ControlLaw {
  friend class ::NestedSat_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a NestedSat at given place position. \n
  * The NestedSat will automatically be child of position->getLayout() Layout.
  *After calling this function,
  * position will be deleted as it is no longer usefull. \n
  *
  * \param position position to display settings
  * \param name name
  */
  NestedSat(const gui::LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~NestedSat();

  /*!
  * \brief Set input values
  *
  * \param p_ref proportional reference
  * \param p proportional value
  * \param d derivative value
  */
  void SetValues(float p_ref, float p, float d);

  /*!
  * \brief Convert saturation parameters in radians
  *
  * If this function is called, saturation parameters
  * on the ground station will be interpreted as degrees. \n
  * Thus, an internal conversion from degrees to radians will
  * be done (k=PI/180).
  */
  void ConvertSatFromDegToRad(void);

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

  NestedSat_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // NESTEDSAT_H
