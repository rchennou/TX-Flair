// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "RangeFinderPlot.h"
#include "Layout.h"
#include <stdlib.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_rescaler.h>
#include <qwt_plot_shapeitem.h>
#include <QMouseEvent>
#include <QMenu>
#include <QInputDialog>
#include <qendian.h>
#include <qmath.h>

RangeFinderPlot::RangeFinderPlot(Layout *parent, int row, int col, QString name,
                                 QString x_name, QString y_name, float xmin,
                                 float xmax, float ymin, float ymax,
                                 float start_angle, float end_angle,
                                 uint32_t nb_samples, QString data_type,
                                 bool invert_axis, bool enabled, int period)
    : DataRemote(name, "RangeFinderPlot", parent, enabled, period) {
  invert_axis = true;
  this->start_angle = start_angle;
  this->end_angle = end_angle;
  this->nb_samples = nb_samples;
  this->data_type = data_type;
  this->invert_axis = invert_axis;

  if (data_type == "float") {
    receivesize = nb_samples * sizeof(float);
  } else if (data_type == "int8_t") {
    receivesize = nb_samples * sizeof(int8_t);
  } else if (data_type == "int16_t") {
    receivesize = nb_samples * sizeof(int16_t);
  } else {
    printf("RangeFinderPlot::RangeFinderPlot unknown type %s\n",
           data_type.toLocal8Bit().constData());
  }

  plot = new QwtPlot(NULL);
  plot->setEnabled(enabled);
  // plot->setAutoReplot( false );

  parent->addWidget(plot, row, col);
  visible_widget = plot;

  plot->setTitle(name);

  // grid
  QwtPlotGrid *grid = new QwtPlotGrid;
  grid->setPen(QPen(Qt::black, 0, Qt::DotLine));
  grid->attach(plot);

  plot->updateAxes();

  // zoomer
  QwtPlotMagnifier *zoomer = new QwtPlotMagnifier(plot->canvas());
  zoomer->setMouseButton(Qt::RightButton, Qt::ControlModifier);

  // scroller
  QwtPlotPanner *scroller = new QwtPlotPanner(plot->canvas());

  // Axis
  if (!invert_axis) {
    plot->setAxisTitle(QwtPlot::xBottom, x_name);
    setXAxisScale(xmin, xmax);

    plot->setAxisTitle(QwtPlot::yLeft, y_name);
    setYAxisScale(ymin, ymax);
  } else {
    plot->setAxisTitle(QwtPlot::xBottom, y_name);
    setXAxisScale(ymin, ymax);

    plot->setAxisTitle(QwtPlot::yLeft, x_name);
    setYAxisScale(xmin, xmax);
  }

  QwtPlotRescaler *rescaler = new QwtPlotRescaler(plot->canvas());
  rescaler->setRescalePolicy(QwtPlotRescaler::Fixed);

  //( void ) new QwtPlotMagnifier( plot->canvas() );

  plot->canvas()->installEventFilter(this);

  for (uint32_t i = 0; i < nb_samples; i++) {
    addTriangle(start_angle + i * (end_angle - start_angle + 1) / nb_samples,
                start_angle +
                    (i + 1) * (end_angle - start_angle + 1) / nb_samples);
  }
}

RangeFinderPlot::~RangeFinderPlot() { delete plot; }

void RangeFinderPlot::XmlEvent(QDomElement dom) { XmlSetup(dom); }

bool RangeFinderPlot::eventFilter(QObject *o, QEvent *e) {
  if (o == plot->canvas()) {
    switch (e->type()) {
    case QEvent::MouseButtonPress: {
      mousePressEvent((QMouseEvent *)e);
      break;
    }

    default:
      break;
    }
  }
  return plot->eventFilter(o, e);
}

//
//  Set a plain canvas frame and align the scales to it
//
void RangeFinderPlot::alignScales(void) {
  // The code below shows how to align the scales to
  // the canvas frame, but is also a good example demonstrating
  // why the spreaded API needs polishing.
  /*
      plot->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
      plot->canvas()->setLineWidth(1);
  */
  for (int i = 0; i < QwtPlot::axisCnt; i++) {
    QwtScaleWidget *scaleWidget = (QwtScaleWidget *)plot->axisWidget(i);
    if (scaleWidget)
      scaleWidget->setMargin(0);

    QwtScaleDraw *scaleDraw = (QwtScaleDraw *)plot->axisScaleDraw(i);
    if (scaleDraw)
      scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
  }
}

