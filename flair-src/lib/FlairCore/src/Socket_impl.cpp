// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/11/17
//  filename:   Socket_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe pour une Socket_impl
//
//
/*********************************************************************/
#include "Socket_impl.h"
#include "Socket.h"
#include "FrameworkManager.h"
#include <fcntl.h>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#ifdef __XENO__
#include "config.h"
#endif

using std::string;
using namespace flair::core;

Socket_impl::Socket_impl(const Socket *self, string name, uint16_t port) {
  this->self = self;
  this->port = port;
  this->address = "";
  this->broadcast = false;
  Init();
}

Socket_impl::Socket_impl(const Socket *self, string name, string address,
                         bool broadcast) {
  this->self = self;
  int pos = address.find(":");
  this->address = address.substr(0, pos);
  port = atoi(address.substr(pos + 1).c_str());
  this->broadcast = broadcast;

  if (pos == 0 || address == "") {
    self->Err("address %s is not correct\n", address.c_str());
  }
  Init();
}

void Socket_impl::Init(void) {
  int yes = 1;

  fd = socket(AF_INET, SOCK_DGRAM, 0); // UDP

  if (broadcast == true) {
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int)) != 0)
      self->Err("Setsockopt error\n");
  }

  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0)
    self->Err("Setsockopt error\n");

  if (address == "" || broadcast == true) {
    sockaddr_in sin = {0};

    if (broadcast == true) {
      struct hostent *hostinfo;

      hostinfo = gethostbyname(this->address.c_str());
      if (hostinfo == NULL) {
        self->Err("hostinfo error\n");
      }
      sin.sin_addr = *(in_addr *)hostinfo->h_addr;
    } else {
      sin.sin_addr.s_addr = INADDR_ANY;
    }

    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;
    if (bind(fd, (sockaddr *)&sin, sizeof sin) == -1) {
      self->Err("bind error\n");
    }
  }

#ifdef __XENO__
  string tmp_name;
  int status;
  is_running = true;

  // pipe
  tmp_name =
      getFrameworkManager()->ObjectName() + "-" + self->ObjectName() + "-pipe";
  // xenomai limitation
  if (tmp_name.size() > 31)
    self->Err("rt_pipe_create error (%s is too long)\n", tmp_name.c_str());
#ifdef RT_PIPE_SIZE
  status = rt_pipe_create(&pipe, tmp_name.c_str(), P_MINOR_AUTO, RT_PIPE_SIZE);
#else
  status = rt_pipe_create(&pipe, tmp_name.c_str(), P_MINOR_AUTO, 0);
#endif
  if (status != 0) {
    self->Err("rt_pipe_create error (%s)\n", strerror(-status));
  }

// start user side thread
#ifdef NRT_STACK_SIZE
  // Initialize thread creation attributes
  pthread_attr_t attr;
  if (pthread_attr_init(&attr) != 0) {
    self->Err("pthread_attr_init error\n");
  }
  if (pthread_attr_setstacksize(&attr, NRT_STACK_SIZE) != 0) {
    self->Err("pthread_attr_setstacksize error\n");
  }
  if (pthread_create(&user_thread, &attr, user, (void *)this) < 0) {
    self->Err("pthread_create error\n");
  }
  if (pthread_attr_destroy(&attr) != 0) {
    self->Err("pthread_attr_destroy error\n");
  }
#else  // NRT_STACK_SIZE
  if (pthread_create(&user_thread, NULL, user, (void *)this) < 0) {
    self->Err("pthread_create error\n");
  }
#endif // NRT_STACK_SIZE
#endif //__XENO__

  if (address != "") {
    struct hostent *hostinfo;
    hostinfo = gethostbyname(address.c_str());
    if (hostinfo == NULL) {
      self->Err("gethostbyname\n");
    }

    sock_in.sin_addr = *(in_addr *)hostinfo->h_addr;
    sock_in.sin_port = htons(port);
    sock_in.sin_family = AF_INET;
  }
}

