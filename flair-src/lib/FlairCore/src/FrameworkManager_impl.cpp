// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/08/31
//  filename:   FrameworkManager.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Classe de base de la librairie
//
//
/*********************************************************************/

#include "FrameworkManager_impl.h"
#include "FrameworkManager.h"
#include "Widget_impl.h"
#include <unistd.h>
#include "IODevice.h"
#include "IODevice_impl.h"
#include "TabWidget.h"
#include "Layout.h"
#include "PushButton.h"
#include "communication.h"
#include "config.h"
#include "Watchdog.h"
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <execinfo.h>
#include <signal.h>
#include <fcntl.h>
#ifdef __XENO__
#include <native/task.h>
#endif

using namespace std;
using namespace flair::core;
using namespace flair::gui;

ui_com *FrameworkManager_impl::com = NULL;
FrameworkManager_impl *FrameworkManager_impl::_this = NULL;

namespace {
#ifdef __XENO__

#ifdef SIGDEBUG
static const char *reason_str[] = {
    "undefined", "received signal", "invoked syscall", "triggered fault",
    "affected by priority inversion", "missing mlockall", "runaway thread",
};

void warn_upon_switch(int sig, siginfo_t *si, void *context) {
  unsigned int reason = si->si_value.sival_int;
  void *bt[32];
  int nentries;
#ifdef SIGDEBUG_WATCHDOG
  printf("\nSIGDEBUG received, reason %d: %s\n", reason,
         reason <= SIGDEBUG_WATCHDOG ? reason_str[reason] : "<unknown>");
#endif
  // Dump a backtrace of the frame which caused the switch to secondary mode:
  nentries = backtrace(bt, sizeof(bt) / sizeof(bt[0]));
  backtrace_symbols_fd(bt, nentries, fileno(stdout));
}
#else  // SIGDEBUG
void warn_upon_switch(int sig __attribute__((unused))) {
  void *bt[32];
  int nentries;

  /* Dump a backtrace of the frame which caused the switch to
     secondary mode: */
  nentries = backtrace(bt, sizeof(bt) / sizeof(bt[0]));
  backtrace_symbols_fd(bt, nentries, fileno(stdout));
}
#endif // SIGDEBUG
#endif //__XENO__
void seg_fault(int sig __attribute__((unused))) {
  void *bt[32];
  int nentries;

  printf("Segmentation fault:\n");
  /* Dump a backtrace of the frame which caused the segfault: */
  nentries = backtrace(bt, sizeof(bt) / sizeof(bt[0]));
  backtrace_symbols_fd(bt, nentries, fileno(stdout));

  exit(1);
}
}

FrameworkManager_impl::FrameworkManager_impl(FrameworkManager *self,
                                             string name)
    : Thread(self, "FrameworkManager", FRAMEWORK_TASK_PRIORITY) {
  this->self = self;
  is_logging = false;
  logger_defined = false;
  disable_errors = false;
  ui_defined = false;
  rcv_buf = NULL;
  gcs_watchdog = NULL;
  _this = this;
  tabwidget=NULL;

  // Avoids memory swapping for this program
  mlockall(MCL_CURRENT | MCL_FUTURE);

  // catch segfault
  signal(SIGSEGV, seg_fault);

// catch primary->secondary switch
#ifdef __XENO__
#ifdef SIGDEBUG
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = warn_upon_switch;
  sa.sa_flags = SA_SIGINFO;
  sigaction(SIGDEBUG, &sa, NULL);
#else
  signal(SIGXCPU, warn_upon_switch);
#endif

  string task_name = "Framework_" + name;
  int status = rt_task_shadow(NULL, task_name.c_str(), 10, 0);
  if (status != 0) {
    self->Err("rt_task_shadow error (%s)\n", strerror(-status));
  }

#endif //__XENO__
}

void FrameworkManager_impl::ConnectionLost(void) {
  Err("connection lost\n");
  gcs_watchdog->SafeStop();
  connection_lost = true;
}

