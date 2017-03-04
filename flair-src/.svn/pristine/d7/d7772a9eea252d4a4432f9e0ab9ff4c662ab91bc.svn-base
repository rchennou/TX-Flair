// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/10
//  filename:   X4X8Multiplex_impl.cpp
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

#include "X4X8Multiplex_impl.h"
#include "X4X8Multiplex.h"
#include <cvmatrix.h>
#include <Tab.h>
#include <GridLayout.h>
#include <GroupBox.h>
#include <ComboBox.h>
#include <DataPlot1D.h>
#include <math.h>

#define MAX_MOTORS 8

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

X4X8Multiplex_impl::X4X8Multiplex_impl(flair::filter::X4X8Multiplex *self,
                                       int nb_mot) {
  this->nb_mot = nb_mot;
  this->self = self;

  if (nb_mot == 4) {
    GroupBox *groupbox =
        new GroupBox(self->GetLayout()->NewRow(), "x4 multiplex");
    pas = new ComboBox(groupbox->NewRow(), "front left blade pitch:");
  } else {
    GroupBox *groupbox =
        new GroupBox(self->GetLayout()->NewRow(), "x8 multiplex");
    pas = new ComboBox(groupbox->NewRow(), "top front left blade pitch:");
  }
  pas->AddItem("counter clockwise");
  pas->AddItem("clockwise");

  cvmatrix_descriptor *desc = new cvmatrix_descriptor(nb_mot, 1);
  for (int i = 0; i < nb_mot; i++) {
    desc->SetElementName(i, 0, MotorName(i));
  }

  output = new cvmatrix(self, desc, floatType);

  self->AddDataToLog(output);
}

X4X8Multiplex_impl::~X4X8Multiplex_impl(void) {}

void X4X8Multiplex_impl::UseDefaultPlot(void) {
  Tab *plot_tab = new Tab(self->GetTabWidget(), "Values");
  plots[0] = new DataPlot1D(plot_tab->NewRow(), "front left", 0, 1);
  plots[1] = new DataPlot1D(plot_tab->LastRowLastCol(), "front right", 0, 1);
  plots[2] = new DataPlot1D(plot_tab->NewRow(), "rear left", 0, 1);
  plots[3] = new DataPlot1D(plot_tab->LastRowLastCol(), "rear right", 0, 1);

  for (int i = 0; i < 4; i++)
    plots[i]->AddCurve(output->Element(i));

  if (nb_mot == 8) {
    for (int i = 0; i < 4; i++)
      plots[i]->AddCurve(output->Element(i + 4), DataPlot::Blue);
  }
}

void X4X8Multiplex_impl::UpdateFrom(const io_data *data) {
  float u_roll, u_pitch, u_yaw, u_thrust;
  float trim_roll, trim_pitch, trim_yaw;
  float value[MAX_MOTORS];

  cvmatrix *input = (cvmatrix *)data;

  // on prend une fois pour toute le mutex et on fait des accès directs
  input->GetMutex();

  u_roll = input->ValueNoMutex(0, 0);
  u_pitch = input->ValueNoMutex(1, 0);
  u_yaw = input->ValueNoMutex(2, 0);
  u_thrust = input->ValueNoMutex(3, 0);
  trim_roll = input->ValueNoMutex(4, 0);
  trim_pitch = input->ValueNoMutex(5, 0);
  trim_yaw = input->ValueNoMutex(6, 0);

  input->ReleaseMutex();

  if (pas->CurrentIndex() == 1) {
    trim_yaw = -trim_yaw;
    u_yaw = -u_yaw;
  }

  if (nb_mot == 2) {
    //(top) front left
    value[self->MultiplexValue(X4X8Multiplex::TopFrontLeft)] = Set(
        trim_pitch + trim_roll + trim_yaw, u_thrust + u_pitch + u_roll + u_yaw);

    //(top) front right
    value[self->MultiplexValue(X4X8Multiplex::TopFrontRight)] = Set(
        trim_pitch - trim_roll - trim_yaw, u_thrust + u_pitch - u_roll - u_yaw);
  }
  if (nb_mot == 4 || nb_mot == 8) {
    //(top) front left
    value[self->MultiplexValue(X4X8Multiplex::TopFrontLeft)] = Set(
        trim_pitch + trim_roll + trim_yaw, u_thrust + u_pitch + u_roll + u_yaw);

    //(top) front right
    value[self->MultiplexValue(X4X8Multiplex::TopFrontRight)] = Set(
        trim_pitch - trim_roll - trim_yaw, u_thrust + u_pitch - u_roll - u_yaw);

    //(top) rear left
    value[self->MultiplexValue(X4X8Multiplex::TopRearLeft)] =
        Set(-trim_pitch + trim_roll - trim_yaw,
            u_thrust - u_pitch + u_roll - u_yaw);

    //(top) rear right
    value[self->MultiplexValue(X4X8Multiplex::TopRearRight)] =
        Set(-trim_pitch - trim_roll + trim_yaw,
            u_thrust - u_pitch - u_roll + u_yaw);
  }

  if (nb_mot == 8) {
    // bottom front left
    value[self->MultiplexValue(X4X8Multiplex::BottomFrontLeft)] = Set(
        trim_pitch + trim_roll - trim_yaw, u_thrust + u_pitch + u_roll - u_yaw);

    // bottom front right
    value[self->MultiplexValue(X4X8Multiplex::BottomFrontRight)] = Set(
        trim_pitch - trim_roll + trim_yaw, u_thrust + u_pitch - u_roll + u_yaw);

    // bottom rear left
    value[self->MultiplexValue(X4X8Multiplex::BottomRearLeft)] =
        Set(-trim_pitch + trim_roll + trim_yaw,
            u_thrust - u_pitch + u_roll + u_yaw);

    // bottom rear right
    value[self->MultiplexValue(X4X8Multiplex::BottomRearRight)] =
        Set(-trim_pitch - trim_roll - trim_yaw,
            u_thrust - u_pitch - u_roll - u_yaw);
  }

  // on prend une fois pour toute le mutex et on fait des accès directs
  output->GetMutex();
  for (int i = 0; i < nb_mot; i++)
    output->SetValueNoMutex(i, 0, value[i]);
  output->ReleaseMutex();

  output->SetDataTime(data->DataTime());

  self->ProcessUpdate(output);
}

float X4X8Multiplex_impl::Set(float trim, float u) {
  float value = trim;

  if (u > 0) {
    value += sqrtf(u);
  }

  return value;
}

string X4X8Multiplex_impl::MotorName(int index) {
  switch (nb_mot) {
  case 4: {
    switch (index) {
    case 0:
      return "front left";
    case 1:
      return "front rigth";
    case 2:
      return "rear left";
    case 3:
      return "rear rigth";
    default:
      return "unammed motor";
    }
  }
  case 8: {
    switch (index) {
    case 0:
      return "top front left";
    case 1:
      return "top front rigth";
    case 2:
      return "top rear left";
    case 3:
      return "top rear rigth";
    case 4:
      return "bottom front left";
    case 5:
      return "bottom front rigth";
    case 6:
      return "bottom rear left";
    case 7:
      return "bottom rear rigth";
    default:
      return "unammed motor";
    }
  }
  default: { return "unammed motor"; }
  }
}
