// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef LAYOUT_H
#define LAYOUT_H

#include "XmlWidget.h"

class QWidget;
class QGridLayout;

class Layout : public XmlWidget {
public:
  Layout(QWidget *parent, XmlWidget *xml, QString name, QString type);
  Layout(Layout *parent, QString name, QString type);
  ~Layout();
  bool IsUptodate(void);
  void addWidget(QWidget *, int row, int column);
  QGridLayout *getQGridLayout();

  // QSplitter *splitter;
private:
  void Constructor(QString name);
  void XmlEvent(QDomElement dom);
  QGridLayout *qgridlayout;
};

#endif // LAYOUT_H
