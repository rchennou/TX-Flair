// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   ui_com.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe permettant la lecture et l'ecriture sur socket UDT
//
//
/*********************************************************************/

#include "ui_com.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include "Mutex.h"
#include "SendData.h"
#include "communication.h"
#include "FrameworkManager.h"
#include "zlib.h"
#include <assert.h>
#include "config.h"

#ifdef __XENO__
#include <pthread.h>
#include <native/task.h>
#include <native/task.h>
#include <fcntl.h>
#endif

using std::string;
using namespace flair::core;
using namespace flair::gui;

ui_com::ui_com(const Object *parent, UDTSOCKET sock)
    : Thread(parent, "send", 2) {
  // buffer envoi
  send_buffer = (char *)malloc(3);
  send_size = 3; // id(1)+period(2)

  // mutex
  send_mutex = NULL;
  send_mutex = new Mutex(this, ObjectName());

  socket_fd = sock;
  connection_lost = false;

#ifdef __XENO__
  int status;
  string tmp_name;

  is_running = true;

  // pipe
  tmp_name = getFrameworkManager()->ObjectName() + "-" + ObjectName() + "-pipe";
  // xenomai limitation
  if (tmp_name.size() > 31)
    Err("rt_pipe_create error (%s is too long)\n", tmp_name.c_str());
#ifdef RT_PIPE_SIZE
  status = rt_pipe_create(&pipe, tmp_name.c_str(), P_MINOR_AUTO, RT_PIPE_SIZE);
#else
  status = rt_pipe_create(&pipe, tmp_name.c_str(), P_MINOR_AUTO, 0);
#endif

  if (status != 0) {
    Err("rt_pipe_create error (%s)\n", strerror(-status));
    // return -1;
  }

// start user side thread
#ifdef NRT_STACK_SIZE
  // Initialize thread creation attributes
  pthread_attr_t attr;
  if (pthread_attr_init(&attr) != 0) {
    Err("pthread_attr_init error\n");
  }

  if (pthread_attr_setstacksize(&attr, NRT_STACK_SIZE) != 0) {
    Err("pthread_attr_setstacksize error\n");
  }

  if (pthread_create(&thread, &attr, user_thread, (void *)this) < 0)
#else  // NRT_STACK_SIZE
  if (pthread_create(&thread, NULL, user_thread, (void *)this) < 0)
#endif // NRT_STACK_SIZE
  {
    Err("pthread_create error\n");
    // return -1;
  }
#ifdef NRT_STACK_SIZE
  if (pthread_attr_destroy(&attr) != 0) {
    Err("pthread_attr_destroy error\n");
  }
#endif

#endif //__XENO__
  int timeout = 100;
  if (UDT::setsockopt(socket_fd, 0, UDT_RCVTIMEO, &timeout, sizeof(int)) != 0)
    Err("UDT::setsockopt error (UDT_RCVTIMEO)\n");

  bool blocking = true;
  if (UDT::setsockopt(socket_fd, 0, UDT_SNDSYN, &blocking, sizeof(bool)) != 0)
    Err("UDT::setsockopt error (UDT_SNDSYN)\n");

  if (UDT::setsockopt(socket_fd, 0, UDT_RCVSYN, &blocking, sizeof(bool)) != 0)
    Err("UDT::setsockopt error (UDT_RCVSYN)\n");
  //#endif //__XENO__

  Start();
}

ui_com::~ui_com() {
// printf("destruction ui_com\n");

#ifdef __XENO__
  is_running = false;

  pthread_join(thread, NULL);

  int status = rt_pipe_delete(&pipe);
  if (status != 0)
    Err("rt_pipe_delete error (%s)\n", strerror(-status));
#endif

  SafeStop();

  if (IsSuspended() == true)
    Resume();

  Join();

  if (send_buffer != NULL)
    free(send_buffer);
  send_buffer = NULL;

  // printf("destruction ui_com ok\n");
}

