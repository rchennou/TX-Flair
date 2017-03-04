// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef SPINBOX_H
#define SPINBOX_H

#include "FormLayout.h"

class Layout;
class QSpinBox;

class SpinBox : public FormLayout {
  Q_OBJECT

public:
  SpinBox(Layout *parent, int row, int col, QString name, QString suffix,
          int value, int min, int max, int step);
  ~SpinBox();

private:
  QSpinBox *spinbox;
  int spinbox_value;
  void SetUptodate(void);
  void Reset(void);
  void LoadEvent(QDomElement dom);

  void ui_to_var(void);
  void ui_to_xml(void);

private slots:
  void valuechanged(int value);
};

#endif // SPINBOX_H
