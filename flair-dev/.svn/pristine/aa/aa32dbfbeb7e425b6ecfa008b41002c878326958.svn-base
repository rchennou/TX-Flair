// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Uav.h
 * \brief Base class to construct sensors/actuators depending on uav type
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/22
 * \version 3.4
 */

#ifndef HDSUAV_H
#define HDSUAV_H

#include <Object.h>

namespace flair {
namespace core {
class FrameworkManager;
}
namespace filter {
class Ahrs;
class UavMultiplex;
}
namespace actuator {
class Bldc;
}
namespace sensor {
class UsRangeFinder;
class BatteryMonitor;
class VrpnClient;
class Imu;
class Camera;
}
}

namespace flair {
namespace meta {
class MetaUsRangeFinder;
class MetaVrpnObject;

/*! \class Uav
*
* \brief Base class to construct sensors/actuators depending on uav type
*/
class Uav : public core::Object {
public:
  /*
      typedef enum {
          None,
          Auto,//rt serial if hds x4 ou x8, auto ip sinon
          AutoIP,
          UserDefinedIP,
          AutoSerialPort,
          } VRPNType_t;
*/
  // uav_name: for optitrack
  Uav(core::FrameworkManager *parent, std::string name,
      filter::UavMultiplex *multiplex = NULL);
  ~Uav();
  void SetupVRPN(std::string optitrack_address, std::string name);
  // vrpn serial: broken, need to add serial port in uav specific code
  // void SetupVRPNSerial(core::SerialPort *vrpn_port,std::string name,int
  // VRPNSerialObjectId);
  virtual void SetupVRPNAutoIP(std::string name);

  virtual void StartSensors(void);
  void UseDefaultPlot(void);
  actuator::Bldc *GetBldc(void) const;
  filter::UavMultiplex *GetUavMultiplex(void) const;
  sensor::Imu *GetImu(void) const;
  filter::Ahrs *GetAhrs(void) const;
  MetaUsRangeFinder *GetMetaUsRangeFinder(void) const;
  sensor::UsRangeFinder *GetUsRangeFinder(void) const;
  sensor::BatteryMonitor *GetBatteryMonitor(void) const;
  sensor::VrpnClient *GetVrpnClient(void) const;
  meta::MetaVrpnObject *GetVrpnObject(void) const;
  sensor::Camera *GetVerticalCamera(void) const;

protected:
  void SetBldc(const actuator::Bldc *bldc);
  void SetMultiplex(const filter::UavMultiplex *multiplex);
  void SetAhrs(const filter::Ahrs *ahrs);
  void SetUsRangeFinder(const sensor::UsRangeFinder *us);
  void SetBatteryMonitor(const sensor::BatteryMonitor *battery);
  void SetVerticalCamera(const sensor::Camera *verticalCamera);

private:
  sensor::Imu *imu;
  filter::Ahrs *ahrs;
  actuator::Bldc *bldc;
  filter::UavMultiplex *multiplex;
  sensor::UsRangeFinder *us;
  MetaUsRangeFinder *meta_us;
  sensor::VrpnClient *vrpnclient;
  MetaVrpnObject *uav_vrpn;
  sensor::BatteryMonitor *battery;
  sensor::Camera *verticalCamera;
};
} // end namespace meta
} // end namespace flair
#endif // HDSUAV_H
