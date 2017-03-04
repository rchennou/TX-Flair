// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef LABELWIDGET_H
#define LABELWIDGET_H

#include "XmlWidget.h"

class QFormLayout;
class Layout;

class FormLayout : public XmlWidget {

public:
  FormLayout(Layout *parent, int row, int col, QString name, QString type);
  ~FormLayout();

private:
  bool IsUptodate(void);
  virtual void SetUptodate(void) = 0;
  bool eventFilter(QObject *o, QEvent *e);

protected:
  QFormLayout *object_layout;
};

#endif // LABELWIDGET_H
