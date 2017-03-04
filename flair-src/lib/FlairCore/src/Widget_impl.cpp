// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/05/02
//  filename:   Widget.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe pour widget
//
//
/*********************************************************************/

#include "Widget.h"
#include "Widget_impl.h"
#include "Object_impl.h"
#include "FrameworkManager.h"
#include "FrameworkManager_impl.h"
#include "config.h"
#ifdef __XENO__
#include <native/heap.h>
#else
#include <errno.h>
#include <cstring>
#endif

using std::string;
using std::vector;
using namespace flair::core;
using namespace flair::gui;

namespace {
#ifdef __XENO__
RT_HEAP xml_heap;

void xml2_free(void *mem) {
  // Printf("free %x\n",mem);
  if (mem == NULL)
    return;
  int status = rt_heap_free(&xml_heap, mem);

  if (status != 0) {
    printf("libxml2: rt_heap_free error (%s)\n", strerror(-status));
  }
}

void *xml2_alloc(size_t sz) {
  void *ptr;
  // printf("alloc %i\n",sz);
  int status = rt_heap_alloc(&xml_heap, sz, TM_NONBLOCK, &ptr);
  if (status != 0) {
    printf("libxml2: rt_heap_alloc error (%s)\n", strerror(-status));
  }
  // Printf("alloc %x %i\n",ptr,sz);

  return ptr;
}

void *xml2_realloc(void *emem, size_t sz) {
  // Printf("realloc %x %i -> %i\n",emem,sz,sz);
  void *mem_re;

  if (emem == NULL) {
    return xml2_alloc(sz);
  } else if (sz == 0) {
    xml2_free(emem);
  }

  mem_re = xml2_alloc(sz);

  memcpy(mem_re, emem, sz);

  xml2_free(emem);

  return mem_re;
}

char *xml2_strdup(const char *str) {
  // printf("strdup %s\n",str);
  char *s = (char *)xml2_alloc(strlen(str) + 1);
  if (s == NULL)
    return NULL;

  strcpy(s, str);
  return s;
}
#endif //__XENO__
}

Widget_impl::Widget_impl(Widget *self, const Widget *parent, string name,
                         string type) {
  // Printf("Widget %s\n",name.c_str());
  isenabled = true;
  file_node = NULL;
  this->self = self;

  // n'est execute qu'une fois lorsqu'on construit le FrameworkManager
  if (parent == NULL) {
#ifdef __XENO__
    string tmp_name;
    tmp_name = name + "-xml";
    int status = rt_heap_create(&xml_heap, tmp_name.c_str(), XML_HEAP, H_FIFO);
    if (status != 0) {
      self->Err("rt_heap_create error (%s)\n", strerror(-status));
    }

    xmlMemSetup(xml2_free, xml2_alloc, xml2_realloc, xml2_strdup);
#endif //__XENO__
  }

  // xml init
  if (parent == NULL) {
    // create local doc
    send_doc = xmlNewDoc((xmlChar *)"1.0");
    send_node = xmlNewNode(NULL, (xmlChar *)type.c_str());
    xmlDocSetRootElement(send_doc, send_node);
    xmlSetProp(send_node, (xmlChar *)"name",
               (xmlChar *)self->ObjectName().c_str());
  } else {
    parent->pimpl_->AddChild(self);

    // get node corresponding to this widget in the xml file
    if (parent->pimpl_->file_node != NULL) {
      xmlChar *search = xmlCharStrdup(type.c_str());
      file_node =
          GetNodeByProp(parent->pimpl_->file_node->xmlChildrenNode, search,
                        (xmlChar *)"name", (xmlChar *)name.c_str());
      xmlFree(search);
    } else {
      self->Err("parent->file_node is NULL\n");
    }

    if (file_node == NULL) {
      self->Warn("%s, no match found in xml file\n", type.c_str());
      xmlNode *node;
      node = xmlNewNode(NULL, (xmlChar *)type.c_str());
      xmlSetProp(node, (xmlChar *)"name", (xmlChar *)name.c_str());
      file_node = xmlAddChild(parent->pimpl_->file_node, node);
      //((Widget*)getFrameworkManager())->pimpl_->PrintXml();
    }

    send_doc = parent->pimpl_->CopyDoc();

    // on recupere le dernier node
    xmlNodePtr node = xmlDocGetRootElement(send_doc);
    while (node->children != NULL)
      node = node->children;

    // on ajoute le node du widget
    send_node = xmlNewNode(NULL, (xmlChar *)type.c_str());
    xmlSetProp(send_node, (xmlChar *)"name", (xmlChar *)name.c_str());
    xmlAddChild(node, send_node);
  }

  // Printf("Widget ok %s\n",name.c_str());
}