void ui_com::Send(char *buf, ssize_t size) {
  if (connection_lost == true)
    return;

  char *tosend = buf;
  ssize_t nb_write;

  if (buf[0] == XML_HEADER) {
    // cut xml header
    tosend = strstr(buf, "<root");
    size -= tosend - buf;
  }

#ifdef __XENO__
  nb_write = rt_pipe_write(&pipe, tosend, size, P_NORMAL);

  if (nb_write < 0) {
    Err("rt_pipe_write error (%s)\n", strerror(-nb_write));
  } else if (nb_write != size) {
    Err("rt_pipe_write error %i/%i\n", nb_write, size);
  }
#else //__XENO__

#ifdef COMPRESS_FRAMES
  bool sendItCompressed = false;
  if (buf[0] == XML_HEADER) {
    sendItCompressed = true;
  }

  if (sendItCompressed) {
    char *out;
    ssize_t out_size;
    if (compressBuffer(tosend, size, &out, &out_size, 9) == Z_OK) {
      size = out_size;
      nb_write = UDT::sendmsg(socket_fd, out, size, -1, true);
      free(out);
    } else {
      Warn("Compress error, sending it uncompressed\n");
      sendItCompressed = false;
    }
  }

  if (!sendItCompressed) {
    nb_write = UDT::sendmsg(socket_fd, tosend, size, -1, true);
  }

#else // COMPRESS_FRAMES
  nb_write = UDT::sendmsg(socket_fd, tosend, size, -1, true);
#endif // COMPRESS_FRAMES
  // Printf("write %i %i\n",nb_write,size);
  if (nb_write < 0) {
    Err("UDT::sendmsg error (%s)\n", UDT::getlasterror().getErrorMessage());
    if (UDT::getlasterror().getErrorCode() == CUDTException::ECONNLOST ||
        UDT::getlasterror().getErrorCode() == CUDTException::EINVSOCK) {
      connection_lost = true;
    }
  } else if (nb_write != size) {
    Err("%s, code %i (%ld/%ld)\n", UDT::getlasterror().getErrorMessage(),
        UDT::getlasterror().getErrorCode(), nb_write, size);
  }
#endif //__XENO__
}

ssize_t ui_com::Receive(char *buf, ssize_t buf_size) {
  ssize_t bytesRead = UDT::recvmsg(socket_fd, buf, buf_size);

  if (bytesRead < 0) {
    if (UDT::getlasterror().getErrorCode() == CUDTException::ECONNLOST) {
      Err("UDT::recvmsg error (%s)\n", UDT::getlasterror().getErrorMessage());
      connection_lost = true;
    }
  }

  return bytesRead;
}

