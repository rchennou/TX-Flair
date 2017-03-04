// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "XmlWidget.h"
#include <QWidget>
#include "ConnectionLayout.h"
#include <stdio.h>

XmlWidget::XmlWidget(QString name, QString type, XmlWidget *parent)
    : QObject() {
  childs = new QList<XmlWidget *>;
  isContainer = false;
  isExpandable = false;
  visible_widget = NULL;
  parent_widget = parent;

  red_pal.setColor(QPalette::Text, QColor(255, 0, 0));
  red_pal.setColor(QPalette::Foreground, QColor(255, 0, 0));
  red_pal_greyed.setColor(QPalette::Text, QColor(128, 0, 0));
  red_pal_greyed.setColor(QPalette::Foreground, QColor(128, 0, 0));

  black_pal.setColor(QPalette::Text, QColor(0, 0, 0));
  black_pal.setColor(QPalette::Foreground, QColor(0, 0, 0));
  black_pal_greyed.setColor(QPalette::Text, QColor(128, 128, 128));
  black_pal_greyed.setColor(QPalette::Foreground, QColor(128, 128, 128));

  setObjectName(name);

  if (parent != NULL) {
    parent->childs->append(this);

    document = parent->document.cloneNode(true).toDocument();

    write_elem = QDomElement(document.createElement(type));
    write_elem.setAttribute("name", name);
    // recupere le node le plus profond
    QDomNode node = document.firstChild();
    while (node.firstChild().isNull() == false) {
      node = node.firstChild();
    }
    node.appendChild(write_elem);
  } else {
    document = QDomDocument("remote_ui_xml");
    write_elem = QDomElement(document.createElement(type));
    write_elem.setAttribute("name", name);
    document.appendChild(write_elem);
  }
}

XmlWidget::~XmlWidget() {
  if (parent_widget != NULL)
    parent_widget->childs->removeOne(this);

  // on efface les widgets enfants
  // dans le delete child on modifie le child du parent, donc on se refere
  // toujours au premier
  while (childs->count() != 0) {
    delete childs->first();
  }

  delete childs;
  if (visible_widget != NULL) {
    delete visible_widget;
  }
}

QString XmlWidget::Name(void) { return write_elem.attribute("name"); }

void XmlWidget::SetIsContainer(bool status) { isContainer = status; }

void XmlWidget::SetIsExpandable(bool status) { isExpandable = status; }

XmlWidget *XmlWidget::GetXmlWidget(QString name, QString type) {
  // printf("recherche %s
  // %s\n",name.toLocal8Bit().constData(),type.toLocal8Bit().constData());

  for (int i = 0; i < childs->count(); i++) {
    // printf("child name
    // %s\n",childs->at(i)->write_elem.attribute("name").toLocal8Bit().constData());
    // printf("child tag
    // %s\n",childs->at(i)->write_elem.tagName().toLocal8Bit().constData());
    if (childs->at(i)->write_elem.attribute("name") == name &&
        childs->at(i)->write_elem.tagName() == type)
      return childs->at(i);
  }
  return NULL;
}

void XmlWidget::ParseXml(QDomElement to_parse) {

  if (to_parse.isNull())
    return;

  QString type = to_parse.tagName();
  QString name = to_parse.attribute("name");

  // printf("parse %s
  // %s\n",type.toLocal8Bit().constData(),name.toLocal8Bit().constData());
  XmlWidget *match;
  match = GetXmlWidget(name, type);

  if (match == NULL) {
    // printf("not match\n");
    XmlEvent(to_parse);
  } else {
    // printf("match\n");
    // si on a une balise IsEnabled, on ne traite que ca
    if (match->visible_widget != NULL) {
      if (to_parse.attribute("IsEnabled") == "0") {
        match->visible_widget->setEnabled(false);
        return;
      }
      if (to_parse.attribute("IsEnabled") == "1") {
        match->visible_widget->setEnabled(true);
        return;
      }
    }

    // si on a une balise delete, on ne traite que ca
    if (to_parse.attribute("Delete") == "1") {
      // printf("delete flag\n");
      if (match->isContainer == true && match->childs->count() != 0) {
        // printf("non vide
        // %s\n",match->objectName().toLocal8Bit().constData());
        return;
      }

      delete match;
      return;
    }

    if (to_parse.firstChild().isNull() == true &&
        match->isExpandable == false) {
      QString new_name;
      printf("possible doublon\n");
      for (int i = 0; i < 65535; i++) {
        new_name = QString("%1_%2").arg(name).arg(i);
        bool continuer = false;
        for (int i = 0; i < childs->count(); i++) {
          if (childs->at(i)->write_elem.attribute("name") == new_name) {
            continuer = true;
            break;
          }
        }
        if (continuer == false)
          break;
      }
      printf("new_name %s\n", new_name.toLocal8Bit().constData());
      to_parse.setAttribute("name", new_name);
      to_parse.setAttribute("old_name", name);

      XmlEvent(to_parse);

      // return -1;//ou retourner le xml a renvoyer pour chager de nom
    } else {
      if (to_parse.firstChild().toElement().isNull()) {
        match->XmlEvent(to_parse);
        return;
      } else {
        match->ParseXml(to_parse.firstChild().toElement());
      }
    }
  }
}

