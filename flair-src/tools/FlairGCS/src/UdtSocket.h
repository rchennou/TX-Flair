// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef UDTSOCKET_H
#define UDTSOCKET_H

#include <udt.h>
#include <QObject>
#include <QTimer>

class file_ui;

class UdtSocket : public QObject {
  Q_OBJECT

public:
  UdtSocket(UDTSOCKET file_socket, UDTSOCKET com_socket, QString name);
  ~UdtSocket();

private:
  UDTSOCKET file_socket, com_socket;
  file_ui *file_dialog;
  bool stop;
  QString name;
  QTimer *heartbeat_timer;
  void receiveData(void);
  void receiveFile(void);

signals:
  void dataReady(char *, int size);

public slots:
  void handleConnections(void);
  void kill(void);
  void write(const char *buf, qint64 size);
private slots:
  void heartbeat(void);
};

#endif // UDTSOCKET_H
