// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "Picture.h"
#include "Layout.h"
#include <QMenu>
#include <QInputDialog>
#include <QLabel>
#include <QMouseEvent>
#include <QGroupBox>
#include <QVBoxLayout>

Picture::Picture(Layout *parent, int row, int col, QString name, uint16_t width,
                 uint16_t height, bool enabled, int period)
    : DataRemote(name, "Picture", parent, enabled, period) {
  box = new QGroupBox(name);
  box->setObjectName(name);

  parent->addWidget(box, row, col);

  label = new QLabel();

  layout = new QVBoxLayout;
  layout->addWidget(label);
  box->setLayout(layout);

  visible_widget = box;

  label->setAlignment(Qt::AlignCenter);

  im_width = width;
  im_height = height;
  label->setMinimumSize(width, height);
  label->setMaximumSize(width, height);
  receivesize = width * height;

  for (int i = 0; i < 256; i++) {
    color_table.append(qRgb(i, i, i));
  }

  label->installEventFilter(this);
}

Picture::~Picture() { delete layout; }

void Picture::BufEvent(char **buf, int *buf_size, uint16_t period,
                       bool big_endian) {
  if (big_endian)
    printf("Picture::BufEvent, big endian not handled\n");

  if (IsEnabled() == false || RefreshRate_ms() != period)
    return;

  if ((*buf_size) >= im_width * im_height) {
    QImage image = QImage((const uchar *)*buf, im_width, im_height,
                          QImage::Format_Indexed8); // Format_RGB888);
    *buf += im_width *im_height;
    image.setColorTable(color_table);

    label->setPixmap(QPixmap::fromImage(image));
  } else
    printf("buffer trop petit\n");
}

bool Picture::eventFilter(QObject *o, QEvent *e) {
  if (o == label) {
    switch (e->type()) {
    case QEvent::MouseButtonPress: {
      mousePressEvent((QMouseEvent *)e);
      break;
    }

    default:
      break;
    }
  }
  return label->eventFilter(o, e);
}

void Picture::mousePressEvent(QMouseEvent *event) {

  if (event->x() > 0 && event->x() < label->width() && event->y() > 0 &&
      event->y() < label->height() && event->button() == Qt::RightButton) {

    QMenu *menu = new QMenu("nom", label);
    // ajout des actions
    QAction *a, *z;

    a = menu->addAction("get frame");
    a->setEnabled(!auto_refresh);

    appendmenu(menu);
    z = execmenu(label, menu, event->globalPos());
    delete menu;
  }
}

void Picture::XmlEvent(QDomElement dom) { XmlSetup(dom); }