FrameworkManager_impl::~FrameworkManager_impl() {
  // Printf("destruction FrameworkManager_impl\n");
  int status;

  SafeStop();
  Join();

  if (rcv_buf != NULL)
    free(rcv_buf);

  if (logger_defined == true) {
    continuer = false;
    (void)pthread_join(log_th, NULL);

    status = DeletePipe(&cmd_pipe);
    if (status != 0) {
      Err("Error deleting pipe (%s)\n", strerror(-status));
    }
    status = DeletePipe(&data_pipe);
    if (status != 0) {
      Err("Error deleting pipe (%s)\n", strerror(-status));
    }

#ifdef __XENO__
    status = rt_heap_delete(&log_heap);
    if (status != 0) {
      Err("rt_heap_delete error (%s)\n", strerror(-status));
    }
#endif

    logs.clear();
  }

  if (file_doc != NULL)
    xmlFreeDoc(file_doc);

  if (ui_defined)
    delete top_layout;

  if (com != NULL) {
    delete com;
    status = UDT::close(com_sock);
    if (status != 0)
      Printf("Error udt::close %s", UDT::getlasterror().getErrorMessage());

    status = UDT::close(file_sock);
    if (status != 0)
      Printf("Error udt::close %s", UDT::getlasterror().getErrorMessage());

    SleepMS(200); // a revoir, sinon UDT::cleanup bloque en RT
    UDT::cleanup();
  }

  // Printf("destruction FrameworkManager_impl ok\n");
}

void FrameworkManager_impl::SetupConnection(string address, uint16_t port,Time watchdogTimeout,
                                            size_t rcv_buf_size) {
  UDT::startup();
  this->rcv_buf_size = rcv_buf_size;

  // socket file_socket, doit être créé en premier, cf station sol
  Printf("Connecting to %s:%i\n", address.c_str(), port);
  file_sock = GetSocket(address, port);
  com_sock = GetSocket(address, port);

  // receive buffer allocation
  rcv_buf = (char *)malloc(rcv_buf_size);
  if (rcv_buf == NULL) {
    Err("receive buffer malloc error\n");
  }

  com = new ui_com(this, com_sock);

  // file managment
  bool blocking = true;
  UDT::setsockopt(file_sock, 0, UDT_SNDSYN, &blocking, sizeof(bool));
  UDT::setsockopt(file_sock, 0, UDT_RCVSYN, &blocking, sizeof(bool));

  int timeout = 100; // ms
  UDT::setsockopt(com_sock, 0, UDT_RCVTIMEO, &timeout, sizeof(int));

  Start();

  // watchdog for connection with ground station
  connection_lost = false;
  gcs_watchdog = new Watchdog(
      this, std::bind(&FrameworkManager_impl::ConnectionLost, this),
      (Time)1000000000);
  gcs_watchdog->Start();
}

void FrameworkManager_impl::SetupUserInterface(string xml_file) {
  ui_defined = true;
  this->xml_file = xml_file;

  // top_layout=new Layout(NULL,XML_ROOT_ELEMENT,XML_ROOT_TYPE);
  top_layout = new Layout(NULL, self->ObjectName(), XML_ROOT_TYPE);

  // xml setup of the main widget
  if (xml_file != "") {
    xmlNodePtr *file_node = &(((Widget *)(top_layout))->pimpl_->file_node);
    file_doc = xmlParseFile(xml_file.c_str());
    if (file_doc == NULL) {
      self->Warn("XML document not parsed successfully. Creating a new one.\n");
      file_doc = xmlNewDoc((xmlChar *)"1.0");
      *file_node = xmlNewNode(NULL, (xmlChar *)XML_ROOT_TYPE);
      xmlSetProp(*file_node, (xmlChar *)"name",
                 (xmlChar *)ObjectName().c_str());
      xmlDocSetRootElement(file_doc, *file_node);
      // PrintXml();
    } else {
      *file_node = xmlDocGetRootElement(file_doc);
      if (xmlStrcmp((*file_node)->name, (xmlChar *)XML_ROOT_TYPE)) {
        self->Warn("%s, no match found in xml file\n", XML_ROOT_TYPE);
        *file_node = xmlNewNode(NULL, (xmlChar *)XML_ROOT_TYPE);
        xmlSetProp(*file_node, (xmlChar *)"name",
                   (xmlChar *)ObjectName().c_str());
        xmlDocSetRootElement(file_doc, *file_node);
      }
    }
  } else {
    self->Err("xml file not defined\n");
  }

  // gui
  tabwidget =
      new TabWidget(top_layout->At(0, 0), XML_MAIN_TABWIDGET, TabWidget::North);
  save_button =
      new PushButton(top_layout->At(1, 0),
                     "save config on target (" + self->ObjectName() + ")");
  // load_button=new PushButton(top_layout->At(1,1),"load config on target (" +
  // self->ObjectName() + ")");
}

