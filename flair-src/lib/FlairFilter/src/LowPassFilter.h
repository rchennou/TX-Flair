// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file LowPassFilter.h
 * \brief Class defining a first order low pass filter
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef LOWPASSFILTER_FILTER_H
#define LOWPASSFILTER_FILTER_H

#include <IODevice.h>

namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class Layout;
class LayoutPosition;
}
}

class LowPassFilter_impl;

namespace flair {
namespace filter {
/*! \class LowPassFilter
*
* \brief Class defining a first order low pass filter
*/
class LowPassFilter : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a LowPassFilter at position. \n
  * After calling this function, position will be deleted as it is no longer
  *usefull. \n
  * The filter is automatically updated when parent's
  * IODevice::ProcessUpdate is called. \n
  * The optional init_value parameters allow to specify
  * the size of the input datas and its inital values.
  * If unspecified, a 1*1 size is used, and values are
  * initialized with 0.
  *
  * \param parent parent
  * \param position position to display settings
  * \param name name
  * \param init_value initial value
  */
  LowPassFilter(const core::IODevice *parent,
                const gui::LayoutPosition *position, std::string name,
                const core::cvmatrix *init_value = NULL);

  /*!
  * \brief Destructor
  *
  */
  ~LowPassFilter();

  /*!
  * \brief Output value
  *
  * \param row row element
  * \param col column element
  *
  * \return element value
  */
  float Output(int row, int col) const;

  /*!
  * \brief Output matrix
  *
  * \return filtered output
  */
  core::cvmatrix *Matrix(void) const;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

  class LowPassFilter_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // LOWPASSFILTER_FILTER_H
