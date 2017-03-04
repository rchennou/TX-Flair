// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "Layout.h"
#include "TabWidget.h"
#include "GroupBox.h"
#include "GridLayout.h"
#include "SpinBox.h"
#include "DoubleSpinBox.h"
#include "Vector3DSpinBox.h"
#include "CheckBox.h"
#include "ComboBox.h"
#include "PushButton.h"
#include "TextEdit.h"
#include "Label.h"
#include "DataPlot1D.h"
#include "DataPlot2D.h"
#include "RangeFinderPlot.h"
#include "Picture.h"
#include "Map.h"
#include <QGeoCoordinate>
#include <QGridLayout>
#include "ListWidget.h"
#include <QStringList>

Layout::Layout(QWidget *parent, XmlWidget *xml, QString name, QString type)
    : XmlWidget(name, type, xml) {
  qgridlayout = new QGridLayout(parent);
  Constructor(name);
}

Layout::Layout(Layout *parent, QString name, QString type)
    : XmlWidget(name, type, parent) {
  qgridlayout = new QGridLayout(new QWidget());
  Constructor(name);
}

void Layout::Constructor(QString name) {
  visible_widget = qgridlayout->parentWidget();
  // if(visible_widget==NULL) printf("null\n");
  qgridlayout->setObjectName(name);
  // printf("layout\n%s\n",XmlDoc().toString().toLocal8Bit().constData());
  SetIsContainer(true);
  SetIsExpandable(true);

  qgridlayout->setHorizontalSpacing(2);
  qgridlayout->setVerticalSpacing(2);
  qgridlayout->setContentsMargins(2, 2, 2, 2);

  // splitter = new QSplitter();
  // addWidget(splitter);
  /*
  QWidget *widget = new QWidget();
  //QHBoxLayout *parentLayout = new QHBoxLayout();
  widget->setLayout(this);
  parent->addWidget(widget);
  //QTabWidget *tabWidget = new QTabWidget();
  //parentLayout->addWidget(tabWidget);*/
}

Layout::~Layout() { delete qgridlayout; }

void Layout::addWidget(QWidget *widget, int row, int column) {
  qgridlayout->addWidget(widget, row, column);
}

QGridLayout *Layout::getQGridLayout() { return qgridlayout; }

