// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/29
//  filename:   BlCtrlV2_x4_speed.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les moteurs i2c, controle en vitesse
//
//
/*********************************************************************/

#include "BlCtrlV2_x4_speed.h"
#include "I2cPort.h"
#include <TabWidget.h>
#include <Tab.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <DoubleSpinBox.h>
#include <ComboBox.h>
#include <PushButton.h>
#include <cvmatrix.h>
#include <Mutex.h>
#include <FrameworkManager.h>
#include <DataPlot1D.h>
#include <math.h>
#include <string.h>

#define TAU_US 1000

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace actuator {
BlCtrlV2_x4_speed::BlCtrlV2_x4_speed(FrameworkManager *parent, string name,
                                     I2cPort *i2cport, uint8_t base_address,
                                     uint8_t priority)
    : Thread(parent, name, priority), IODevice(parent, name) {
  this->i2cport = i2cport;
  slave_address = base_address;
  tested_motor = -1;
  enabled = false;
  int_av_g = 0;
  int_av_d = 0;
  int_ar_g = 0;
  int_ar_d = 0;

  // flight time
  FILE *file;
  file = fopen("/etc/flight_time", "r");
  if (file == NULL) {
    Printf("fichier d'info de vol vide\n");
    time_sec = 0;
  } else {
    char ligne[32];
    fgets(ligne, 32, file);
    time_sec = atoi(ligne);
    Printf("temps de vol total: %is = %imin = %ih\n", time_sec, time_sec / 60,
           time_sec / 3600);
    fclose(file);
  }

  // station sol
  main_tab = new Tab(parent->GetTabWidget(), name);
  tab = new TabWidget(main_tab->NewRow(), name);
  Tab *sensor_tab = new Tab(tab, "Reglages");
  reglages_groupbox = new GroupBox(sensor_tab->NewRow(), name);
  poles = new SpinBox(reglages_groupbox->NewRow(), "nb poles", 0, 255, 1);
  kp = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(), "kp", 0., 255,
                         0.001, 4);
  ki = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(), "ki", 0., 255,
                         0.001, 4);
  min = new SpinBox(reglages_groupbox->NewRow(), "min pwm", 0., 2048, 1);
  max =
      new SpinBox(reglages_groupbox->LastRowLastCol(), "max pwm", 0., 2048, 1);
  test = new SpinBox(reglages_groupbox->LastRowLastCol(), "test value", 0.,
                     2048, 1);
  start_value = new SpinBox(reglages_groupbox->NewRow(), "valeur demarrage", 0,
                            10000, 10);
  trim = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(), "pas decollage",
                           0, 1000, .1);

  av_g = new ComboBox(reglages_groupbox->NewRow(), "avant gauche");
  av_g->AddItem("1");
  av_g->AddItem("2");
  av_g->AddItem("3");
  av_g->AddItem("4");
  button_avg = new PushButton(reglages_groupbox->LastRowLastCol(), "test avg");

  av_d = new ComboBox(reglages_groupbox->LastRowLastCol(), "avant droite:");
  av_d->AddItem("1");
  av_d->AddItem("2");
  av_d->AddItem("3");
  av_d->AddItem("4");
  button_avd = new PushButton(reglages_groupbox->LastRowLastCol(), "test avd");

  ar_g = new ComboBox(reglages_groupbox->NewRow(), "arriere gauche:");
  ar_g->AddItem("1");
  ar_g->AddItem("2");
  ar_g->AddItem("3");
  ar_g->AddItem("4");
  button_arg = new PushButton(reglages_groupbox->LastRowLastCol(), "test arg");

  ar_d = new ComboBox(reglages_groupbox->LastRowLastCol(), "arriere droite:");
  ar_d->AddItem("1");
  ar_d->AddItem("2");
  ar_d->AddItem("3");
  ar_d->AddItem("4");
  button_ard = new PushButton(reglages_groupbox->LastRowLastCol(), "test ard");

  pas = new ComboBox(reglages_groupbox->NewRow(), "pas helice avant gauche:");
  pas->AddItem("normal");
  pas->AddItem("inverse");

  input = new cvmatrix((IODevice *)this, 8, 1, floatType);

  cvmatrix_descriptor *desc = new cvmatrix_descriptor(4, 2);
  desc->SetElementName(0, 0, "avant gauche");
  desc->SetElementName(1, 0, "arriere droite");
  desc->SetElementName(2, 0, "avant droite");
  desc->SetElementName(3, 0, "arriere gauche");

  desc->SetElementName(0, 1, "cons avant gauche");
  desc->SetElementName(1, 1, "cons arriere droite");
  desc->SetElementName(2, 1, "cons avant droite");
  desc->SetElementName(3, 1, "cons arriere gauche");
  output = new cvmatrix((IODevice *)this, desc, floatType);

  /*

  //le 3ieme lu est la tension batteire
          if(i2c_mutex!=NULL) i2c_mutex->GetMutex();
      uint16_t pwm_moteur;
      pwm_moteur=0;
      ssize_t read;
      uint8_t rx[8];
      SetSlave(slave_address);

      for(int j=0;j<10;j++)
      {


          WriteValue(pwm_moteur);


          read = rt_dev_read(i2c_fd, rx, sizeof(rx));

          if(read<0)
          {
              rt_printf("BlCtrlV2_x4_speed::BlCtrlV2_x4_speed: %s, erreur
  rt_dev_read (%s)\n",IODevice::ObjectName().c_str(),strerror(-read));
          }
          else if (read != sizeof(rx))
          {
              rt_printf("BlCtrlV2_x4_speed::BlCtrlV2_x4_speed: %s, erreur
  rt_dev_read %i/2\n",IODevice::ObjectName().c_str(),read);

          }
          for(int i=0;i<sizeof(rx);i++) printf("%i ",rx[i]);

          printf("\n");

      }

      if(i2c_mutex!=NULL) i2c_mutex->ReleaseMutex();*/
}