void ui_com::Run(void) {
  // check endianness
  char header;
  if (IsBigEndian()) {
    header = DATAS_BIG_ENDIAN;
    Printf("System is big endian\n");
  } else {
    header = DATAS_LITTLE_ENDIAN;
    Printf("System is little endian\n");
  }

#ifdef __XENO__
  WarnUponSwitches(true);
  printf("\n"); // a revoir pourquoi??
// sans ce printf, dans le simu_roll, le suspend ne fonctionne pas...
#endif
  // on attend d'avoir des choses à faire
  Suspend();

  while (!ToBeStopped()) {
    size_t resume_id;
    Time min = 0xffffffffffffffffULL;

    // on recpuere l'id de la prochaine execution
    send_mutex->GetMutex();
    resume_id = resume_time.size();
    for (size_t i = 0; i < resume_time.size(); i++) {
      if (resume_time.at(i) < min && data_to_send.at(i)->IsEnabled() == true) {
        min = resume_time.at(i);
        resume_id = i;
      }
    }

    // attente
    if (resume_id < resume_time.size()) {
      Time time = resume_time.at(resume_id);
      uint16_t resume_period = data_to_send.at(resume_id)->SendPeriod();
      send_mutex->ReleaseMutex();
      // on dort jusqu'a la prochaine execution
      SleepUntil(time);

      // envoi des donnees
      int offset = 3;
      send_buffer[0] = header;
      send_mutex->GetMutex();

      for (size_t i = 0; i < data_to_send.size(); i++) {
        if (data_to_send.at(i)->SendPeriod() == resume_period &&
            data_to_send.at(i)->IsEnabled() == true) {
          data_to_send.at(i)->CopyDatas(send_buffer + offset);
          offset += data_to_send.at(i)->SendSize();
        }
      }
      if (offset != 3) {
        memcpy(&send_buffer[1], &resume_period, sizeof(uint16_t));
        // printf("send %i %i %i %x
        // %x\n",resume_period,offset,sizeof(uint16_t),send_buffer,&send_buffer[1]);
        // for(int i=0;i<offset;i++) printf("%x ",send_buffer[i]);
        // printf("\n");
        Send(send_buffer, offset);
      }

      // on planifie la prochaine execution
      for (size_t i = 0; i < data_to_send.size(); i++) {
        if (data_to_send.at(i)->SendPeriod() == resume_period) {
          resume_time.at(i) += data_to_send.at(i)->SendPeriod() * 1000000;
        }
      }
      send_mutex->ReleaseMutex();
      // Printf("%i %lld\n",resume_period,GetTime()/1000000);
    } else {
      send_mutex->ReleaseMutex();
      // rien a faire, suspend
      // Printf("rien a faire suspend\n");
      Suspend();
      // Printf("wake\n");
      // on planifie la prochaine execution
      Time time = GetTime();
      send_mutex->GetMutex();
      for (size_t i = 0; i < data_to_send.size(); i++) {
        resume_time.at(i) =
            time + (Time)data_to_send.at(i)->SendPeriod() * 1000000;
      }
      send_mutex->ReleaseMutex();
    }
  }
}
#ifdef __XENO__
void *ui_com::user_thread(void *arg) {
  int pipe_fd = -1;
  string devname;
  char *buf = NULL;
  ui_com *caller = (ui_com *)arg;
  int rv;
  fd_set set;
  struct timeval timeout;
  ssize_t nb_read, nb_write;

  buf = (char *)malloc(NRT_PIPE_SIZE);
  if (buf == NULL) {
    caller->Err("malloc error\n");
  }

  devname = NRT_PIPE_PATH + getFrameworkManager()->ObjectName() + "-" +
            caller->ObjectName() + "-pipe";
  while (pipe_fd < 0) {
    pipe_fd = open(devname.c_str(), O_RDWR);
    if (pipe_fd < 0 && errno != ENOENT)
      caller->Err("open pipe_fd error (%s)\n", strerror(-errno));
    usleep(1000);
  }

  while (1) {
    FD_ZERO(&set);         // clear the set
    FD_SET(pipe_fd, &set); // add our file descriptor to the set

    timeout.tv_sec = 0;
    timeout.tv_usec = SELECT_TIMEOUT_MS * 1000;

    rv = select(FD_SETSIZE, &set, NULL, NULL, &timeout);

    if (rv == -1) {
      if (caller->is_running == false &&
          UDT::getlasterror().getErrorCode() == CUDTException::ETIMEOUT)
        break; // timeout
      if (UDT::getlasterror().getErrorCode() != CUDTException::ETIMEOUT)
        caller->Err("epoll_wait, %s, code %i\n",
                    UDT::getlasterror().getErrorMessage(),
                    UDT::getlasterror().getErrorCode());
    } else if (rv == 0) {
      // printf("timeout\n"); // a timeout occured
      if (caller->is_running == false)
        break;

    } else {
      nb_read = read(pipe_fd, buf, NRT_PIPE_SIZE);
      buf[nb_read] = 0;
// printf("envoi\n%s\n",buf);

#ifdef COMPRESS_FRAMES
      char *out;
      ssize_t out_size;

      if (buf[0] == XML_HEADER) {
        if (compressBuffer(buf, nb_read, &out, &out_size, 9) == Z_OK) {
          nb_read = out_size;
          nb_write = UDT::sendmsg(caller->socket_fd, out, out_size, -1, true);
          free(out);
        } else {
          caller->Warn("Compress error, sending it uncompressed\n");
          nb_write = UDT::sendmsg(caller->socket_fd, buf, nb_read, -1, true);
        }
      } else {
        nb_write = UDT::sendmsg(caller->socket_fd, buf, nb_read, -1, true);
      }
#else
      nb_write = UDT::sendmsg(caller->socket_fd, buf, nb_read, -1, true);
#endif

      if (nb_write < 0) {
        caller->Err("UDT::sendmsg error (%s)\n",
                    UDT::getlasterror().getErrorMessage());
        if (UDT::getlasterror().getErrorCode() == CUDTException::ECONNLOST ||
            UDT::getlasterror().getErrorCode() == CUDTException::EINVSOCK) {
          caller->connection_lost = true;
        }
      } else if (nb_write != nb_read) {
        caller->Err("UDT::sendmsg error %i/%i\n", nb_write, nb_read);
      }
    }
  }

  close(pipe_fd);
  if (buf != NULL)
    free(buf);
  pthread_exit(0);
}
#endif

int ui_com::compressBuffer(char *in, ssize_t in_size, char **out,
                           ssize_t *out_size, int level) {
  int ret, flush;
  unsigned have;
  z_stream strm;

  /* allocate deflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  ret = deflateInit(&strm, level);
  if (ret != Z_OK)
    return ret;

  *out = (char *)malloc(COMPRESS_CHUNK);
  if (!(*out))
    return Z_BUF_ERROR;

  strm.next_in = (unsigned char *)in;
  strm.avail_out = COMPRESS_CHUNK;
  strm.next_out = (unsigned char *)*out;
  strm.avail_in = in_size;
  flush = Z_FINISH;

  ret = deflate(&strm, flush); /* no bad return value */
  if (ret == Z_STREAM_ERROR) {
    free(*out);
    return ret;
  }

  have = COMPRESS_CHUNK - strm.avail_out;
  *out_size = have;
  // printf("%i -> %i\n",in_size,have);
  /* clean up and return */
  (void)deflateEnd(&strm);

  if (strm.avail_out != 0) {
    return Z_OK;
  } else {
    return Z_STREAM_ERROR;
  }
}

