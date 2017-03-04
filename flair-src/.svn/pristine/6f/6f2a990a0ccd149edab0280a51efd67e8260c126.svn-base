// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/03/01
//  filename:   AhrsData.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class defining ahrs datas
//
//
/*********************************************************************/

#include "AhrsData.h"
#include "Euler.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

using std::string;

namespace flair {
namespace core {

/*! \class AhrsDataElement
    */
class AhrsDataElement : public IODataElement {
public:
  AhrsDataElement(const AhrsData *inAhrsData, string name,
                  AhrsData::PlotableData_t inPlotableData)
      : IODataElement(inAhrsData, name), ahrsData(inAhrsData),
        plotableData(inPlotableData) {

    size = sizeof(float);
  }

  ~AhrsDataElement() {}

  void CopyData(char *destination) const {
    float data;
    Vector3D angularRates;
    Euler eulerAngles;
    Quaternion quaternion;
    ahrsData->GetQuaternionAndAngularRates(quaternion, angularRates);
    quaternion.ToEuler(eulerAngles);
    switch (plotableData) {
    case AhrsData::Roll:
      data = eulerAngles.roll;
      break;
    case AhrsData::Pitch:
      data = eulerAngles.pitch;
      break;
    case AhrsData::Yaw:
      data = eulerAngles.yaw;
      break;
    case AhrsData::RollDeg:
      data = Euler::ToDegree(eulerAngles.roll);
      break;
    case AhrsData::PitchDeg:
      data = Euler::ToDegree(eulerAngles.pitch);
      break;
    case AhrsData::YawDeg:
      data = Euler::ToDegree(eulerAngles.yaw);
      break;
    case AhrsData::Q0:
      data = quaternion.q0;
      break;
    case AhrsData::Q1:
      data = quaternion.q1;
      break;
    case AhrsData::Q2:
      data = quaternion.q2;
      break;
    case AhrsData::Q3:
      data = quaternion.q3;
      break;
    case AhrsData::Wx:
      data = angularRates.x;
      break;
    case AhrsData::Wy:
      data = angularRates.y;
      break;
    case AhrsData::Wz:
      data = angularRates.z;
      break;
    case AhrsData::WxDeg:
      data = Euler::ToDegree(angularRates.x);
      break;
    case AhrsData::WyDeg:
      data = Euler::ToDegree(angularRates.y);
      break;
    case AhrsData::WzDeg:
      data = Euler::ToDegree(angularRates.z);
      break;
    default:
      ahrsData->Err("data type unavailable.\n");
      data = 0;
      break;
    }
    memcpy(destination, &data, sizeof(float));
  }

  const FloatType &GetDataType(void) const { return dataType; }

private:
  const AhrsData *ahrsData;
  AhrsData::PlotableData_t plotableData;
  FloatType dataType;
};

AhrsData::AhrsData(const Object *parent, std::string name, int n)
    : io_data(parent, name, n), dataType(floatType) {
  if (n > 1)
    Warn("n>1 not supported\n");

  AppendLogDescription("q0", floatType);
  AppendLogDescription("q1", floatType);
  AppendLogDescription("q2", floatType);
  AppendLogDescription("q3", floatType);

  AppendLogDescription("wx", floatType);
  AppendLogDescription("wy", floatType);
  AppendLogDescription("wz", floatType);
}

AhrsData::~AhrsData() {}

Quaternion AhrsData::GetQuaternion(void) const {
  Quaternion out;
  GetMutex();
  out = quaternion;
  ReleaseMutex();
  return out;
}

Vector3D AhrsData::GetAngularRates(void) const {
  Vector3D out;
  GetMutex();
  out = angularRates;
  ReleaseMutex();
  return out;
}

void AhrsData::GetQuaternionAndAngularRates(Quaternion &outQuaternion,
                                            Vector3D &outAngularRates) const {
  GetMutex();
  outQuaternion = quaternion;
  outAngularRates = angularRates;
  ReleaseMutex();
}

void AhrsData::SetQuaternionAndAngularRates(const Quaternion &inQuaternion,
                                            const Vector3D &inAngularRates) {
  GetMutex();
  quaternion = inQuaternion;
  angularRates = inAngularRates;
  ReleaseMutex();
}

void AhrsData::SetQuaternion(const Quaternion &inQuaternion) {
  GetMutex();
  quaternion = inQuaternion;
  ReleaseMutex();
}

void AhrsData::SetAngularRates(const Vector3D &inAngularRates) {
  GetMutex();
  angularRates = inAngularRates;
  ReleaseMutex();
}

IODataElement *AhrsData::Element(PlotableData_t plotableData) const {
  string name;
  switch (plotableData) {
  case AhrsData::Roll:
    name = "Roll";
    break;
  case AhrsData::Pitch:
    name = "Pitch";
    break;
  case AhrsData::Yaw:
    name = "Yaw";
    break;
  case AhrsData::RollDeg:
    name = "Roll degree";
    break;
  case AhrsData::PitchDeg:
    name = "Pitch degree";
    break;
  case AhrsData::YawDeg:
    name = "Yaw degree";
    break;
  case AhrsData::Q0:
    name = "Q0";
    break;
  case AhrsData::Q1:
    name = "Q1";
    break;
  case AhrsData::Q2:
    name = "Q2";
    break;
  case AhrsData::Q3:
    name = "Q3";
    break;
  case AhrsData::Wx:
    name = "Wx";
    break;
  case AhrsData::Wy:
    name = "Wy";
    break;
  case AhrsData::Wz:
    name = "Wz";
    break;
  case AhrsData::WxDeg:
    name = "Wx degree";
    break;
  case AhrsData::WyDeg:
    name = "Wy degree";
    break;
  case AhrsData::WzDeg:
    name = "Wz degree";
    break;
  default:
    Err("data type unavailable.\n");
  }

  return new AhrsDataElement(this, name, plotableData);
}

void AhrsData::CopyDatas(char *dst) const {
  GetMutex();
  Queue(&dst, &quaternion.q0, sizeof(quaternion.q0));
  Queue(&dst, &quaternion.q1, sizeof(quaternion.q1));
  Queue(&dst, &quaternion.q2, sizeof(quaternion.q2));
  Queue(&dst, &quaternion.q3, sizeof(quaternion.q3));

  Queue(&dst, &angularRates.x, sizeof(angularRates.x));
  Queue(&dst, &angularRates.y, sizeof(angularRates.y));
  Queue(&dst, &angularRates.z, sizeof(angularRates.z));
  ReleaseMutex();
}

void AhrsData::Queue(char **dst, const void *src, size_t size) const {
  memcpy(*dst, src, size);
  *dst += size;
}

} // end namespace core
} // end namespace flair
