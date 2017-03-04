// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "Tab.h"
#include "TabWidget.h"
#include <QGridLayout>

Tab::Tab(TabWidget *parent, QString name, int position)
    : Layout(new QWidget(), parent, name, "Tab") {
  parent_tab = parent;
  onglet = getQGridLayout()->parentWidget();
  onglet->setObjectName(name);
  if (position == -1) {
    parent->tab->addTab(onglet, name);
  } else {
    parent->tab->insertTab(position, onglet, name);
  }
}

Tab::~Tab() { parent_tab->tab->removeTab(parent_tab->tab->indexOf(onglet)); }
