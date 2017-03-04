// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "Label.h"
#include "Layout.h"
#include <QLabel>

Label::Label(Layout *parent, int row, int col, QString name)
    : XmlWidget(name, "Label", parent) {

  label = new QLabel();
  label->setObjectName(name);
  visible_widget = label;

  parent->addWidget(label, row, col);

  // pour ne pas faire de doublons qd on change le texte
  SetIsExpandable(true);
}

Label::~Label() {}

void Label::XmlEvent(QDomElement dom) {
  label->setText(dom.attribute("value"));
}
