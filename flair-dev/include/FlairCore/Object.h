// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Object.h
 * \brief Base class for all Framework's classes
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/05/07
 * \version 4.0
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>
#include <stdarg.h>

#define Warn(...) Warning(__PRETTY_FUNCTION__, __VA_ARGS__)
#define Err(...) Error(__PRETTY_FUNCTION__, __VA_ARGS__)
#define Info(...) Information(__PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)

#define TIME_INFINITE 0
#define TIME_NONBLOCK ((Time)-1)

class Object_impl;
class Widget_impl;

namespace flair {
namespace core {

class FrameworkManager;

class Message {
public:
  Message(unsigned int myBufferSize) : bufferSize(myBufferSize) {
    buffer = new char[bufferSize];
  }
  ~Message() { delete buffer; }
  char *buffer;
  size_t bufferSize;
};

/*!
* \brief Time definition, in ns
*
*/
typedef unsigned long long Time;

/*!
* \brief Time
*
* \return actual time in ns (origin depends on whether the method is compiled in
*hard real time mode or not. As a conquence, only time differences should be
*used)
*/
Time GetTime(void);

/*!
* \brief Formatted print
*
* See standard printf for syntax.
*
* \param format text string to display
*/
void Printf(const char *format, ...);

/*! \class Object
*
* \brief Base class for all Framework's classes
*
* This is the base class for all other classes. \n
* It handles parent/child links and thus allow auto destruction of childs.
*
*/
class Object {
  friend class ::Widget_impl;

public:
  typedef enum { Auto = 0, Red = 31, Green = 32, Orange = 33 } color_t;
  /*!
  * \brief Constructor
  *
  * Construct an Object, which is child of its parent.
  *
  * \param parent parent
  * \param name name
  * \param type type
  */
  Object(const Object *parent = NULL, std::string name = "",
         std::string type = "");

  /*!
  * \brief Destructor
  *
  * Calling it will automatically destruct all childs.
  *
  */
  virtual ~Object();

  /*!
  * \brief Name
  *
  * \return Object's name
  */
  std::string ObjectName(void) const;

  /*!
  * \brief Type
  *
  * \return Object's type
  */
  std::string ObjectType(void) const;

  /*!
  * \brief Parent
  *
  * \return Object's parent
  */
  const Object *Parent(void) const;

  /*!
  * \brief Childs of the same type
  *
  * \return a vector of all childs of the same type
  */
  std::vector<const Object *> *TypeChilds(void) const;

  /*!
  * \brief Childs
  *
  * \return a vector of all childs
  */
  std::vector<const Object *> *Childs(void) const;

  /*!
  * \brief Formatted information
  *
  * Green colored Printf(). \n
  * Note that it is better to call Info macro, which automatically fills
  *function parameter.
  *
  * \param function name of calling function
  * \param line line number in calling function
  * \param format text string to display
  */
  void Information(const char *function, int line, const char *format,
                   ...) const;

  /*!
  * \brief Formatted warning
  *
  * Orange colored Printf(). \n
  * Note that it is better to call Warn macro, which automatically fills
  *function parameter.
  *
  * \param function name of calling function
  * \param format text string to display
  */
  void Warning(const char *function, const char *format, ...) const;

  /*!
  * \brief Formatted error
  *
  * Red colored Printf(). \n
  * Note that it is better to call Err macro, which automatically fills function
  *parameter. \n
  * After calling this method, ErrorOccured() will always return true.
  *
  * \param function name of calling function
  * \param format text string to display
  */
  void Error(const char *function, const char *format, ...) const;

  /*!
  * \brief Has an errror occured?
  *
  * Check if an error occured, in fact if Error() was called at least once. \n
  * Once Error() was called, this method will never return back false.
  *
  * \param recursive if true, recursively check among childs
  * \return true if an error occured
  */
  bool ErrorOccured(bool recursive = true) const;

private:
  class Object_impl *pimpl_;
  void ColorPrintf(color_t, const char *function, int line, const char *format,
                   va_list *args) const;
};

} // end namespace core
} // end namespace flair

#endif // OBJECT_H
