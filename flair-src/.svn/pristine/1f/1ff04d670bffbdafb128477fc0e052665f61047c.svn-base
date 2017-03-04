// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/15
//  filename:   ImuData.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class defining imu datas
//
//
/*********************************************************************/

#include "ImuData.h"
#include "Euler.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

using std::string;

namespace flair {
namespace core {

/*! \class ImuDataElement
    */
class ImuDataElement : public IODataElement {
public:
  ImuDataElement(const ImuData *inImudata, string name,
                 ImuData::PlotableData_t inPlotableData)
      : IODataElement(inImudata, name) {
    imudata = inImudata;
    plotableData = inPlotableData;

    size = 4;
  }

  ~ImuDataElement() {}

  void CopyData(char *dst) const {
    float data;
    Vector3D rawAcc = imudata->GetRawAcc();
    Vector3D rawMag = imudata->GetRawMag();
    Vector3D rawGyr = imudata->GetRawGyr();
    switch (plotableData) {
    case ImuData::RawAx:
      data = rawAcc.x;
      break;
    case ImuData::RawAy:
      data = rawAcc.y;
      break;
    case ImuData::RawAz:
      data = rawAcc.z;
      break;
    case ImuData::RawGx:
      data = rawGyr.x;
      break;
    case ImuData::RawGy:
      data = rawGyr.y;
      break;
    case ImuData::RawGz:
      data = rawGyr.z;
      break;
    case ImuData::RawGxDeg:
      data = Euler::ToDegree(rawGyr.x);
      break;
    case ImuData::RawGyDeg:
      data = Euler::ToDegree(rawGyr.y);
      break;
    case ImuData::RawGzDeg:
      data = Euler::ToDegree(rawGyr.z);
      break;
    case ImuData::RawMx:
      data = rawMag.x;
      break;
    case ImuData::RawMy:
      data = rawMag.y;
      break;
    case ImuData::RawMz:
      data = rawMag.z;
      break;
    default:
      imudata->Err("data type unavailable.\n");
      data = 0;
      break;
    }

    memcpy(dst, &data, sizeof(float));
  }

  FloatType const &GetDataType(void) const { return dataType; }

private:
  const ImuData *imudata;
  ImuData::PlotableData_t plotableData;
  FloatType dataType;
};

ImuData::ImuData(const Object *parent, std::string name, int n)
    : io_data(parent, name, n), dataType(floatType) {
  if (n > 1)
    Warn("n>1 not supported\n");

  AppendLogDescription("raw_ax", floatType);
  AppendLogDescription("raw_ay", floatType);
  AppendLogDescription("raw_az", floatType);

  AppendLogDescription("raw_gx", floatType);
  AppendLogDescription("raw_gy", floatType);
  AppendLogDescription("raw_gz", floatType);

  AppendLogDescription("raw_mx", floatType);
  AppendLogDescription("raw_my", floatType);
  AppendLogDescription("raw_mz", floatType);
}

ImuData::~ImuData() {}

Vector3D ImuData::GetRawAcc(void) const {
  Vector3D out;
  GetMutex();
  out = rawAcc;
  ReleaseMutex();
  return out;
}

Vector3D ImuData::GetRawMag(void) const {
  Vector3D out;
  GetMutex();
  out = rawMag;
  ReleaseMutex();
  return out;
}

Vector3D ImuData::GetRawGyr(void) const {
  Vector3D out;
  GetMutex();
  out = rawGyr;
  ReleaseMutex();
  return out;
}

void ImuData::GetRawAccMagAndGyr(Vector3D &inRawAcc, Vector3D &inRawMag,
                                 Vector3D &inRawGyr) const {
  GetMutex();
  inRawAcc = rawAcc;
  inRawMag = rawMag;
  inRawGyr = rawGyr;
  ReleaseMutex();
}

void ImuData::SetRawAcc(const Vector3D &inRawAcc) {
  GetMutex();
  rawAcc = inRawAcc;
  ReleaseMutex();
}

void ImuData::SetRawMag(const Vector3D &inRawMag) {
  GetMutex();
  rawMag = inRawMag;
  ReleaseMutex();
}

void ImuData::SetRawGyr(const Vector3D &inRawGyr) {
  GetMutex();
  rawGyr = inRawGyr;
  ReleaseMutex();
}

void ImuData::SetRawAccMagAndGyr(const Vector3D &inRawAcc,
                                 const Vector3D &inRawMag,
                                 const Vector3D &inRawGyr) {
  GetMutex();
  rawAcc = inRawAcc;
  rawMag = inRawMag;
  rawGyr = inRawGyr;
  ReleaseMutex();
}

IODataElement *ImuData::Element(PlotableData_t data_type) const {
  string name;
  switch (data_type) {
  case ImuData::RawAx:
    name = "RawAx";
    break;
  case ImuData::RawAy:
    name = "RawAy";
    break;
  case ImuData::RawAz:
    name = "RawAz";
    break;
  case ImuData::RawGx:
    name = "RawGx";
    break;
  case ImuData::RawGy:
    name = "RawGy";
    break;
  case ImuData::RawGz:
    name = "RawGz";
    break;
  case ImuData::RawGxDeg:
    name = "RawGx degree";
    break;
  case ImuData::RawGyDeg:
    name = "RawGy degree";
    break;
  case ImuData::RawGzDeg:
    name = "RawGz degree";
    break;
  case ImuData::RawMx:
    name = "RawMx";
    break;
  case ImuData::RawMy:
    name = "RawMy";
    break;
  case ImuData::RawMz:
    name = "RawMz";
    break;
  }

  return new ImuDataElement(this, name, data_type);
}

void ImuData::CopyDatas(char *dst) const {
  GetMutex();

  Queue(&dst, &rawAcc.x, sizeof(rawAcc.x));
  Queue(&dst, &rawAcc.y, sizeof(rawAcc.y));
  Queue(&dst, &rawAcc.z, sizeof(rawAcc.z));

  Queue(&dst, &rawGyr.x, sizeof(rawGyr.x));
  Queue(&dst, &rawGyr.y, sizeof(rawGyr.y));
  Queue(&dst, &rawGyr.z, sizeof(rawGyr.z));

  Queue(&dst, &rawMag.x, sizeof(rawMag.x));
  Queue(&dst, &rawMag.y, sizeof(rawMag.y));
  Queue(&dst, &rawMag.z, sizeof(rawMag.z));

  ReleaseMutex();
}

void ImuData::Queue(char **dst, const void *src, size_t size) const {
  memcpy(*dst, src, size);
  *dst += size;
}

} // end namespace core
} // end namespace flair
