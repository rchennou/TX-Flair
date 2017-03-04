// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}

/*!
 * \file Vector3Ddata.h
 * \brief Class defining a 3D vector and a io_data
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/05/02
 * \version 4.0
 */
#ifndef VECTOR3DDATA_H
#define VECTOR3DDATA_H

#include <io_data.h>
#include <IODataElement.h>
#include <Vector3D.h>

namespace flair {
namespace core {

/*! \class Vector3Ddata
*
* \brief Class defining a 3D vector and a io_data
* User must manually use the io_data's Mutex to access to Vector3D values.
*/
class Vector3Ddata : public io_data, public Vector3D {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Vector3D using specified values.
  *
  * \param x
  * \param y
  * \param z
  */
  Vector3Ddata(const Object *parent, std::string name, float x = 0, float y = 0,
               float z = 0, uint32_t n = 1);

  /*!
  * \brief Destructor
  *
  */
  ~Vector3Ddata();

  /*!
  * \brief X Element
  *
  * Get a vectorer to x element. This pointer can be used for plotting.
  *
  * \return pointer to the element
  */
  IODataElement *XElement(void) const;

  /*!
  * \brief Y Element
  *
  * Get a pointer to y element. This pointer can be used for plotting.
  *
  * \return pointer to the element
  */
  IODataElement *YElement(void) const;

  /*!
  * \brief Z Element
  *
  * Get a pointer to z element. This pointer can be used for plotting.
  *
  * \return pointer to the element
  */
  IODataElement *ZElement(void) const;

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
};

} // end namespace core
} // end namespace flair

#endif // VECTOR3DDATA_H