// in case of RT, this thread switches to secondary mode when calling
// com->Receive
// it switches back to RT in ProcessXML when mutex are locked
void FrameworkManager_impl::Run(void) {
  while (!ToBeStopped()) {
    ssize_t bytesRead;

    bytesRead = com->Receive(rcv_buf, rcv_buf_size);

    if (bytesRead == (ssize_t)rcv_buf_size)
      Err("FrameworkManager max receive size, augmenter le buffer size!\n");

    if (bytesRead > 0) {
      // printf("recu %ld, trame %x\n",bytesRead,(uint8_t)rcv_buf[0]);
      // rcv_buf[bytesRead-1]=0;//pour affichage
      // printf("%s\n",rcv_buf);

      switch ((uint8_t)rcv_buf[0]) {
      case XML_HEADER: {
        xmlDoc *doc;
        rcv_buf[bytesRead] = 0;
 //Printf("%s\n",rcv_buf);
        doc = xmlReadMemory(rcv_buf, (int)bytesRead, "include.xml",
                            "ISO-8859-1", 0);
        xmlNode *cur_node = NULL;

        for (cur_node = xmlDocGetRootElement(doc); cur_node;
             cur_node = cur_node->next) {
          if (cur_node->type == XML_ELEMENT_NODE) {
            if (!xmlStrcmp(cur_node->name, (xmlChar *)XML_ROOT_TYPE)) {
#ifdef __XENO__
              WarnUponSwitches(
                  true); // ProcessXML should not switch to secondary mode
#endif
              top_layout->Widget::pimpl_->ProcessXML(cur_node->children);
#ifdef __XENO__
              WarnUponSwitches(false); // other parts of this thread can switch
                                       // to secondary mode
#endif
              break;
            }
          }
        }

        xmlFreeDoc(doc);

        if (save_button->Clicked())
          SaveXml();

        SaveXmlChange(rcv_buf);

        break;
      }
      case WATCHDOG_HEADER: {
        gcs_watchdog->Touch();
        break;
      }
      default:
        Err("unknown id: %x\n", (uint8_t)rcv_buf[0]);
        break;
      }
    } else {
      if (com->ConnectionLost())
        SleepMS(10); // avoid infinite loop in this case
    }
  }
}

void FrameworkManager_impl::SaveXml(void) {
  if (ui_defined)
    xmlSaveFormatFile(xml_file.c_str(), file_doc, 1);
}

void FrameworkManager_impl::SaveXmlChange(char *buf) {
  if (is_logging == true) {
    FILE *xml_change;
    char filename[256];
    Time time = GetTime();

    sprintf(filename, "%s/changes_at_%lld.xml", log_path.c_str(), time);

    xml_change = fopen(filename, "a");
    fprintf(xml_change, "%s", buf);
    fclose(xml_change);

    sprintf(filename, "changes_at_%lld.xml", time);
    xml_changes.push_back(filename);
  }
}

void FrameworkManager_impl::SendFile(string path, string name) {
  char *buf, *more_buf;
  int size;
  filebuf *pbuf;
  ssize_t nb_write;
  string filename = path + "/" + name;

  // open the file
  fstream ifs(filename.c_str(), ios::in | ios::binary);
  ifs.seekg(0, ios::end);
  size = ifs.tellg();
  ifs.seekg(0, ios::beg);
  pbuf = ifs.rdbuf();

  if (size <= 0) {
    Err("error opening file %s\n", filename.c_str());
    return;
  }

  buf = (char *)malloc(sizeof(uint8_t) + sizeof(int) + name.size());
  if (buf == NULL) {
    Err("malloc error, not sending file\n");
    return;
  }

  if (IsBigEndian()) {
    buf[0] = FILE_INFO_BIG_ENDIAN;
  } else {
    buf[0] = FILE_INFO_LITTLE_ENDIAN;
  }

  memcpy(buf + 1, &size, sizeof(int));
  memcpy(buf + 1 + sizeof(int), name.c_str(), name.size());
  Printf("sending %s, size: %i\n", filename.c_str(), size);
  // send file information
  UDT::sendmsg(file_sock, buf, sizeof(uint8_t) + sizeof(int) + name.size(), -1,
               true);

  more_buf = (char *)realloc((void *)buf, size);
  if (more_buf == NULL) {
    Err("realloc error, not sending file\n");
    free(buf);
    return;
  } else {
    buf = more_buf;
  }

  pbuf->sgetn(buf, size);
  // send the file
  nb_write = UDT::sendmsg(file_sock, buf, size, -1, true);

  if (nb_write < 0) {
    Err("UDT::sendmsg error (%s)\n", UDT::getlasterror().getErrorMessage());
  } else if (nb_write != size) {
    Err("UDT::sendmsg error, sent %ld/%i\n", nb_write, size);
  }

  ifs.close();
  free(buf);
}

