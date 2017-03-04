// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SharedMem_impl.h
 * \brief Class defining a shared memory
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/10
 * \version 4.0
 */

#ifndef SHAREDMEM_IMPL_H
#define SHAREDMEM_IMPL_H

#include <string>

#ifdef __XENO__
#include <native/heap.h>
#include <native/mutex.h>
#else
#include <semaphore.h>
#endif

namespace flair {
namespace core {
class SharedMem;
}
}

/*! \class SharedMem_impl
* \brief Class defining a shared memory
*
*/

class SharedMem_impl {
public:
  SharedMem_impl(const flair::core::SharedMem *self, std::string name,
                 size_t size);
  ~SharedMem_impl();

  void Write(const char *buf, size_t size);
  void Read(char *buf, size_t size);

private:
  const flair::core::SharedMem *self;
  size_t size;
  char *mem_segment;
#ifdef __XENO__
  RT_HEAP heap;
  RT_MUTEX mutex;
  bool heap_binded;
  bool mutex_binded;
#else
  int fd;
  sem_t *sem;
  std::string sem_name, shm_name;
#endif
};

#endif // SHAREDMEM_IMPL_H
