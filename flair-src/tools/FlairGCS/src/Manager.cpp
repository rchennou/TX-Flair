// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "Manager.h"
#include "UdtSocket.h"
#include "ConnectionLayout.h"
#include "communication.h"
#include <QDate>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QTabBar>
#include <QTimer>
#include <QThread>
#include <QTextStream>
#include <QVBoxLayout>
#include <QModelIndex>
//#include <qmetatype.h>
#include <qendian.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

#ifndef WIN32
#include <arpa/inet.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

using namespace std;

Manager::Manager(QString name, int port) : QWidget() {
  qRegisterMetaType<QModelIndex>("QModelIndex"); // pour le file ui??
  this->name = name;

  setWindowTitle(name);
//statusBar()->showMessage(tr("Ready to serve"));
  // manager layout
  managerLayout = new QVBoxLayout;
  setLayout(managerLayout);

  // tab bar for multiple connections
  tabBar = new QTabBar();
  managerLayout->addWidget(tabBar);
  connect(tabBar, SIGNAL(currentChanged(int)), this,
          SLOT(tabBarCurrentChanged(int)));
  currentTab = 0;

  // layout boutons
  button_layout = new QGridLayout();
  managerLayout->addLayout(button_layout);

  // boutons du button_Layout
  send_button = new QPushButton("apply all");
  reset_button = new QPushButton("reset all");
  load_button = new QPushButton("load all locally");
  save_button = new QPushButton("save all locally");
  button_layout->addWidget(send_button, 0, 0);
  button_layout->addWidget(reset_button, 0, 1);
  button_layout->addWidget(load_button, 0, 2);
  button_layout->addWidget(save_button, 0, 3);

  connect(send_button, SIGNAL(clicked(bool)), this, SLOT(send()));
  connect(reset_button, SIGNAL(clicked(bool)), this, SLOT(reset()));
  connect(load_button, SIGNAL(clicked(bool)), this, SLOT(load()));
  connect(save_button, SIGNAL(clicked(bool)), this, SLOT(save()));

  status=new QStatusBar();
  status->setSizeGripEnabled(false);
  button_layout->addWidget(status, 1,0);

  UDT::startup();
  serv = UDT::socket(AF_INET, SOCK_DGRAM, 0);

  // for non blocking accept
  bool blocking = false;
  UDT::setsockopt(serv, 0, UDT_RCVSYN, &blocking, sizeof(bool));

  sockaddr_in my_addr;
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(port);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  memset(&(my_addr.sin_zero), '\0', 8);

  if (UDT::ERROR == UDT::bind(serv, (sockaddr *)&my_addr, sizeof(my_addr))) {
    printf("bind error, %s\n", UDT::getlasterror().getErrorMessage());
  }

  if (UDT::ERROR == UDT::listen(serv, 1)) {
    printf("listen error, %s\n", UDT::getlasterror().getErrorMessage());
  }

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(acceptConnections()));
  timer->start(20);
}

Manager::~Manager() {
  emit killUdtSockets();

  // delete main_layout;
  UDT::cleanup();
}

void Manager::acceptConnections(void) {
  static UDTSOCKET first_socket = 0;
  UDTSOCKET socket;

  sockaddr_in their_addr;
  int namelen = sizeof(their_addr);

  if (UDT::INVALID_SOCK ==
      (socket = UDT::accept(serv, (sockaddr *)&their_addr, &namelen))) {
    if (UDT::getlasterror().getErrorCode() != 6002)
      printf("accept: %s, code %i\n", UDT::getlasterror().getErrorMessage(),
             UDT::getlasterror().getErrorCode());
    return;
  } else {
    printf("connected to %s:%i\n", inet_ntoa(their_addr.sin_addr),
           their_addr.sin_port);

    if (!first_socket) {
      first_socket = socket;
      return;
    } else {
      QThread *thread = new QThread(this);
      UdtSocket *new_udt = new UdtSocket(first_socket, socket, name);
      new_udt->moveToThread(thread);

      newConnection(new_udt);

      connect(this, SIGNAL(killUdtSockets()), thread, SLOT(quit()));
      connect(this, SIGNAL(killUdtSockets()), new_udt, SLOT(kill()),
              Qt::BlockingQueuedConnection);

      connect(thread, SIGNAL(started()), new_udt, SLOT(handleConnections()));

      thread->start();
      first_socket = 0;
    }
  }
}

void Manager::newConnection(UdtSocket *socket) {

  // no tabs to 2 tabs
  if (connectionsLayout.count() == 1) {
    tabBar->addTab(hiddenTabName);
    currentTab = 0;
    connectionsWidget.at(0)->show();
  }

  // layout utilisateur
  ConnectionLayout *newLayout = new ConnectionLayout(socket, "interface");
  connectionsLayout.append(newLayout);
  connect(newLayout, SIGNAL(setRemoteName(QString)), this,
          SLOT(tabName(QString)));
  connect(newLayout, SIGNAL(computedRxRate(float)), this,
          SLOT(printRxRates(float)));
  connect(socket, SIGNAL(dataReady(char *, int)), newLayout,
          SLOT(receive(char *, int)));
  connect(newLayout, SIGNAL(destroyed(QObject *)), this,
          SLOT(layoutDestroyed(QObject *)));
  connect(socket, SIGNAL(destroyed()), newLayout, SLOT(deleteLater()));

  // widget
  QWidget *newWidget = new QWidget();
  connectionsWidget.append(newWidget);
  newWidget->setLayout(newLayout->getQGridLayout());
  managerLayout->insertWidget(1, newWidget);
  newWidget->hide();

  if (connectionsLayout.count() == 1) { // first connection
    newWidget->show();
  } else { // add a tab for the new connection
    tabBar->addTab("unknown");
  }
}

