// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef TABWIDGET_H
#define TABWIDGET_H

#include "XmlWidget.h"
#include <QTabWidget>

class Layout;

class TabWidget : public XmlWidget {
  friend class Tab;

public:
  TabWidget(Layout *parent, int row, int col, QString name,
            QTabWidget::TabPosition position);
  ~TabWidget();
  bool IsUptodate(void);

private:
  QTabWidget *tab;
  void XmlEvent(QDomElement dom);
};

#endif // TABWIDGET_H
