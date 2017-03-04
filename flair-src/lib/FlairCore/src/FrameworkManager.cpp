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
//  purpose:    Main class of the Framework library
//
//
/*********************************************************************/

#include "FrameworkManager.h"
#include "FrameworkManager_impl.h"
#include "IODevice.h"
#include "config.h"
#include "compile_info.h"

using std::string;
using std::vector;
using namespace flair::gui;

namespace {
  flair::core::FrameworkManager *frameworkmanager = NULL;
}

static void constructor() __attribute__((constructor));

void constructor() {
  compile_info("FlairCore");
}


namespace flair {
namespace core {

FrameworkManager *getFrameworkManager(void) { return frameworkmanager; }

bool IsBigEndian(void) {
  union {
    uint32_t i;
    char c[4];
  } bint = {0x01020304};

  if (bint.c[0] == 1) {
    return true;
  } else {
    return false;
  }
}

FrameworkManager::FrameworkManager(string name)
    : Object(NULL, name, XML_ROOT_TYPE) {
  if (frameworkmanager != NULL) {
    Err("FrameworkManager should be instanced only one time\n");
    return;
  }

  frameworkmanager = this;
  pimpl_ = new FrameworkManager_impl(this, name);
}

FrameworkManager::~FrameworkManager() {
  // Printf("destruction FrameworkManager\n");

  // stop ui_com thread (which sends datas for graphs), we do not need it as
  // graphs will be destroyed
  if (getUiCom() != NULL) {
    getUiCom()->SafeStop();
    getUiCom()->Join();
  }

  // we start by deleting threads (except pimpl which must be deleted at last)
  // (before deleting objects that could be used by the threads)
  // Printf("delete Threads\n");
  for (vector<const Object *>::iterator it = Childs()->begin();
       it < Childs()->end(); it++) {
    // Printf("child %i %s
    // %s\n",Childs()->size(),(*it)->ObjectName().c_str(),(*it)->ObjectType().c_str());
    if ((*it)->ObjectType() == "Thread") {
      if (*it != pimpl_) {
        // Printf("del\n");
        delete (Thread *)(*it);
        // Childs() vector has been modified, we start from beginning again
        // it will be incremented by the loop, so in fact we start again at
        // begin()+1
        // it is not a problem since begin is pimpl
        it = Childs()->begin();
        // Printf("del ok\n");
      }
    }
  }

  // next we delete IODevice
  // (before deleting objects that could be used by the IODevice)
  // Printf("delete IODevices\n");
  for (vector<const Object *>::iterator it = Childs()->begin();
       it < Childs()->end(); it++) {
    // Printf("child %i %s
    // %s\n",Childs()->size(),(*it)->ObjectName().c_str(),(*it)->ObjectType().c_str());
    if ((*it)->ObjectType() == "IODevice") {
      // Printf("del\n");
      delete (IODevice *)*it;
      // Printf("del ok\n");
      // Childs() vector has been modified, we start from beginning again
      // it will be incremented by the loop, so in fact we start again at
      // begin()+1
      // it is not a problem since begin is pimpl (not an IODevice)
      it = Childs()->begin();
      // Printf("del ok\n");
    }
  }

  // Printf("delete childs\n");
  // on efface les enfants en commencant par la fin
  // le ui_com puis FrameworkManager_impl est détruit en dernier
  // permet de garder l'uicom pour notifer des destructions
  while (Childs()->size() != 0) {
    // Printf("child %i %s
    // %s\n",Childs()->size(),Childs()->back()->ObjectName().c_str(),Childs()->back()->ObjectType().c_str());
    if (Childs()->back() != NULL)
      delete Childs()->back();
  }

  // childs.clear();

  // Printf("destruction FrameworkManager ok\n");
}

void FrameworkManager::SetupConnection(string address, uint16_t port,Time watchdogTimeout,
                                       size_t rcv_buf_size) {
  pimpl_->SetupConnection(address, port, rcv_buf_size);
}

void FrameworkManager::SetupUserInterface(string xml_file) {
  pimpl_->SetupUserInterface(xml_file);
}

gui::TabWidget *FrameworkManager::GetTabWidget(void) const {
  if(pimpl_->tabwidget==NULL) Err("SetupUserInterface must be called before\n");
  return pimpl_->tabwidget;
}

void FrameworkManager::UpdateSendData(const SendData *obj) {
  if (getUiCom() != NULL)
    getUiCom()->UpdateSendData(obj);
}

void FrameworkManager::BlockCom(void) {
  if (getUiCom() != NULL)
    getUiCom()->Block();
}

void FrameworkManager::UnBlockCom(void) {
  if (getUiCom() != NULL)
    getUiCom()->UnBlock();
}

bool FrameworkManager::ConnectionLost(void) const {
  if (getUiCom() != NULL) {
    return (getUiCom()->ConnectionLost() | pimpl_->connection_lost);
  } else {
    return false;
  }
}

void FrameworkManager::SetupLogger(string log_path) {
  pimpl_->SetupLogger(log_path);
}

void FrameworkManager::AddDeviceToLog(IODevice *device) {
  pimpl_->AddDeviceToLog(device);
}

void FrameworkManager::StartLog(void) { pimpl_->StartLog(); }

void FrameworkManager::StopLog(void) { pimpl_->StopLog(); }

bool FrameworkManager::IsLogging(void) const { return pimpl_->is_logging; }

void FrameworkManager::DisableErrorsDisplay(bool value) {
  pimpl_->disable_errors = value;
}

bool FrameworkManager::IsDisplayingErrors(void) const {
  return !(pimpl_->disable_errors);
}

} // end namespace core
} // end namespace flair
