// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/02/10
//  filename:   SharedMem_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining a shared memory
//
//
/*********************************************************************/

#include "SharedMem_impl.h"
#include "SharedMem.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

using std::string;
using namespace flair::core;

SharedMem_impl::SharedMem_impl(const SharedMem *self, string name,
                               size_t size) {
  this->size = size;
  this->self = self;

#ifdef __XENO__
  heap_binded = false;
  int status = rt_heap_create(&heap, name.c_str(), size,
                              H_SHARED | H_FIFO | H_NONCACHED);
  if (status == -EEXIST) {
    heap_binded = true;
    status = rt_heap_bind(&heap, name.c_str(), TM_INFINITE);
  }
  if (status != 0) {
    self->Err("rt_heap_create error (%s)\n", strerror(-status));
    return;
  }

  void *ptr;
  status = rt_heap_alloc(&heap, 0, TM_NONBLOCK, &ptr);
  if (status != 0) {
    self->Err("rt_heap_alloc error (%s)\n", strerror(-status));
  }
  mem_segment = (char *)ptr;

  mutex_binded = false;
  string mutex_name = "mutex_" + name;
  status = rt_mutex_create(&mutex, mutex_name.c_str());
  if (status == -EEXIST) {
    mutex_binded = true;
    status = rt_mutex_bind(&mutex, mutex_name.c_str(), TM_INFINITE);
  }
  if (status != 0) {
    self->Err("rt_mutex_create error (%s)\n", strerror(-status));
    return;
  }

#else
  shm_name = "/" + name;
  fd = shm_open(shm_name.c_str(), O_RDWR | O_CREAT, 0666);
  if (fd == -1) {
    self->Err("Error creating shared memory\n");
  }
  ftruncate(fd, size);

  sem_name = "/" + name;
  sem = sem_open(sem_name.c_str(), O_CREAT, 0666, 1);
  if (sem == SEM_FAILED) {
    self->Err("Error creating semaphore\n");
  }

  mem_segment =
      (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (mem_segment == MAP_FAILED) {
    self->Err("Failed to map memory\n");
  }
#endif
}

SharedMem_impl::~SharedMem_impl() {
  int status;
#ifdef __XENO__
  /* unnecessary because heap is opened in H_SINGLE mode
  status=rt_heap_free(&heap,mem_segment);
  if(status!=0)
  {
      self->Err("rt_heap_free error (%s)\n",strerror(-status));
  }
  */

  if (heap_binded == false) {
    status = rt_heap_delete(&heap);
    if (status != 0) {
      self->Err("rt_heap_delete error (%s)\n", strerror(-status));
    }
  }

  if (mutex_binded == false) {
    status = rt_mutex_delete(&mutex);
    if (status != 0) {
      self->Err("error destroying mutex (%s)\n", strerror(-status));
    }
  }
#else
  status = munmap(mem_segment, size);
  if (status != 0) {
    self->Err("Failed to unmap memory (%s)\n", strerror(-status));
  }

  status = close(fd);
  if (status != 0) {
    self->Err("Failed to close file (%s)\n", strerror(-status));
  }

  // do not check erros as it can be done by another process
  status = shm_unlink(shm_name.c_str()); /*
   if(status!=0)
   {
       self->Err("Failed to unlink memory (%s)\n",strerror(-status));
   }
*/
  // do not check erros as it can be done by another process
  status = sem_unlink(sem_name.c_str()); /*
   if(status!=0)
   {
       self->Err("Failed to unlink semaphore (%s)\n",strerror(-status));
   }*/

  status = sem_close(sem);
  if (status != 0) {
    self->Err("Failed to close semaphore (%s)\n", strerror(-status));
  }
#endif
}

void SharedMem_impl::Write(const char *buf, size_t size) {
#ifdef __XENO__
  int status = rt_mutex_acquire(&mutex, TM_INFINITE);
  if (status != 0)
    self->Err("error (%s)\n", strerror(-status));
  memcpy(mem_segment, buf, size);
  status = rt_mutex_release(&mutex);
  if (status != 0)
    self->Err("error (%s)\n", strerror(-status));
#else
  sem_wait(sem);
  memcpy(mem_segment, buf, size);
  sem_post(sem);
#endif
}

void SharedMem_impl::Read(char *buf, size_t size) {
#ifdef __XENO__
  int status = rt_mutex_acquire(&mutex, TM_INFINITE);
  if (status != 0)
    self->Err("error (%s)\n", strerror(-status));
  memcpy(buf, mem_segment, size);
  status = rt_mutex_release(&mutex);
  if (status != 0)
    self->Err("error (%s)\n", strerror(-status));
#else
  sem_wait(sem);
  memcpy(buf, mem_segment, size);
  sem_post(sem);
#endif
}
