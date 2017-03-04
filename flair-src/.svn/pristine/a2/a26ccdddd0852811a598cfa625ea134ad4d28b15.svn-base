// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef XMLWIDGET_H
#define XMLWIDGET_H

#include <QObject>
#include <stdint.h>
#include <qdom.h>
#include <QPalette>

class QWidget;
class ConnectionLayout;

class XmlWidget : public QObject {
  Q_OBJECT

public:
  XmlWidget(QString name, QString type, XmlWidget *parent);
  ~XmlWidget();
  QDomDocument XmlDoc(void);
  void ParseXml(QDomElement to_parse);
  void GetFullXml(QDomElement *doc);
  void GetUpdateXml(QDomElement *doc);
  void ResetAllChilds(void);
  virtual bool IsUptodate(void) { return true; };
  void LoadXml(QDomElement to_parse);
  void RenamedFrom(QString old_name);
  QString Name(void);

private:
  QDomDocument document;
  QDomElement write_elem;
  XmlWidget *GetXmlWidget(QString name, QString type);
  static void merge(QDomElement *from, QDomElement *into);
  bool isExpandable; // true if we can receive extra frame for this widget (ex
                     // combobox, plots, layout)
  bool isContainer;  // true if it can contain other widget (ex layout),
                     // isExpandable is also true in this case
  virtual void SetUptodate(void){};
  virtual void Reset(void){};
  XmlWidget *parent_widget;

protected:
  QList<XmlWidget *> *childs;
  ConnectionLayout *connectionLayout(void);
  QWidget *visible_widget;
  QPalette red_pal, red_pal_greyed;
  QPalette black_pal, black_pal_greyed;
  void SetIsContainer(bool status);
  void SetIsExpandable(bool status);
  virtual void XmlEvent(QDomElement dom){};
  virtual void LoadEvent(QDomElement dom){};
  QDomElement *AddXmlChild(QString type);
  void RemoveXmlChild(QDomElement *element);
  void ClearDoc(void);
  void SetValue(QString value);
  void SetAttribute(const QString &name, const QString &value);
  void SetAttribute(const QString &name, qlonglong value);
  void SetAttribute(const QString &name, qulonglong value);
  inline void SetAttribute(const QString &name, int value) {
    SetAttribute(name, qlonglong(value));
  }
  inline void SetAttribute(const QString &name, uint value) {
    SetAttribute(name, qulonglong(value));
  }
  void SetAttribute(const QString &name, float value);
  void SetAttribute(const QString &name, double value);
  void RemoveAllAttributes(); //except name
  void RemoveAttribute(const QString &name);
};

#endif // XMLWIDGET_H
