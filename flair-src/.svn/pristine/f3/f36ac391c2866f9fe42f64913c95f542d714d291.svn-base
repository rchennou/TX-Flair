// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/03
//  filename:   VrpnClient_impl.cpp
//
//  author:     César Richard, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet se connectant au serveur vrpn
//
//
/*********************************************************************/

#include "VrpnClient.h"
#include "VrpnClient_impl.h"
#include "VrpnObject.h"
#include "VrpnObject_impl.h"
#include <SerialPort.h>
#include <vrpn_Connection.h>
#include <FrameworkManager.h>
#include <TabWidget.h>
#include <Tab.h>
#include <GridLayout.h>
#include <OneAxisRotation.h>
#include <Vector3D.h>
#include <Quaternion.h>
#include <Mutex.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

using std::string;
using std::vector;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;

VrpnClient_impl::VrpnClient_impl(VrpnClient *self, std::string name,
                                 std::string address, uint16_t us_period) {
  this->us_period = us_period;
  this->self = self;
  serialport = NULL;

  mutex = new Mutex(self, name);

  connection = vrpn_get_connection_by_name(address.c_str());

  // station sol
  main_tab = new Tab(getFrameworkManager()->GetTabWidget(), name);
  tab = new TabWidget(main_tab->NewRow(), name);
  setup_tab = new Tab(tab, "Reglages");

  rotation_1 = new OneAxisRotation(setup_tab->NewRow(), "post rotation 1");
  rotation_2 = new OneAxisRotation(setup_tab->NewRow(), "post rotation 2");
}

VrpnClient_impl::VrpnClient_impl(VrpnClient *self, std::string name,
                                 SerialPort *serialport, uint16_t us_period) {
  this->us_period = us_period;
  this->self = self;
  this->serialport = serialport;
  connection = NULL;
  mutex = new Mutex(self, name);

  serialport->SetBaudrate(111111);
  serialport->SetRxTimeout(us_period * 1000);

  // station sol
  main_tab = new Tab(getFrameworkManager()->GetTabWidget(), name);
  tab = new TabWidget(main_tab->NewRow(), name);
  setup_tab = new Tab(tab, "Reglages");

  rotation_1 = new OneAxisRotation(setup_tab->NewRow(), "post rotation 1");
  rotation_2 = new OneAxisRotation(setup_tab->NewRow(), "post rotation 2");
}

VrpnClient_impl::~VrpnClient_impl() {
  if (!UseXbee()) {
    // on fait une copie car le delete touche a xbee_objects_copy via
    // RemoveTrackable
    vector<VrpnObject *> trackables_copy = trackables;
    for (unsigned int i = 0; i < trackables_copy.size(); i++)
      delete trackables_copy.at(i);
    // trackables.clear();
  } else {
    // on fait une copie car le delete touche a xbee_objects_copy via
    // RemoveTrackable
    vector<xbee_object> xbee_objects_copy = xbee_objects;
    for (unsigned int i = 0; i < xbee_objects_copy.size(); i++)
      delete xbee_objects_copy.at(i).vrpnobject->self;
  }

  delete main_tab;

  if (!UseXbee()) {
    // it will automatically delete connection
    connection->removeReference();
  }
}

void VrpnClient_impl::ComputeRotations(Vector3D &point) {
  rotation_1->ComputeRotation(point);
  rotation_2->ComputeRotation(point);
}

void VrpnClient_impl::ComputeRotations(Quaternion &quat) {
  rotation_1->ComputeRotation(quat);
  rotation_2->ComputeRotation(quat);
}

void VrpnClient_impl::AddTrackable(VrpnObject *obj) {
  mutex->GetMutex();
  trackables.push_back(obj);
  mutex->ReleaseMutex();
}

void VrpnClient_impl::RemoveTrackable(VrpnObject *obj) {
  mutex->GetMutex();
  for (vector<VrpnObject *>::iterator it = trackables.begin();
       it < trackables.end(); it++) {
    if (*it == obj) {
      trackables.erase(it);
      break;
    }
  }
  mutex->ReleaseMutex();
}

void VrpnClient_impl::AddTrackable(VrpnObject_impl *obj, uint8_t id) {
  xbee_object tmp;
  tmp.vrpnobject = obj;
  tmp.id = id;
  mutex->GetMutex();
  xbee_objects.push_back(tmp);
  mutex->ReleaseMutex();
}

void VrpnClient_impl::RemoveTrackable(VrpnObject_impl *obj) {
  mutex->GetMutex();
  for (vector<xbee_object>::iterator it = xbee_objects.begin();
       it < xbee_objects.end(); it++) {
    if ((*it).vrpnobject == obj) {
      xbee_objects.erase(it);
      break;
    }
  }
  mutex->ReleaseMutex();
}

bool VrpnClient_impl::UseXbee(void) {
  if (connection == NULL) {
    return true;
  } else {
    return false;
  }
}

void VrpnClient_impl::Run(void) {
  while (!self->ToBeStopped()) {
    if (UseXbee()) {
      ssize_t read = 0;
      uint8_t response[38] = {0};

      read = serialport->Read(response, sizeof(response));
      if (read > 0 && read != sizeof(response))
        read += serialport->Read(&response[read], sizeof(response) - read);
      // int temps=(float)self->GetTime()/(1000*1000);
      // self->Printf("%i %i %i\n",temps-last,temps,last);
      // last=temps;
      if (read < 0) {
        // self->Warn("erreur rt_dev_read (%s)\n",strerror(-read));
      } else if (read != sizeof(response)) {
        self->Warn("erreur rt_dev_read %i/%i\n", read, sizeof(response));
      } else {
        // for(ssize_t i=0;i<read;i++) printf("%x ",response[i]);
        // printf("\n");
        uint8_t checksum = 0;
        for (ssize_t i = 3; i < read; i++)
          checksum += response[i];
        if (checksum != 255) {
          self->Err("checksum error\n");
        } else {
          vrpn_TRACKERCB t;
          float pos[3];
          float quat[4];
          uint8_t id = response[8];

          mutex->GetMutex();
          if (id < xbee_objects.size()) {
            memcpy(pos, &response[9], sizeof(pos));
            memcpy(quat, &response[9] + sizeof(pos), sizeof(quat));
            for (int i = 0; i < 3; i++)
              t.pos[i] = pos[i];
            for (int i = 0; i < 4; i++)
              t.quat[i] = quat[i];
            if (fabs(pos[0] > 10) || fabs(pos[1] > 10) || fabs(pos[2] > 10)) {
              printf("prob pos %f %f %f\n", pos[0], pos[1], pos[2]);
            } else {
              // self->Printf("%i %f %f %f
              // %f\n",id,pos[0],pos[1],pos[2],(float)self->GetTime()/(1000*1000));
              VrpnObject_impl::handle_pos(xbee_objects.at(id).vrpnobject, t);
            }
          }
          mutex->ReleaseMutex();
        }
      }
    } else {
      connection->mainloop();
      mutex->GetMutex();
      for (unsigned int i = 0; i < trackables.size(); i++)
        trackables.at(i)->mainloop();
      mutex->ReleaseMutex();

      self->SleepUS(us_period);
    }
  }
}
