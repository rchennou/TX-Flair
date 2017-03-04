// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2015/03/30
//  filename:   DualShock3.h
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for host side remote controls that talks to target
//  side through ethernet connection
//
//
/*********************************************************************/
#include "DualShock3.h"
#include <Controller.h>
#include <cvmatrix.h>
#include <Tab.h>
#include <TabWidget.h>
#include <CheckBox.h>
#include <Label.h>
#include <DataPlot1D.h>
#include <SpinBox.h>
#include <GroupBox.h>
#include <FrameworkManager.h>
#include <Socket.h>
#include <sstream>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sstream>
#include <linux/input.h>
#include <linux/hidraw.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define USB_DIR_IN 0x80
#define USB_DIR_OUT 0
#define USB_GET_REPORT 0x01
#define USB_SET_REPORT 0x09
#define VENDOR_SONY 0x054c
#define PRODUCT_SIXAXIS_DS3 0x0268

#define L2CAP_PSM_HIDP_CTRL 0x11
#define L2CAP_PSM_HIDP_INTR 0x13

#define HIDP_TRANS_GET_REPORT 0x40
#define HIDP_TRANS_SET_REPORT 0x50
#define HIDP_DATA_RTYPE_OUTPUT 0x02
#define HIDP_DATA_RTYPE_FEATURE 0x03

#define SIXAXIS 1
#define DUALSHOCK3 2

#define X_AXIS_RANGE 127
#define Y_AXIS_RANGE 127

using namespace flair::core;
using namespace flair::gui;
using namespace std;

typedef struct motion_dev {
  int index;
  bdaddr_t addr;
  char type;
  int csk;
  int isk;
  struct motion_dev *next;
} motion_dev_t;

bdaddr_t bdaddr_any = {{0, 0, 0, 0, 0, 0}};

