// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/11/26
//  filename:   Vector3Ddata.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a 3D vector and a io_data
//
//
/*********************************************************************/

#include "Vector3Ddata.h"
#include <string.h>

#define X 0
#define Y 1
#define Z 2

using std::string;

namespace flair {
namespace core {

/*! \class Vector3DdataElement
 */
class Vector3DdataElement : public IODataElement {
public:
  Vector3DdataElement(const Vector3Ddata *data, string name, uint32_t elem)
      : IODataElement(data, name) {
    this->data = data;
    this->elem = elem;
    size = 4;
  }

  ~Vector3DdataElement() {}

  void CopyData(char *dst) const {
    float value;
    data->GetMutex();
    switch (elem) {
    case X:
      value = data->x;
      break;
    case Y:
      value = data->y;
      break;
    case Z:
      value = data->z;
      break;
    default:
      data->Err("type not handled\n");
      value = 0;
      break;
    }
    data->ReleaseMutex();

    memcpy(dst, &value, sizeof(float));
  }

  ScalarType const &GetDataType() const { return dataType; }

private:
  const Vector3Ddata *data;
  uint32_t elem;
  FloatType dataType;
};

Vector3Ddata::Vector3Ddata(const Object *parent, string name, float x, float y,
                           float z, uint32_t n)
    : io_data(parent, name, n), Vector3D(x, y, z) {}

Vector3Ddata::~Vector3Ddata() {}

void Vector3Ddata::CopyDatas(char *dst) const {
  GetMutex();
  memcpy(dst, &x, sizeof(float));
  memcpy(dst + sizeof(float), &y, sizeof(float));
  memcpy(dst + 2 * sizeof(float), &z, sizeof(float));
  ReleaseMutex();
}

IODataElement *Vector3Ddata::XElement(void) const {
  return new Vector3DdataElement(this, "x", X);
}

IODataElement *Vector3Ddata::YElement(void) const {
  return new Vector3DdataElement(this, "y", Y);
}

IODataElement *Vector3Ddata::ZElement(void) const {
  return new Vector3DdataElement(this, "z", Z);
}

} // end namespace core
} // end namespace flair