void Layout::XmlEvent(QDomElement dom) {
  XmlWidget *widget = NULL;
  QString type = dom.tagName();
  QString name = dom.attribute("name");
  QString old_name = dom.attribute("old_name");
  int row = dom.attribute("row").toInt();
  int col = dom.attribute("col").toInt();

  // initially rowCount()=1 and columnCount()=1 but count()=0 !
  // new row
  if (row == -1 && col == -1) {
    row = qgridlayout->rowCount();
    if (qgridlayout->count() == 0)
      row = 0;
    col = 0;
  }
  // last row last col
  if (row == -1 && col == 0) {
    row = qgridlayout->rowCount() - 1;
    int i;
    for (i = 0; i <= qgridlayout->columnCount(); i++) {
      if (qgridlayout->itemAtPosition(row, i) == NULL)
        break;
    }
    col = i;
  }
  // if an item already exists at this position, put it on a new row
  if (qgridlayout->itemAtPosition(row, col) != NULL) {
    printf("existe %s\n", name.toLocal8Bit().constData());
    row = qgridlayout->rowCount();
  }

  if (type == "TabWidget") {
    int position = dom.attribute("position").toInt();
    widget =
        new TabWidget(this, row, col, name, (QTabWidget::TabPosition)position);
  }
  if (type == "GroupBox") {
    widget = new GroupBox(this, row, col, name);
  }
  if (type == "GridLayout") {
    widget = new GridLayout(this, row, col, name);
  }
  if (type == "SpinBox") {
    int value = dom.attribute("value").toInt();
    QString suffix = dom.attribute("suffix");
    int min = dom.attribute("min").toInt();
    int max = dom.attribute("max").toInt();
    int step = dom.attribute("step").toInt();
    widget = new SpinBox(this, row, col, name, suffix, value, min, max, step);
  }
  if (type == "DoubleSpinBox") {
    QString value = dom.attribute("value");
    QString suffix = dom.attribute("suffix");
    double min = dom.attribute("min").toDouble();
    double max = dom.attribute("max").toDouble();
    double step = dom.attribute("step").toDouble();
    int decimals = dom.attribute("decimals").toInt();
    widget = new DoubleSpinBox(this, row, col, name, suffix, value, min, max,
                               step, decimals);
  }
  if (type == "Vector3DSpinBox") {
    QString value[3];
    value[0] = dom.attribute("value_x");
    value[1] = dom.attribute("value_y");
    value[2] = dom.attribute("value_z");
    double min = dom.attribute("min").toDouble();
    double max = dom.attribute("max").toDouble();
    double step = dom.attribute("step").toDouble();
    int decimals = dom.attribute("decimals").toInt();
    widget = new Vector3DSpinBox(this, row, col, name, value, min, max, step,
                                 decimals);
  }
  if (type == "CheckBox") {
    int value = dom.attribute("value").toInt();
    widget = new CheckBox(this, row, col, name, value);
  }
  if (type == "ComboBox") {
    int value = dom.attribute("value").toInt();
    widget = new ComboBox(this, row, col, name, value);
  }
  if (type == "PushButton") {
    widget = new PushButton(this, row, col, name);
  }
  if (type == "DataPlot1D") {
    float ymin = dom.attribute("min").toFloat();
    float ymax = dom.attribute("max").toFloat();
    int enabled = dom.attribute("enabled").toInt();
    int period = dom.attribute("period").toInt();
    if (enabled == 1) {
      widget = new DataPlot1D(this, row, col, name, ymin, ymax, true, period);
    } else {
      widget = new DataPlot1D(this, row, col, name, ymin, ymax, false, 100);
    }
  }
  if (type == "DataPlot2D") {
    float xmin = dom.attribute("xmin").toFloat();
    float xmax = dom.attribute("xmax").toFloat();
    float ymin = dom.attribute("ymin").toFloat();
    float ymax = dom.attribute("ymax").toFloat();
    QString x_name = dom.attribute("x_name");
    QString y_name = dom.attribute("y_name");
    int enabled = dom.attribute("enabled").toInt();
    int period = dom.attribute("period").toInt();
    if (enabled == 1) {
      widget = new DataPlot2D(this, row, col, name, x_name, y_name, xmin, xmax,
                              ymin, ymax, true, period);
    } else {
      widget = new DataPlot2D(this, row, col, name, x_name, y_name, xmin, xmax,
                              ymin, ymax, false, 100);
    }
  }
  if (type == "RangeFinderPlot") {
    float xmin = dom.attribute("xmin").toFloat();
    float xmax = dom.attribute("xmax").toFloat();
    float ymin = dom.attribute("ymin").toFloat();
    float ymax = dom.attribute("ymax").toFloat();
    QString x_name = dom.attribute("x_name");
    QString y_name = dom.attribute("y_name");
    QString data_type = dom.attribute("type");
    float start_angle = dom.attribute("start_angle").toFloat();
    float end_angle = dom.attribute("end_angle").toFloat();
    uint32_t nb_samples = dom.attribute("nb_samples").toUInt();
    int enabled = dom.attribute("enabled").toInt();
    int period = dom.attribute("period").toInt();
    int invert_axis = dom.attribute("invert_axis").toInt();
    bool invert_axis_bool;
    if (invert_axis == 0) {
      invert_axis_bool = false;
    } else {
      invert_axis_bool = true;
    }
    if (enabled == 1) {
      widget =
          new RangeFinderPlot(this, row, col, name, x_name, y_name, xmin, xmax,
                              ymin, ymax, start_angle, end_angle, nb_samples,
                              data_type, invert_axis, true, period);
    } else {
      widget =
          new RangeFinderPlot(this, row, col, name, x_name, y_name, xmin, xmax,
                              ymin, ymax, start_angle, end_angle, nb_samples,
                              data_type, invert_axis, false, 100);
    }
  }
  if (type == "Picture") {
    int width = dom.attribute("width").toInt();
    int height = dom.attribute("height").toInt();
    int enabled = dom.attribute("enabled").toInt();
    int period = dom.attribute("period").toInt();
    if (enabled == 1) {
      widget = new Picture(this, row, col, name, width, height, true, period);
    } else {
      widget = new Picture(this, row, col, name, width, height, false, period);
    }
  }
  if (type == "Map") {
    int period = dom.attribute("period").toInt();
    int enabled = dom.attribute("enabled").toInt();
    int i = 0;
    QList<QtMobility::QGeoCoordinate> coordinates;
    while (dom.hasAttribute("lat" + QString::number(i))) {
      double latitude = dom.attribute("lat" + QString::number(i)).toDouble();
      double longitude = dom.attribute("long" + QString::number(i)).toDouble();
      double alt = dom.attribute("alt" + QString::number(i)).toDouble();
      QtMobility::QGeoCoordinate coordinate =
          QtMobility::QGeoCoordinate(latitude, longitude, alt);
      coordinates.append(coordinate);
      i++;
    }

    if (enabled == 1) {
      widget = new Map(this, row, col, name, coordinates, true, period);
    } else {
      widget = new Map(this, row, col, name, coordinates, false, period);
    }
  }
  if (type == "TextEdit") {
    widget = new TextEdit(this, row, col, name);
  }
  if (type == "Label") {
    widget = new Label(this, row, col, name);
  }
  if (type == "ListWidget") {
    // Parse the item list    
    QStringList items;
    int count = 0;
    while (dom.hasAttribute("item" + QString::number(count))) {
      QString item = dom.attribute("item" + QString::number(count));
      items.append(item);
      count++;
    }
    widget = new ListWidget(this, row, col, name, items);
  }

  if (widget != NULL) {
    if (old_name != "") {
      widget->RenamedFrom(old_name);
    }
  }
}

bool Layout::IsUptodate(void) {
  for (int i = 0; i < childs->count(); i++) {
    if (childs->at(i)->IsUptodate() == false)
      return false;
  }
  return true;
}