Widget_impl::~Widget_impl() {
  // Printf("destruction widget %s\n",self->ObjectName().c_str());

  if (self->Parent() != NULL)
    ((Widget *)(self->Parent()))->pimpl_->RemoveChild(self);

  // on efface les widgets enfants avant d'envoyer son propre delete au sol
  // dans le delete child on modifie le child du parent, donc on se refere
  // toujours au premier
  while (childs.size() != 0) {
    // Printf("child %i
    // %s\n",childs.size(),childs.front()->ObjectName().c_str());
    if (childs.front() != NULL)
      delete childs.front();
  }
  childs.clear();

  self->SetVolatileXmlProp("Delete", true);

  if (self->Parent() != NULL)
    SendXml();

  xmlFreeDoc(send_doc);

  if (self->Parent() == NULL) {
    xmlCleanupParser();
#ifdef __XENO__
    int status;
    RT_HEAP_INFO info;
    status = rt_heap_inquire(&xml_heap, &info);
    if (status != 0) {
      self->Err("rt_heap_inquire error (%s)\n", strerror(-status));
    }
    if (info.usedmem != 0)
      self->Err("fuite memoire xml heap (%ld)\n", info.usedmem);
    // Printf("fin heap xml\n");
    status = rt_heap_delete(&xml_heap);
    if (status != 0) {
      self->Err("rt_heap_delete error (%s)\n", strerror(-status));
    }
#endif
  }
  // Printf("destruction widget %s ok\n",self->ObjectName().c_str());
}

void Widget_impl::AddChild(const Widget *child) {
  childs.push_back((Widget *)child);
}

void Widget_impl::RemoveChild(const Widget *child) {
  for (vector<Widget *>::iterator it = childs.begin(); it < childs.end();
       it++) {
    if (*it == child) {
      childs.erase(it);
      break;
    }
  }
}

xmlDocPtr Widget_impl::CopyDoc(void) { return xmlCopyDoc(send_doc, 1); }

void Widget_impl::ClearXmlProps(void) {
  xmlUnlinkNode(send_node);
  xmlFreeNode(send_node);

  xmlNodePtr node;
  node = xmlDocGetRootElement(send_doc);

  if (node == NULL) { // il ne reste plus rien, on refait le rootelement
    send_node = xmlNewNode(NULL, (xmlChar *)XML_ROOT_TYPE);
    xmlSetProp(send_node, (xmlChar *)"name",
               (xmlChar *)self->ObjectName().c_str());
    xmlDocSetRootElement(send_doc, send_node);
  } else {
    while (node->children != NULL)
      node = node->children;
    send_node = xmlNewNode(NULL, (xmlChar *)self->ObjectType().c_str());
    xmlSetProp(send_node, (xmlChar *)"name",
               (xmlChar *)self->ObjectName().c_str());
    xmlAddChild(node, send_node);
  }
}

void Widget_impl::printSendNode() {

  xmlChar *xmlbuff;
  int buffersize;
  xmlDocDumpFormatMemory(send_doc, &xmlbuff, &buffersize, 1);
  Printf("xml:\n%s\n", xmlbuff);
  xmlFree(xmlbuff);
}

