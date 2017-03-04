// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "FormLayout.h"

class Layout;
class QCheckBox;

class CheckBox : public FormLayout {
  Q_OBJECT

public:
  CheckBox(Layout *parent, int row, int col, QString name, bool value);
  ~CheckBox();

private:
  QCheckBox *checkbox;
  bool checkbox_value;
  void SetUptodate(void);
  void Reset(void);
  void LoadEvent(QDomElement dom);

  void ui_to_var(void);
  void ui_to_xml(void);

private slots:
  void valuechanged(bool value);
};

#endif // CHECKBOX_H
