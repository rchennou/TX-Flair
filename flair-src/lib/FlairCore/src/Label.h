// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Label.h
 * \brief Class displaying a QLabel on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/08/17
 * \version 4.0
 */

#ifndef LABEL_H
#define LABEL_H

#include <Widget.h>

namespace flair {
namespace gui {

class LayoutPosition;

/*! \class Label
*
* \brief Class displaying a QLabel on the ground station
*
*/
class Label : public Widget {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QLabel at given position. \n
  * The Label will automatically be child of position->getLayout() Layout. After
  *calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param parent parent
  * \param name name
  * \param buf_size size of the text buffer
  */
  Label(const LayoutPosition *position, std::string name,
        size_t buf_size = 255);

  /*!
  * \brief Destructor
  *
  */
  ~Label();

  /*!
  * \brief Set text
  *
  * \param format text string to display, see standard printf
  */
  void SetText(const char *format, ...);

private:
  char *printf_buffer;
};

} // end namespace gui
} // end namespace flair

#endif // LABEL_H
