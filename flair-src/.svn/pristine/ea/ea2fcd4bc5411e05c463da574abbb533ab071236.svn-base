// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef DATAPLOT1D_H_INCLUDED
#define DATAPLOT1D_H_INCLUDED

#include <ScopeFixedStep.h>
#include "DataRemote.h"

class Layout;
class QMouseEvent;

class DataPlot1D : public ScopeFixedStep, public DataRemote {
public:
  DataPlot1D(Layout *parent, int row, int col, QString title, float ymin,
             float ymax, bool enabled, int period);
  ~DataPlot1D();

private:
  void XmlEvent(QDomElement dom);
  bool eventFilter(QObject *, QEvent *);
  void BufEvent(char **buf, int *buf_size, uint16_t period, bool big_endian);
  bool mouseEvent(QMouseEvent *event);
  QList<QString> datas_type;
};

#endif // DATAPLOT1D_H_INCLUDED
