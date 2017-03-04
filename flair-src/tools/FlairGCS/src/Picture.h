// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef PICTURE_H
#define PICTURE_H

#include <stdint.h>
#include "DataRemote.h"
#include <QRgb>
#include <QVector>

class Layout;
class QGroupBox;
class QMouseEvent;
class QLabel;
class QVBoxLayout;

class Picture : public DataRemote {
  Q_OBJECT

public:
  Picture(Layout *parent, int row, int col, QString name, uint16_t width,
          uint16_t height, bool enabled, int period);
  ~Picture();

protected:
  void mousePressEvent(QMouseEvent *event);

private:
  QGroupBox *box;
  QLabel *label;
  QVBoxLayout *layout;
  QVector<QRgb> color_table;
  uint16_t im_width;
  uint16_t im_height;

  bool eventFilter(QObject *, QEvent *);
  void BufEvent(char **buf, int *buf_size, uint16_t period, bool big_endian);
  void XmlEvent(QDomElement dom);
};

#endif // PICTURE_H
