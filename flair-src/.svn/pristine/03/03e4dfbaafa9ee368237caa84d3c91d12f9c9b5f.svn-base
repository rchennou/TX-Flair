// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file VrpnObject.h
 * \brief Class for VRPN object
 * \author César Richard, Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS
 * 7253
 * \date 2013/04/03
 * \version 4.0
 */

#ifndef VRPNOBJECT_H
#define VRPNOBJECT_H

#include <IODevice.h>
#include <stdint.h>

namespace flair {
namespace core {
class cvmatrix;
class Vector3D;
class Euler;
class Quaternion;
}
namespace gui {
class TabWidget;
class Tab;
class DataPlot1D;
}
}

class VrpnObject_impl;
class VrpnClient_impl;

namespace flair {
namespace sensor {
class VrpnClient;

/*! \class VrpnObject
*
* \brief Class for VRPN object
*/
class VrpnObject : public core::IODevice {
  friend class ::VrpnObject_impl;
  friend class ::VrpnClient_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a VrpnObject. Connection is done by IP.
  *
  * \param parent parent
  * \param name VRPN object name, should be the same as defined in the server
  * \param tab Tab for the user interface
  */
  VrpnObject(const VrpnClient *parent, std::string name,
             const gui::TabWidget *tab);

  /*!
  * \brief Constructor
  *
  * Construct a VrpnObject. Connection is done by IP.
  *
  * \param parent parent
  * \param name name
  * \param id VRPN object id, should be the same as defined in the server
  * \param tab Tab for the user interface
  */
  VrpnObject(const VrpnClient *parent, std::string name, uint8_t id,
             const gui::TabWidget *tab);

  /*!
  * \brief Destructor
  *
  */
  ~VrpnObject(void);

  /*!
  * \brief Plot tab
  *
  * \return plot Tab
  */
  gui::Tab *GetPlotTab(void) const;

  /*!
  * \brief Get Last Packet Time
  *
  * \return Time of last received packe
  */
  core::Time GetLastPacketTime(void) const;

  /*!
  * \brief Is object tracked?
  *
  * \param timeout_ms timeout
  * \return true if object is tracked during timeout_ms time
  */
  bool IsTracked(unsigned int timeout_ms) const;

  /*!
  * \brief Get Euler angles
  *
  * \param euler output datas
  */
  void GetEuler(core::Euler &euler) const;

  /*!
  * \brief Get Quaternion
  *
  * \param quaternion output datas
  */
  void GetQuaternion(core::Quaternion &quaternion) const;
  /*!
  * \brief Get Position
  *
  * \param point output datas
  */
  void GetPosition(core::Vector3D &point) const;

  /*!
  * \brief Output matrix
  *
  * Matrix is of type float and as follows: \n
  * (0,0) roll (rad) \n
  * (1,0) pitch (rad) \n
  * (2,0) yaw (rad) \n
  * (3,0) x \n
  * (4,0) y \n
  * (5,0) z \n
  *
  * \return Output metrix
  */
  core::cvmatrix *Output(void) const;

  /*!
  * \brief State matrix
  *
  * Matrix is of type float and as follows: \n
  * (0,0) roll (deg) \n
  * (1,0) pitch (deg) \n
  * (2,0) yaw (deg) \n
  *
  * \return State metrix
  */
  core::cvmatrix *State(void) const;

  /*!
  * \brief x plot
  *
  * \return x plot
  */
  gui::DataPlot1D *xPlot(void) const;

  /*!
  * \brief y plot
  *
  * \return y plot
  */
  gui::DataPlot1D *yPlot(void) const;

  /*!
  * \brief z plot
  *
  * \return z plot
  */
  gui::DataPlot1D *zPlot(void) const;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  void mainloop(void);
  class VrpnObject_impl *pimpl_;
};
} // end namespace sensor
} // end namespace flair
#endif // VRPNOBJECT_H
