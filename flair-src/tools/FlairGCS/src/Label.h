// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef LABEL_H
#define LABEL_H

#include "XmlWidget.h"

class Layout;
class QLabel;

class Label : public XmlWidget {
public:
  Label(Layout *parent, int row, int col, QString name);
  ~Label();

private:
  void XmlEvent(QDomElement dom);
  QLabel *label;
};

#endif // LABEL_H
