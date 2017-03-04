// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file GeoCoordinate.h
 * \brief Class defining a point by its lla coordinates
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/07/29
 * \version 4.0
 */
#ifndef GEOCOORDINATE_H
#define GEOCOORDINATE_H

#include <io_data.h>

namespace flair {
namespace core {

/*! \class GeoCoordinate
*
* \brief Class defining a point by its lla coordinates
*/
class GeoCoordinate : public io_data {
public:
  class Type : public DataType {
  public:
    size_t GetSize() const {
      return sizeof(latitude) + sizeof(longitude) + sizeof(altitude);
    }
    std::string GetDescription() const { return "lla"; }
  };

  /*!
  * \brief Constructor
  *
  * Construct GeoCoordinate using values from another class.
  *
  * \param parent parent
  * \param name name
  * \param point class to copy
  * \param n number of samples
  */
  GeoCoordinate(const Object *parent, std::string name,
                const GeoCoordinate *point, int n = 1);

  /*!
  * \brief Constructor
  *
  * Construct GeoCoordinate using specified values.
  *
  * \param parent parent
  * \param name name
  * \param latitude latitude
  * \param longitude longitude
  * \param altitude altitude
  * \param n number of samples
  */
  GeoCoordinate(const Object *parent, std::string name, double latitude,
                double longitude, double altitude, int n = 1);

  /*!
  * \brief Destructor
  *
  */
  ~GeoCoordinate();

  /*!
  * \brief Copy
  *
  * \param point class to copy
  */
  void CopyFrom(const GeoCoordinate *point);

  /*!
  * \brief Set coordinates
  *
  * \param latitude latitude
  * \param longitude longitude
  * \param altitude altitude
  */
  void SetCoordinates(double latitude, double longitude, double altitude);

  /*!
  * \brief Get coordinates
  *
  * \param latitude latitude
  * \param longitude longitude
  * \param altitude altitude
  */
  void GetCoordinates(double *latitude, double *longitude,
                      double *altitude) const;

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
  void CopyDatas(char *ptr) const;

  double latitude;
  double longitude;
  double altitude;
  Type dataType;
};

} // end namespace core
} // end namespace flair

#endif // GEOCOORDINATE_H