void Manager::printRxRates(float rxRate) {
  int index = connectionsLayout.indexOf((ConnectionLayout *)sender());

  if (tabBar->count() == 0) {
    status->showMessage(tr("rx rate %1 kB/s").arg(rxRate,0,'f',3));
  } else if (index==tabBar->currentIndex()) {
    status->showMessage(tr("%1 rx rate %2 kB/s").arg(tabBar->tabText(index)).arg(rxRate,0,'f',3));
  }
}

void Manager::tabBarCurrentChanged(int index) {
  if (index >= 0) {
    connectionsWidget.at(currentTab)->hide();
    connectionsWidget.at(index)->show();
    currentTab = index;
  } else {
    currentTab = 0;
    connectionsWidget.at(0)->show();
  }
}

void Manager::tabName(QString name) {
  int index = connectionsLayout.indexOf((ConnectionLayout *)sender());
  if (tabBar->count() == 0) {
    hiddenTabName = name;
  } else {
    tabBar->setTabText(index, name);
  }
}

void Manager::layoutDestroyed(QObject *obj) {
  int index = connectionsLayout.indexOf((ConnectionLayout *)obj);

  if (tabBar->count() > 1) {
    tabBar->removeTab(index);
  }

  delete connectionsWidget.at(index);
  connectionsWidget.removeAt(index);
  connectionsLayout.removeOne((ConnectionLayout *)obj);

  if (connectionsLayout.count() == 1) {
    hiddenTabName = tabBar->tabText(0);
    tabBar->removeTab(0);
  }

  if (connectionsLayout.count() == 0) {
    status->showMessage("");
  }
}

void Manager::load(void) {
  QString dir_name =
      QFileDialog::getExistingDirectory(this, "Select a directory", 0, 0);

  if (dir_name != "") {
    for (int i = 0; i < connectionsLayout.count(); i++) {
      QFile *file;
      file = new QFile(dir_name + "/" +
                       connectionsLayout.at(i)->getRemoteName() + ".xml");
      if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Enable to load " +
                                 connectionsLayout.at(i)->getRemoteName() +
                                 ".xml");
        continue;
      }

      QDomDocument doc;
      QString errorMsg;
      int errorLine;
      int errorColumn;
      if (!doc.setContent(file, &errorMsg, &errorLine, &errorColumn)) {
        QMessageBox::critical(
            this, "Error",
            "unable to read " + connectionsLayout.at(i)->getRemoteName() +
                ".xml" + " (" + errorMsg + " at " + QString::number(errorLine) +
                "," + QString::number(errorColumn) + ")");
      } else {
        connectionsLayout.at(i)->LoadXml(doc);
      }
      delete file;
    }
  }
}

void Manager::save(void) {
  bool isUptodate = true;

  for (int i = 0; i < connectionsLayout.count(); i++) {
    if (!connectionsLayout.at(i)->IsUptodate()) {
      isUptodate = false;
      break;
    }
  }

  if (!isUptodate) {
    QMessageBox msgBox;
    msgBox.setText("There are pending modifications");
    msgBox.setInformativeText("Apply and save?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
      send();
      break;
    case QMessageBox::Cancel:
      return;
      break;
    default:
      // should never be reached
      break;
    }
  }

  // create dirctory for storage
  QDateTime dateTime = QDateTime::currentDateTime();
  QString dir_name =
      "configs_" + dateTime.toString("yyyyMMdd_hhmm") + "_" + name;
  if (QDir().exists(dir_name) == true) {
    dir_name = "configs_" + dateTime.toString("yyyyMMdd_hhmm_ss") + "_" + name;
  }
  QDir().mkdir(dir_name);

  for (int i = 0; i < connectionsLayout.count(); i++) {
    QDomDocument *xml = new QDomDocument("remote_ui_xml");

    connectionsLayout.at(i)->GetFullXml((QDomElement *)xml);

    QFile fichier(dir_name + "/" + connectionsLayout.at(i)->getRemoteName() +
                  ".xml");
    QString write_doc = (xml->ownerDocument()).toString();

    if (!fichier.open(QIODevice::WriteOnly)) {
      fichier.close();
      QMessageBox::critical(this, "Error", "Enable to write XML");
      continue;
    }
    QTextStream stream(&fichier);
    stream << write_doc; // On utilise l'opérateur << pour écrire write_doc dans
                         // le document XML.
    fichier.close();

    delete xml;
  }

  QMessageBox::information(this, "save all", "saved to ./" + dir_name);
}

void Manager::send(void) {
  for (int i = 0; i < connectionsLayout.count(); i++) {
    QDomDocument doc("remote_ui_xml");
    connectionsLayout.at(i)->GetUpdateXml((QDomElement *)&doc);
    // printf("merge\n%s\n",doc.toString().toLocal8Bit().constData());

    connectionsLayout.at(i)->XmlToSend(doc);
  }
}

void Manager::reset() {
  for (int i = 0; i < connectionsLayout.count(); i++)
    connectionsLayout.at(i)->ResetAllChilds();
}
