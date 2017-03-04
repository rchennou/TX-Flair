// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Socket_impl.h
 * \brief Classe creant une socket
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/11/17
 * \version 4.0
 */

#ifndef SOCKET_IMPL_H
#define SOCKET_IMPL_H

#include <sys/socket.h>
#include <netdb.h>
#include <Object.h>
#ifdef __XENO__
#include <native/pipe.h>
#endif

namespace flair {
namespace core {
class Socket;
}
}

class Socket_impl {
public:
  Socket_impl(const flair::core::Socket *self, std::string name,
              std::string address, bool broadcast = false);
  Socket_impl(const flair::core::Socket *self, std::string name, uint16_t port);
  ~Socket_impl();

  void SendMessage(std::string message);
  void SendMessage(const char *src, size_t src_len);
  ssize_t RecvMessage(char *msg, size_t msg_len, flair::core::Time timeout,
                      char *src = NULL, size_t *src_len = NULL);

private:
  int fd;
  uint16_t port;
  std::string address;
  bool broadcast;
  void Init(void);
  const flair::core::Socket *self;
  struct sockaddr_in sock_in;
#ifdef __XENO__
  bool is_running;
  static void *user(void *arg);
  pthread_t user_thread;
  RT_PIPE pipe;
#endif
};

#endif // SOCKET_IMPL_H
