// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "TabWidget.h"
#include "Tab.h"
#include <stdio.h>
#include "Layout.h"

//#include "qledindicator.h"

TabWidget::TabWidget(Layout *parent, int row, int col, QString name,
                     QTabWidget::TabPosition position)
    : XmlWidget(name, "TabWidget", parent) {
  tab = new QTabWidget();
  // tab->setTabShape(QTabWidget::Triangular);
  // tab->setDocumentMode(true);
  parent->addWidget(tab, row, col);
  tab->setTabPosition(position);
  SetIsContainer(true);
  SetIsExpandable(true);
  visible_widget = tab;

  // QLedIndicator* led=new QLedIndicator(tab);
  // tab->setCornerWidget(led,Qt::TopLeftCorner);
}

TabWidget::~TabWidget() {}

void TabWidget::XmlEvent(QDomElement dom) {
  QString type = dom.tagName();
  QString name = dom.attribute("name");
  int position = dom.attribute("position").toInt();

  if (type == "Tab") {
    Tab *layout = new Tab(this, name, position);
  }
}

bool TabWidget::IsUptodate(void) {
  for (int i = 0; i < childs->count(); i++) {
    if (childs->at(i)->IsUptodate() == false)
      return false;
  }
  return true;
}