int ui_com::uncompressBuffer(unsigned char *in, ssize_t in_size,
                             unsigned char **out, ssize_t *out_size) {
  int ret;
  // unsigned have;
  z_stream strm;

  /* allocate inflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  ret = inflateInit(&strm);
  if (ret != Z_OK)
    return ret;

  *out = (unsigned char *)malloc(COMPRESS_CHUNK);
  if (!(*out))
    return Z_BUF_ERROR;

  strm.avail_in = in_size;
  strm.next_in = in;
  strm.avail_out = COMPRESS_CHUNK;
  strm.next_out = *out;

  ret = inflate(&strm, Z_NO_FLUSH);
  assert(ret != Z_STREAM_ERROR); /* state not clobbered */
  switch (ret) {
  case Z_NEED_DICT:
    ret = Z_DATA_ERROR; /* and fall through */
  case Z_DATA_ERROR:
  case Z_MEM_ERROR:
    (void)inflateEnd(&strm);
    return ret;
  }
  // have = COMPRESS_CHUNK - strm.avail_out;

  /* clean up and return */
  (void)inflateEnd(&strm);
  return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

bool ui_com::ConnectionLost() { return connection_lost; }

void ui_com::AddSendData(const SendData *obj) {
  send_mutex->GetMutex();

  resume_time.push_back(GetTime() + (Time)obj->SendPeriod() * 1000000);

  // on resume en meme temps tout ceux qui ont la meme periode
  for (size_t i = 0; i < data_to_send.size(); i++) {
    if (data_to_send.at(i)->SendPeriod() == obj->SendPeriod()) {
      resume_time.at(resume_time.size() - 1) = resume_time.at(i);
      break;
    }
  }

  data_to_send.push_back(obj);

  send_mutex->ReleaseMutex();
}

void ui_com::UpdateSendData(const SendData *obj) {
  // le mutex est deja pris par l'appellant
  size_t id, i;

  // on recupere l'id
  for (i = 0; i < data_to_send.size(); i++) {
    if (data_to_send.at(i) == obj) {
      id = i;
      break;
    }
  }

  // on resume en meme temps tout ceux qui ont la meme periode
  for (i = 0; i < data_to_send.size(); i++) {
    if (i == id)
      continue;
    if (data_to_send.at(i)->IsEnabled() == true &&
        data_to_send.at(i)->SendPeriod() == obj->SendPeriod()) {
      resume_time.at(id) = resume_time.at(i);
      break;
    }
  }

  // si aucun match, on planifie l'execution
  if (i == data_to_send.size())
    resume_time.at(id) = GetTime() + (Time)obj->SendPeriod() * 1000000;

  if (IsSuspended() == true)
    Resume();

  return;
}

void ui_com::UpdateDataToSendSize(void) {
  send_mutex->GetMutex();
  send_size = 3; // id(1)+period(2)
  for (size_t i = 0; i < data_to_send.size(); i++) {
    if (data_to_send[i] != NULL)
      send_size += data_to_send[i]->SendSize();
  }

  // send_buffer=(char*)realloc((void*)send_buffer,send_size*sizeof(char));
  if (send_buffer != NULL)
    free(send_buffer);
  send_buffer = (char *)malloc(send_size * sizeof(char));
  send_mutex->ReleaseMutex();
}

void ui_com::RemoveSendData(const SendData *obj) {
  // printf("remove_data_to_send %i\n",data_to_send.size());

  send_mutex->GetMutex();
  // on recupere l'id
  for (size_t i = 0; i < data_to_send.size(); i++) {
    if (data_to_send.at(i) == obj) {
      data_to_send.erase(data_to_send.begin() + i);
      resume_time.erase(resume_time.begin() + i);
      // printf("remove_data_to_send %i ok\n",data_to_send.size());
      break;
    }
  }
  send_mutex->ReleaseMutex();

  return;
}

void ui_com::Block(void) { send_mutex->GetMutex(); }

void ui_com::UnBlock(void) { send_mutex->ReleaseMutex(); }