Socket_impl::~Socket_impl() {
#ifdef __XENO__
  is_running = false;

  pthread_join(user_thread, NULL);
  int status = rt_pipe_delete(&pipe);
  if (status != 0)
    self->Err("rt_pipe_delete error (%s)\n", strerror(-status));

#endif
  close(fd);
}

void Socket_impl::SendMessage(const char *src, size_t src_len) {
  ssize_t written;
  string to_send;

  if (broadcast == true) {
    to_send = getFrameworkManager()->ObjectName() + ":" + string(src, src_len);
    src_len = to_send.size();
    src = (char *)to_send.c_str();
  }

#ifdef __XENO__
  // Printf("send pipe %s\n",src);
  written = rt_pipe_write(&pipe, src, src_len, P_NORMAL);

  if (written < 0) {
    self->Err("rt_pipe_write error (%s)\n", strerror(-written));
  } else if (written != (ssize_t)src_len) {
    self->Err("rt_pipe_write error %i/%i\n", written, to_send.size());
  }
#else
  written =
      sendto(fd, src, src_len, 0, (struct sockaddr *)&sock_in, sizeof(sock_in));
  if(written==-1) {
    self->Err("sendto error (%s)\n",strerror(-errno));
  } else if (written != (ssize_t)src_len) {
    self->Err("sendto error %i/%i\n",written,src_len);
  }
#endif
}

void Socket_impl::SendMessage(string message) {
  ssize_t written;

  if (broadcast == true)
    message = self->Parent()->ObjectName() + ":" + message;
// Printf("SendMessage %s\n",message.c_str());
#ifdef __XENO__
  written = rt_pipe_write(&pipe, message.c_str(), message.size(), P_NORMAL);

  if (written < 0) {
    self->Err("rt_pipe_write error (%s)\n", strerror(-written));
  } else if (written != (ssize_t)message.size()) {
    self->Err("rt_pipe_write error %i/%i\n", written, message.size());
  }
#else
  written = sendto(fd, message.c_str(), message.size(), 0,
                   (struct sockaddr *)&sock_in, sizeof(sock_in));
  if (written != (ssize_t)message.size()) {
    self->Err("sendto error\n");
  }

#endif
}

ssize_t Socket_impl::RecvMessage(char *msg, size_t msg_len, Time timeout,
                                 char *src, size_t *src_len) {
  ssize_t nb_read;
  char buffer[128];
#ifdef __XENO__
  nb_read = rt_pipe_read(&pipe, &buffer, sizeof(buffer), timeout);
#else
  socklen_t sinsize = sizeof(sock_in);
  struct timeval tv;

  if (timeout != TIME_NONBLOCK) {
    int attr = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, attr & (~O_NONBLOCK));

    tv.tv_sec = timeout / 1000000000;
    timeout = timeout - (timeout / 1000000000) * 1000000000;
    tv.tv_usec = timeout / 1000;
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
      self->Err("setsockopt SO_RCVTIMEO failed\n");
    }
  } else {
    fcntl(fd, F_SETFL, O_NONBLOCK);
  }

  if (broadcast == false) {
    nb_read =
        recvfrom(fd, buffer, sizeof(buffer), 0, (sockaddr *)&sock_in, &sinsize);
  } else {
    nb_read = recvfrom(fd, buffer, sizeof(buffer), 0, NULL, NULL);
  }
