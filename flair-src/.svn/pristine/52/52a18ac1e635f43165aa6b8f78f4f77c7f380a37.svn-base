// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/11/14
//  filename:   Bldc_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Virtual class for brushless drivers
//
//
/*********************************************************************/
#include "Bldc_impl.h"
#include "Bldc.h"
#include <GridLayout.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <cvmatrix.h>
#include <Label.h>
#include <PushButton.h>
#include <DataPlot1D.h>
#include <TabWidget.h>
#include <Tab.h>
#include <FrameworkManager.h>
#include <sstream>

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::actuator;

Bldc_impl::Bldc_impl(Bldc *self, Layout *layout, string name,
                     uint8_t motors_count) {
  this->self = self;
  this->motors_count = motors_count;
  this->layout = layout;
  are_enabled = false;
  is_running = false;
  tested_motor = -1;

  values = (float *)malloc(motors_count * sizeof(float));
  power = (float *)malloc(motors_count * sizeof(float));
  for (int i = 0; i < motors_count; i++)
    power[i] = 1;

  // station sol
  GroupBox *groupbox = new GroupBox(layout->NewRow(), "bldc");
  flight_time = new Label(groupbox->NewRow(), "flight time");
  min_value = new DoubleSpinBox(groupbox->NewRow(), "min value:", 0, 1, .1, 2);
  max_value =
      new DoubleSpinBox(groupbox->LastRowLastCol(), "max value:", 0, 1, .1, 2);
  test_value =
      new DoubleSpinBox(groupbox->LastRowLastCol(), "test value:", 0, 1, 0.1);

  int index = 0;
  button_test = (PushButton **)malloc(motors_count * sizeof(PushButton *));
  for (int i = 0; i < motors_count / 2; i++) {
    for (int j = 0; j < 2; j++) {
      ostringstream test_name;
      test_name << "test motor " << index;
      button_test[index] =
          new PushButton(groupbox->At(2 + i, j), test_name.str());
      index++;
    }
  }

  // flight time
  FILE *file;
  file = fopen("/etc/flight_time", "r");
  if (file == NULL) {
    time_sec = 0;
  } else {
    char ligne[32];
    fgets(ligne, 32, file);
    time_sec = atoi(ligne);
    fclose(file);
  }
  flight_time->SetText("total flight time: %is = %imin = %ih\n", time_sec,
                       time_sec / 60, time_sec / 3600);
}

Bldc_impl::Bldc_impl(Bldc *self, uint8_t motors_count) {
  this->self = self;
  this->motors_count = motors_count;
  values = NULL;
  button_test = NULL;
  power = NULL;
}

Bldc_impl::~Bldc_impl() {
  if (values != NULL)
    free(values);
  if (button_test != NULL)
    free(button_test);
  if (power != NULL)
    free(power);
}

void Bldc_impl::UseDefaultPlot(TabWidget *tab) {
  Tab *plot_tab = new Tab(tab, "speeds");
  plots = new DataPlot1D(plot_tab->NewRow(), "values", 0, 1);
  for (int i = 0; i < motors_count; i++) {
    plots->AddCurve(self->output->Element(i));
  }
}

void Bldc_impl::UpdateFrom(const io_data *data) {
  cvmatrix *input = (cvmatrix *)data;
  bool is_motor_running = false;

  if (values == NULL)
    return; // nothing to do in simulator

  if (input->Rows() != motors_count) {
    self->Err("nb motors mismatch\n");
    return;
  }

  input->GetMutex();
  for (int i = 0; i < motors_count; i++) {
    if (input->ValueNoMutex(i, 0) != 0)
      is_motor_running = true;
    if (are_enabled) {
      // Printf("%i %f %f\n",i,input->ValueNoMutex(i,0),power[i]);
      values[i] = power[i] * Sat(input->ValueNoMutex(i, 0));
      // Printf("%i %f\n",i,values[i]);
    } else {
      values[i] = 0;
    }
  }
  input->ReleaseMutex();

  if (are_enabled && is_motor_running && !is_running) {
    flight_start_time = GetTime();
    is_running = true;
  }
  if ((!are_enabled || !is_motor_running) && is_running) {
    Time now = GetTime();
    int t_sec;
    FILE *file;
    char ligne[32];

    t_sec = (now - flight_start_time) / 1000000000;
    time_sec += t_sec;

    Printf("temps de vol: %is = %imin\n", t_sec, t_sec / 60);
    // Printf("temps de vol total: %is = %imin =
    // %ih\n",time_sec,time_sec/60,time_sec/3600);
    flight_time->SetText("total flight time: %is = %imin = %ih\n", time_sec,
                         time_sec / 60, time_sec / 3600);

    file = fopen("/etc/flight_time", "w");
    if (file == NULL) {
      Printf("Erreur a l'ouverture du fichier d'info vol\n");
    } else {
      sprintf(ligne, "%i", time_sec);
      fputs(ligne, file);
      fclose(file);
    }
    is_running = false;
  }

  for (int i = 0; i < motors_count; i++) {
    if (button_test[i]->Clicked() == true) {
      if (!are_enabled) {
        tested_motor = i;
        test_start_time = GetTime();
        LockUserInterface();
      } else {
        self->Warn("testing motor is not possible when enabled\n");
      }
    }
  }
  if (tested_motor != -1) {
    for (int i = 0; i < motors_count; i++) {
      values[i] = 0;
    }
    values[tested_motor] = test_value->Value();

    if (GetTime() > (test_start_time + 2 * 1000000000)) {
      tested_motor = -1;
      UnlockUserInterface();
    }
  }

  self->SetMotors(values);
  self->output->SetDataTime(data->DataTime());
  self->ProcessUpdate(self->output);
}

float Bldc_impl::Sat(float value) {
  float result = value;

  if (result < min_value->Value()) {
    result = min_value->Value();
  }
  if (result > max_value->Value()) {
    result = max_value->Value();
  }

  return result;
}

void Bldc_impl::LockUserInterface(void) const { layout->setEnabled(false); }

void Bldc_impl::UnlockUserInterface(void) const { layout->setEnabled(true); }
