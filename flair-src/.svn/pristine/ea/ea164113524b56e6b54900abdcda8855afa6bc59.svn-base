// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file IODevice_impl.h
 * \brief Classe de base pour un système à entrées/sorties
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef IO_DEVICE_IMPL_H
#define IO_DEVICE_IMPL_H

#include <string>
#include <Object.h>

namespace flair {
namespace core {
class io_data;
class IODevice;
class Thread;
class Mutex;
class FrameworkManager;
class SharedMem;
}
}

class FrameworkManager_impl;

class IODevice_impl {
public:
  IODevice_impl(const flair::core::IODevice *self);
  ~IODevice_impl();
  void ResumeThread(void);
  size_t LogSize(void) const;
  void AppendLog(char **ptr);
  void AddDataToLog(const flair::core::io_data *data);
  void WriteLogsDescriptors(std::fstream &desc_file, int *index);
  int SetToWake(const flair::core::Thread *thread);
  void WriteLog(flair::core::Time time);
  void AddDeviceToLog(const flair::core::IODevice *device);
  bool SetToBeLogged(void); // return true if possible
  void OutputToShMem(bool enabled);
  void WriteToShMem(void);
  void PrintLogsDescriptors(void);

private:
  std::vector<const flair::core::IODevice *> devicesToLog;
  const flair::core::IODevice *self;
  const flair::core::FrameworkManager *framework;
  FrameworkManager_impl *framework_impl;
  std::vector<const flair::core::io_data *> datasToLog;
  flair::core::Thread *thread_to_wake;
  flair::core::Mutex *wake_mutex;
  bool tobelogged;
  bool outputtoshm;
  flair::core::SharedMem *shmem;
};

#endif // IO_DEVICE_IMPL_H
