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
//  purpose:    classe pour qobject
//
//
/*********************************************************************/

#include "Object.h"
#include "Object_impl.h"

using std::string;
using std::vector;
using namespace flair::core;

Object_impl::Object_impl(const Object *self, const Object *parent, string name,
                         string type) {
  // Printf("Object %s\n",name.c_str());
  this->self = self;
  this->parent = parent;
  this->name = name;
  this->type = type;
  error_occured = false;

  if (parent != NULL) {
    if (name == "")
      this->name = parent->ObjectName();
  }
}

Object_impl::~Object_impl() {
  // Printf("destruction Object %s %s\n",name.c_str(),type.c_str());

  while (childs.size() != 0) {
    // Printf("child %i %s
    // %s\n",childs.size(),childs.front()->ObjectName().c_str(),childs.front()->ObjectType().c_str());
    // if(childs.front()!=NULL)
    delete childs.front();
  }

  if (type_childs.size() != 0) {
    type_childs.clear();
    self->Warn("type_childs not cleared\n");
  }

  // Printf("destruction Object %s %s ok\n",name.c_str(),type.c_str());
}

void Object_impl::AddChild(const Object *child) {
  childs.push_back(child);
  // self->Printf("added Object %s %s (%s
  // %s)\n",child->ObjectName().c_str(),child->ObjectType().c_str(),name.c_str(),type.c_str());
  if (child->ObjectType() == type)
    type_childs.push_back(child);
}

void Object_impl::RemoveChild(const Object *child) {
  // self->Printf("removed Object %s %s (%s
  // %s)\n",child->ObjectName().c_str(),child->ObjectType().c_str(),name.c_str(),type.c_str());

  for (vector<const Object *>::iterator it = childs.begin(); it < childs.end();
       it++) {
    if (*it == child) {
      childs.erase(it);
      break;
    }
  }

  for (vector<const Object *>::iterator it = type_childs.begin();
       it < type_childs.end(); it++) {
    if (*it == child) {
      type_childs.erase(it);
      break;
    }
  }
}

bool Object_impl::ErrorOccured(bool recursive) {
  if (recursive == true) {
    for (size_t i = 0; i < childs.size(); i++) {
      if (childs[i]->ErrorOccured(true) == true) {
        return true;
      }
    }
  }
  return error_occured;
}
