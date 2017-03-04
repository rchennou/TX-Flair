// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Ahrs.h
 * \brief Abstract class for AHRS
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/14
 * \version 4.0
 */

#ifndef AHRS_H
#define AHRS_H

#include <IODevice.h>
#include <DataPlot.h>

namespace flair {
  namespace core {
    class Euler;
    class Vector3D;
    class ImuData;
    class Quaternion;
    class AhrsData;
  }
  namespace gui {
    class Tab;
    class DataPlot1D;
  }
  namespace sensor {
    class Imu;
  }
}

class Ahrs_impl;

namespace flair {
namespace filter {
/*! \class Ahrs
*
* \brief Abstract class for AHRS
*
* Use this class to define a custom AHRS. This class is child
* of an Imu class, which will provide measurements. \n
*
*/
class Ahrs : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct an Ahrs.
  *
  * \param parent parent
  * \param name name
  */
  Ahrs(const sensor::Imu *parent, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~Ahrs();

  /*!
  * \brief Get parent Imu
  *
  * This function is identical to (Imu*)Parent()
  */
  const sensor::Imu *GetImu(void) const;

  /*!
  * \brief Get ahrs datas
  *
  * \return AhrsData
  */
  const core::AhrsData *GetDatas(void) const;

  /*!
  * \brief Lock the graphical user interface
  *
  * When locked, parameters cannot be modified.
  *
  */
  void LockUserInterface(void) const;

  /*!
  * \brief Unlock the graphical user interface
  *
  */
  void UnlockUserInterface(void) const;

  /*!
  * \brief Use default plot
  *
  * Plot the datas defined in imudata,
  * and datas defined in Imu::imudata.
  *
  */
  void UseDefaultPlot(void);

  /*!
  * \brief Add plot
  *
  * Add plot of an AhrsData to the default plot
  *
  * \param ahrsData ahrs datas to plot
  * \param color color to use
  */
  void AddPlot(const core::AhrsData *ahrsData, gui::DataPlot::Color_t color);

  /*!
  * \brief Roll plot
  *
  * Use this plot to add own curves.
  *
  * \return plot
  *
  */
  gui::DataPlot1D *RollPlot(void) const;

  /*!
  * \brief Pitch plot
  *
  * Use this plot to add own curves.
  *
  * \return plot
  *
  */
  gui::DataPlot1D *PitchPlot(void) const;

  /*!
  * \brief Yaw plot
  *
  * Use this plot to add own curves.
  *
  * \return plot
  *
  */
  gui::DataPlot1D *YawPlot(void) const;

  /*!
  * \brief Rotation speed around x axis plot
  *
  * Use this plot to add own curves.
  *
  * \return plot
  *
  */
  gui::DataPlot1D *WXPlot(void) const;

  /*!
  * \brief Rotation speed around y axis plot
  *
  * Use this plot to add own curves.
  *
  * \return plot
  *
  */
  gui::DataPlot1D *WYPlot(void) const;

  /*!
  * \brief Rotation speed around z axis plot
  *
  * Use this plot to add own curves.
  *
  * \return plot
  *
  */
  gui::DataPlot1D *WZPlot(void) const;

protected:
  /*!
  * \brief Get ahrs datas
  *
  * \param ahrsData ahrs datas
  */
  void GetDatas(core::AhrsData **ahrsData) const;

private:
  class Ahrs_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // AHRS_H