void FrameworkManager_impl::FinishSending() {
  char rm_cmd[256];

  // send orignal xml
  SendFile(log_path, "setup.xml");
  sprintf(rm_cmd, "rm %s/setup.xml", log_path.c_str());
  system(rm_cmd);

  // send xml changes
  for (size_t i = 0; i < xml_changes.size(); i++) {
    // Printf("%s\n",xml_changes.at(i).c_str());
    SendFile(log_path, xml_changes.at(i).c_str());
    sprintf(rm_cmd, "rm %s/%s", log_path.c_str(), xml_changes.at(i).c_str());
    system(rm_cmd);
  }
  xml_changes.clear();

  // end notify
  char buf = END;
  int nb_write = UDT::sendmsg(file_sock, &buf, 1, -1, true);

  if (nb_write < 0) {
    Err("UDT::sendmsg error (%s)\n", UDT::getlasterror().getErrorMessage());
  } else if (nb_write != 1) {
    Err("UDT::sendmsg error, sent %i/%i\n", nb_write, 1);
  }

    //wait end ACK
    int nb_read = UDT::recvmsg(file_sock,&buf,1);
    if(nb_read<0) {
    Err("UDT::recvmsg error (%s)\n",UDT::getlasterror().getErrorMessage());
    } else if (nb_read != 1)  {
    Err("UDT::recvmsg error, sent %i/%i\n",nb_read,1);
    }
}

UDTSOCKET FrameworkManager_impl::GetSocket(string address, uint16_t port) {
  while (1) {
    UDTSOCKET new_fd;
    new_fd = UDT::socket(AF_INET, SOCK_DGRAM, 0);
    if (new_fd == UDT::INVALID_SOCK) {
      Err("socket error: %s\n", UDT::getlasterror().getErrorMessage());
      return 0;
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(short(port));

    if (inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) <= 0) {
      Err("incorrect network address\n");
      return 0;
    }

    memset(&(serv_addr.sin_zero), '\0', 8);

    if (UDT::ERROR ==
        UDT::connect(new_fd, (sockaddr *)&serv_addr, sizeof(serv_addr))) {
      // Printf("connect error: %s
      // %i\n",UDT::getlasterror().getErrorMessage(),UDT::getlasterror().getErrorCode());
      UDT::close(new_fd);
      if (UDT::getlasterror().getErrorCode() != 1001 &&
          UDT::getlasterror().getErrorCode() != 1002) {
        Err("connect error: %s\n", UDT::getlasterror().getErrorMessage());
        return 0;
      }
    } else {
      // printf("connected to
      // %s:%i\n",inet_ntoa(serv_addr.sin_addr),serv_addr.sin_port);
      return new_fd;
    }
  }
}

