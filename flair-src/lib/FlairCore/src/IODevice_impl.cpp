// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   IODevice.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe de base avec entrees sorties
//
//
/*********************************************************************/

#include "IODevice_impl.h"
#include "IODevice.h"
#include "io_data.h"
#include "io_data_impl.h"
#include "Thread.h"
#include "Mutex.h"
#include "FrameworkManager.h"
#include "FrameworkManager_impl.h"
#include "SharedMem.h"
#include <string.h>

using std::string;
using std::fstream;
using namespace flair::core;

IODevice_impl::IODevice_impl(const IODevice *self) {
  this->self = self;
  thread_to_wake = NULL;
  wake_mutex = new Mutex(self);
  framework_impl = ::getFrameworkManagerImpl();
  framework = getFrameworkManager();
  tobelogged = false;
  outputtoshm = false;
}

IODevice_impl::~IODevice_impl() {}

void IODevice_impl::OutputToShMem(bool enabled) {
  if (framework->IsLogging()) {
    self->Err("impossible while logging\n");
  } else {
    if (LogSize() == 0) {
      self->Warn("log size is null, not enabling output to shared memory.");
      return;
    }

    if (enabled) {
      string dev_name =
          getFrameworkManager()->ObjectName() + "-" + self->ObjectName();
      shmem = new SharedMem(self, dev_name.c_str(), LogSize());
      outputtoshm = true;

      Printf("Created %s shared memory for object %s; size: %i\n",
             dev_name.c_str(), self->ObjectName().c_str(), LogSize());
      PrintLogsDescriptors();
    } else {
      outputtoshm = false;
      delete shmem;
    }
  }
}

void IODevice_impl::PrintLogsDescriptors(void) {
  // own logs
  for (size_t i = 0; i < datasToLog.size(); i++)
    datasToLog.at(i)->pimpl_->PrintLogDescriptor();
  // childs logs
  for (size_t i = 0; i < self->TypeChilds()->size(); i++)
    ((IODevice *)self->TypeChilds()->at(i))->pimpl_->PrintLogsDescriptors();
  // manually added logs
  for (size_t i = 0; i < devicesToLog.size(); i++)
    devicesToLog.at(i)->pimpl_->PrintLogsDescriptors();
}

void IODevice_impl::WriteToShMem(void) {
  if (outputtoshm) {
    size_t size = LogSize();

    char *buf = framework_impl->GetBuffer(size);
    char *buf_orig = buf;
    if (buf == NULL) {
      self->Err("err GetBuffer\n");
      return;
    }

    AppendLog(&buf);

    shmem->Write(buf_orig, size);
    framework_impl->ReleaseBuffer(buf_orig);
  }
}

void IODevice_impl::AddDeviceToLog(const IODevice *device) {
  if (framework->IsLogging()) {
    self->Err("impossible while logging\n");
  } else {
    devicesToLog.push_back(device);
  }
}

bool IODevice_impl::SetToBeLogged(void) {
  if (!tobelogged) {
    tobelogged = true;
    return true;
  } else {
    self->Warn("already added to log\n");
    return false;
  }
}

void IODevice_impl::WriteLogsDescriptors(fstream &desc_file, int *index) {
  // own descriptor
  for (size_t i = 0; i < datasToLog.size(); i++)
    datasToLog.at(i)->pimpl_->WriteLogDescriptor(desc_file, index);
  // childs descriptors
  for (size_t i = 0; i < self->TypeChilds()->size(); i++)
    ((IODevice *)self->TypeChilds()->at(i))
        ->pimpl_->WriteLogsDescriptors(desc_file, index);
  // manually added logs
  for (size_t i = 0; i < devicesToLog.size(); i++)
    devicesToLog.at(i)->pimpl_->WriteLogsDescriptors(desc_file, index);
}

void IODevice_impl::ResumeThread(void) {
  wake_mutex->GetMutex();
  if (thread_to_wake != NULL) {
    thread_to_wake->Resume();
    thread_to_wake = NULL;
  }
  wake_mutex->ReleaseMutex();
}

void IODevice_impl::AddDataToLog(const io_data *data) {
  if (framework->IsLogging()) {
    self->Err("impossible while logging\n");
  } else {
    datasToLog.push_back(data);
  }
}

size_t IODevice_impl::LogSize() const {
  size_t value = 0;

  for (size_t i = 0; i < datasToLog.size(); i++) {
    value += datasToLog.at(i)->GetDataType().GetSize();
  }

  // childs logs
  for (size_t i = 0; i < self->TypeChilds()->size(); i++) {
    value += ((IODevice *)self->TypeChilds()->at(i))->pimpl_->LogSize();
  }
  // manually added logs
  for (size_t i = 0; i < devicesToLog.size(); i++) {
    value += devicesToLog.at(i)->pimpl_->LogSize();
  }

  return value;
}

void IODevice_impl::WriteLog(Time time) {
  if (tobelogged == false)
    return;

  size_t size = LogSize();

  char *buf = framework_impl->GetBuffer(
      sizeof(FrameworkManager_impl::log_header_t) + size);
  char *buf_orig = buf;
  if (buf == NULL) {
    self->Err("err GetBuffer\n");
    return;
  }

  FrameworkManager_impl::log_header_t header;
  header.device = self;
  header.size = size;
  header.time = time;

  memcpy(buf, &header, sizeof(FrameworkManager_impl::log_header_t));
  buf += sizeof(FrameworkManager_impl::log_header_t);
  AppendLog(&buf);

  framework_impl->WriteLog(buf_orig,
                           sizeof(FrameworkManager_impl::log_header_t) + size);
  framework_impl->ReleaseBuffer(buf_orig);
}

void IODevice_impl::AppendLog(char **ptr) {
  // Printf("AppendLog %s %x\n",self->ObjectName().c_str(),*ptr);

  // copy state to buf
  for (size_t i = 0; i < datasToLog.size(); i++) {
    // printf("copy\n");
    datasToLog.at(i)->CopyDatas(*ptr);
    (*ptr) += datasToLog.at(i)->GetDataType().GetSize();
  }

  // copy linked states to buf
  for (size_t i = 0; i < self->TypeChilds()->size(); i++) {
    ((IODevice *)self->TypeChilds()->at(i))->pimpl_->AppendLog(ptr);
  }
  // copy manually added logs to buf
  for (size_t i = 0; i < devicesToLog.size(); i++) {
    devicesToLog.at(i)->pimpl_->AppendLog(ptr);
    // devices.at(i)->DataToLog()->CopyDatas(*ptr);
    //(*ptr)+=devices.at(i)->DataToLog()->Size();
  }
  // Printf("AppendLog %s ok\n",self->ObjectName().c_str());
}

int IODevice_impl::SetToWake(const Thread *thread) {
  int status = 0;

  wake_mutex->GetMutex();
  if (thread_to_wake == NULL) {
    thread_to_wake = (Thread *)thread;
  } else {
    status = -1;
  }
  wake_mutex->ReleaseMutex();

  return status;
}
