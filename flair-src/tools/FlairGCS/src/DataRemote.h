// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef DATAREMOTE_H
#define DATAREMOTE_H

#include <stdint.h>
#include "XmlWidget.h"
#include <QPoint>

class QMenu;
class QAction;

class DataRemote : public XmlWidget {
public:
  DataRemote(QString name, QString type, XmlWidget *parent, bool enabled,
             int period);
  ~DataRemote();
  uint16_t RefreshRate_ms(void);
  bool IsEnabled(void);
  int ReceiveSize(void);
  virtual void BufEvent(char **buf, int *buf_size, uint16_t period,
                        bool big_endian) = 0;
  void appendmenu(QMenu *menu);
  QAction *execmenu(QWidget *parent, QMenu *menu, QPoint point);

protected:
  bool auto_refresh;
  bool is_logging;
  double refresh_rate; // en s
  int receivesize;

  void XmlSetup(QDomElement dom);

private:
  void SendPeriod(int period, bool auto_refresh);
  QAction *b, *c, *d;
};

#endif // DATAREMOTE_H
