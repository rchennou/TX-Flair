// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/30
//  filename:   ControlLaw.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for control law
//
//
/*********************************************************************/

#include "ControlLaw.h"
#include <cvmatrix.h>
#include <cvmatrix_descriptor.h>
#include <DataPlot1D.h>
#include <sstream>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

ControlLaw::ControlLaw(const Object *parent, string name, uint32_t nb_out)
    : IODevice(parent, name) {
  if (nb_out == 1) {
    output = new cvmatrix(this, nb_out, 1, floatType, name);
  } else {
    cvmatrix_descriptor *desc = new cvmatrix_descriptor(nb_out, 1);
    for (int i = 0; i < nb_out; i++) {
      std::stringstream ss;
      ss << i;
      desc->SetElementName(i, 0, ss.str());
    }
    output = new cvmatrix(this, desc, floatType, name);
  }

  input = NULL;
  AddDataToLog(output);
}

ControlLaw::~ControlLaw(void) {}

void ControlLaw::Update(Time time) {
  input->SetDataTime(time);
  UpdateFrom(input);
}

float ControlLaw::Output(uint32_t index) const {
  return output->Value(index, 0);
}

void ControlLaw::UseDefaultPlot(const LayoutPosition *position) {
  if (output->Rows() != 1)
    Warn("Output size is different from 1. Plotting only Output(1,1).\n");

  DataPlot1D *plot = new DataPlot1D(position, ObjectName(), -1, 1);
  plot->AddCurve(output->Element(0));
}
} // end namespace filter
} // end namespace flair
