// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "XmlWidget.h"

class QTextEdit;
class QPushButton;
class QGridLayout;
class Layout;

class TextEdit : public XmlWidget {
public:
  TextEdit(Layout *parent, int row, int col, QString name);
  ~TextEdit();

private:
  QGridLayout *layout;
  QPushButton *clear;
  QTextEdit *text;
  void XmlEvent(QDomElement dom);
};

#endif // TEXTEDIT_H
