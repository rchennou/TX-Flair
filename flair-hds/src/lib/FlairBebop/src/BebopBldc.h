// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file BebopBldc.h
 * \brief Class for bebop Bldc
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/07/25
 * \version 4.0
 */

#ifndef BEBOPBLDC_H
#define BEBOPBLDC_H

#include "Bldc.h"

namespace flair {
  namespace core {
    class FrameworkManager;
    class I2cPort;
  }
  namespace gui {
    class Layout;
  }
  namespace sensor {
    class BatteryMonitor;
  }
}

namespace flair {
namespace actuator {
/*! \class BebopBldc
*
* \brief Class for bebop Bldc
*/
class BebopBldc : public Bldc {
public:
  /*!
  * \brief Constructor
  *
  * Construct a BebopBldc.
  *
  * \param parent parent
  * \param layout layout
  * \param name name
  * \param i2cPort i2c port
  */
  BebopBldc(const core::IODevice *parent, gui::Layout *layout, std::string name,
            core::I2cPort *i2cPort);

  /*!
  * \brief Destructor
  *
  */
  ~BebopBldc();

  /*!
  * \brief Has speed measurement
  *
  * Reimplemented from Bldc. \n
  *
  * \return true if it has speed measurement
  */
  bool HasSpeedMeasurement(void) const { return true; };

  /*!
  * \brief Has current measurement
  *
  * Reimplemented from Bldc. \n
  *
  * \return true if it has current measurement
  */
  bool HasCurrentMeasurement(void) const { return false; };
  
  /*!
  * \brief Get battery monitor
  *
  * \return BatteryMonitor
  */
  sensor::BatteryMonitor *GetBatteryMonitor(void) const;

  private:
  typedef struct datasStruct_t {
    uint16_t speed[4];
    uint16_t batteryVoltage;
    uint8_t status;
    uint8_t errorNumber;
    uint8_t faultMotors;
    uint8_t temperature;
    uint8_t checksum;

  } __attribute__((packed)) datasStruct_t;
  /*!
  * \brief Set motors values
  *
  * Reimplemented from Bldc. \n
  * Values size must be the same as MotorsCount()
  *
  * \param values motor values
  */
  void SetMotors(float *value);

  void PrintInfo(void);
  void StartMotors(void);
  void StopMotors(void);
  void ClearError(void);
  bool GetDatas(datasStruct_t& outDatasStruct);

  uint8_t CalcChecksum(uint8_t* buf, uint8_t bufSize);
  bool areMotorsStarted;
  bool areMotorsSpinning;
  core::I2cPort* i2cPort;
  sensor::BatteryMonitor* battery;
  core::Time last_voltage_time;
};
} // end namespace actuator
} // end namespace flair
#endif // BEBOPBLDC_H
