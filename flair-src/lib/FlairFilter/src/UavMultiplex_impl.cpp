// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/11
//  filename:   UavMultiplex_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining uav multiplexing
//
//
/*********************************************************************/

#include "UavMultiplex_impl.h"
#include "UavMultiplex.h"
#include <cvmatrix.h>
#include <FrameworkManager.h>
#include <TabWidget.h>
#include <Tab.h>
#include <GridLayout.h>
#include <ComboBox.h>
#include <GroupBox.h>
#include <sstream>

using std::string;
using std::ostringstream;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

UavMultiplex_impl::UavMultiplex_impl(const FrameworkManager *parent,
                                     UavMultiplex *self, std::string name) {
  input = new cvmatrix(self, 7, 1, floatType);
  multiplexcombobox = NULL;
  this->self = self;

  // station sol
  main_tab = new Tab(parent->GetTabWidget(), name);
  tabwidget = new TabWidget(main_tab->NewRow(), "UavMultiplex");
  setup_tab = new Tab(tabwidget, "Setup");
}

UavMultiplex_impl::~UavMultiplex_impl(void) {
  delete main_tab;
  if (multiplexcombobox != NULL)
    free(multiplexcombobox);
}

void UavMultiplex_impl::SetMultiplexComboBox(string name, int index) {
  // we do not know motorcount at constructor time, so allocation is done here
  if (multiplexcombobox == NULL) {
    multiplexcombobox =
        (ComboBox **)malloc(self->MotorsCount() * sizeof(ComboBox *));
    for (int i = 0; i < self->MotorsCount(); i++)
      multiplexcombobox[i] = NULL;
    groupbox = new GroupBox(setup_tab->NewRow(), "motor attribution");
  }
  if (index > self->MotorsCount()) {
    self->Err("index out of bound %i/%i\n", index, self->MotorsCount());
    return;
  }
  if (multiplexcombobox[index] != NULL) {
    self->Err("index already setup\n");
    return;
  }

  multiplexcombobox[index] =
      new ComboBox(groupbox->At(index / 4, index % 4), name);

  for (int i = 0; i < self->MotorsCount(); i++) {
    ostringstream oss;
    oss << i;
    multiplexcombobox[index]->AddItem(oss.str());
  }
}

int UavMultiplex_impl::MultiplexValue(int index) const {
  if (multiplexcombobox[index] != NULL) {
    return multiplexcombobox[index]->CurrentIndex();
  } else {
    self->Err("multiplex not setup for motor %i\n", index);
    return 0;
  }
}
