// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/03
//  filename:   VrpnClient_impl.h
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

#ifndef VRPNCLIENT_IMPL_H
#define VRPNCLIENT_IMPL_H

#include <string>
#include <vector>

namespace flair {
namespace core {
class OneAxisRotation;
class Vector3D;
class Quaternion;
class Mutex;
class SerialPort;
}
namespace gui {
class TabWidget;
class Tab;
class Layout;
}
namespace sensor {
class VrpnClient;
class VrpnObject;
}
}

class VrpnObject_impl;
class vrpn_Connection;

class VrpnClient_impl {
public:
  VrpnClient_impl(flair::sensor::VrpnClient *self, std::string name,
                  std::string address, uint16_t us_period);
  VrpnClient_impl(flair::sensor::VrpnClient *self, std::string name,
                  flair::core::SerialPort *serialport, uint16_t us_period);
  ~VrpnClient_impl();
  void AddTrackable(flair::sensor::VrpnObject *obj);    // normal
  void RemoveTrackable(flair::sensor::VrpnObject *obj); // normal
  void AddTrackable(VrpnObject_impl *obj, uint8_t id);  // xbee
  void RemoveTrackable(VrpnObject_impl *obj);           // xbee
  void ComputeRotations(flair::core::Vector3D &point);
  void ComputeRotations(flair::core::Quaternion &quat);
  bool UseXbee(void);
  void Run(void);
  flair::gui::Tab *setup_tab;
  flair::gui::TabWidget *tab;
  vrpn_Connection *connection;

private:
  flair::sensor::VrpnClient *self;
  flair::core::Mutex *mutex;
  uint16_t us_period;
  std::vector<flair::sensor::VrpnObject *> trackables;
  typedef struct xbee_object {
    VrpnObject_impl *vrpnobject;
    uint8_t id;
  } xbee_object;

  std::vector<xbee_object> xbee_objects;
  flair::gui::Tab *main_tab;
  flair::core::OneAxisRotation *rotation_1, *rotation_2;
  flair::core::SerialPort *serialport;
};

#endif // VRPNCLIENT_IMPL_H
