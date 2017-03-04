// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "UdtSocket.h"
#include <stdio.h>
#include <stdlib.h>
#include <QApplication>
#include <QtEndian>
#include <QDir>
#include <QDate>
#include "file_ui.h"
#include "communication.h"

#ifndef WIN32
#include <arpa/inet.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

using namespace std;

UdtSocket::UdtSocket(UDTSOCKET file_socket, UDTSOCKET com_socket, QString name)
    : QObject() {
  this->file_socket = file_socket;
  this->com_socket = com_socket;
  this->name = name;
  stop = false;
  file_dialog = new file_ui();

  bool blocking = true;
  UDT::setsockopt(file_socket, 0, UDT_RCVSYN, &blocking, sizeof(bool));

  heartbeat_timer = new QTimer(this);
  connect(heartbeat_timer, SIGNAL(timeout()), this, SLOT(heartbeat()));
  heartbeat_timer->start(200);
}

UdtSocket::~UdtSocket() {
  heartbeat_timer->stop();

  UDT::close(file_socket);
  UDT::close(com_socket);

  file_dialog->deleteLater();
}

// send signal to uav, to check connectivity through a watchdog
// this is necessary because we use udt (udp based), and we cannot check
// disconnection of ground station
void UdtSocket::heartbeat(void) {
  char data = WATCHDOG_HEADER;
  write(&data, 1);
}

void UdtSocket::kill(void) {
  printf("disconnected\n");
  stop = true;
  deleteLater();
}

void UdtSocket::handleConnections(void) {
  while (!stop) {
    int eid = UDT::epoll_create();
    if (eid < 0) {
      printf("epoll_create error: %s\n", UDT::getlasterror().getErrorMessage());
    }

    if (UDT::epoll_add_usock(eid, file_socket) < 0) {
      if (UDT::getlasterror().getErrorCode() == 5004) {
        printf("epoll_add_usock error\n");
        break;
      } else {
        printf("epoll_add_usock error: %s\n",
               UDT::getlasterror().getErrorMessage());
      }
    }
    if (UDT::epoll_add_usock(eid, com_socket) < 0) {
      if (UDT::getlasterror().getErrorCode() == 5004) {
        printf("epoll_add_usock error\n");
        break;
      } else {
        printf("epoll_add_usock error: %s\n",
               UDT::getlasterror().getErrorMessage());
      }
    }

    set<UDTSOCKET> readfds;

    int rv = UDT::epoll_wait(eid, &readfds, NULL, 10);

    if (rv == -1) {
      if (UDT::getlasterror().getErrorCode() != 6003)
        printf("prob %i\n", UDT::getlasterror().getErrorCode());
      // printf("wait\n");
    } else if (rv == 0) {
      printf("timeout\n"); // a timeout occured
    } else {
      /*
      if(UDT::getlasterror().getErrorCode()==2001) {
          UDT::epoll_release(eid);
      }*/
      for (set<UDTSOCKET>::iterator i = readfds.begin(); i != readfds.end();
           i++) {
        // printf("a\n");
        if (*i == file_socket)
          receiveFile();
        if (*i == com_socket)
          receiveData();
      }
    }

    UDT::epoll_remove_usock(eid, file_socket);
    UDT::epoll_remove_usock(eid, com_socket);
    UDT::epoll_release(eid);

    QCoreApplication::processEvents();
  }
  kill();
}

void UdtSocket::receiveFile(void) {
  char *recv_buf;
  int bytesRead;
  static bool flag_new_seq = true;
  static QString folder_name;

  // receive file info
  recv_buf = (char *)malloc(1024);
  bytesRead = UDT::recvmsg(file_socket, recv_buf, 1024);

  if (bytesRead <= 0) {
    free(recv_buf);
    return;
  }

  int size;
  memcpy(&size, &recv_buf[1], sizeof(int));
  if (recv_buf[0] == FILE_INFO_BIG_ENDIAN)
    size = qFromBigEndian(size);

  // printf("file_ui recu %i %x\n",bytesRead,recv_buf[0]);
  if ((recv_buf[0] == FILE_INFO_LITTLE_ENDIAN ||
       recv_buf[0] == FILE_INFO_BIG_ENDIAN) &&
      size > 0) {
    if (flag_new_seq == true) {
      // create directory for storage
      QDateTime dateTime = QDateTime::currentDateTime();
      folder_name = dateTime.toString("yyyyMMdd_hhmm") + "_" + name;
      if (QDir().exists(folder_name) == true) {
        folder_name = dateTime.toString("yyyyMMdd_hhmm_ss") + "_" + name;
      }
      QDir().mkdir(folder_name);

      flag_new_seq = false;
      file_dialog->log("Creating directory " + folder_name);
    }

    QString file_name =
        QString::fromAscii((const char *)&recv_buf[5], bytesRead - 5);
    QString file_path = folder_name + "/" + file_name;
    file_dialog->log(
        QString("receiving %1 (%2 bytes)").arg(file_name).arg(size));
    QFile fichier(file_path);

    if (!fichier.open(QIODevice::WriteOnly)) {
      file_dialog->log("      could not write to file!");
    } else {
      // receive file
      recv_buf = (char *)realloc((void *)recv_buf, size);
      bytesRead = UDT::recvmsg(file_socket, recv_buf, size);
      if (bytesRead != size) {
        file_dialog->log(QString("      error receiving file! (%1/%2)")
                             .arg(bytesRead)
                             .arg(size));
        free(recv_buf);
        return;
      } else {
        file_dialog->log("      ok");
      }

      QDataStream stream(&fichier);
      stream.writeRawData(recv_buf, size);
      fichier.close();

      file_dialog->addFile(file_path);
    }

    free(recv_buf);
  } else if (recv_buf[0] == END) {
    file_dialog->endOfFiles();
    flag_new_seq = true;
    //end ack
    UDT::sendmsg(file_socket,&recv_buf[0],1);
  }
}

void UdtSocket::receiveData(void) {
  while (1) {
    int buf_size;
    int opt_size;
    UDT::getsockopt(com_socket, 0, UDT_RCVBUF, &buf_size, &opt_size);

    char *buf = (char *)malloc(buf_size);
    int size;
    size = UDT::recvmsg(com_socket, buf, buf_size);
    buf = (char *)realloc(buf, size + 1);

    if (size > 0) {
      buf[size] = 0;
      emit dataReady(buf, size + 1);
    } else {
      // if(UDT::getlasterror().getErrorCode()!=6002) printf("udt socket:
      // %s\n",UDT::getlasterror().getErrorMessage());
      free(buf);
      break;
    }
  }
}

void UdtSocket::write(const char *buf, qint64 size) {
  // printf("write\n%s\n",buf);
  qint64 sent = UDT::sendmsg(com_socket, buf, size, -1, true);
  if (sent != size) {
    printf("erreur envoi: %s\n", UDT::getlasterror().getErrorMessage());
    if (UDT::getlasterror().getErrorCode() == 2001) {
      stop = true;
    }
  }
}
