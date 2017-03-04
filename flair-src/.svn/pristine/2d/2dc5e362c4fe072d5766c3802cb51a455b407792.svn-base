// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef CONNECTIONLAYOUT_H
#define CONNECTIONLAYOUT_H

#include <QTimer>
#include "Layout.h"

class UdtSocket;
class DataRemote;

class ConnectionLayout : public Layout {
  Q_OBJECT

public:
  ConnectionLayout(UdtSocket *socket, QString name);
  ~ConnectionLayout();
  void XmlToSend(QDomDocument doc);
  void addDataRemote(DataRemote *data);
  void removeDataRemote(DataRemote *data);
  void LoadXml(QDomDocument to_parse);
  QString getRemoteName();

private:
  static int uncompressBuffer(char *in, ssize_t in_size, char **out,
                              ssize_t *out_size);
  void handleUncompressedFrame(char *buf, ssize_t size);
  void drawDatas(char *buf, int buf_size, uint16_t period,
                 bool big_endian = false);
  bool isRemoteNameDefined;
  QString remoteName;
  UdtSocket *socket;
  QList<DataRemote *> dataremotes;
  unsigned int total_received;
  QTimer *receive_timer;

private slots:
  void receive(char *buf, int size);
  void computeRxRate(void);

signals:
  void setRemoteName(QString name);
  void computedRxRate(float rxRate);
};

#endif // CONNECTIONLAYOUT_H