BlCtrlV2_x4_speed::~BlCtrlV2_x4_speed(void) {
  SafeStop();
  Join();
  delete main_tab;
}

void BlCtrlV2_x4_speed::UseDefaultPlot(void) {
  Tab *plot_tab = new Tab(tab, "Mesures");
  DataPlot1D *av_g_plot = new DataPlot1D(plot_tab->NewRow(), "avg", 0, 10000);
  av_g_plot->AddCurve(output->Element(0, 0));
  av_g_plot->AddCurve(output->Element(0, 1), DataPlot::Blue);
  DataPlot1D *av_d_plot =
      new DataPlot1D(plot_tab->LastRowLastCol(), "avd", 0, 10000);
  av_d_plot->AddCurve(output->Element(2, 0));
  av_d_plot->AddCurve(output->Element(2, 1), DataPlot::Blue);
  DataPlot1D *ar_g_plot = new DataPlot1D(plot_tab->NewRow(), "arg", 0, 10000);
  ar_g_plot->AddCurve(output->Element(3, 0));
  ar_g_plot->AddCurve(output->Element(3, 1), DataPlot::Blue);
  DataPlot1D *ar_d_plot =
      new DataPlot1D(plot_tab->LastRowLastCol(), "ard", 0, 10000);
  ar_d_plot->AddCurve(output->Element(1, 0));
  ar_d_plot->AddCurve(output->Element(1, 1), DataPlot::Blue);
}

float BlCtrlV2_x4_speed::TrimValue(void) { return (float)trim->Value(); }

int BlCtrlV2_x4_speed::StartValue(void) { return start_value->Value(); }

void BlCtrlV2_x4_speed::Run(void) {
  WarnUponSwitches(true);

  SetPeriodUS(TAU_US);

  while (!ToBeStopped()) {
    WaitPeriod();

    Update();
  }

  WarnUponSwitches(false);
}

