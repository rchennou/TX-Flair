// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   Simulator_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe de base du Simulator
//
/*********************************************************************/

#include "Simulator_impl.h"
#include "Simulator.h"
#include "Euler.h"
#ifdef GL
#include "Gui.h"
#include "Gui_impl.h"
#endif
#include "Model.h"
#include "Model_impl.h"
#include <unistd.h>

using namespace flair::core;
using namespace flair::simulator;

Simulator_impl::Simulator_impl(Simulator *self, int optitrack_mstime,
                               float yaw_deg)
    : vrpn_Connection_IP(), Thread(self, "simulator", 1) {
  this->self = self;
  this->optitrack_mstime = optitrack_mstime;
  yaw_rad = Euler::ToRadian(yaw_deg);
}

Simulator_impl::~Simulator_impl() {
  // printf("del Simulator_impl\n");

  SafeStop();
  Join();

  for (size_t i = 0; i < models.size(); i++) {
    models.at(i)->pimpl_->SafeStop();
    models.at(i)->pimpl_->Join();
    delete models.at(i);
  }

#ifdef GL
  if (getGui() != NULL)
    delete getGui();
#endif

  // printf("del Simulator_impl ok\n");
}

void Simulator_impl::Run(void) {
  SetPeriodMS(optitrack_mstime);

  while (ToBeStopped() == false) {
    WaitPeriod();
    // printf("%lld\n",GetTime());
    mainloop();
    for (size_t i = 0; i < models.size(); i++) {
      models.at(i)->pimpl_->mainloop();
    }
  }
}

void Simulator_impl::RunSimu(void) {
  if (models.size() == 0) {
    self->Err("No model to run\n");
    return;
  }

  for (size_t i = 0; i < models.size(); i++) {
    models.at(i)->pimpl_->Start();
  }

  Start();

#ifdef GL
  if (getGui() != NULL) {
    getGui()->pimpl_->RunGui(models, objects);
  } else
#endif
  {
    models.at(0)->pimpl_->Join();
  }

  SafeStop();
  Join();
}
