// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "TextEdit.h"
#include "Layout.h"
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>

TextEdit::TextEdit(Layout *parent, int row, int col, QString name)
    : XmlWidget(name, "TextEdit", parent) {

  visible_widget = new QWidget();
  visible_widget->setObjectName(name);

  layout = new QGridLayout(visible_widget);
  clear = new QPushButton("Effacer");
  text = new QTextEdit();

  layout->addWidget(text, 0, 0);
  layout->addWidget(clear, 1, 0);

  connect(clear, SIGNAL(clicked(bool)), text, SLOT(clear()));

  parent->addWidget(visible_widget, row, col);
}

TextEdit::~TextEdit() {}

void TextEdit::XmlEvent(QDomElement dom) {
  text->append(dom.attribute("value"));
}
