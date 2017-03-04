// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/03/21
//  filename:   io_data_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe définissant une donnée générique
//
//
/*********************************************************************/

#include "io_data.h"
#include "io_data_impl.h"
#include <fstream>

using std::string;
using namespace flair::core;

io_data_impl::io_data_impl(io_data *self, int n) {
  this->self = self;
  this->n = n;
  if (n < 1)
    self->Err("n doit être >0\n");
  size = 0;
  is_consistent = false;
  circle_ptr = NULL;
}

io_data_impl::~io_data_impl() {}

void io_data_impl::AppendLogDescription(string description,
                                        DataType const &datatype) {
  description += " (" + datatype.GetDescription() + ")";
  descriptors.push_back(description);
}

void io_data_impl::WriteLogDescriptor(std::fstream &desc_file, int *index) {
  for (size_t i = 0; i < descriptors.size(); i++) {
    desc_file << (*index)++ << ": " << self->ObjectName() << " - "
              << descriptors.at(i) << "\n";
  }
}

void io_data_impl::PrintLogDescriptor(void) {
  for (size_t i = 0; i < descriptors.size(); i++) {
    Printf("    %s\n", descriptors.at(i).c_str());
  }
}

void io_data_impl::Circle(void) {
  if (n > 1) {
    self->GetMutex();

    void *tmp = *self->Prev(n - 1)->pimpl_->circle_ptr;

    for (int i = 0; i < n - 1; i++) {
      // printf("%i\n",i);
      *(self->Prev(n - 1 - i)->pimpl_->circle_ptr) =
          *(self->Prev(n - 2 - i)->pimpl_->circle_ptr);
      self->Prev(n - 1 - i)->pimpl_->is_consistent =
          self->Prev(n - 2 - i)->pimpl_->is_consistent;
      self->Prev(n - 1 - i)->pimpl_->time = self->Prev(n - 2 - i)->pimpl_->time;
    }
    *circle_ptr = tmp;
    is_consistent = false;
    self->ReleaseMutex();
  }
}

bool io_data_impl::IsConsistent(void) { return is_consistent; }

void io_data_impl::SetConsistent(bool status) { is_consistent = status; }
