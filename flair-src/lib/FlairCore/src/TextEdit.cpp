// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/17
//  filename:   TextEdit.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QTextEdit on the ground station
//
//
/*********************************************************************/

#include "TextEdit.h"
#include "Layout.h"
#include "LayoutPosition.h"

using std::string;

namespace flair {
namespace gui {

TextEdit::TextEdit(const LayoutPosition *position, string name, size_t buf_size)
    : Widget(position->getLayout(), name, "TextEdit") {
  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());
  SendXml();

  delete position;

  //    text_node=AddXmlChild("Text");

  printf_buffer = (char *)malloc(buf_size);
  if (printf_buffer == NULL)
    Err("erreur malloc\n");
}

TextEdit::~TextEdit() { free(printf_buffer); }

void TextEdit::Append(const char *format, ...) {
  int n;

  va_list args;
  va_start(args, format);
  n = vsprintf(printf_buffer, format, args);
  va_end(args);
  if (n <= 0)
    return;

  SetVolatileXmlProp("value", printf_buffer, text_node);
  SendXml();
}

} // end namespace gui
} // end namespace flair
