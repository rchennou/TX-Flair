// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file GpsData.h
 * \brief Class defining gps datas
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/07/01
 * \version 4.0
 */
#ifndef GPSDATA_H
#define GPSDATA_H

#include <io_data.h>

namespace flair {
namespace core {

  class IODataElement;
  class Vector3D;

/*! \class GpsData
*
* \brief Class defining gps datas
*
* GPS datas consist of
*
*
*/
class GpsData : public io_data {
public:
  class Type : public DataType {
  public:
    Type(void){}
    std::string GetDescription() const { return "gps data"; }
    size_t GetSize() const {
      size_t size = 0;
      size += 2*doubleType.GetSize(); // Latitude, Longitude
      size += floatType.GetSize(); // Altitude
      size += UInt8Type.GetSize(); // NumberOfSatellites
      size += UInt8Type.GetSize(); // FixQuality_t
      size += 5*floatType.GetSize();//e,n,u,ve,vn
      return size;
    }

  private:
  };

  /*!
  \enum PlotableData_t
  \brief Datas wich can be plotted in a DataPlot1D
  */
  typedef enum {
    Latitude /*! latitude in degrees */,
    Longitude /*! longitude in degrees */,
    Altitude /*! altitude */,
    NumberOfSatellites /*! number of satellites */,
    FixQuality /*! fix quality */,
    East /*! east */,
    North /*! north */,
    Up /*! up */,
    EastVelocity /*! east velocity*/,
    NorthVelocity /*! north velocity*/,
  } PlotableData_t;

  /*!
  \enum FixQuality_t
  \brief Fix qualty indicators
  */
  enum class FixQuality_t : uint8_t {
    Invalid = 0,    /*!< invalid */
    Gps = 1,        /*!< Gps */
    DGps = 2,       /*!< Differential Gps */
    Pps = 3,        /*!< Pps */
    Rtk = 4,        /*!< RTK */
    RtkFloat = 5,   /*!< RTK float */
    Estimated = 6,  /*!< Estimated */
    Manual = 7,     /*!< Manual */
    Simulation = 8, /*!< Simulation */
  };

  /*!
  * \brief Constructor
  *
  * Construct an io_data representing GPS datas. \n
  *
  * \param parent parent
  * \param name name
  * \param n number of samples
  */
  GpsData(const Object *parent, std::string name = "", int n = 1);

  /*!
  * \brief Destructor
  *
  */
  ~GpsData();

  /*!
  * \brief Element
  *
  * Get a pointer to a specific element. This pointer can be used for plotting.
  *
  * \param data_type data type
  *
  * \return pointer to the element
  */
  IODataElement *Element(PlotableData_t data_type) const;

  /*!
  * \brief Get latitude, longitude and altitude
  *
  * This method is mutex protected.
  *
  * \param latitude latitude
  * \param longitude longitude
  * \param altitude altitude
  *
  */
  void GetLla(double &latitude, double &longitude,
                          float &altitude) const;

  /*!
  * \brief Set latitude, longitude and altitude
  *
  * This method is mutex protected.
  *
  * \param latitude latitude
  * \param longitude longitude
  * \param altitude altitude
  *
  */
  void SetLla(double latitude,double longitude,
                          float altitude);


  /*!
  * \brief Get east, north and up
  *
  * This method is mutex protected.
  *
  * \param east east
  * \param north north
  * \param up up
  *
  */
  void GetEnu(float &east, float &north,
                          float &up) const;

  /*!
  * \brief Set east, north and up
  *
  * This method is mutex protected.
  *
  * \param east east
  * \param north north
  * \param up up
  *
  */
  void SetEnu(float east, float north,
                          float up);

  /*!
  * \brief Get east and north velocities
  *
  * This method is mutex protected.
  *
  * \param eastVelocity east velocity
  * \param northVelocity north velocity
  *
  */
  void GetVelocity(float &eastVelocity, float &northVelocity) const;

  /*!
  * \brief Set east and north velocities
  *
  * This method is mutex protected.
  *
  * \param eastVelocity east velocity
  * \param northVelocity north velocity
  *
  */
  void SetVelocity(float eastVelocity, float northVelocity);

  /*!
  * \brief Get number of satellites
  *
  * \return number of satellites
  *
  */
  uint8_t GetNumberOfSatellites(void) const;

  /*!
  * \brief Set number of satellites
  *
  * \param numberOfSatellites number of satellites
  *
  */
  void SetNumberOfSatellites(uint8_t numberOfSatellites);

  /*!
  * \brief Get fix quality
  *
  * \return fix quality
  *
  */
  FixQuality_t GetFixQuality(void) const;

  /*!
  * \brief Set fix quality
  *
  * \param fixQuality fix quality
  *
  */
  void SetFixQuality(FixQuality_t fixQuality);

  Type const &GetDataType() const { return dataType; }

private:
  /*!
  * \brief Copy datas
  *
  * Reimplemented from io_data. \n
  * See io_data::CopyDatas.
  *
  * \param dst destination buffer
  */
  void CopyDatas(char *dst) const;

  void Queue(char **dst, const void *src, size_t size) const;
  Type dataType;
  double latitude,longitude;
  float altitude;
  uint8_t numberOfSatellites;
  FixQuality_t fixQuality;
  float east,north,up,eastVelocity,northVelocity;
};

} // end namespace core
} // end namespace flair

#endif // GPSDATA_H
