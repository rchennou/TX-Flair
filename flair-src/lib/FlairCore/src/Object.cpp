// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/05/07
//  filename:   Object.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Base class for all Framework's classes
//
//
/*********************************************************************/

#include <stdio.h>

#include "Object.h"
#include "Object_impl.h"
#include "FrameworkManager.h"

#ifdef __XENO__
#include <native/task.h>
#include <native/timer.h>
#include "rtdk.h"
#else
#include <sys/time.h>
#endif

using std::string;
using std::vector;

namespace flair {
namespace core {

Time GetTime(void) {
#ifdef __XENO__
  return rt_timer_read();
#else
  struct timeval t;
  gettimeofday(&t, NULL);
  return (Time)((Time)(t.tv_sec) * 1000000 + (Time)(t.tv_usec)) * 1000;

#endif
}

void Printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
#ifdef __XENO__
  if (rt_task_self() != NULL) {
    rt_vfprintf(stderr, format, args);
  } else
#endif
  {
    vfprintf(stderr, format, args);
  }

  va_end(args);
}

Object::Object(const Object *parent, string name, string type) {
  pimpl_ = new Object_impl(this, parent, name, type);
  if (parent != NULL)
    parent->pimpl_->AddChild(this);
}

Object::~Object() {
  if (pimpl_->parent != NULL)
    pimpl_->parent->pimpl_->RemoveChild(this);
  delete pimpl_;
}

string Object::ObjectName(void) const { return pimpl_->name; }

string Object::ObjectType(void) const { return pimpl_->type; }

const Object *Object::Parent(void) const { return pimpl_->parent; }

vector<const Object *> *Object::TypeChilds(void) const {
  return &(pimpl_->type_childs);
}

vector<const Object *> *Object::Childs(void) const { return &(pimpl_->childs); }

void Object::ColorPrintf(color_t color, const char *function, int line,
                         const char *format, va_list *args) const {
#ifdef __XENO__
  if (rt_task_self() != NULL) {
    rt_fprintf(stderr, "\033[%dm", color);
    if (line) {
      rt_fprintf(stderr, "%s - line %d, %s: ", function, line,
                 pimpl_->name.c_str());
    } else {
      rt_fprintf(stderr, "%s, %s: ", function, pimpl_->name.c_str());
    }
    rt_vfprintf(stderr, format, *args);
    rt_fprintf(stderr, "\033[%dm", color_t::Auto);
  } else
#endif
  {
    fprintf(stderr, "\033[%dm", color);
    if (line) {
      fprintf(stderr, "%s - line %d, %s: ", function, line,
              pimpl_->name.c_str());
    } else {
      fprintf(stderr, "%s, %s: ", function, pimpl_->name.c_str());
    }
    vfprintf(stderr, format, *args);
    fprintf(stderr, "\033[%dm", color_t::Auto);
  }
}

void Object::Information(const char *function, int line, const char *format,
                         ...) const {
  va_list args;
  va_start(args, format);
  ColorPrintf(color_t::Green, function, line, format, &args);
  va_end(args);
}

void Object::Warning(const char *function, const char *format, ...) const {
  va_list args;
  va_start(args, format);
  ColorPrintf(color_t::Orange, function, 0, format, &args);
  va_end(args);
}

void Object::Error(const char *function, const char *format, ...) const {
  va_list args;
  va_start(args, format);
  ColorPrintf(color_t::Red, function, 0, format, &args);
  va_end(args);

  pimpl_->error_occured = true;
}

bool Object::ErrorOccured(bool recursive) const {
  return pimpl_->ErrorOccured(recursive);
}

} // end namespace core
} // end namespace flair
