// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file IODataElement.h
 * \brief Abstract class for accessing an element of an io_data.
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/11/26
 * \version 4.0
 */

#ifndef IODATAELEMENT_H
#define IODATAELEMENT_H

#include "io_data.h"

namespace flair {
namespace core {

class DataType;

/*! \class IODataElement
*
* \brief Abstract class for accessing an element of an io_data.
*/
class IODataElement : public Object {
public:
  /*!
  * \brief Constructor
  *
  * Construct an IODataElement. \n
  *
  */
  IODataElement(const io_data *parent, std::string name)
      : Object(parent, name) {
    this->parent = parent;
  }
  size_t Size() const { return size; }

  virtual void CopyData(char *dst) const = 0;

  /*!
  * \brief DataType
  *
  * \return type of data
  */
  virtual DataType const &GetDataType(void) const = 0;

protected:
  size_t size;

private:
  const io_data *parent;
};

} // end namespace core
} // end namespace framework

#endif // IODATAELEMENT_H