void RangeFinderPlot::setXAxisScale(float xmin, float xmax) {
  xmin_orig = xmin;
  xmax_orig = xmax;
  plot->setAxisScale(QwtPlot::xBottom, xmin_orig, xmax_orig);
}

void RangeFinderPlot::setYAxisScale(float ymin, float ymax) {
  ymin_orig = ymin;
  ymax_orig = ymax;
  plot->setAxisScale(QwtPlot::yLeft, ymin_orig, ymax_orig);
}

void RangeFinderPlot::BufEvent(char **buf, int *buf_size, uint16_t period,
                               bool big_endian) {
  plot->setEnabled(IsEnabled());
  if (IsEnabled() == false || RefreshRate_ms() != period)
    return;

  for (uint32_t i = 0; i < nb_samples; i++) {
    if (data_type == "float") {
      uint32_t data_raw;
      float *data = (float *)&data_raw;

      memcpy((void *)&data_raw, *buf, sizeof(uint32_t));
      *buf += sizeof(uint32_t);
      if (big_endian == true)
        data_raw = qFromBigEndian(data_raw);
      SetTriangle(i, *data);
    } else if (data_type == "int8_t") {
      int8_t data;
      memcpy((void *)&data, *buf, sizeof(data));
      *buf += sizeof(data);
      SetTriangle(i, data);
    } else if (data_type == "int16_t") {
      int16_t data;
      memcpy((void *)&data, *buf, sizeof(data));
      *buf += sizeof(data);
      if (big_endian == true)
        data = qFromBigEndian(data);
      SetTriangle(i, data);
    } else {
      printf("RangeFinderPlot::BufEvent unknown type %s\n",
             data_type.toLocal8Bit().constData());
    }
  }

  plot->replot();
}

void RangeFinderPlot::addTriangle(float angle_min, float angle_max) {
  QwtPlotShapeItem *item = new QwtPlotShapeItem();

  item->setRenderHint(QwtPlotItem::RenderAntialiased, true);
  item->attach(plot);
  triangles.append(item);
}

void RangeFinderPlot::SetTriangle(uint32_t id, float length) {
  QPainterPath path;
  QPolygonF triangle;
  float angle_min =
      start_angle + id * (end_angle - start_angle + 1) / nb_samples;
  float angle_max =
      start_angle + (id + 1) * (end_angle - start_angle + 1) / nb_samples;

  if (invert_axis) {
    angle_min = 90 - angle_min;
    angle_max = 90 - angle_max;
  }

  triangle += QPointF(0, 0);
  triangle += QPointF(length * cos(angle_min * M_PI / 180.),
                      length * sin(angle_min * M_PI / 180.));
  triangle += QPointF(length * cos(angle_max * M_PI / 180.),
                      length * sin(angle_max * M_PI / 180.));

  path.addPolygon(triangle);

  path.closeSubpath();
  triangles.at(id)->setShape(path);

  QColor fillColor = "SandyBrown";
  fillColor.setAlpha(200);

  QPen pen(QColor("SandyBrown"), 1);
  pen.setJoinStyle(Qt::MiterJoin);
  triangles.at(id)->setPen(pen);
  triangles.at(id)->setBrush(fillColor);
}

// context menu
void RangeFinderPlot::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    QMenu *menu = new QMenu("nom", plot);
    // ajout des actions
    QAction *a, *z;

    a = menu->addAction("reset y zoom");

    appendmenu(menu);
    z = execmenu(plot, menu, event->globalPos());
    delete menu;

    if (z == a) {
      // zoom to original size
      if (!invert_axis) {
        plot->setAxisScale(QwtPlot::yLeft, ymin_orig, ymax_orig);
      } else {
        plot->setAxisScale(QwtPlot::yLeft, xmin_orig, xmax_orig);
      }
      plot->replot();
    }
  }
}
