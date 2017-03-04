// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef DATAPLOT2D_H_INCLUDED
#define DATAPLOT2D_H_INCLUDED

#include "DataRemote.h"
#include <stdint.h>
#include <QPen>

class Layout;
class QwtPlot;
class QwtPlotCurve;
class QwtPlotItem;
class QMouseEvent;

class DataPlot2D : public DataRemote {
  Q_OBJECT

public:
  DataPlot2D(Layout *parent, int row, int col, QString plot_name,
             QString x_name, QString y_name, float xmin, float xmax, float ymin,
             float ymax, bool enabled, int period);
  ~DataPlot2D();
  void addCurve(QPen pen, QString legend, QString type);

protected:
  void mousePressEvent(QMouseEvent *event);

private:
  QwtPlot *plot;
  void XmlEvent(QDomElement dom);
  void alignScales(void);
  void plot_data(double data_x, double data_y, int index);
  float xmin_orig, xmax_orig, ymin_orig, ymax_orig;

  QList<QwtPlotCurve *> *datas;
  QList<QString> *datas_type;
  QList<bool> datas_first_update;
  QList<double *> d_x;
  QList<double *> d_y;
  double view_size; // en s

  bool eventFilter(QObject *, QEvent *);
  void setYAxisScale(float ymin, float ymax);
  void setXAxisScale(float xmin, float xmax);
  void BufEvent(char **buf, int *buf_size, uint16_t period, bool big_endian);
  void showCurve(QwtPlotItem *item, bool on);

private slots:
  void legendChecked(const QVariant &itemInfo, bool on);
};

#endif // DATAPLOT2D_H_INCLUDED