void BlCtrlV2_x4_speed::Update(void) {
  float u_roll, u_pitch, u_yaw, u_gaz;
  float trim_roll, trim_pitch, trim_yaw;
  float pwm[4];
  uint16_t pwm_moteur[4];

  // on prend une fois pour toute le mutex et on fait des accès directs
  input->GetMutex();

  u_roll = input->ValueNoMutex(0, 0);
  u_pitch = input->ValueNoMutex(1, 0);
  u_yaw = input->ValueNoMutex(2, 0);
  u_gaz =
      input->ValueNoMutex(3, 0) +
      input->ValueNoMutex(7, 0) * input->ValueNoMutex(7, 0); // ugaz+trim*trim
  trim_roll = input->ValueNoMutex(4, 0);
  trim_pitch = input->ValueNoMutex(5, 0);
  trim_yaw = input->ValueNoMutex(6, 0);

  input->ReleaseMutex();

  if (pas->CurrentIndex() == 1) {
    trim_yaw = -trim_yaw;
    u_yaw = -u_yaw;
  }

  // rt_printf("%f %f %f %f\n",u_roll,u_pitch,u_yaw,u_gaz);
  // if(u_gaz!=0) rt_printf("gaz: %f\n",u_gaz);

  // avant gauche
  if (u_gaz + u_pitch + u_roll + u_yaw > 0) {
    pwm[0] = trim_pitch + trim_roll + trim_yaw +
             sqrtf(u_gaz + u_pitch + u_roll + u_yaw);
  } else {
    pwm[0] = trim_pitch + trim_roll + trim_yaw;
  }

  // arriere gauche
  if (u_gaz - u_pitch + u_roll - u_yaw > 0) {
    pwm[3] = -trim_pitch + trim_roll - trim_yaw +
             sqrtf(u_gaz - u_pitch + u_roll - u_yaw);
  } else {
    pwm[3] = -trim_pitch + trim_roll - trim_yaw;
  }

  // arriere droit
  if (u_gaz - u_pitch - u_roll + u_yaw > 0) {
    pwm[1] = -trim_pitch - trim_roll + trim_yaw +
             sqrtf(u_gaz - u_pitch - u_roll + u_yaw);
  } else {
    pwm[1] = -trim_pitch - trim_roll + trim_yaw;
  }

  // avant droit
  if (u_gaz + u_pitch - u_roll - u_yaw > 0) {
    pwm[2] = trim_pitch - trim_roll - trim_yaw +
             sqrtf(u_gaz + u_pitch - u_roll - u_yaw);
  } else {
    pwm[2] = trim_pitch - trim_roll - trim_yaw;
  }

  int_av_g += ki->Value() * (pwm[0] - speed_av_g);
  pwm[0] = kp->Value() * (pwm[0] - speed_av_g) + int_av_g;

  int_ar_g += ki->Value() * (pwm[3] - speed_ar_g);
  pwm[3] = kp->Value() * (pwm[3] - speed_ar_g) + int_ar_g;

  int_ar_d += ki->Value() * (pwm[1] - speed_ar_d);
  pwm[1] = kp->Value() * (pwm[1] - speed_ar_d) + int_ar_d;

  int_av_d += ki->Value() * (pwm[2] - speed_av_d);
  pwm[2] = kp->Value() * (pwm[2] - speed_av_d) + int_av_d;

  // rt_printf("%f\n",pwm[0]);
  for (int i = 0; i < 4; i++)
    pwm_moteur[i] = SatPWM(pwm[i], min->Value(), max->Value());

  if (button_avg->Clicked() == true) {
    tested_motor = 0;
    StartTest();
  }
  if (button_avd->Clicked() == true) {
    tested_motor = 2;
    StartTest();
  }
  if (button_arg->Clicked() == true) {
    tested_motor = 3;
    StartTest();
  }
  if (button_ard->Clicked() == true) {
    tested_motor = 1;
    StartTest();
  }

  if (tested_motor != -1) {
    for (int i = 0; i < 4; i++) {
      pwm_moteur[i] = 0;
    }
    pwm_moteur[tested_motor] = (uint16_t)test->Value();

    if (GetTime() > (start_time + 2 * 1000000000))
      StopTest();
  }

  i2cport->GetMutex();

  if (enabled == true) {
    i2cport->SetSlave(slave_address + av_g->CurrentIndex());
    WriteValue(pwm_moteur[0]);

    i2cport->SetSlave(slave_address + av_d->CurrentIndex());
    WriteValue(pwm_moteur[2]);

    i2cport->SetSlave(slave_address + ar_g->CurrentIndex());
    WriteValue(pwm_moteur[3]);

    i2cport->SetSlave(slave_address + ar_d->CurrentIndex());
    WriteValue(pwm_moteur[1]);

  } else {
    for (int i = 0; i < 4; i++) {
      i2cport->SetSlave(slave_address + i);
      WriteValue(0);
    }
    int_av_g = 0;
    int_av_d = 0;
    int_ar_g = 0;
    int_ar_d = 0;
  }

  i2cport->SetSlave(slave_address + av_g->CurrentIndex());
  speed_av_g = GetSpeed();

  i2cport->SetSlave(slave_address + av_d->CurrentIndex());
  speed_av_d = GetSpeed();

  i2cport->SetSlave(slave_address + ar_g->CurrentIndex());
  speed_ar_g = GetSpeed();

  i2cport->SetSlave(slave_address + ar_d->CurrentIndex());
  speed_ar_d = GetSpeed();

  i2cport->ReleaseMutex();

  // on prend une fois pour toute le mutex et on fait des accès directs
  output->GetMutex();
  output->SetValueNoMutex(0, 0, speed_av_g);
  output->SetValueNoMutex(1, 0, speed_ar_d);
  output->SetValueNoMutex(2, 0, speed_av_d);
  output->SetValueNoMutex(3, 0, speed_ar_g);
  // rt_printf("%i %i %i
  // %i\n",pwm_moteur[0],pwm_moteur[1],pwm_moteur[2],pwm_moteur[3]);
  output->ReleaseMutex();

  output->SetDataTime(GetTime());
  ProcessUpdate(output);
}

