// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include <udt.h>
#include <qdom.h>
#include <QStatusBar>

class UdtSocket;
class ConnectionLayout;
class QVBoxLayout;
class QTabBar;
class QPushButton;
class QGridLayout;

class Manager : public QWidget {
  Q_OBJECT

public:
  Manager(QString name, int port);
  ~Manager();

private:
  UDTSOCKET serv;
  QVBoxLayout *managerLayout;
  QList<ConnectionLayout *> connectionsLayout;
  QList<QWidget *> connectionsWidget;
  QTabBar *tabBar;
  QString name, hiddenTabName;
  int currentTab;

  QPushButton *send_button;
  QPushButton *reset_button;
  QPushButton *load_button;
  QPushButton *save_button;
  QGridLayout *button_layout;
  QStatusBar *status;

  void newConnection(UdtSocket *socket);

private slots:
  void acceptConnections(void);
  void load(void);
  void send(void);
  void save(void);
  void reset(void);
  void layoutDestroyed(QObject *obj);
  void tabBarCurrentChanged(int index);
  void tabName(QString name);
  void printRxRates(float rxRate);

signals:
  void killUdtSockets(void);

protected:
};

#endif // MANAGER_H
