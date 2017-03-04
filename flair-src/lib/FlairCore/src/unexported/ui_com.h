// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   ui_com.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe permettant la lecture et l'ecriture RT sur socket UDT
//
//
/*********************************************************************/

#ifndef UI_COM_H
#define UI_COM_H

#include "Thread.h"
#include <udt.h>
#ifdef __XENO__
#include <native/pipe.h>
#endif

namespace flair {
namespace core {
class Mutex;
class Object;
}
namespace gui {
class SendData;
}
}

class ui_com : public flair::core::Thread {
public:
  ui_com(const flair::core::Object *parent, UDTSOCKET sock);
  ~ui_com();
  void Send(char *buf, ssize_t size);
  ssize_t Receive(char *buf, ssize_t buf_size);
  void AddSendData(const flair::gui::SendData *obj);
  void UpdateSendData(const flair::gui::SendData *obj);
  void RemoveSendData(const flair::gui::SendData *obj);
  void UpdateDataToSendSize(void);
  void Block(void);
  void UnBlock(void);
  bool ConnectionLost(void);

private:
  ssize_t send_size;
  char *send_buffer;
  std::vector<const flair::gui::SendData *> data_to_send;
  std::vector<flair::core::Time> resume_time;
  flair::core::Mutex *send_mutex;
  UDTSOCKET socket_fd;
  bool connection_lost;
  void Run(void);
  void SendDatas(void);
  static int compressBuffer(char *in, ssize_t in_size, char **out,
                            ssize_t *out_size, int level);
  static int uncompressBuffer(unsigned char *in, ssize_t in_size,
                              unsigned char **out, ssize_t *out_size);
#ifdef __XENO__
  bool is_running;
  static void *user_thread(void *arg);
  pthread_t thread;
  RT_PIPE pipe;
#endif
};

#endif // UI_COM_H
