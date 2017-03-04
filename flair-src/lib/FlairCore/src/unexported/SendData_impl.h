// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SendData_impl.h
 * \brief Base class for sending datas to ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/07
 * \version 4.0
 */

#ifndef SENDDATA_IMPL_H
#define SENDDATA_IMPL_H

#include <stddef.h>
#include <stdint.h>

class SendData_impl;

/*! \class SendData_impl
* \brief Base class for sending datas to ground station
*
*/
class SendData_impl {
public:
  SendData_impl();
  ~SendData_impl();
  bool is_enabled;
  size_t send_size;
  uint16_t send_period;
};

#endif // SENDDATA_IMPL_H
