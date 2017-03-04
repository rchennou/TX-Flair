// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef VECTOR3DSPINBOX_H
#define VECTOR3DSPINBOX_H

#include "XmlWidget.h"
#include <QDoubleSpinBox>

class Layout;
class QGroupBox;
class QGridLayout;

class Vector3DSpinBox : public XmlWidget {
  Q_OBJECT

public:
  // handle value as string, becouse double value are not exact
  Vector3DSpinBox(Layout *parent, int row, int col, QString name,
                  QString value[3], float min, float max, float step,
                  int decimals);
  ~Vector3DSpinBox();

private:
  QGridLayout *qgridlayout;
  QGroupBox *box;
  QDoubleSpinBox doublespinbox[3];
  QString doublespinbox_value[3];
  void AddElement(QString name, int index);
  void SetUptodate(void);
  void SetValues(QString value[3]);
  void Reset(void);
  void LoadEvent(QDomElement dom);
  void ui_to_var(void);
  void ui_to_xml(void);
  bool eventFilter(QObject *o, QEvent *e);
  void adjust_decimals(QString value[3]);
  bool IsUptodate(void);

private slots:
  void valuechanged(const QString &value);
};

#endif // VECTOR3DSPINBOX_H