#ifdef __XENO__
int FrameworkManager_impl::CreatePipe(RT_PIPE *fd, string name) {
  name = self->ObjectName() + "-" + name;
  // xenomai limitation
  if (name.size() > 31)
    self->Err("rt_pipe_create error (%s is too long)\n", name.c_str());
// start log writter
#ifdef RT_PIPE_SIZE
  return rt_pipe_create(fd, name.c_str(), P_MINOR_AUTO, RT_PIPE_SIZE);
#else
  return rt_pipe_create(fd, name.c_str(), P_MINOR_AUTO, 0);
#endif
}
#else
int FrameworkManager_impl::CreatePipe(int (*fd)[2], string name) {
  // if(pipe2(fd[0],O_NONBLOCK) == -1)
  if (pipe(fd[0]) == -1) {
    return errno;
  } else {
    int attr = fcntl((*fd)[0], F_GETFL, 0);
    if (attr == -1) {
      return errno;
    }
    if (fcntl((*fd)[0], F_SETFL, attr | O_NONBLOCK) == -1) {
      return errno;
    }
    attr = fcntl((*fd)[1], F_GETFL, 0);
    if (attr == -1) {
      return errno;
    }
    if (fcntl((*fd)[1], F_SETFL, attr | O_NONBLOCK) == -1) {
      return errno;
    }

    return 0;
  }
}
#endif

#ifdef __XENO__
int FrameworkManager_impl::DeletePipe(RT_PIPE *fd) {
  return rt_pipe_delete(fd);
}
#else
int FrameworkManager_impl::DeletePipe(int (*fd)[2]) {
  int status1 = close((*fd)[0]);
  int status2 = close((*fd)[1]);
  if (status1 == 0 && status2 == 0)
    return 0;
  if (status1 != 0)
    return status1;
  if (status2 != 0)
    return status2;
}
#endif

void FrameworkManager_impl::SetupLogger(string log_path) {
  if (logger_defined == true) {
    Warn("SetupLogger() was already called.\n");
    return;
  }

  this->log_path = log_path;

  int status = CreatePipe(&cmd_pipe, "log_cmd");
  if (status != 0) {
    Err("Error creating pipe (%s)\n", strerror(-status));
    return;
  }

  status = CreatePipe(&data_pipe, "log_data");
  if (status != 0) {
    Err("Error creating pipe (%s)\n", strerror(-status));
    return;
  }

#ifdef __XENO__
  string tmp_name;
  tmp_name = self->ObjectName() + "-log_heap";
  status = rt_heap_create(&log_heap, tmp_name.c_str(), LOG_HEAP, H_FIFO);
  if (status != 0) {
    Err("rt_heap_create error (%s)\n", strerror(-status));
    return;
  }
#endif //__XENO__

  continuer = true;

#ifdef NRT_STACK_SIZE
  // Initialize thread creation attributes
  pthread_attr_t attr;
  if (pthread_attr_init(&attr) != 0) {
    Err("pthread_attr_init error\n");
    return;
  }

  if (pthread_attr_setstacksize(&attr, NRT_STACK_SIZE) != 0) {
    Err("pthread_attr_setstacksize error\n");
    return;
  }

  if (pthread_create(&log_th, &attr, write_log_user, (void *)this) < 0)
#else
  if (pthread_create(&log_th, NULL, write_log_user, (void *)this) < 0)
#endif
  {
    Err("pthread_create error\n");
    return;
  }
#ifdef NRT_STACK_SIZE
  if (pthread_attr_destroy(&attr) != 0) {
    Err("pthread_attr_destroy error\n");
    return;
  }
#endif

  logger_defined = true;
}

void FrameworkManager_impl::AddDeviceToLog(IODevice *device) {
  if (logger_defined == false) {
    Warn("SetupLogger() was not called, not adding to log\n");
    return;
  }

  if (is_logging == false) {
    if (device->pimpl_->SetToBeLogged()) {
      log_desc_t tmp;
      tmp.device = device;
      logs.push_back(tmp);
    } else {
      Warn("not adding it twice\n");
    }
  } else {
    Err("impossible while logging\n");
  }
}

void FrameworkManager_impl::StartLog(void) {
  if (logger_defined == false) {
    Err("SetupLogger() was not called, not starting log\n");
    return;
  }

  ssize_t written;
  size_t nb_err = 0;

  if (logs.size() == 0) {
    Warn("Not starting log: nothing to log!\n");
    return;
  }

  if (is_logging == false) {
    for (size_t i = 0; i < logs.size(); i++) {

      logs.at(i).running = true;
      logs.at(i).dbtFile = NULL;
      logs.at(i).size = logs.at(i).device->pimpl_->LogSize();
#ifdef __XENO__
      written =
          rt_pipe_write(&cmd_pipe, &logs.at(i), sizeof(log_desc_t), P_NORMAL);
#else
      written = write(cmd_pipe[1], &logs.at(i), sizeof(log_desc_t));
#endif

      if (written < 0) {
        Err("write pipe error (%s)\n", strerror(-written));
        nb_err++;
        logs.at(i).running = false;
      } else if (written != sizeof(log_desc_t)) {
        Err("write pipe error %ld/%ld\n", written, sizeof(log_desc_t));
        nb_err++;
        logs.at(i).running = false;
      }
    }

    if (nb_err != logs.size())
      is_logging = true;
  } else {
    Warn("Already logging\n");
  }
}

