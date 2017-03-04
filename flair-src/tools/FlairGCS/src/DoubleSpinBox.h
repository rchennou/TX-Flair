// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include "FormLayout.h"

class Layout;
class QDoubleSpinBox;

class DoubleSpinBox : public FormLayout {
  Q_OBJECT

public:
  // handle value as string, becouse double value are not exact
  DoubleSpinBox(Layout *parent, int row, int col, QString name, QString suffix,
                QString value, float min, float max, float step, int decimals);
  ~DoubleSpinBox();

private:
  QDoubleSpinBox *doublespinbox;
  QString doublespinbox_value;
  void SetUptodate(void);
  void Reset(void);
  void LoadEvent(QDomElement dom);
  void ui_to_var(void);
  void ui_to_xml(void);
  bool eventFilter(QObject *o, QEvent *e);
  void adjust_decimals(QString value);

private slots:
  void valuechanged(const QString &value);
};

#endif // DOUBLESPINBOX_H
