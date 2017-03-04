// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "PushButton.h"
#include "ConnectionLayout.h"
#include <QPushButton>

PushButton::PushButton(Layout *parent, int row, int col, QString name)
    : XmlWidget(name, "PushButton", parent) {
  button = new QPushButton(name);
  parent->addWidget(button, row, col);

  SetValue("0");

  connect(button, SIGNAL(clicked(bool)), this, SLOT(button_clicked(bool)));
}

PushButton::~PushButton() { delete button; }

void PushButton::button_clicked(bool state) {
  SetValue("1");
  connectionLayout()->XmlToSend(XmlDoc());
  SetValue("0");
}
