// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "DataPlot2D.h"
#include "Layout.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_widget.h>
#include <qwt_legend_label.h>
#include <qwt_legend.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_rescaler.h>
#include <QMouseEvent>
#include <QMenu>
#include <QInputDialog>
#include <qendian.h>

DataPlot2D::DataPlot2D(Layout *parent, int row, int col, QString plot_name,
                       QString x_name, QString y_name, float xmin, float xmax,
                       float ymin, float ymax, bool enabled, int period)
    : DataRemote(plot_name, "DataPlot2D", parent, enabled, period) {
  plot = new QwtPlot(NULL);
  plot->setEnabled(enabled);

  parent->addWidget(plot, row, col);
  visible_widget = plot;

  view_size = 20; // default 20s
                  /*
                      // Disable polygon clipping
                      QwtPainter::setDeviceClipping(false);
                  
                      // We don't need the cache here
                      plot->canvas()->setPaintAttribute(QwtPlotCanvas::PaintCached, false);
                      plot->canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, false);
                  */
#if QT_VERSION >= 0x040000
#ifdef Q_WS_X11
  /*
     Qt::WA_PaintOnScreen is only supported for X11, but leads
     to substantial bugs with Qt 4.2.x/Windows
   */
  plot->canvas()->setAttribute(Qt::WA_PaintOnScreen, true);
#endif
#endif

  alignScales();

  // d_x=new QList<double*>;
  // d_y=new QList<double*>;
  datas = new QList<QwtPlotCurve *>;
  datas_type = new QList<QString>;

  // Assign a title
  plot->setTitle(plot_name);

  // Axis
  plot->setAxisTitle(QwtPlot::xBottom, x_name);
  setXAxisScale(xmin, xmax);

  plot->setAxisTitle(QwtPlot::yLeft, y_name);
  setYAxisScale(ymin, ymax);

  QwtPlotRescaler *rescaler = new QwtPlotRescaler(plot->canvas());
  rescaler->setRescalePolicy(QwtPlotRescaler::Fixed); /*
 rescaler->setReferenceAxis(QwtPlot::xBottom);
 rescaler->setAspectRatio(QwtPlot::yLeft, 1.0);*/

  // grid
  QwtPlotGrid *grid = new QwtPlotGrid;
  // grid->enableXMin(false);
  grid->setPen(QPen(Qt::black, 0, Qt::DotLine));
  // grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
  grid->attach(plot);

  // zoomer
  QwtPlotMagnifier *zoomer = new QwtPlotMagnifier(plot->canvas());
  zoomer->setMouseButton(Qt::RightButton, Qt::ControlModifier);

  // scroller
  QwtPlotPanner *scroller = new QwtPlotPanner(plot->canvas());

  // legend
  QwtLegend *new_legend = new QwtLegend();
  new_legend->setDefaultItemMode(QwtLegendData::Checkable);
  plot->insertLegend(new_legend, QwtPlot::BottomLegend);

  connect(new_legend, SIGNAL(checked(const QVariant &, bool, int)),
          SLOT(legendChecked(const QVariant &, bool)));

  plot->canvas()->installEventFilter(this);
}

DataPlot2D::~DataPlot2D() {
  for (int i = 0; i < d_x.count(); i++) {
    free(d_x.at(i));
    free(d_y.at(i));
  }

  delete datas;
  delete datas_type;
}

void DataPlot2D::XmlEvent(QDomElement dom) {
  if (dom.attribute("curve") != "") {
    QString type = dom.attribute("type");
    int r = dom.attribute("r").toInt();
    int g = dom.attribute("g").toInt();
    int b = dom.attribute("b").toInt();
    QString name = dom.attribute("curve");
    addCurve(QPen(QColor(r, g, b, 255)), name, type);
  } else {
    XmlSetup(dom);
  }
}

