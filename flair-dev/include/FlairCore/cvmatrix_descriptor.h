// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file cvmatrix_descriptor.h
 * \brief Class describing cvmatrix elements, for log and graphs purpose
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/05
 * \version 4.0
 */

#ifndef CVMATRIX_DESCRIPTOR_H
#define CVMATRIX_DESCRIPTOR_H

#include <string>

namespace flair {
namespace core {

/*! \class cvmatrix_descriptor
*
* \brief Class describing cvmatrix elements, for log and graphs purpose
*
* This class allows to give a name to matrix elements. These names
* will be used in graphs and logs.
*/
class cvmatrix_descriptor {
public:
  /*!
  * \brief Constructor
  *
  * Construct a matrix descriptor.
  *
  * \param rows matrix rows
  * \param cols matrix cols
  */
  cvmatrix_descriptor(uint32_t rows, uint32_t cols);

  /*!
  * \brief Destructor
  *
  */
  ~cvmatrix_descriptor();

  /*!
  * \brief Set element name
  *
  * \param row element row
  * \param col element col
  * \param name element name
  */
  void SetElementName(uint32_t row, uint32_t col, std::string name);

  /*!
  * \brief Element name
  *
  * \param row element row
  * \param col element col
  *
  * \return element name
  */
  std::string ElementName(uint32_t row, uint32_t col) const;

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

private:
  uint32_t rows, cols;
  std::string **element_names;
};

} // end namespace core
} // end namespace flair

#endif // CVMATRIX_DESCRIPTOR_H