void FrameworkManager_impl::StopLog(void) {
  ssize_t written;

  if (is_logging == true) {
    for (size_t i = 0; i < logs.size(); i++) {
      logs.at(i).running = false;
    }
// send only one running false condition, user thread will stop and send all
#ifdef __XENO__
    written =
        rt_pipe_write(&cmd_pipe, &logs.at(0), sizeof(log_desc_t), P_NORMAL);
#else
    written = write(cmd_pipe[1], &logs.at(0), sizeof(log_desc_t));
#endif

    if (written < 0) {
      Err("write pipe error (%s)\n", strerror(-written));
      return;
    } else if (written != sizeof(log_desc_t)) {
      Err("write pipe error %ld/%ld\n", written, sizeof(log_desc_t));
      return;
    }

    is_logging = false;
  } else {
    Warn("Not logging\n");
  }
}

char *FrameworkManager_impl::GetBuffer(size_t sz) {
// Printf("alloc %i\n",sz);
#ifdef __XENO__
  void *ptr;
  int status = rt_heap_alloc(&log_heap, sz, TM_NONBLOCK, &ptr);
  if (status != 0) {
    Err("rt_heap_alloc error (%s)\n", strerror(-status));
    ptr = NULL;
  }
  return (char *)ptr;
#else
  return (char *)malloc(sz);
#endif
}

void FrameworkManager_impl::ReleaseBuffer(char *buf) {
#ifdef __XENO__
  int status = rt_heap_free(&log_heap, buf);

  if (status != 0) {
    Err("rt_heap_free error (%s)\n", strerror(-status));
  }
#else
  free(buf);
#endif
}

void FrameworkManager_impl::WriteLog(const char *buf, size_t size) {
  ssize_t written;

#ifdef __XENO__
  written = rt_pipe_write(&data_pipe, buf, size, P_NORMAL);
#else
  written = write(data_pipe[1], buf, size);
#endif

  if (written < 0) {
    Err("erreur write pipe (%s)\n", strerror(-written));
  } else if (written != (ssize_t)size) {
    Err("erreur write pipe %ld/%ld\n", written, size);
  }
}

