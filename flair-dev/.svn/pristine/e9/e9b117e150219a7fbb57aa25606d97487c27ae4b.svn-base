// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ImuData.h
 * \brief Class defining IMU datas
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/15
 * \version 4.0
 */
#ifndef IMUDATA_H
#define IMUDATA_H

#include <io_data.h>
#include <IODataElement.h>
#include <Vector3D.h>

namespace flair {
namespace core {

/*! \class ImuData
*
* \brief Class defining IMU datas
*
* IMU (inertial measurement unit) datas consist of raw accelerometer values, raw
*gyrometer values
* and raw magnetometer values.
*
*/
class ImuData : public io_data {
public:
  class Type : public DataType {
  public:
    Type(ScalarType const &_elementDataType)
        : elementDataType(_elementDataType) {}
    ScalarType const &GetElementDataType() const { return elementDataType; }
    std::string GetDescription() const { return "imu data"; }
    size_t GetSize() const {
      size_t size = 0;
      size += 3 * elementDataType.GetSize(); // RawAcc
      size += 3 * elementDataType.GetSize(); // RawGyr
      size += 3 * elementDataType.GetSize(); // RawMag
      return size;
    }

  private:
    ScalarType const &elementDataType;
  };

  /*!
  \enum PlotableData_t
  \brief Datas wich can be plotted in a DataPlot1D
  */
  typedef enum {
    RawAx /*! x raw accelerometer */,
    RawAy /*! y raw accelerometer */,
    RawAz /*! z raw accelerometer */,
    RawGx /*! x raw gyrometer */,
    RawGy /*! y raw gyrometer */,
    RawGz /*! z raw gyrometer */,
    RawGxDeg /*! x raw gyrometer degree */,
    RawGyDeg /*! y raw gyrometer degree */,
    RawGzDeg /*! z raw gyrometer degree */,
    RawMx /*! x raw magnetometer */,
    RawMy /*! y raw magnetometer */,
    RawMz /*! z raw magnetometer */
  } PlotableData_t;

  /*!
  * \brief Constructor
  *
  * Construct an io_data representing IMU datas. \n
  *
  * \param parent parent
  * \param name name
  * \param n number of samples
  */
  ImuData(const Object *parent, std::string name = "", int n = 1);

  /*!
  * \brief Destructor
  *
  */
  ~ImuData();

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
  * \brief Get raw accelerations
  *
  * This method is mutex protected.
  *
  * \return raw accelerations
  *
  */
  Vector3D GetRawAcc(void) const;

  /*!
  * \brief Get raw magnetometers
  *
  * This method is mutex protected.
  *
  * \return raw magnetometers
  *
  */
  Vector3D GetRawMag(void) const;

  /*!
  * \brief Get raw angular speed
  *
  * This method is mutex protected.
  *
  * \return raw angular speed
  *
  */
  Vector3D GetRawGyr(void) const;

  /*!
  * \brief Get raw accelerations, magnetometers and angular speeds
  *
  * This method is mutex protected.
  *
  * \param rawAcc raw accelerations
  * \param rawMag raw magnetometers
  * \param rawGyr raw angular speeds
  *
  */
  void GetRawAccMagAndGyr(Vector3D &rawAcc, Vector3D &rawMag,
                          Vector3D &rawGyr) const;

  /*!
  * \brief Set raw accelerations
  *
  * This method is mutex protected.
  *
  * \param raw accelerations
  *
  */
  void SetRawAcc(const Vector3D &rawAcc);

  /*!
  * \brief Set raw magnetometers
  *
  * This method is mutex protected.
  *
  * \param raw magnetometers
  *
  */
  void SetRawMag(const Vector3D &rawMag);

  /*!
  * \brief Set raw angular speed
  *
  * This method is mutex protected.
  *
  * \param raw angular speed
  *
  */
  void SetRawGyr(const Vector3D &rawGyr);

  /*!
  * \brief Set raw accelerations, magnetometers and angular speeds
  *
  * This method is mutex protected.
  *
  * \param rawAcc raw accelerations
  * \param rawMag raw magnetometers
  * \param rawGyr raw angular speeds
  *
  */
  void SetRawAccMagAndGyr(const Vector3D &rawAcc, const Vector3D &rawMag,
                          const Vector3D &rawGyr);

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

  /*!
  * \brief Raw accelerometer
  *
  */
  Vector3D rawAcc;

  /*!
  * \brief Raw gyrometer
  *
  */
  Vector3D rawGyr;

  /*!
  * \brief Raw magnetometer
  *
  */
  Vector3D rawMag;

  void Queue(char **dst, const void *src, size_t size) const;
  Type dataType;
};

} // end namespace core
} // end namespace flair

#endif // IMUDATA_H
