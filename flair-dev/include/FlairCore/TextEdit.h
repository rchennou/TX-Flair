// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file TextEdit.h
 * \brief Class displaying a QTextEdit on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/08/17
 * \version 4.0
 */

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <Widget.h>

namespace flair {
namespace gui {

class LayoutPosition;

/*! \class TextEdit
*
* \brief Class displaying a QTextEdit on the ground station
*
* QTextEdit allows printing on multiple lines. \n
*
*/
class TextEdit : public Widget {
public:
  /*!
  * \brief Constructor
  *
  * Construct a QTabWidget at given position. \n
  * The TextEdit will automatically be child of position->getLayout() Layout.
  *After calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param parent parent
  * \param name name
  * \param buf_size size of the text buffer
  */
  TextEdit(const LayoutPosition *position, std::string name,
           size_t buf_size = 255);

  /*!
  * \brief Destructor
  *
  */
  ~TextEdit();

  /*!
  * \brief Append a line
  *
  * \param format text string to display, see standard printf
  */
  void Append(const char *format, ...);

private:
  char *printf_buffer;
  xmlNodePtr text_node;
};

} // end namespace gui
} // end namespace flair

#endif // TEXTEDIT_H
