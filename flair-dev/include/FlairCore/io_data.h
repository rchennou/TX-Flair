// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file io_data.h
 * \brief Abstract class for data types.
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/21
 * \version 4.0
 */

#ifndef IO_DATA_H
#define IO_DATA_H

#include <Mutex.h>

class IODevice_impl;
class io_data_impl;

namespace flair {
namespace core {

class Object;

class DataType {
public:
  virtual std::string GetDescription() const = 0;
  // size in bytes
  virtual size_t GetSize() const = 0;
};

class DummyType : public DataType {
public:
  size_t GetSize() const { return 0; }
  std::string GetDescription() const { return "dummy"; };
};
extern DummyType dummyType;

class ScalarType : public DataType {
public:
  ScalarType(size_t _size) : size(_size) {}
  size_t GetSize() const { return size; }
  virtual std::string GetDescription() const { return "scalar"; };

private:
  size_t size;
};

class SignedIntegerType : public ScalarType {
public:
  SignedIntegerType(size_t sizeInBits) : ScalarType(sizeInBits / 8) {}
  std::string GetDescription() const {
    return "int" + std::to_string(GetSize() * 8) + "_t";
  };
};
extern SignedIntegerType Int8Type;
extern SignedIntegerType Int16Type;

class UnsignedIntegerType : public ScalarType {
public:
  UnsignedIntegerType(size_t sizeInBits) : ScalarType(sizeInBits / 8) {}
  std::string GetDescription() const {
    return "uint" + std::to_string(GetSize() * 8) + "_t";
  };
};
extern UnsignedIntegerType UInt8Type;
extern UnsignedIntegerType UInt16Type;

class FloatType : public ScalarType {
public:
  FloatType() : ScalarType(4) {}
  std::string GetDescription() const { return "float"; };
};
extern FloatType floatType;

class DoubleType : public ScalarType {
public:
  DoubleType() : ScalarType(8) {}
  std::string GetDescription() const { return "double"; };
};
extern DoubleType doubleType;

/*! \class io_data
*
* \brief Abstract class for data types.
*
* Use this class to define a custom data type. Data types ares used for logging
*and graphs. \n
* The reimplemented class must call SetSize() in its constructor. \n
* io_data can be constructed with n samples (see io_data::io_data).
* In this case, old samples can be accessed throug io_data::Prev.
*/
class io_data : public Mutex {
  friend class IODevice;
  friend class ::IODevice_impl;
  friend class ::io_data_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct an io_data. \n
  *
  * \param parent parent
  * \param name name
  * \param n number of samples
  */
  io_data(const Object *parent, std::string name, int n);

  /*!
  * \brief Destructor
  *
  */
  virtual ~io_data();

  /*!
  * \brief Set data time
  *
  * \param time time
  */
  void SetDataTime(Time time);

  /*!
  * \brief Data time
  *
  * \return data time
  */
  Time DataTime(void) const;

  /*!
  * \brief Previous data
  *
  * Access previous data. io_data must have been constructed with
  * n>1, io_data::SetPtrToCircle must have been set and
  * io_data::prev must have been allocated.
  *
  * \param n previous data number
  *
  * \return previous data
  */
  const io_data *Prev(int n) const;

  virtual DataType const &GetDataType() const = 0;

protected:
  /*!
  * \brief Specify the description of the reimplemented class data's
  *
  *  This method must be called in the constructor of the reimplemented class,
  *once by element. \n
  *  Each element description must be called in the same order as CopyDatas put
  *the datas in the buffer. \n
  *  The description will be used for the log descriptor file.
  *
  * \param description description of the element
  * \param datatype type of the element
  */
  void AppendLogDescription(std::string description, DataType const &datatype);

  /*!
  * \brief Set the datas to circle
  *
  * \param ptr pointer to the data to circle
  */
  void SetPtrToCircle(void **ptr);

  /*!
  * \brief Pointer to previous data
  *
  * Reimplemented class must allocate this pointer if n>1. \n
  * Pointer must be allocated with the same kind of reimplemented class.
  */
  io_data *prev;

private:
  /*!
  * \brief Copy datas
  *
  * This method is automatically called by IODevice::ProcessUpdate to log
  *io_data datas. \n
  * This method must be reimplemented, in order to copy the datas to the logs.
  * Copied datas must be of size io_data::Size.
  *
  * \param dst destination buffer
  */
  virtual void CopyDatas(char *dst) const = 0;

  io_data_impl *pimpl_;
};

} // end namespace core
} // end namespace flair

#endif // IO_DATA_H