bool DataPlot2D::eventFilter(QObject *o, QEvent *e) {
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

void DataPlot2D::legendChecked(const QVariant &itemInfo, bool on) {
  QwtPlotItem *plotItem = plot->infoToItem(itemInfo);
  if (plotItem)
    showCurve(plotItem, on);
}

void DataPlot2D::showCurve(QwtPlotItem *item, bool on) {
  item->setVisible(on);

  QwtLegend *lgd = qobject_cast<QwtLegend *>(plot->legend());

  QList<QWidget *> legendWidgets = lgd->legendWidgets(plot->itemToInfo(item));

  if (legendWidgets.size() == 1) {
    QwtLegendLabel *legendLabel =
        qobject_cast<QwtLegendLabel *>(legendWidgets[0]);

    if (legendLabel)
      legendLabel->setChecked(on);
  }

  plot->replot();
}

void DataPlot2D::addCurve(QPen pen, QString legend, QString type) {
  double *new_dx;
  new_dx = (double *)malloc(view_size / refresh_rate * sizeof(double));
  d_x.append(new_dx);
  double *new_dy;
  new_dy = (double *)malloc(view_size / refresh_rate * sizeof(double));
  d_y.append(new_dy);

  //  Initialize data
  for (int i = 0; i < view_size / refresh_rate; i++)
    new_dx[i] = 0;
  for (int i = 0; i < view_size / refresh_rate; i++)
    new_dy[i] = 0;

  // Insert new curve
  QwtPlotCurve *new_data;

  new_data = new QwtPlotCurve(legend);
  new_data->attach(plot);
  new_data->setPen(pen);
  datas->append(new_data);

  showCurve(new_data, true);

  datas_type->append(type);
  bool tmp = true;
  datas_first_update.append(tmp);

  // Attach (don't copy) data. Both curves use the same x array.
  new_data->setRawSamples(new_dx, new_dy, view_size / refresh_rate);

  if (type == "float") {
    receivesize += sizeof(float);
  } else if (type == "int8_t") {
    receivesize += sizeof(int8_t);
  } else if (type == "int16_t") {
    receivesize += sizeof(int16_t);
  } else {
    printf("DataPlot2D::addCurve unknown type %s\n",
           type.toLocal8Bit().constData());
  }
}

void DataPlot2D::setXAxisScale(float xmin, float xmax) {
  xmin_orig = xmin;
  xmax_orig = xmax;
  plot->setAxisScale(QwtPlot::xBottom, xmin_orig, xmax_orig);
}

void DataPlot2D::setYAxisScale(float ymin, float ymax) {
  ymin_orig = ymin;
  ymax_orig = ymax;
  plot->setAxisScale(QwtPlot::yLeft, ymin_orig, ymax_orig);
}

//
//  Set a plain canvas frame and align the scales to it
//
void DataPlot2D::alignScales(void) {
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

void DataPlot2D::BufEvent(char **buf, int *buf_size, uint16_t period,
                          bool big_endian) {
  plot->setEnabled(IsEnabled());
  if (IsEnabled() == false || RefreshRate_ms() != period)
    return;

  for (int i = 0; i < datas->count(); i++) {
    if (datas_type->at(i) == "float") {
      uint32_t data1_raw;
      float *data1 = (float *)&data1_raw;
      uint32_t data2_raw;
      float *data2 = (float *)&data2_raw;

      memcpy((void *)&data1_raw, *buf, sizeof(uint32_t));
      *buf += sizeof(uint32_t);
      memcpy((void *)&data2_raw, *buf, sizeof(uint32_t));
      *buf += sizeof(uint32_t);
      if (big_endian == true)
        data1_raw = qFromBigEndian(data1_raw);
      if (big_endian == true)
        data2_raw = qFromBigEndian(data2_raw);
      plot_data(*data1, *data2, i);
    } else if (datas_type->at(i) == "int8_t") {
      int8_t data1, data2;
      memcpy((void *)&data1, *buf, sizeof(data1));
      *buf += sizeof(data1);
      memcpy((void *)&data2, *buf, sizeof(data2));
      *buf += sizeof(data2);
      plot_data(data1, data2, i);
    } else if (datas_type->at(i) == "int16_t") {
      int16_t data1, data2;
      memcpy((void *)&data1, *buf, sizeof(data1));
      *buf += sizeof(data1);
      memcpy((void *)&data2, *buf, sizeof(data2));
      *buf += sizeof(data2);
      plot_data(data1, data2, i);
    } else {
      printf("DataPlot1D::DrawDatas type non connu\n");
    }
  }

  plot->replot();
}

void DataPlot2D::plot_data(double data_x, double data_y, int index) {
  if (index < d_y.count()) {
    if (datas_first_update.at(index) == false) {
      // Shift y array left and assign new value to y[view_size/refresh_rate -
      // 1].
      for (int j = 0; j < view_size / refresh_rate - 1; j++)
        d_y.at(index)[j] = d_y.at(index)[j + 1];
      for (int j = 0; j < view_size / refresh_rate - 1; j++)
        d_x.at(index)[j] = d_x.at(index)[j + 1];
      d_y.at(index)[(int)(view_size / refresh_rate) - 1] = data_y;
      d_x.at(index)[(int)(view_size / refresh_rate) - 1] = data_x;
    } else {
      for (int j = 0; j <= view_size / refresh_rate - 1; j++)
        d_y.at(index)[j] = data_y;
      for (int j = 0; j <= view_size / refresh_rate - 1; j++)
        d_x.at(index)[j] = data_x;
      datas_first_update[index] = false;
    }
  }
}

// context menu
void DataPlot2D::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {

    QMenu *menu = new QMenu("nom", plot);
    // ajout des actions
    QAction *a, *z, *d;

    a = menu->addAction("reset zoom");
    menu->addSeparator();

    d = menu->addAction(QString("set view size (%1s)").arg(view_size));

    appendmenu(menu);
    z = execmenu(plot, menu, event->globalPos());
    delete menu;

    if (z == a) {
      // zoom to original size
      plot->setAxisScale(QwtPlot::yLeft, ymin_orig, ymax_orig);
      plot->setAxisScale(QwtPlot::xBottom, xmin_orig, xmax_orig);
    }

    if (z == d) {
      bool ok;
      float time = QInputDialog::getInt(
          plot, QString("Set view size (%1)").arg(plot->title().text()),
          tr("Value (s):"), view_size, 1, 65535, 10, &ok);
      if (ok == true) {
        for (int i = 0; i < datas->count(); i++) {
          if (time > view_size) {
            double *buf =
                (double *)malloc(time / refresh_rate * sizeof(double));
            d_x[i] = (double *)realloc(d_x.at(i),
                                       time / refresh_rate * sizeof(double));
            memcpy(buf, d_x[i], (view_size / refresh_rate) * sizeof(double));
            memcpy(&d_x[i][(int)(time / refresh_rate) -
                           (int)(view_size / refresh_rate)],
                   buf, (view_size / refresh_rate) * sizeof(double));
            d_y[i] = (double *)realloc(d_y.at(i),
                                       time / refresh_rate * sizeof(double));
            memcpy(buf, d_y[i], (view_size / refresh_rate) * sizeof(double));
            memcpy(&d_y[i][(int)(time / refresh_rate) -
                           (int)(view_size / refresh_rate)],
                   buf, (view_size / refresh_rate) * sizeof(double));
            free(buf);
            for (int j = 0; j < (int)(time / refresh_rate) -
                                    (int)(view_size / refresh_rate);
                 j++) {
              d_x.at(i)[j] = d_x.at(i)[(int)(time / refresh_rate) -
                                       (int)(view_size / refresh_rate) + 1];
              d_y.at(i)[j] = d_y.at(i)[(int)(time / refresh_rate) -
                                       (int)(view_size / refresh_rate) + 1];
            }
          } else {
            double *buf =
                (double *)malloc(time / refresh_rate * sizeof(double));
            memcpy(buf, &d_x[i][(int)(view_size / refresh_rate) -
                                (int)(time / refresh_rate)],
                   (time / refresh_rate) * sizeof(double));
            d_x[i] = (double *)realloc(d_x.at(i),
                                       time / refresh_rate * sizeof(double));
            memcpy(d_x[i], buf, (time / refresh_rate) * sizeof(double));
            memcpy(buf, &d_y[i][(int)(view_size / refresh_rate) -
                                (int)(time / refresh_rate)],
                   (time / refresh_rate) * sizeof(double));
            d_y[i] = (double *)realloc(d_y.at(i),
                                       time / refresh_rate * sizeof(double));
            memcpy(d_y[i], buf, (time / refresh_rate) * sizeof(double));
            free(buf);
          }
          datas->at(i)
              ->setRawSamples(d_x.at(i), d_y.at(i), time / refresh_rate);
        }
        view_size = time;
      }
    }
  }
}
