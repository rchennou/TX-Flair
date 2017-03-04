// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/03/31
//  filename:   DualShock3.h
//
//  authors:    pabr.org, Gildas Bayard
//              Copyright (c) 2010 pabr@pabr.org
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Sony DualShock3 host side driver class. Talks to target side
//  through ethernet.
//
//
/*********************************************************************/

#ifndef DUALSHOCK3_H
#define DUALSHOCK3_H

#include <HostEthController.h>

#include <stdint.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>
#include <usb.h>

namespace flair {
namespace core {
class FrameworkManager;
}
namespace gui {
class SpinBox;
class Label;
class CheckBox;
}
}

struct motion_dev;

namespace flair {
namespace sensor {
/*! \class DualShock3
*
* \brief Sony DualShock3 host side driver class. Talks to target side through
*ethernet.
*/
class DualShock3 : public HostEthController {
public:
  typedef enum { Usb, Bluetooth } ConnectionType_t;

  DualShock3(const core::FrameworkManager *parent, std::string name,
             std::string receiverAddress, int receiverPort,
             ConnectionType_t connectionType, uint32_t period = 10,
             uint32_t bitsPerAxis = 7, uint8_t priority = 0);
  ~DualShock3();

private:
  gui::SpinBox *deadZone;
  gui::CheckBox *enabled;
  gui::Label *batteryChargeLevel;
  ConnectionType_t connectionType;
  core::Time now;

  std::string GetAxisDescription(unsigned int axis);
  std::string GetButtonDescription(unsigned int button);
  void GetAxisData();
  void GetButtonData();
  bool IsDataFrameReady();
  void ProcessMessage(core::Message *controllerAction);

  void UpdateFrom(const core::io_data *data){};
  void fatal(const char *msg);
  int l2cap_listen(const bdaddr_t *bdaddr, unsigned short psm);
  struct motion_dev *accept_device(int csk, int isk);
  void hidp_trans(int csk, char *buf, int len);
  void setup_device(struct motion_dev *dev);
  bool parse_report_sixaxis_ds3(unsigned char *r, int len);
  int mystr2ba(const char *s, bdaddr_t *ba);
  char *myba2str(const bdaddr_t *ba);
  int8_t compute_dead_zone(int axis, unsigned char value);
  struct motion_dev *dev;
  int usb_fd;
  int isk;
  core::Time last_voltage_time;

  int8_t *datas;
  uint8_t dataSize;

  void usb_scan();
  void usb_pair_device(struct usb_device *dev, int itfnum);

  void rumble(uint8_t left_force, uint8_t left_timeout, uint8_t right_force,
              uint8_t right_timeout);
  void set_led(uint8_t led, uint8_t on_timeout, uint8_t off_timeout);
  char ledmask;
  uint8_t led1_on, led1_off, led2_on, led2_off, led3_on, led3_off, led4_on,
      led4_off;
};
}
}

#endif // DUALSHOCK3_H
