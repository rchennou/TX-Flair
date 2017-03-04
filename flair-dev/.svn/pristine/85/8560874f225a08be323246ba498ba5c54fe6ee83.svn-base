// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file AhrsData.h
 * \brief Class defining AHRS datas
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/03/01
 * \version 4.0
 */
#ifndef AHRSDATA_H
#define AHRSDATA_H

#include <io_data.h>
#include <IODataElement.h>
#include <Vector3D.h>
#include <Quaternion.h>

namespace flair {
namespace core {

/*! \class AhrsData
*
* \brief Class defining AHRS datas
*
* AHRS datas consist of quaternion and rotational angles values. \n
*
*/
class AhrsData : public io_data {
public:
  class Type : public DataType {
  public:
    Type(const ScalarType &inElementDataType)
        : elementDataType(inElementDataType) {}
    const ScalarType &GetElementDataType() const { return elementDataType; }
    std::string GetDescription() const { return "ahrs data"; }
    size_t GetSize() const { return 7 * elementDataType.GetSize(); }

  private:
    const ScalarType &elementDataType;
  };

  /*!
  \enum PlotableData_t
  \brief Datas wich can be plotted in a DataPlot1D
  */
  typedef enum {
    Roll /*! roll */,
    Pitch /*! pitch */,
    Yaw /*! yaw */,
    RollDeg /*! roll degree*/,
    PitchDeg /*! pitch degree */,
    YawDeg /*! yaw degree */,
    Q0 /*! quaternion 0 */,
    Q1 /*! quaternion 1 */,
    Q2 /*! quaternion 2 */,
    Q3 /*! quaternion 3 */,
    Wx /*! x filtered angular rate */,
    Wy /*! y filtered angular rate */,
    Wz /*! z filtered angular rate */,
    WxDeg /*! x filtered angular rate degree*/,
    WyDeg /*! y filtered angular rate degree*/,
    WzDeg /*! z filtered angular rate degree*/,
  } PlotableData_t;

  /*!
  * \brief Constructor
  *
  * Construct an io_data representing AHRS datas. \n
  *
  * \param parent parent
  * \param name name
  * \param n number of samples
  */
  AhrsData(const Object *parent, std::string name = "", int n = 1);

  /*!
  * \brief Destructor
  *
  */
  ~AhrsData();

  /*!
  * \brief Element
  *
  * Get a pointer to a specific element. This pointer can be used for plotting.
  *
  * \param plotableData data type
  *
  * \return pointer to the element
  */
  IODataElement *Element(PlotableData_t plotableData) const;

  /*!
  * \brief Set quaternion
  *
  * This method is mutex protected.
  *
  * \param quaternion quaternion
  *
  */
  void SetQuaternion(const Quaternion &quaternion);

  /*!
  * \brief Get quaternion
  *
  * This method is mutex protected.
  *
  * \return quaternion
  *
  */
  Quaternion GetQuaternion(void) const;

  /*!
  * \brief Set angular rates
  *
  * This method is mutex protected.
  *
  * \param angularRates angular rates
  *
  */
  void SetAngularRates(const Vector3D &angularRates);

  /*!
  * \brief Get angular rates
  *
  * This method is mutex protected.
  *
  * \return angular rates
  *
  */
  Vector3D GetAngularRates(void) const;

  /*!
  * \brief Get both quaternion and angular rates
  *
  * This method is mutex protected.
  *
  * \param quaternion quaternion
  * \param angularRates angular rates
  *
  */
  void GetQuaternionAndAngularRates(Quaternion &quaternion,
                                    Vector3D &angularRates) const;

  /*!
  * \brief Set both quaternion and angular rates
  *
  * This method is mutex protected.
  *
  * \param quaternion quaternion
  * \param angularRates angular rates
  *
  */
  void SetQuaternionAndAngularRates(const Quaternion &quaternion,
                                    const Vector3D &angularRates);

  const Type &GetDataType() const { return dataType; }

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

  /*!
  * \brief %Quaternion
  *
  */
  Quaternion quaternion;

  /*!
  * \brief Angular rates
  *
  */
  Vector3D angularRates;

  Type dataType;
};

} // end namespace core
} // end namespace flair

#endif // AHRSDATA_H