void Widget_impl::SendXml(void) {
  if (getUiCom() != NULL) {
    xmlChar *xmlbuff;
    int buffersize;
    xmlDocDumpFormatMemory(send_doc, &xmlbuff, &buffersize, 0);
    getUiCom()->Send((char *)xmlbuff, buffersize);
    xmlFree(xmlbuff);

    ClearXmlProps();
  }
}

void Widget_impl::setEnabled(bool status) {
  self->SetVolatileXmlProp("IsEnabled", status);
  SendXml();
}

void Widget_impl::ProcessXML(xmlNode *node) {
  // Printf("ProcessXML %s %s\n",xmlGetProp(send_node,
  // (xmlChar*)"name"),send_node->name);
  xmlNode *cur_node = NULL;

  for (size_t i = 0; i < childs.size(); i++) {
    for (cur_node = node; cur_node; cur_node = cur_node->next) {
      if (cur_node->type == XML_ELEMENT_NODE) {
        // Printf("recherche %s\n", xmlGetProp(cur_node, (xmlChar*)"name"));
        xmlChar *name = NULL;
        name = xmlGetProp(cur_node, (xmlChar *)"name");
        if (!xmlStrcmp((xmlChar *)childs[i]->ObjectName().c_str(), name)) {
          // Printf("correspond %s\n",childs[i]->ObjectName().c_str());
          xmlChar *new_name = NULL;
          new_name = xmlGetProp(cur_node, (xmlChar *)"new_name");
          if (new_name != NULL) {
            unsigned char *ren_name =
                new_name; // xmlGetProp(cur_node, (xmlChar*)"new_name");
            self->Warn(
                "%s existe deja, renommage en %s; possiblite de problemes!!\n",
                childs[i]->ObjectName().c_str(), new_name);
            childs[i]->Object::pimpl_->name = ((const char *)ren_name);
            xmlSetProp(childs[i]->pimpl_->send_node, (xmlChar *)"name",
                       xmlGetProp(cur_node, (xmlChar *)"new_name"));
            xmlFree(new_name);
            if (name != NULL)
              xmlFree(name);
            break;
          }

          if (name != NULL)
            xmlFree(name);

          // update file node
          xmlAttr *cur_prop = NULL;
          // xmlAttr *file_prop = NULL;
          for (cur_prop = cur_node->properties; cur_prop;
               cur_prop = cur_prop->next) {
            // Printf("rcv prop %s
            // %s\n",cur_prop->name,cur_prop->children->content);
            xmlSetProp(childs[i]->pimpl_->file_node, cur_prop->name,
                       cur_prop->children->content);
          }

          childs[i]->XmlEvent();

          childs[i]->pimpl_->ProcessXML(cur_node->children);
          break;
        }
        if (name != NULL)
          xmlFree(name);
      }
    }
  }

  // printf("fin ProcessXML %s %s\n",xmlGetProp(send_node,
  // (xmlChar*)"name"),send_node->name);
}

xmlNodePtr Widget_impl::GetNodeByProp(xmlNodePtr doc, xmlChar *type,
                                      xmlChar *prop, xmlChar *value) {
  // printf("cherche keyword: %s %s %s\n", type,prop,value);
  xmlNode *cur_node = NULL;
  for (cur_node = doc; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      // printf("node %s %s\n",xmlGetProp(cur_node,
      // (xmlChar*)"name"),cur_node->name);
      xmlChar *test = NULL;
      test = xmlGetProp(cur_node, prop);
      if (!xmlStrcmp(test, value) && !xmlStrcmp(cur_node->name, type)) {
        // printf("ok\n");
        if (test != NULL)
          xmlFree(test);
        return cur_node;
      }
      if (test != NULL)
        xmlFree(test);
    }
  }

  return NULL;
}