void XmlWidget::LoadXml(QDomElement to_parse) {
  if (to_parse.isNull())
    return;

  LoadEvent(to_parse);

  QDomElement elem = to_parse.firstChild().toElement();

  while (!elem.isNull()) {

    QString type = elem.tagName();
    QString name = elem.attribute("name");
    // printf("%s
    // %s\n",type.toLocal8Bit().constData(),name.toLocal8Bit().constData());
    XmlWidget *match;
    match = GetXmlWidget(name, type);

    if (match != NULL) {
      // printf("match\n");
      match->LoadXml(elem);
    }
    elem = elem.nextSibling().toElement();
  }
}

void XmlWidget::GetFullXml(QDomElement *doc) {
  QDomDocument tmp_doc = XmlDoc();
  merge((QDomElement *)&tmp_doc, doc);

  for (int i = 0; i < childs->count(); i++) {
    childs->at(i)->GetFullXml(doc);
  }
}

void XmlWidget::GetUpdateXml(QDomElement *doc) {
  if (IsUptodate() == false && isContainer == false) {
    SetUptodate();
    QDomDocument tmp_doc = XmlDoc();
    merge((QDomElement *)&tmp_doc, doc);
  }

  for (int i = 0; i < childs->count(); i++) {
    childs->at(i)->GetUpdateXml(doc);
  }
}

void XmlWidget::ResetAllChilds(void) {
  Reset();
  for (int i = 0; i < childs->count(); i++) {
    childs->at(i)->ResetAllChilds();
  }
}

void XmlWidget::merge(QDomElement *from, QDomElement *into) {
  QDomElement tmp_into, tmp_from;
  tmp_from = from->firstChildElement();

  while (tmp_from.isNull() == false) {
    // search corresponding child
    bool match = false;
    tmp_into = into->firstChildElement(tmp_from.tagName());
    while (tmp_into.isNull() == false) {
      if (tmp_into.attribute("name") == tmp_from.attribute("name")) {
        merge(&tmp_from, &tmp_into);
        match = true;
        break;
      }
      tmp_into = tmp_into.nextSiblingElement(tmp_from.tagName());
    }

    if (match == false) {
      into->appendChild(tmp_from.cloneNode());
    }

    tmp_from = tmp_from.nextSiblingElement();
  }
}

QDomDocument XmlWidget::XmlDoc(void) {
  return document.cloneNode(true).toDocument();
}

QDomElement *XmlWidget::AddXmlChild(QString type) {
  QDomElement *elem;

  elem = new QDomElement(document.createElement(type));
  write_elem.appendChild(*elem);

  return elem;
}

void XmlWidget::RemoveXmlChild(QDomElement *element) {
  write_elem.removeChild(*element);
  delete element;
}

void XmlWidget::ClearDoc(void) { document.clear(); }

void XmlWidget::SetValue(QString value) {
  write_elem.setAttribute("value", value);
}

void XmlWidget::SetAttribute(const QString &name, const QString &value) {
  write_elem.setAttribute(name, value);
}

void XmlWidget::SetAttribute(const QString &name, qlonglong value) {
  write_elem.setAttribute(name, value);
}

void XmlWidget::SetAttribute(const QString &name, qulonglong value) {
  write_elem.setAttribute(name, value);
}

void XmlWidget::SetAttribute(const QString &name, float value) {
  write_elem.setAttribute(name, value);
}

void XmlWidget::SetAttribute(const QString &name, double value) {
  write_elem.setAttribute(name, value);
}

void XmlWidget::RemoveAttribute(const QString &name) {
  write_elem.removeAttribute(name);
}

void XmlWidget::RemoveAllAttributes() {
  QString name = write_elem.attribute("name");

  QDomNamedNodeMap attributes=write_elem.attributes();
  while(attributes.count()!=0) {
    //printf("%i %s\n",attributes.count(),attributes.item(0).toAttr().name().toLocal8Bit().constData());
    write_elem.removeAttribute(attributes.item(0).toAttr().name());
  }
  SetAttribute("name", name);
}

void XmlWidget::RenamedFrom(QString old_name) {
  QString name = write_elem.attribute("name");
  SetAttribute("name", old_name);
  SetAttribute("new_name", name);
  connectionLayout()->XmlToSend(XmlDoc());
  SetAttribute("name", name);
  write_elem.removeAttribute("new_name");
}

ConnectionLayout *XmlWidget::connectionLayout(void) {
  if (parent_widget != NULL) {
    return (ConnectionLayout *)(parent_widget->connectionLayout());
  } else {
    return (ConnectionLayout *)this;
  }
}