namespace flair {
namespace sensor {

DualShock3::DualShock3(const FrameworkManager *parent, string name,
                       string receiverAddress, int receiverPort,
                       ConnectionType_t _connectionType, uint32_t period,
                       uint32_t bitsPerAxis, uint8_t priority)
    : HostEthController(parent, name, receiverAddress, receiverPort, period,
                        bitsPerAxis, priority),
      connectionType(_connectionType) {
  controllerName = "DualShock3";
  last_voltage_time = 0;

  // axis stuff
  axisNumber = 4;
  nativeBitsPerAxis = 8;
  cvmatrix_descriptor *axisDescriptor = new cvmatrix_descriptor(axisNumber, 1);
  for (unsigned int i = 0; i < axisNumber; i++) {
    axisDescriptor->SetElementName(i, 0, GetAxisDescription(i));
  }
  axis = new cvmatrix((IODevice *)this, axisDescriptor, Int16Type);
  AddDataToLog(axis);

  // buttons stuff
  buttonNumber = 16;
  cvmatrix_descriptor *buttonDescriptor =
      new cvmatrix_descriptor(buttonNumber, 1);
  for (unsigned int i = 0; i < buttonNumber; i++) {
    buttonDescriptor->SetElementName(i, 0, GetButtonDescription(i));
  }
  button = new cvmatrix((IODevice *)this, buttonDescriptor, Int8Type);
  AddDataToLog(button);

  Tab *settingsTab = new Tab(tabWidget, "Settings");
  dataSize = 6;
  datas = new int8_t[dataSize];

  GroupBox *settingsGroupBox =
      new GroupBox(settingsTab->NewRow(), controllerName);
  deadZone =
      new SpinBox(settingsGroupBox->NewRow(), "dead zone:", -130, 130, 1);
  batteryChargeLevel =
      new Label(settingsGroupBox->LastRowLastCol(), "battery charge level");
  enabled = new CheckBox(settingsGroupBox->LastRowLastCol(), "enabled");

  if (connectionType == Bluetooth) {
    // init DS3
    usb_scan();

    int csk = l2cap_listen(&bdaddr_any, L2CAP_PSM_HIDP_CTRL);
    isk = l2cap_listen(&bdaddr_any, L2CAP_PSM_HIDP_INTR);

    if (csk >= 0 && isk >= 0)
      Printf("Waiting for Bluetooth connections.\n");
    else
      Thread::Err("Unable to listen on HID PSMs.\n");

    fd_set fds;
    FD_ZERO(&fds);

    if (csk >= 0)
      FD_SET(csk, &fds);
    if (select(csk + 1, &fds, NULL, NULL, NULL) < 0)
      Thread::Err("select\n");
    // Incoming connection ?

    if (csk >= 0 && FD_ISSET(csk, &fds)) {
      // printf("accept\n");
      dev = accept_device(csk, isk);
      setup_device(dev);
    }
  } else if (connectionType == Usb) {
    int nr, i;
    unsigned char buf[128];

    for (i = 0; i < 255; i++) {
      ostringstream dev_name;
      dev_name << "/dev/hidraw" << i;
      if ((usb_fd = open(dev_name.str().c_str(), O_RDONLY)) >= 0) {
        int res = 0;
        struct hidraw_devinfo info;

        res = ioctl(usb_fd, HIDIOCGRAWINFO, &info);
        if (res < 0) {
          Thread::Err("ioctl error (HIDIOCGRAWINFO) on %s\n",
                      dev_name.str().c_str());
        } else {
          // Printf("%x %x\n", info.vendor, info.product);
          if (info.vendor == 0x054c && info.product == 0x0268) {
            Printf("successfully opened %s\n", dev_name.str().c_str());
            Printf("Press PS button to turn the controller on\n");
            break;
          }
        }
        close(usb_fd);
      }
    }
    if (i == 255) {
      Thread::Err("sixad-raw::open(hidrawX) - failed to open hidraw device\n");
      return;
    }

    // block until PS button is pressed
    if ((nr = read(usb_fd, buf, sizeof(buf))) < 0) {
      Thread::Err("sixad-raw::read(fd) - failed to read from device\n");
    }

    if (nr < 49 || nr > 50) {
      Thread::Err("sixad-raw::read(fd) - not a sixaxis (nr = %i )\n", nr);
    }
  }
  ledmask = 0;
}

DualShock3::~DualShock3() {
  if (connectionType == Usb) {
    close(usb_fd);
  }
  if (connectionType == Bluetooth) {
    if (!popen("/etc/init.d/bluetooth restart", "r"))
      Thread::Warn("Could not restart bluetooth service\n");
  }
}

string DualShock3::GetAxisDescription(unsigned int axis) {
  string description;

  switch (axis) {
  case 0:
    description = "left stick x-axis";
    break;
  case 1:
    description = "left stick y-axis";
    break;
  case 2:
    description = "right stick x-axis";
    break;
  case 3:
    description = "right stick y-axis";
    break;
  }
  return description;
}

string DualShock3::GetButtonDescription(unsigned int button) {
  switch (button) {
  case 0:
    return "start";
    break;
  case 1:
    return "select";
    break;
  case 2:
    return "square";
    break;
  case 3:
    return "triangle";
    break;
  case 4:
    return "circle";
    break;
  case 5:
    return "cross";
    break;
  case 6:
    return "left 1";
    break;
  case 7:
    return "left 2";
    break;
  case 8:
    return "left 3";
    break;
  case 9:
    return "right 1";
    break;
  case 10:
    return "right 2";
    break;
  case 11:
    return "right 3";
    break;
  case 12:
    return "up";
    break;
  case 13:
    return "down";
    break;
  case 14:
    return "left";
    break;
  case 15:
    return "right";
    break;
  }
}

bool DualShock3::IsDataFrameReady() {
  unsigned char report[256];
  unsigned char tmp_report[256];

  if (!enabled->IsChecked()) {
    meaningfulDataAvailable = false;
    usleep(100000);
    return false;
  }
  now = GetTime();
  if (connectionType == Bluetooth) {
    fd_set fds;
    FD_ZERO(&fds);
    int fdmax = 0; /*
     if ( isk >= 0 ) FD_SET(isk, &fds);
     if ( isk > fdmax ) fdmax = isk;
*/
    FD_SET(dev->isk, &fds);
    if (dev->isk > fdmax)
      fdmax = dev->isk;

    if (select(fdmax + 1, &fds, NULL, NULL, NULL) < 0)
      fatal("select");

    // Incoming input report ?
    if (FD_ISSET(dev->isk, &fds)) {
      int nr;
      int recv_result;
      bool flushed = false;
      while (!flushed) {
        recv_result = recv(dev->isk, tmp_report, sizeof(report), MSG_DONTWAIT);
        if (recv_result <= 0) {
          if ((errno != EAGAIN) && (errno != EWOULDBLOCK)) {
            fprintf(stderr, "%d disconnected\n", dev->index);
            close(dev->csk);
            close(dev->isk);
            free(dev);
            return false;
          } else {
            flushed = true;
            // fprintf(stderr, "\n");
            continue;
          }
        } else {
          // fprintf(stderr, ".");
          nr = recv_result;
          memcpy(report, tmp_report, nr);
        }
      }
      if (report[0] == 0xa1) {
        return parse_report_sixaxis_ds3(report + 1, nr - 1);
      }
    }
    return false;

  } else if (connectionType == Usb) {
    int nr = read(usb_fd, report, sizeof(report));
    return parse_report_sixaxis_ds3(report, nr);
  }
  return false;
}

bool DualShock3::parse_report_sixaxis_ds3(unsigned char *r, int len) {
  if (r[0] == 0x01 && r[1] == 0 && len >= 49) {
    datas[0] = r[2];
    datas[1] = r[3];
    datas[2] = compute_dead_zone(0, r[6]);
    datas[3] = compute_dead_zone(1, r[7]);
    datas[4] = compute_dead_zone(2, r[8]);
    datas[5] = compute_dead_zone(3, r[9]);

    if (GetTime() > (last_voltage_time + 5 * (Time)1000000000)) {
      // toute les 5 secondes
      // report battery charge level
      if (connectionType == Bluetooth) {
        batteryChargeLevel->SetText("battery: %i/5", r[30]);
      }
      if (connectionType == Usb) {
        batteryChargeLevel->SetText("battery: usb connected");
      }
      last_voltage_time = GetTime();
    }

    return true;
  }
  return false;
}

void DualShock3::GetAxisData() {

  axis->GetMutex();
  //    axis->SetValueNoMutex(0, 0,datas[2]/(float)X_AXIS_RANGE); //left stick
  //    x-axis
  //    axis->SetValueNoMutex(1, 0,datas[3]/(float)Y_AXIS_RANGE); //left stick
  //    y-axis
  //    axis->SetValueNoMutex(2, 0,datas[4]/(float)X_AXIS_RANGE); //right stick
  //    x-axis
  //    axis->SetValueNoMutex(3, 0,datas[5]/(float)Y_AXIS_RANGE); //right stick
  //    y-axis
  axis->SetValueNoMutex(0, 0, datas[2]); // left stick x-axis
  axis->SetValueNoMutex(1, 0, datas[3]); // left stick y-axis
  axis->SetValueNoMutex(2, 0, datas[4]); // right stick x-axis
  axis->SetValueNoMutex(3, 0, datas[5]); // right stick y-axis
  axis->ReleaseMutex();
  axis->SetDataTime(now);
}

void DualShock3::GetButtonData() {
  // static uint8_t old_start_button=0;
  button->GetMutex();
  button->SetValueNoMutex(0, 0, (datas[0] & 0x08) == 0 ? 0 : 1); // start
  /*
      uint8_t start_button=datas[0]&0x08;
      if (start_button!=old_start_button) {
          if (start_button==0) {
              Thread::Info("Debug: start button released\n");
          } else {
              Thread::Info("Debug: start button pressed\n");
          }
          old_start_button=start_button;
      }
  */
  button->SetValueNoMutex(1, 0, (datas[0] & 0x01) == 0 ? 0 : 1); // select
  button->SetValueNoMutex(2, 0, (datas[1] & 0x80) == 0 ? 0 : 1); // square
  button->SetValueNoMutex(3, 0, (datas[1] & 0x10) == 0 ? 0 : 1); // triangle
  button->SetValueNoMutex(4, 0, (datas[1] & 0x20) == 0 ? 0 : 1); // circle
  button->SetValueNoMutex(5, 0, (datas[1] & 0x40) == 0 ? 0 : 1); // cross
  button->SetValueNoMutex(6, 0, (datas[1] & 0x04) == 0 ? 0 : 1); // left 1
  button->SetValueNoMutex(7, 0, (datas[1] & 0x01) == 0 ? 0 : 1); // left 2
  button->SetValueNoMutex(8, 0, (datas[0] & 0x02) == 0 ? 0 : 1); // left 3
  button->SetValueNoMutex(9, 0, (datas[1] & 0x08) == 0 ? 0 : 1); // right 1
  button->SetValueNoMutex(10, 0, (datas[1] & 0x02) == 0 ? 0 : 1); // right 2
  button->SetValueNoMutex(11, 0, (datas[0] & 0x04) == 0 ? 0 : 1); // right 3
  button->SetValueNoMutex(12, 0, (datas[0] & 0x10) == 0 ? 0 : 1); // up
  button->SetValueNoMutex(13, 0, (datas[0] & 0x40) == 0 ? 0 : 1); // down
  button->SetValueNoMutex(14, 0, (datas[0] & 0x80) == 0 ? 0 : 1); // left
  button->SetValueNoMutex(15, 0, (datas[0] & 0x20) == 0 ? 0 : 1); // right
  button->ReleaseMutex();
  button->SetDataTime(now);
}

void DualShock3::ProcessMessage(core::Message *controllerAction) {
  ControllerAction action;
  memcpy(&action, controllerAction->buffer, sizeof(ControllerAction));
  if (action == ControllerAction::SetLedOn) {
    Thread::Info("LedOn action request\n");
  } else if (action == ControllerAction::SetLedOff) {
    Thread::Info("LedOff action request\n");
  } else if (action == ControllerAction::Rumble) {
    Thread::Info("Rumble action request\n");
  } else if (action == ControllerAction::FlashLed) {
    Thread::Info("FlashLed action request\n");
  }
  // (char *msg, int msgSize)
  /*    for (unsigned int i=0; i<4; i++) {
          if(msg[4+2*i]!=0 || msg[5+2*i]!=0) set_led(i+1,msg[4+2*i],msg[5+2*i]);

      }
      if(msg[0]!=0 || msg[2]!=0) rumble(msg[0],msg[1],msg[2],msg[3]);
          */
}

// ----------------------------------------------------------------------
// Replacement for libbluetooth

int DualShock3::mystr2ba(const char *s, bdaddr_t *ba) {
  if (strlen(s) != 17)
    return 1;
  for (int i = 0; i < 6; ++i) {
    int d = strtol(s + 15 - 3 * i, NULL, 16);
    if (d < 0 || d > 255)
      return 1;
    ba->b[i] = d;
  }
  return 0;
}

char *DualShock3::myba2str(const bdaddr_t *ba) {
  static char buf[2][18]; // Static buffer valid for two invocations.
  static int index = 0;
  index = (index + 1) % 2;
  sprintf(buf[index], "%02x:%02x:%02x:%02x:%02x:%02x", ba->b[5], ba->b[4],
          ba->b[3], ba->b[2], ba->b[1], ba->b[0]);
  return buf[index];
}

void DualShock3::fatal(const char *msg) {
  if (errno)
    perror(msg);
  else
    fprintf(stderr, "%s\n", msg);
  exit(1);
}

/**********************************************************************/
// Bluetooth HID devices
// Incoming connections.

int DualShock3::l2cap_listen(const bdaddr_t *bdaddr, unsigned short psm) {
  int sk = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
  if (sk < 0)
    fatal("socket");

  struct sockaddr_l2 addr;
  addr.l2_family = AF_BLUETOOTH;
  addr.l2_bdaddr = *BDADDR_ANY;
  addr.l2_psm = htobs(psm);
  addr.l2_cid = 0;

  if (bind(sk, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    close(sk);
    fatal("bind");
  }

  if (listen(sk, 5) < 0)
    fatal("listen");
  return sk;
}

struct motion_dev *DualShock3::accept_device(int csk, int isk) {
  Printf("Incoming connection...\n");
  struct motion_dev *dev = (motion_dev *)malloc(sizeof(struct motion_dev));
  if (!dev)
    fatal("malloc");

  dev->csk = accept(csk, NULL, NULL);
  if (dev->csk < 0)
    fatal("accept(CTRL)");
  dev->isk = accept(isk, NULL, NULL);
  if (dev->isk < 0)
    fatal("accept(INTR)");

  struct sockaddr_l2 addr;
  socklen_t addrlen = sizeof(addr);
  if (getpeername(dev->isk, (struct sockaddr *)&addr, &addrlen) < 0)
    fatal("getpeername");
  dev->addr = addr.l2_bdaddr;

  // Distinguish SIXAXIS / DS3
  unsigned char resp[64];
  char get03f2[] = {HIDP_TRANS_GET_REPORT | HIDP_DATA_RTYPE_FEATURE | 8,
                    (char)0xf2, sizeof(resp), sizeof(resp) >> 8};
  send(dev->csk, get03f2, sizeof(get03f2), 0); // 0301 is interesting too.
  int nr = recv(dev->csk, resp, sizeof(resp), 0);

  dev->type = (resp[13] == 0x40) ? SIXAXIS : DUALSHOCK3; // My guess.

  return dev;
}

/**********************************************************************/
// Device setup

#define IR0 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x41
#define IR1 0x40, 0x00

#define BIT1 2

void DualShock3::hidp_trans(int csk, char *buf, int len) {
  if (send(csk, buf, len, 0) != len)
    fatal("send(CTRL)");
  char ack;
  int nr = recv(csk, &ack, sizeof(ack), 0);
  if (nr != 1 || ack != 0)
    fatal("ack");
}

void DualShock3::setup_device(struct motion_dev *dev) {

  switch (dev->type) {
  case SIXAXIS:
  case DUALSHOCK3:
    // Enable reporting
    char set03f4[] = {HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_FEATURE,
                      (char)0xf4, 0x42, 0x03, 0x00, 0x00};
    hidp_trans(dev->csk, set03f4, sizeof(set03f4));

    break;
  }
}

/**********************************************************************/
// Reports

// faire un reglage station sol pour dead zone
int8_t DualShock3::compute_dead_zone(int axis, unsigned char value) {
  float tmp;

  if (value > 128 + deadZone->Value()) {
    tmp =
        (value - deadZone->Value() - 128.) * 128. / (128. - deadZone->Value());
  } else if (value < 128 - deadZone->Value()) {
    // return value+DEAD_ZONE-128;
    tmp =
        (value + deadZone->Value() - 128.) * 127. / (128. - deadZone->Value());
  } else {
    return 0;
  }

  if (tmp > 127)
    return 127;
  if (tmp < -127)
    return -127;
  if (tmp > ((int8_t)tmp + .5) && tmp > 0)
    return (int8_t)(tmp + 1);
  if (tmp < ((int8_t)tmp - .5) && tmp < 0)
    return (int8_t)(tmp - 1);

  return (int8_t)tmp;
}

/**********************************************************************/
// USB functions

void DualShock3::usb_pair_device(struct usb_device *dev, int itfnum) {

  usb_dev_handle *devh = usb_open(dev);
  if (!devh)
    fatal("usb_open");
  usb_detach_kernel_driver_np(devh, itfnum);
  int res = usb_claim_interface(devh, itfnum);
  if (res < 0)
    fatal("usb_claim_interface");

  bdaddr_t current_ba; // Current pairing address.

  switch (dev->descriptor.idProduct) {
  case PRODUCT_SIXAXIS_DS3: {
    // remote_printf("USB: SIXAXIS/DS3\n");
    char msg[8];
    res =
        usb_control_msg(devh, USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                        USB_GET_REPORT, 0x03f5, itfnum, msg, sizeof(msg), 5000);
    /*
            unsigned char msg[8];
            res = usb_control_msg
                  (devh, USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                   USB_GET_REPORT, 0x03f5, itfnum, (void*)msg, sizeof(msg),
       5000);*/
    if (res < 0)
      fatal("usb_control_msg(read master)");
    for (int i = 0; i < 6; ++i)
      current_ba.b[i] = (uint8_t)msg[7 - i];
    break;
  }
  }

  // New pairing address
  int dev_id;
  dev_id = hci_get_route(NULL);
  struct hci_dev_info di;
  hci_devinfo(dev_id, &di);

  // Perform pairing.
  if (!bacmp(&current_ba, &di.bdaddr)) {
    printf("  Already paired to %s\n", myba2str(&di.bdaddr));
  } else {
    printf("  Changing master from %s to %s\n", myba2str(&current_ba),
           myba2str(&di.bdaddr));
    switch (dev->descriptor.idProduct) {
    case PRODUCT_SIXAXIS_DS3: {
      char msg[8] = {0x01, 0x00, (char)di.bdaddr.b[5], (char)di.bdaddr.b[4],
                     (char)di.bdaddr.b[3], (char)di.bdaddr.b[2],
                     (char)di.bdaddr.b[1], (char)di.bdaddr.b[0]};
      res = usb_control_msg(
          devh, USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
          USB_SET_REPORT, 0x03f5, itfnum, msg, sizeof(msg), 5000);
      if (res < 0)
        fatal("usb_control_msg(write master)");
      break;
    }
    }
  }

  if (dev->descriptor.idProduct == PRODUCT_SIXAXIS_DS3)
    printf("  Now unplug the USB cable and press the PS button.\n");
  else
    printf("  Now press the PS button.\n");
}

void DualShock3::usb_scan() {
  usb_init();
  if (usb_find_busses() < 0)
    fatal("usb_find_busses");
  if (usb_find_devices() < 0)
    fatal("usb_find_devices");
  struct usb_bus *busses = usb_get_busses();
  if (!busses)
    fatal("usb_get_busses");

  struct usb_bus *bus;
  for (bus = busses; bus; bus = bus->next) {
    struct usb_device *dev;
    for (dev = bus->devices; dev; dev = dev->next) {
      struct usb_config_descriptor *cfg;
      for (cfg = dev->config;
           cfg < dev->config + dev->descriptor.bNumConfigurations; ++cfg) {
        int itfnum;
        for (itfnum = 0; itfnum < cfg->bNumInterfaces; ++itfnum) {
          struct usb_interface *itf = &cfg->interface[itfnum];
          struct usb_interface_descriptor *alt;
          for (alt = itf->altsetting;
               alt < itf->altsetting + itf->num_altsetting; ++alt) {
            if (dev->descriptor.idVendor == VENDOR_SONY &&
                (dev->descriptor.idProduct == PRODUCT_SIXAXIS_DS3) &&
                alt->bInterfaceClass == 3)
              usb_pair_device(dev, itfnum);
          }
        }
      }
    }
  }
}

void DualShock3::rumble(uint8_t left_force, uint8_t left_timeout,
                        uint8_t right_force, uint8_t right_timeout) {
  // printf("rumble\n");

  unsigned char datas[] = {
      0x52 /* HIDP_TRANS_SET_REPORT|HIDP_DATA_RTYPE_OUPUT */, 0x01, 0x00, 0x00,
      0x00, 0x00, 0x00, // rumble values
      0x00, 0x00, 0x00, 0x00, (unsigned char)ledmask, // 0x10=LED1 .. 0x02=LED4

      0xff, 0x27, led4_on, led4_off, 0x32, 0xff, 0x27, led3_on, led3_off, 0x32,
      0xff, 0x27, led2_on, led2_off, 0x32, 0xff, 0x27, led1_on, led1_off, 0x32,
      0x00, 0x00, 0x00, 0x00, 0x00,
  };

  datas[5] = left_timeout;  // left timeout
  datas[6] = left_force;    // left force
  datas[3] = right_timeout; // right timeout
  datas[4] = right_force;   // right force

  if (connectionType == Bluetooth) {
    hidp_trans(dev->csk, (char *)datas, sizeof(datas));
  }
}

void DualShock3::set_led(uint8_t led, uint8_t on_timeout, uint8_t off_timeout) {
  uint8_t mask;

  switch (led) {
  case 1:
    led1_on = on_timeout;
    led1_off = off_timeout;
    mask = 2;
    break;
  case 2:
    led2_on = on_timeout;
    led2_off = off_timeout;
    mask = 4;
    break;
  case 3:
    led3_on = on_timeout;
    led3_off = off_timeout;
    mask = 8;
    break;
  case 4:
    led4_on = on_timeout;
    led4_off = off_timeout;
    mask = 16;
    break;
  }

  if (on_timeout != 0) {
    ledmask |= mask;
  } else {
    ledmask &= ~mask;
  }
  /*
      printf("led %x\n",ledmask);
      printf("1:%i %i\n",led1_on,led1_off);
      printf("2:%i %i\n",led2_on,led2_off);
      printf("3:%i %i\n",led3_on,led3_off);
      printf("4:%i %i\n",led4_on,led4_off);*/

  unsigned char datas[] = {
      0x52 /* HIDP_TRANS_SET_REPORT|HIDP_DATA_RTYPE_OUPUT */, 0x01, 0x00, 0x00,
      0x00, 0x00, 0x00, // rumble values
      0x00, 0x00, 0x00, 0x00, (unsigned char)ledmask, // 0x10=LED1 .. 0x02=LED4

      0xff, 0x27, led4_on, led4_off, 0x32, 0xff, 0x27, led3_on, led3_off, 0x32,
      0xff, 0x27, led2_on, led2_off, 0x32, 0xff, 0x27, led1_on, led1_off, 0x32,
      0x00, 0x00, 0x00, 0x00, 0x00,
  };

  if (connectionType == Bluetooth) {
    hidp_trans(dev->csk, (char *)datas, sizeof(datas));
  }
}

} // end namespace sensor
} // end namespace flair
