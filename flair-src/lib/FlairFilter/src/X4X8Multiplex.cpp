// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/10
//  filename:   X4X8Multiplex.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining X4 and X8 multiplexing
//
//
/*********************************************************************/

#include "X4X8Multiplex.h"
#include "X4X8Multiplex_impl.h"

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

X4X8Multiplex::X4X8Multiplex(const FrameworkManager *parent, std::string name,
                             UavType_t type)
    : UavMultiplex(parent, name) {
  int nb_mot;

  switch (type) {
  case X4:
    nb_mot = 4;
    break;
  case X8:
    nb_mot = 8;
    break;
  default:
    Err("uav type not supported\n");
    break;
  }

  pimpl_ = new X4X8Multiplex_impl(this, nb_mot);

  for (int i = 0; i < nb_mot; i++) {
    SetMultiplexComboBox(pimpl_->MotorName(i), i);
  }
}

X4X8Multiplex::~X4X8Multiplex(void) { delete pimpl_; }

uint8_t X4X8Multiplex::MotorsCount(void) const { return pimpl_->nb_mot; }

void X4X8Multiplex::UseDefaultPlot(void) { pimpl_->UseDefaultPlot(); }

void X4X8Multiplex::UpdateFrom(const io_data *data) {
  pimpl_->UpdateFrom(data);
}

} // end namespace filter
} // end namespace flair
