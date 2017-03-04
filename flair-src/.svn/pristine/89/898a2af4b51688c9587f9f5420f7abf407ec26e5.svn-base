// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file FrameworkManager.h
 * \brief Classe de base de la librairie
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/08/31
 * \version 4.0
 */

#ifndef FRAMEWORKMANAGER_IMPL_H
#define FRAMEWORKMANAGER_IMPL_H

#include "Thread.h"
#include "ui_com.h"
#include <io_hdfile.h>
#include <libxml/xpath.h>

#ifdef __XENO__
#include <native/pipe.h>
#include <native/heap.h>
#endif

namespace flair {
namespace core {
class FrameworkManager;
class IODevice;
class Watchdog;
}
namespace gui {
class TabWidget;
class PushButton;
class Layout;
}
}

class ui_com;

class FrameworkManager_impl : public flair::core::Thread {
public:
  FrameworkManager_impl(flair::core::FrameworkManager *self, std::string name);
  ~FrameworkManager_impl();
  void SetupConnection(std::string address, uint16_t port,flair::core::Time watchdogTimeout,
                       size_t rcv_buf_size = 10000);
  void SetupUserInterface(std::string xml_file);
  void SetupLogger(std::string log_path);
  void AddDeviceToLog(flair::core::IODevice *device);
  void StartLog();
  void StopLog();
  char *GetBuffer(size_t sz);
  void ReleaseBuffer(char *buf);
  void WriteLog(const char *buf, size_t size);

  /*!
  * \brief Affiche le xml
  *
  * Pour debug.
  */
  void PrintXml(void) const;

  bool is_logging;
  bool disable_errors;
  bool connection_lost;
  static ui_com *com;
  static FrameworkManager_impl *_this;
  std::string log_path;

  flair::gui::TabWidget *tabwidget;
  flair::gui::PushButton *save_button; //,*load_button;

  xmlDocPtr file_doc;

  typedef struct {
    const flair::core::IODevice *device;
    size_t size;
    flair::core::Time time;
  } log_header_t;

private:
  flair::core::FrameworkManager *self;
  UDTSOCKET file_sock, com_sock;
  UDTSOCKET GetSocket(std::string address, uint16_t port);
  void Run();
  void SendFile(std::string path, std::string name);
  void FinishSending(void);
  std::string FileName(flair::core::IODevice *device);
  void SaveXmlChange(char *buf);
  void SaveXml(void);
  size_t rcv_buf_size;
  char *rcv_buf;
#ifdef __XENO__
  int CreatePipe(RT_PIPE *fd, std::string name);
  int DeletePipe(RT_PIPE *fd);
  RT_PIPE cmd_pipe;
  RT_PIPE data_pipe;
  RT_HEAP log_heap;
#else
  int CreatePipe(int (*fd)[2], std::string name);
  int DeletePipe(int (*fd)[2]);
  int cmd_pipe[2];
  int data_pipe[2];
#endif
  // logger
  bool continuer; // a enlever, avoir un seul bool pour toutes les taches
  static void *write_log_user(void *arg);
  pthread_t log_th;
  std::string xml_file;
  bool logger_defined;
  bool ui_defined;
  flair::gui::Layout *top_layout;

  typedef struct {
    flair::core::IODevice *device;
    size_t size;
    hdfile_t *dbtFile;
    bool running;
  } log_desc_t;

  std::vector<log_desc_t> logs;
  std::vector<std::string> xml_changes;
  flair::core::Watchdog *gcs_watchdog;
  void ConnectionLost(void);
};

namespace {
inline ui_com *getUiCom(void) { return FrameworkManager_impl::com; }

inline FrameworkManager_impl *getFrameworkManagerImpl(void) {
  return FrameworkManager_impl::_this;
}
}

#endif // FRAMEWORKMANAGER_IMPL_H
