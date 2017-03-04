// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "GridLayout.h"
#include <QWidget>
#include <QGridLayout>

GridLayout::GridLayout(Layout *parent, int row, int col, QString name)
    : Layout(parent, name, "GridLayout") {
  widget = new QWidget();
  widget->setObjectName(name);

  visible_widget = widget;

  parent->addWidget(widget, row, col);

  widget->setLayout(getQGridLayout());
}

GridLayout::~GridLayout() { widget->setParent(NULL); }
