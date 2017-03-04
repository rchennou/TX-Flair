// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SharedMem.h
 * \brief Class defining a shared memory
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/02/10
 * \version 4.0
 */

#ifndef SHAREDMEM_H
#define SHAREDMEM_H

#include <Object.h>
#include <semaphore.h>

class SharedMem_impl;

namespace flair {
namespace core {

/*! \class SharedMem
*
* \brief Class defining a shared memory
*
* Shared memory is identified by its name so it can be accessed
* by another processus using its name.
*/

class SharedMem : public Object {
public:
  /*!
  * \brief Constructor
  *
  * Construct a shared memory object
  *
  * \param parent parent
  * \param name name
  * \param size size of the shared memory
  */
  SharedMem(const Object *parent, std::string name, size_t size);

  /*!
  * \brief Destructor
  *
  */
  ~SharedMem();

  /*!
  * \brief Write
  *
  * \param buf input buffer to write to memory
  * \param size buffer size
  */
  void Write(const char *buf, size_t size);

  /*!
  * \brief Read
  *
  * \param buf output buffer to write from memory
  * \param size buffer size
  */
  void Read(char *buf, size_t size) const;

private:
  SharedMem_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // SHAREDMEM_H
