// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file io_data_impl.h
 * \brief Abstract class for data types.
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/21
 * \version 4.0
 */

#ifndef IO_DATA_IMPL_H
#define IO_DATA_IMPL_H

#include "io_data.h"

/*! \class io_data_impl
* \brief Abstract class for data types.
*
* Use this class to define a custom data type. Data types ares used for logging
*and graphs. \n
* The reimplemented class must call SetSize() in its constructor. \n
* io_data can be constructed with n samples (see io_data::io_data).
* In this case, old samples can be accessed throug io_data::Prev.
*/
class io_data_impl {
public:
  io_data_impl(flair::core::io_data *self, int n);
  ~io_data_impl();
  void Circle(void);
  bool IsConsistent(void);
  void SetConsistent(bool status);
  void WriteLogDescriptor(std::fstream &desc_file, int *index);
  void PrintLogDescriptor(void);
  void AppendLogDescription(std::string description,
                            flair::core::DataType const &datatype);
  size_t size;
  flair::core::Time time;
  void **circle_ptr;

private:
  flair::core::io_data *self;
  int n;
  bool is_consistent;
  std::vector<std::string> descriptors;
};

#endif // IO_DATA_IMPL_H
