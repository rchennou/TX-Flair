// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/05/07
//  filename:   Object.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe pour object_impl
//
//
/*********************************************************************/

#ifndef OBJECT_IMPL_H
#define OBJECT_IMPL_H

class Object_impl {
public:
  Object_impl(const flair::core::Object *self,
              const flair::core::Object *parent = NULL, std::string name = "",
              std::string type = "");
  ~Object_impl();
  std::string name, type;
  std::vector<const flair::core::Object *> childs;
  std::vector<const flair::core::Object *> type_childs;
  void AddChild(const flair::core::Object *child);
  void RemoveChild(const flair::core::Object *child);
  bool ErrorOccured(bool recursive);
  bool error_occured;
  const flair::core::Object *parent;

private:
  const flair::core::Object *self;
};

#endif // OBJECT_IMPL_H
