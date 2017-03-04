// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "XmlWidget.h"

class QPushButton;
class Layout;

class PushButton : public XmlWidget {
  Q_OBJECT

public:
  PushButton(Layout *parent, int row, int col, QString name);
  ~PushButton();

private:
  QPushButton *button;

private slots:
  void button_clicked(bool state);
};

#endif // PUSHBUTTON_H
