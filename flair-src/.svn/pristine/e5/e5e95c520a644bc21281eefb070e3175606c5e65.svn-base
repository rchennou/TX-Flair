// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "FormLayout.h"

class QComboBox;
class Layout;

class ComboBox : public FormLayout {
  Q_OBJECT

public:
  ComboBox(Layout *parent, int row, int col, QString name, int value);
  ~ComboBox();

private:
  QComboBox *combobox;
  int combobox_value;
  void XmlEvent(QDomElement dom);
  void SetUptodate(void);
  void Reset(void);
  void LoadEvent(QDomElement dom);

  void ui_to_var(void);
  void ui_to_xml(void);

private slots:
  void valuechanged(int value);
};

#endif // COMBOBOX_H
