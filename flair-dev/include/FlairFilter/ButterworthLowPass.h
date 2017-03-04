// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ButterworthLowPass.h
 * \brief Class defining a Butterworth low pass filter
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/12/10
 * \version 4.0
 */

#ifndef BUTTERWORTHLOWPASS_H
#define BUTTERWORTHLOWPASS_H

#include <IODevice.h>

namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class LayoutPosition;
}
}

class ButterworthLowPass_impl;

namespace flair {
namespace filter {
/*! \class ButterworthLowPass
*
* \brief Class defining a Butterworth low pass filter
*/
class ButterworthLowPass : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a ButterworthLowPass at position. \n
  * After calling this function, position will be deleted as it is no longer
  *usefull. \n
  * The filter is automatically updated when parent's
  * IODevice::ProcessUpdate is called.
  *
  * \param parent parent
  * \param position position to display settings
  * \param name name
  * \param order order of the filter
  */
  ButterworthLowPass(const IODevice *parent,
                     const gui::LayoutPosition *position, std::string name,
                     int order);

  /*!
  * \brief Constructor
  *
  * Construct a ButterworthLowPass at position. \n
  * The ButterworthLowPass will automatically be child of position->getLayout()
  *Layout. After calling this function,
  * position will be deleted as it is no longer usefull. \n
  * The filter is updated manually with UpdateFrom method. \n
  *
  * \param position position to display settings
  * \param name name
  * \param order order of the filter
  */
  ButterworthLowPass(const gui::LayoutPosition *position, std::string name,
                     int order);

  /*!
  * \brief Destructor
  *
  */
  ~ButterworthLowPass();

  /*!
  * \brief Output value
  *
  * \return filtered output
  */
  float Output(void) const;

  /*!
  * \brief Output matrix
  *
  * \return filtered output
  */
  core::cvmatrix *Matrix(void) const;

  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

private:
  class ButterworthLowPass_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // BUTTERWORTHLOWPASS_H
