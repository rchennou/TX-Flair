// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Imu.h
 * \brief Base class for Imu
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/16
 * \version 4.0
 */

#ifndef IMU_H
#define IMU_H

#include <IODevice.h>

namespace flair {
  namespace core {
    class ImuData;
    class OneAxisRotation;
  }
  namespace gui {
    class Tab;
    class TabWidget;
    class GroupBox;
    class Layout;
    class DataPlot1D;
  }
}

class Ahrs_impl;

namespace flair {
namespace sensor {
/*! \class Imu
*
* \brief Base class for Imu
*
* Use this class to define a custom Imu.
*
*/
class Imu : public core::IODevice {
  friend class ::Ahrs_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct an Imu.
  *
  * \param parent parent
  * \param name name
  */
  Imu(const core::FrameworkManager *parent, std::string name);

  /*!
  * \brief Constructor
  *
  * Construct an Imu. \n
  * This contructor must only be called for a simulated device.
  *
  * \param parent parent
  * \param name name
  */
  Imu(const core::IODevice *parent, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~Imu();

  /*!
  * \brief Setup Layout
  *
  * \return setup Layout
  */
  gui::Layout *GetLayout(void) const;

  /*!
  * \brief Lock user interface
  *
  */
  void LockUserInterface(void) const;

  /*!
  * \brief Unlock user interface
  *
  */
  void UnlockUserInterface(void) const;

  /*!
  * \brief Use default plot
  *
  */
  void UseDefaultPlot(void);

  /*!
  * \brief Plot tab
  *
  * \return plot Tab
  */
  gui::Tab *GetPlotTab(void) const;

  /*!
  * \brief Get OneAxisRotation
  *
  * \return fixed rotation of the imu
  */
  core::OneAxisRotation *GetOneAxisRotation(void) const;


protected:
  /*!
  * \brief Setup GroupBox
  *
  * \return setup GroupBox
  */
  gui::GroupBox *GetGroupBox(void) const;

  /*!
  * \brief UpdateImu
  *
  * The reimplemented class must call this function as soon as IMU datas are
  *available. \n
  * It handles the data rotation if it was defined.
  *
  */
  void UpdateImu();

  /*!
  * \brief Get imu datas
  *
  * \param imuData imu datas
  */
  void GetDatas(core::ImuData **imuData) const;

private:
  gui::Tab *mainTab, *sensorTab, *plotTab;
  gui::TabWidget *tab;
  gui::GroupBox *setupGroupbox;
  core::OneAxisRotation *rotation;
  core::ImuData *imuData;

  gui::DataPlot1D *axPlot, *ayPlot, *azPlot;
  gui::DataPlot1D *gxPlot, *gyPlot, *gzPlot;
  gui::DataPlot1D *mxPlot, *myPlot, *mzPlot;
};
} // end namespace sensor
} // end namespace flair

#endif // IMU_H
