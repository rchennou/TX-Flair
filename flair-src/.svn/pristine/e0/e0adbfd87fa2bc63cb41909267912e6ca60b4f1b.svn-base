// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file cvmatrix.h
 * \brief Class defining a matrix of kind CvMat
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/21
 * \version 4.0
 */

#ifndef CVMATRIX_H
#define CVMATRIX_H

#include <io_data.h>
#include <IODataElement.h>
#include <cvmatrix_descriptor.h>

class cvmatrix_impl;
struct CvMat;

namespace flair {
namespace core {

/*! \class cvmatrix
*
* \brief Class defining a matrix of kind CvMat
*
* CvMat is a matrix struct defined in OpenCV.
*
*/
class cvmatrix : public io_data {
public:
  class Type : public DataType {
  public:
    Type(size_t _nbRows, size_t _nbCols, ScalarType const &_elementDataType)
        : nbRows(_nbRows), nbCols(_nbCols), elementDataType(_elementDataType) {}
    size_t GetSize() const {
      return nbRows * nbCols * elementDataType.GetSize();
    }
    std::string GetDescription() const { return "matrix"; }
    size_t GetNbRows() const { return nbRows; }
    size_t GetNbCols() const { return nbCols; }
    ScalarType const &GetElementDataType() const { return elementDataType; }

  private:
    size_t nbRows, nbCols;
    ScalarType const &elementDataType;
  };

  /*!
  * \brief Constructor
  *
  * Construct an io_data representing a CvMat. \n
  * It uses a cvmatrix_descriptor to get size and elements' names. \n
  * Names are used for graphs and logs.
  *
  * \param parent parent
  * \param descriptor matrix description
  * \param type type of matrix elements
  * \param name name
  * \param n number of samples
  */
  cvmatrix(const Object *parent, const cvmatrix_descriptor *descriptor,
           ScalarType const &elementDataType, std::string name = "",
           uint32_t n = 1);

  /*!
  * \brief Constructor
  *
  * Construct an io_data representing a CvMat. \n
  * Elements are unamed.
  *
  * \param parent parent
  * \param rows matrix rows
  * \param cols matrix cols
  * \param type type of matrix elements
  * \param name name
  * \param n number of samples
  */
  cvmatrix(const Object *parent, uint32_t rows, uint32_t cols,
           ScalarType const &elementDataType, std::string name = "",
           uint32_t n = 1);

  /*!
  * \brief Destructor
  *
  */
  ~cvmatrix();

  /*!
  * \brief Element value
  *
  * Element is accessed by locking and unlocking the io_data Mutex.
  *
  * \param row element row
  * \param col element col
  *
  * \return element value
  */
  float Value(uint32_t row, uint32_t col) const;

  /*!
  * \brief Element value
  *
  * Element is not accessed by locking and unlocking the io_data Mutex. \n
  * Thus, this function should be called with Mutex locked. \n
  * This function is usefull when multiple successive access are done to the
  * elments of the matrix. It avoids unnecessary locking and unlocking.
  *
  * \param row element row
  * \param col element col
  *
  * \return element value
  */
  float ValueNoMutex(uint32_t row, uint32_t col) const;

  /*!
  * \brief Set element value
  *
  * Element is accessed by locking and unlocking the io_data Mutex.
  *
  * \param row element row
  * \param col element col
  * \param value element value
  */
  void SetValue(uint32_t row, uint32_t col, float value);

  /*!
  * \brief Set element value
  *
  * Element is not accessed by locking and unlocking the io_data Mutex. \n
  * Thus, this function should be called with Mutex locked. \n
  * This function is usefull when multiple successive access are done to the
  * elments of the matrix. It avoids unnecessary locking and unlocking.
  *
  * \param row element row
  * \param col element col
  * \param value element value
  */
  void SetValueNoMutex(uint32_t row, uint32_t col, float value);

  /*!
  * \brief get CvMat
  *
  * The io_data Mutex must be used by the user.
  */
  CvMat *getCvMat(void) const;

  /*!
  * \brief Element name
  *
  * If cvmatrix was created without cvmatrix_descriptor, element name is empty.
  *
  * \param row element row
  * \param col element col
  *
  * \return element name
  */
  std::string Name(uint32_t row, uint32_t col) const;

  /*!
  * \brief Element
  *
  * Get a pointer to a specific element. This pointer can be used for plotting.
  *
  * \param row element row
  * \param col element col
  *
  * \return pointer to the element
  */
  IODataElement *Element(uint32_t row, uint32_t col) const;

  /*!
  * \brief Element
  *
  * Get a pointer to a specific element. This pointer can be used for plotting.
  *\n
  * This function can be used for a 1D matrix.
  *
  * \param index element index
  *
  * \return pointer to the element
  */
  IODataElement *Element(uint32_t index) const;

  /*!
  * \brief Number of rows
  *
  * \return rows
  */
  uint32_t Rows(void) const;

  /*!
  * \brief Number of colomns
  *
  * \return colomns
  */
  uint32_t Cols(void) const;

  Type const &GetDataType() const { return dataType; };

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

  class cvmatrix_impl *pimpl_;
  Type dataType;
};

} // end namespace core
} // end namespace flair

#endif // CVMATRIX_H
