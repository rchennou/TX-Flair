// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "GroupBox.h"
#include <QGroupBox>
#include <QGridLayout>

GroupBox::GroupBox(Layout *parent, int row, int col, QString name)
    : Layout(parent, name, "GroupBox") {
  // creation et ajout QGroupBox
  box = new QGroupBox(name);
  box->setObjectName(name);

  visible_widget = box;

  parent->addWidget(box, row, col);
  // parent->splitter->addWidget(box);

  box->setLayout(getQGridLayout());
}

GroupBox::~GroupBox() {
  // layout->removeItem(this);//ne semble pas necessaire

  box->setParent(NULL); // sinon le delete layout detruit aussi this
  // delete layout;
  // delete box;
}