#endif
  if (nb_read <= 0) {
    return nb_read;
  } else {
    // printf("%s\n",buffer);
    if (broadcast == true) {
      int index = -1;
      for (int i = 0; i < nb_read; i++) {
        if (buffer[i] == ':') {
          index = i;
          break;
        }
      }
      if (index < 0) {
        self->Warn("Malformed message\n");
        return -1;
      } else if (src_len != NULL && src != NULL) {
        if (index + 1 > (int)(*src_len) &&
            src != NULL) { //+1 pour inserer un 0)
          self->Warn("insufficent src size\n");
          return -1;
        }
      } else if (nb_read - index - 1 + 1 >
                 (int)msg_len) { //+1 pour inserer un 0
        self->Warn("insufficent msg size (%i/%i)\n", nb_read - index - 1 + 1,
                   msg_len);
        return -1;
      }
      if (src != NULL) {
        memcpy(src, buffer, index);
        src[index] = 0;
      }
      memcpy(msg, &buffer[index + 1], nb_read - index - 1);
      msg[nb_read - index - 1] = 0;
      return nb_read - index;
    } else {
      if (nb_read > (int)msg_len) {
        self->Warn("insufficent msg size (%i/%i)\n", nb_read, msg_len);
        return -1;
      }
      memcpy(msg, buffer, nb_read);
      return nb_read;
    }
  }
}

#ifdef __XENO__
void *Socket_impl::user(void *arg) {
  Socket_impl *caller = (Socket_impl *)arg;
  int pipe_fd = -1;
  string devname;

  devname = NRT_PIPE_PATH + getFrameworkManager()->ObjectName() + "-" +
            caller->self->ObjectName() + "-pipe";
  while (pipe_fd < 0) {
    pipe_fd = open(devname.c_str(), O_RDWR);
    if (pipe_fd < 0 && errno != ENOENT)
      caller->self->Err("open pipe_fd error (%s)\n", strerror(-errno));
    usleep(1000);
  }

  while (caller->is_running == true) {
    fd_set set;
    struct timeval timeout;
    int rv;

    FD_ZERO(&set);            // clear the set
    FD_SET(caller->fd, &set); // add our file descriptor to the set
    FD_SET(pipe_fd, &set);    // add our file descriptor to the set

    timeout.tv_sec = 0;
    timeout.tv_usec = SELECT_TIMEOUT_MS * 1000;
    rv = select(FD_SETSIZE, &set, NULL, NULL, &timeout);

    if (rv == -1) {
      caller->self->Err("select error\n"); // an error occured
    } else if (rv == 0) {
      // printf("timeout\n");
    } else {
      ssize_t nb_read, nb_write;
      char buffer[1024];

      if (FD_ISSET(caller->fd, &set)) {
        socklen_t sinsize = sizeof(caller->sock_in);
        if (caller->broadcast == false) {
          nb_read = recvfrom(caller->fd, buffer, sizeof(buffer), 0,
                             (sockaddr *)&(caller->sock_in), &sinsize);
        } else {
          nb_read = recvfrom(caller->fd, buffer, sizeof(buffer), 0, NULL, NULL);
        }
        if (nb_read < 0) {
          caller->self->Err("recvfrom error\n");
        }
        // printf("user %s\n",buffer);
        // on ne garde que les messages venant pas de soi meme
        if (caller->broadcast == false ||
            (caller->broadcast == true &&
             getFrameworkManager()->ObjectName().compare(
                 0, getFrameworkManager()->ObjectName().size(), buffer,
                 getFrameworkManager()->ObjectName().size()) != 0)) {
          nb_write = write(pipe_fd, buffer, nb_read);
          if (nb_write != nb_read) {
            caller->self->Err("write error\n");
          }
        } else {
          // printf("self %s\n",buffer);
        }
      }
      if (FD_ISSET(pipe_fd, &set)) {
        nb_read = read(pipe_fd, buffer, sizeof(buffer));
        // printf("read pipe %i %s\n",nb_read,buffer);
        if (nb_read > 0) {
          // printf("send %s\n",buffer);
          nb_write = sendto(caller->fd, buffer, nb_read, 0,
                            (struct sockaddr *)&(caller->sock_in),
                            sizeof(caller->sock_in));
          if (nb_write != nb_read) {
            caller->self->Err("sendto error\n");
          }
        }
      }
    }
  }

  close(pipe_fd);
  pthread_exit(0);
}
#endif