void *FrameworkManager_impl::write_log_user(void *arg) {
  int cmd_pipe = -1;
  int data_pipe = -1;
  string filename;
  fd_set set;
  struct timeval timeout;
  FrameworkManager_impl *caller = (FrameworkManager_impl *)arg;
  int rv;

  vector<log_desc_t> logs;

#ifdef __XENO__
  filename = NRT_PIPE_PATH + caller->self->ObjectName() + "-log_cmd";
  while (cmd_pipe < 0) {
    cmd_pipe = open(filename.c_str(), O_RDWR);
    if (cmd_pipe < 0 && errno != ENOENT)
      caller->self->Err("open rt_pipe error: %s %i\n", filename.c_str(), errno);
    usleep(1000);
  }
  filename = NRT_PIPE_PATH + caller->self->ObjectName() + "-log_data";
  while (data_pipe < 0) {
    data_pipe = open(filename.c_str(), O_RDWR);
    if (data_pipe < 0 && errno != ENOENT)
      caller->self->Err("open rt_pipe error: %s %i\n", filename.c_str(), errno);
    usleep(1000);
  }
#else
  cmd_pipe = caller->cmd_pipe[0];
  data_pipe = caller->data_pipe[0];
#endif

  while (caller->continuer == true) {
    FD_ZERO(&set);
    FD_SET(cmd_pipe, &set);
    FD_SET(data_pipe, &set);

    timeout.tv_sec = 0;
    timeout.tv_usec = SELECT_TIMEOUT_MS * 1000;
    rv = select(FD_SETSIZE, &set, NULL, NULL, &timeout);

    if (rv == -1) {
      caller->Err("select error\n"); // an error accured
    } else if (rv == 0) {
      // printf("timeout write_log_user %s\n",caller->ObjectName().c_str()); //
      // a timeout occured
    } else {
      if (FD_ISSET(cmd_pipe, &set)) {
        log_desc_t tmp;
        read(cmd_pipe, &tmp, sizeof(log_desc_t));

        if (tmp.running == true) // start logging
        {
          filename = caller->log_path + "/" + caller->FileName(tmp.device) + ".dbt";
          printf("Creating log file %s (log size %i)\n", filename.c_str(), (int)tmp.size);
          tmp.dbtFile = inithdFile((char *)filename.c_str(), UAV, tmp.size);
          logs.push_back(tmp);

          if (logs.size() == 1) {
            filename = caller->log_path + "/setup.xml";
            xmlSaveFile(filename.c_str(), caller->file_doc);
          }
        } else // stop logging
        {
            //disable watchdog temporarly
            //this is necessary because GCS is no longer sending the heartbeat when receiving files...
            //TODO: add a thread in GCS for receiving file
            //but be careful that with a xbee modem for exemple, sending files can saturate communication and
            //avoid the heartbeat to be received... so disabling watchdog is not a so bad option...
            if(caller->gcs_watchdog!=NULL) {
                caller->gcs_watchdog->SafeStop();
                caller->gcs_watchdog->Join();
            }
          for (size_t i = 0; i < logs.size(); i++) {
            if (logs.at(i).dbtFile != NULL) {
              close_hdfile(logs.at(i).dbtFile);

              filename = caller->FileName(logs.at(i).device) + ".dbt";
              caller->SendFile(caller->log_path, filename);

              fstream txt_file;
              filename = caller->FileName(logs.at(i).device) + ".txt";
              txt_file.open((caller->log_path + "/" + filename).c_str(),
                            fstream::out);
              txt_file << "1: time (us)\n2: time (ns)\n";
              int index = 3;
              logs.at(i).device->pimpl_->WriteLogsDescriptors(txt_file, &index);
              txt_file.close();

              caller->SendFile(caller->log_path, filename);
            }
          }
          // a revoir celui ci est le xml enregistré et pas forcement l'actuel
          // if(caller->xml_file!="") caller->SendFile(caller->xml_file);
          caller->FinishSending();

          logs.clear();
            //enable watchdog again
            if(caller->gcs_watchdog!=NULL) {
                caller->gcs_watchdog->Start();
            }
        }
      }

      if (FD_ISSET(data_pipe, &set)) {
        log_header_t header;
        read(data_pipe, &header, sizeof(log_header_t));

        for (size_t i = 0; i < logs.size(); i++) {
          if (logs.at(i).device == header.device) {
            char *buf = (char *)malloc(header.size);
            read(data_pipe, buf, header.size);
            // printf("%s \n",header.device->ObjectName().c_str());
            // for(int i=0;i<header.size;i++) printf("%x ",buf[i]);
            // printf("\n");
            if (logs.at(i).size == header.size) {
              if (logs.at(i).dbtFile != NULL) {
                write_hdfile(
                    logs.at(i).dbtFile, buf, (road_time_t)(header.time / 1000),
                    (road_timerange_t)(header.time % 1000), header.size);
              } else {
                printf("err\n");
              }
            } else {
              caller->self->Err("%s log size is not correct %i/%i\n",
                                header.device->ObjectName().c_str(),
                                header.size, logs.at(i).size);
            }
            free(buf);
          }
        }
      }
    }
  }

#ifdef __XENO__
  close(cmd_pipe);
  close(data_pipe);
#endif

  pthread_exit(0);
}

string FrameworkManager_impl::FileName(IODevice *device) {
  return getFrameworkManager()->ObjectName() + "_" + device->ObjectName();
}

void FrameworkManager_impl::PrintXml(void) const {
  xmlChar *xmlbuff;
  int buffersize;
  xmlDocDumpFormatMemory(file_doc, &xmlbuff, &buffersize, 1);
  Printf("xml:\n%s\n", xmlbuff);
  xmlFree(xmlbuff);
}
