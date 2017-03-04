// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "DataPlot1D.h"
#include "Layout.h"
#include <QMouseEvent>
#include <QMenu>
#include <QGridLayout>
#include <qendian.h>

DataPlot1D::DataPlot1D(Layout *parent, int row, int col, QString title,
                       float ymin, float ymax, bool enabled, int period)
    : ScopeFixedStep(title, ymin, ymax, period / 1000.),
      DataRemote(title, "DataPlot1D", parent, enabled, period) {

  setEnabled(enabled);
  parent->addWidget(this, row, col);
  visible_widget = this;
}

DataPlot1D::~DataPlot1D() {
  visible_widget = NULL; // because otherwise xmlwidget will delete it
}

void DataPlot1D::XmlEvent(QDomElement dom) {
  if (dom.attribute("curve") != "") {
    QString type = dom.attribute("type");
    int r = dom.attribute("r").toInt();
    int g = dom.attribute("g").toInt();
    int b = dom.attribute("b").toInt();
    QString name = dom.attribute("curve");
    addCurve(QPen(QColor(r, g, b, 255)), name);
    datas_type.append(type);
    if (type == "float") {
      receivesize += sizeof(float);
    } else if (type == "int8_t") {
      receivesize += sizeof(int8_t);
    } else if (type == "int16_t") {
      receivesize += sizeof(int16_t);
    } else {
      printf("MyDataPlot1D::addCurve unknown type %s\n",
             type.toLocal8Bit().constData());
    }
  } else {
    XmlSetup(dom);
  }
}

bool DataPlot1D::eventFilter(QObject *o, QEvent *e) {
  if (o == canvas()) {
    switch (e->type()) {
    case QEvent::Resize: {
      // resolution bug taille widgets:
      setMaximumHeight(parentWidget()->height() /
                       ((QGridLayout *)(parentWidget()->layout()))->rowCount());
      break;
    }
    case QEvent::MouseButtonPress: {
      return mouseEvent((QMouseEvent *)e);
    }

    default:
      break;
    }
  }
  return Scope::eventFilter(o, e);
}

void DataPlot1D::BufEvent(char **buf, int *buf_size, uint16_t period,
                          bool big_endian) {
  setEnabled(IsEnabled());
  if (IsEnabled() == false || RefreshRate_ms() != period)
    return;
  double *datas = (double *)malloc(datas_type.count() * sizeof(double));

  for (int i = 0; i < datas_type.count(); i++) {
    if (datas_type.at(i) == "float") {
      uint32_t data_raw;
      float *data = (float *)&data_raw;
      memcpy((void *)&data_raw, *buf, sizeof(uint32_t));
      *buf += sizeof(uint32_t);
      if (big_endian == true)
        data_raw = qFromBigEndian(data_raw);
      datas[i] = *data;
    } else if (datas_type.at(i) == "int8_t") {
      int8_t data;
      memcpy((void *)&data, *buf, sizeof(data));
      *buf += sizeof(data);
      datas[i] = data;
    } else if (datas_type.at(i) == "int16_t") {
      int16_t data;
      memcpy((void *)&data, *buf, sizeof(data));
      *buf += sizeof(data);
      if (big_endian == true)
        data = qFromBigEndian(data);
      datas[i] = data;
    } else {
      printf("DataPlot1D::BufEvent unknown type %s\n",
             datas_type.at(i).toLocal8Bit().constData());
    }
  }

  step_s = period / 1000.;
  plot(datas);
}

// context menu
bool DataPlot1D::mouseEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    QMenu *menu = new QMenu("nom", (QwtPlot *)this);
    QAction *a, *b, *z;

    a = menu->addAction("reset time view");
    b = menu->addAction("reset y view");
    menu->addSeparator();

    appendmenu(menu);
    z = execmenu((QwtPlot *)this, menu, event->globalPos());
    delete menu;

    if (z == a)
      resetXView();
    if (z == b)
      resetYView();

    return true;
  }
  return false;
}
