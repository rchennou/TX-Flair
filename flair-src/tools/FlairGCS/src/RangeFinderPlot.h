// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef RANGEFINDERPLOT_H_INCLUDED
#define RANGEFINDERPLOT_H_INCLUDED

#include "DataRemote.h"
#include <stdint.h>

class QwtPlotShapeItem;
class Layout;
class QwtPlot;
class QMouseEvent;

class RangeFinderPlot : public DataRemote {
  Q_OBJECT

public:
  RangeFinderPlot(Layout *parent, int row, int col, QString name,
                  QString x_name, QString y_name, float xmin, float xmax,
                  float ymin, float ymax, float start_angle, float end_angle,
                  uint32_t nb_samples, QString data_type, bool invert_axis,
                  bool enabled, int period);
  ~RangeFinderPlot();

protected:
  void mousePressEvent(QMouseEvent *event);

private:
  void setYAxisScale(float ymin, float ymax);
  void setXAxisScale(float xmin, float xmax);
  void addTriangle(float angle_min, float angle_max);
  void SetTriangle(uint32_t id, float length);
  QwtPlot *plot;
  void XmlEvent(QDomElement dom);
  void alignScales(void);
  float xmin_orig, xmax_orig, ymin_orig, ymax_orig;
  float start_angle, end_angle;
  uint32_t nb_samples;
  QString data_type;
  QList<QwtPlotShapeItem *> triangles;
  bool invert_axis;

  bool eventFilter(QObject *, QEvent *);
  void BufEvent(char **buf, int *buf_size, uint16_t period, bool big_endian);
};

#endif // RANGEFINDERPLOT_H_INCLUDED
