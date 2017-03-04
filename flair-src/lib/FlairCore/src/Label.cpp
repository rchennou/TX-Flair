// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/17
//  filename:   Label.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QLabel on the ground station
//
//
/*********************************************************************/

#include "Label.h"
#include "Layout.h"
#include "LayoutPosition.h"

using std::string;

namespace flair {
namespace gui {

Label::Label(const LayoutPosition *position, string name, size_t buf_size)
    : Widget(position->getLayout(), name, "Label") {
  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());

  SendXml();

  printf_buffer = (char *)malloc(buf_size);
  if (printf_buffer == NULL)
    Err("erreur malloc\n");

  delete position;
}

Label::~Label() {
  if (printf_buffer != NULL)
    free(printf_buffer);
  printf_buffer = NULL;
}

void Label::SetText(const char *format, ...) {
  int n;

  va_list args;
  va_start(args, format);
  n = vsprintf(printf_buffer, format, args);
  va_end(args);
  if (n <= 0)
    return;

  SetVolatileXmlProp("value", printf_buffer);
  SendXml();
}

} // end namespace gui
} // end namespace flair
