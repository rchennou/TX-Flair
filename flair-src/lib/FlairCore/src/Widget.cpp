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
//  purpose:    Abstract class for all Framework's widget classes
//
//
/*********************************************************************/

#include "Widget.h"
#include "Widget_impl.h"

using std::string;

namespace flair {
namespace gui {

using namespace core;

Widget::Widget(const Widget *parent, string name, string type)
    : Object(parent, name, type) {
  pimpl_ = new Widget_impl(this, parent, name, type);
}

Widget::~Widget() { delete pimpl_; }

template <> bool Widget::GetPersistentXmlProp(std::string prop, double &value) {
  xmlChar *result = NULL;
  result = xmlGetProp(pimpl_->file_node, (xmlChar *)prop.c_str());

  if (result != NULL) {
    value = xmlXPathCastStringToNumber(result);
    xmlFree(result);
    return true;
  } else {
    return false;
  }
}

template <> bool Widget::GetPersistentXmlProp(std::string prop, float &value) {
  double tmp;
  if (GetPersistentXmlProp<double>(prop, tmp)) {
    value = tmp;
    return true;
  } else {
    return false;
  }
}

template <> bool Widget::GetPersistentXmlProp(std::string prop, bool &value) {
  double tmp;
  if (GetPersistentXmlProp<double>(prop, tmp)) {
    value = tmp;
    return true;
  } else {
    return false;
  }
}

template <>
bool Widget::GetPersistentXmlProp(std::string prop, int32_t &value) {
  double tmp;
  if (GetPersistentXmlProp<double>(prop, tmp)) {
    value = tmp;
    return true;
  } else {
    return false;
  }
}

template <>
bool Widget::GetPersistentXmlProp(std::string prop, uint16_t &value) {
  double tmp;
  if (GetPersistentXmlProp<double>(prop, tmp)) {
    value = tmp;
    return true;
  } else {
    return false;
  }
}

template <>
bool Widget::GetPersistentXmlProp(std::string prop, std::string &value) {
  xmlChar *result = NULL;
  result = xmlGetProp(pimpl_->file_node, (xmlChar *)prop.c_str());
  if (result != NULL) {
    value = std::string((char *)result);
    xmlFree(result);
    return true;
  } else {
    return false;
  }
}

template <>
void Widget::SetVolatileXmlProp(string prop, string value, xmlNodePtr node) {
  if (node == NULL)
    node = pimpl_->send_node;
  xmlSetProp(node, (xmlChar *)prop.c_str(), (xmlChar *)value.c_str());
}

template <>
void Widget::SetVolatileXmlProp(string prop, char *value, xmlNodePtr node) {
  if (node == NULL)
    node = pimpl_->send_node;
  xmlSetProp(node, (xmlChar *)prop.c_str(), (xmlChar *)value);
}

template <>
void Widget::SetVolatileXmlProp(string prop, double value, xmlNodePtr node) {
  xmlChar *xmlChar_value = xmlXPathCastNumberToString(value);

  if (node == NULL)
    node = pimpl_->send_node;
  xmlSetProp(node, (xmlChar *)prop.c_str(), xmlChar_value);
  xmlFree(xmlChar_value);
}

template <>
void Widget::SetVolatileXmlProp(string prop, float value, xmlNodePtr node) {
  SetVolatileXmlProp<double>(prop, value, node);
}

template <>
void Widget::SetVolatileXmlProp(string prop, int32_t value, xmlNodePtr node) {
  SetVolatileXmlProp<double>(prop, value, node);
}

template <>
void Widget::SetVolatileXmlProp(string prop, uint32_t value, xmlNodePtr node) {
  SetVolatileXmlProp<double>(prop, value, node);
}

template <>
void Widget::SetVolatileXmlProp(string prop, int16_t value, xmlNodePtr node) {
  SetVolatileXmlProp<double>(prop, value, node);
}

template <>
void Widget::SetVolatileXmlProp(string prop, uint16_t value, xmlNodePtr node) {
  SetVolatileXmlProp<double>(prop, value, node);
}

template <>
void Widget::SetVolatileXmlProp(string prop, int8_t value, xmlNodePtr node) {
  SetVolatileXmlProp<double>(prop, value, node);
}

template <>
void Widget::SetVolatileXmlProp(string prop, uint8_t value, xmlNodePtr node) {
  SetVolatileXmlProp<double>(prop, value, node);
}

template <>
void Widget::SetVolatileXmlProp(string prop, bool value, xmlNodePtr node) {
  SetVolatileXmlProp<double>(prop, value, node);
}

template <>
void Widget::SetVolatileXmlProp(string prop, xmlChar *value, xmlNodePtr node) {
  if (node == NULL)
    node = pimpl_->send_node;
  xmlSetProp(node, (xmlChar *)prop.c_str(), value);
}

template <>
void Widget::SetVolatileXmlProp(string prop, DataType const &dataType,
                                xmlNodePtr node) {
  if (node == NULL)
    node = pimpl_->send_node;
  xmlSetProp(node, (xmlChar *)prop.c_str(),
             (xmlChar *)dataType.GetDescription().c_str());
  /*
      switch(dataType)
      {
          case io_data::Float:
              xmlSetProp(node,(xmlChar*)prop.c_str(),(xmlChar*)"float");
              break;
          case io_data::Int8_t:
              xmlSetProp(node,(xmlChar*)prop.c_str(),(xmlChar*)"int8_t");
              break;
          case io_data::Int16_t:
              xmlSetProp(node,(xmlChar*)prop.c_str(),(xmlChar*)"int16_t");
              break;
      }
      */
}

template <> void Widget::SetPersistentXmlProp(std::string prop, double value) {
  SetVolatileXmlProp(prop, value);
  SetVolatileXmlProp(prop, value, pimpl_->file_node);
}

template <> void Widget::SetPersistentXmlProp(std::string prop, float value) {
  SetVolatileXmlProp(prop, value);
  SetVolatileXmlProp(prop, value, pimpl_->file_node);
}

template <> void Widget::SetPersistentXmlProp(std::string prop, int32_t value) {
  SetVolatileXmlProp(prop, value);
  SetVolatileXmlProp(prop, value, pimpl_->file_node);
}

template <>
void Widget::SetPersistentXmlProp(std::string prop, uint16_t value) {
  SetVolatileXmlProp(prop, value);
  SetVolatileXmlProp(prop, value, pimpl_->file_node);
}

template <> void Widget::SetPersistentXmlProp(std::string prop, bool value) {
  SetVolatileXmlProp(prop, value);
  SetVolatileXmlProp(prop, value, pimpl_->file_node);
}

template <> void Widget::SetPersistentXmlProp(std::string prop, std::string value) {
  SetVolatileXmlProp(prop, value);
  SetVolatileXmlProp(prop, value, pimpl_->file_node);
}

void Widget::UnsetPersistentXmlProp(std::string prop) {
  xmlUnsetProp(pimpl_->file_node, (xmlChar *)prop.c_str());
}

void Widget::SendXml(void) { pimpl_->SendXml(); }

void Widget::setEnabled(bool status) { pimpl_->setEnabled(status); }

bool Widget::isEnabled(void) const { return pimpl_->isenabled; }

} // end namespace gui
} // end namespace flair