void BlCtrlV2_x4_speed::StartTest(void) {
  start_time = GetTime();
  SetEnabled(true);
}

void BlCtrlV2_x4_speed::StopTest(void) {
  SetEnabled(false);
  tested_motor = -1;
}

uint16_t BlCtrlV2_x4_speed::SatPWM(float vel_cons, uint16_t min, uint16_t max) {
  uint16_t sat_value = (uint16_t)vel_cons;

  if (vel_cons > ((float)sat_value + 0.5))
    sat_value++;

  if (vel_cons < (float)min)
    sat_value = min;
  if (vel_cons > (float)max)
    sat_value = max;

  return sat_value;
}

void BlCtrlV2_x4_speed::LockUserInterface(void) {
  reglages_groupbox->setEnabled(false);
}

void BlCtrlV2_x4_speed::UnlockUserInterface(void) {
  reglages_groupbox->setEnabled(true);
}

void BlCtrlV2_x4_speed::SetEnabled(bool status) {
  enabled = status;
  if (enabled == true) {
    LockUserInterface();

    flight_start_time = GetTime();
  } else {
    UnlockUserInterface();

    Time now = GetTime();
    int t_sec;
    FILE *file;
    char ligne[32];

    t_sec = (now - flight_start_time) / 1000000000;
    time_sec += t_sec;

    Printf("temps de vol: %is = %imin\n", t_sec, t_sec / 60);
    Printf("temps de vol total: %is = %imin = %ih\n", time_sec, time_sec / 60,
           time_sec / 3600);

    file = fopen("/etc/flight_time", "w");
    if (file == NULL) {
      Thread::Err("Erreur a l'ouverture du fichier d'info vol\n");
    } else {
      sprintf(ligne, "%i", time_sec);
      fputs(ligne, file);
      fclose(file);
    }
  }
}

void BlCtrlV2_x4_speed::SetUroll(float value) { input->SetValue(0, 0, value); }

void BlCtrlV2_x4_speed::SetUpitch(float value) { input->SetValue(1, 0, value); }

void BlCtrlV2_x4_speed::SetUyaw(float value) { input->SetValue(2, 0, value); }

void BlCtrlV2_x4_speed::SetUgaz(float value) { input->SetValue(3, 0, value); }

void BlCtrlV2_x4_speed::SetRollTrim(float value) {
  input->SetValue(4, 0, value);
}

void BlCtrlV2_x4_speed::SetPitchTrim(float value) {
  input->SetValue(5, 0, value);
}

void BlCtrlV2_x4_speed::SetYawTrim(float value) {
  input->SetValue(6, 0, value);
}

void BlCtrlV2_x4_speed::SetGazTrim(float value) {
  input->SetValue(7, 0, value);
}

void BlCtrlV2_x4_speed::WriteValue(uint16_t value) {
  unsigned char tx[2];
  ssize_t written;

  tx[0] = (unsigned char)(value >> 3); // msb
  tx[1] = 16 + 8 + (value & 0x07);     // 16+8 pour recuperer la vitesse
  written = i2cport->Write(tx, 2);
  if (written < 0) {
    Thread::Err("erreur rt_dev_write (%s)\n", strerror(-written));
  } else if (written != 2) {
    Thread::Err("erreur rt_dev_write %i/2\n", written);
  }
}

float BlCtrlV2_x4_speed::GetSpeed(void) {
  ssize_t read;
  uint8_t value;
  read = i2cport->Read(&value, 1);

  if (read < 0) {
    Thread::Err("erreur rt_dev_read (%s)\n", strerror(-read));
  } else if (read != 1) {
    Thread::Err("erreur rt_dev_read %i/2\n", read);
  }

  return value * 780. / poles->Value();
}

} // end namespace actuator
} // end namespace framewor
