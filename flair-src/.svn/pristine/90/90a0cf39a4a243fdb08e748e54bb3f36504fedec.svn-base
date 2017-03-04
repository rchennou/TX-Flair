// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file NmeaGps.h
 * \brief Base class for GPS using NMEA sentances
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/08/23
 * \version 4.0
 */

#ifndef NMEAGPS_H
#define NMEAGPS_H

#include <IODevice.h>
#include <nmea/nmea.h>

namespace flair {
  namespace core {
    class FrameworkManager;
    class GeoCoordinate;
    class Vector3D;
    class GpsData;
  }
  namespace gui {
    class Layout;
    class DataPlot1D;
    class Tab;
    class TabWidget;
    class PushButton;
    class Map;
    class Label;
    class GroupBox;
  }
}

namespace flair {
namespace sensor {

/*! \class NmeaGps
*
* \brief Base class for GPS using NMEA sentances
*/
class NmeaGps : public core::IODevice {
public:
  /*!
  \enum NMEAFlags_t
  \brief NMEA flags
  */
  enum NMEAFlags_t {
    GGA = 0x01, /*!< GGA */
    VTG = 0x02, /*!< VTG */
    GST = 0x04, /*!< GST */
  };

  /*!
  * \brief Constructor
  *
  * Construct a NmeaGps.
  *
  * \param parent parent
  * \param name name
  * \param NMEAFlags NMEA sentances to enable
  */
  NmeaGps(const core::FrameworkManager *parent, std::string name,
      NMEAFlags_t NMEAFlags);

  /*!
  * \brief Constructor
  *
  * Construct a NmeaGps. \n
  * This contructor must only be called for a simulated device.
  *
  * \param parent parent
  * \param name name
  */
  NmeaGps(const core::IODevice *parent, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~NmeaGps();

  /*!
  * \brief Get GPS datas
  *
  * \return GpsData
  */
  const core::GpsData *GetDatas(void) const;

  /*!
  * \brief Use default plot
  *
  */
  void UseDefaultPlot(void);

  /*!
  * \brief East plot
  *
  * \return east plot
  */
  gui::DataPlot1D *EPlot(void) const;

  /*!
  * \brief North plot
  *
  * \return north plot
  */
  gui::DataPlot1D *NPlot(void) const;

  /*!
  * \brief Up plot
  *
  * \return up plot
  */
  gui::DataPlot1D *UPlot(void) const;

  /*!
  * \brief East velocity plot
  *
  * \return east velocity plot
  */
  gui::DataPlot1D *VEPlot(void) const;

  /*!
  * \brief North velocity plot
  *
  * \return north velocity plot
  */
  gui::DataPlot1D *VNPlot(void) const;

  /*!
  * \brief Main tab
  *
  * \return main tab
  */
  gui::TabWidget *GetTab(void) const;

  /*!
  * \brief Setup Layout
  *
  * \return setup Layout
  */
  gui::Layout *GetLayout(void) const;

  /*!
  * \brief Plot tab
  *
  * \return plot Tab
  */
  gui::Tab *GetPlotTab(void) const;

  /*!
  * \brief Set reference for ENU coordinates
  *
  * The actual position is used as reference to calculate
  * ENU coordinates.
  *
  * \return fix quality
  */
  void SetRef(void);

  /*!
  * \brief Get ENU position
  *
  * \param point to store position
  */
  void GetEnu(core::Vector3D *point);

protected:
  /*!
  * \brief Parse a NMEA frame
  *
  * This function must be called by the reimplemented class. \n
  * When a frame is parsed, GPS datas are filled.
  *
  * \param frame NMEA frame
  * \param frame_size frame size
  *
  */
  void parseFrame(const char *frame, int frame_size);

  NMEAFlags_t NMEAFlags;

  /*!
  * \brief Get GPS datas
  *
  * \param gpsData GPS datas
  */
  void GetDatas(core::GpsData **gpsData) const;

  /*!
  * \brief Setup GroupBox
  *
  * \return setup GroupBox
  */
  gui::GroupBox *GetGroupBox(void) const;

private:
  gui::Tab *mainTab, *sensorTab;
  gui::TabWidget *tab;
  gui::GroupBox *setupGroupbox;
  gui::PushButton *buttonRef;
  gui::DataPlot1D *ePlot;
  gui::DataPlot1D *nPlot;
  gui::DataPlot1D *uPlot;
  gui::DataPlot1D *vePlot;
  gui::DataPlot1D *vnPlot;
  gui::Tab *plotTab;
  gui::Map *map;
  gui::Label *nbSatLabel, *fixLabel;
  core::GeoCoordinate *position;
  bool takeRef;
  nmeaINFO info;
  nmeaPARSER parser;
  nmeaGPGGA pack;
  nmeaPOS pos;
  double latRef, longRef, altRef;
  core::GpsData* gpsData;
};
} // end namespace sensor
} // end namespace framewor
#endif // NMEAGPS_H
