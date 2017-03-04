// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "DataRemote.h"
#include <QMenu>
#include <QInputDialog>
#include <QtXml>
#include "Manager.h"
#include "ConnectionLayout.h"

DataRemote::DataRemote(QString name, QString type, XmlWidget *parent,
                       bool enabled, int period)
    : XmlWidget(name, type, parent) {
  auto_refresh = enabled;
  is_logging = true;
  receivesize = 0;
  refresh_rate = (double)period / 1000.;

  connectionLayout()->addDataRemote(this);

  // pour ne pas faire de doublons qd on change la periode
  SetIsExpandable(true);
}

DataRemote::~DataRemote() { connectionLayout()->removeDataRemote(this); }

void DataRemote::appendmenu(QMenu *menu) {
  menu->addSeparator();

  b = menu->addAction("auto refresh");
  b->setCheckable(true);
  b->setChecked(auto_refresh);

  c = menu->addAction(QString("set refresh rate (%1ms)")
                          .arg((uint16_t)(qRound(refresh_rate * 1000))));
  c->setEnabled(auto_refresh);
  menu->addSeparator();

  d = menu->addAction("log");
  d->setCheckable(true);
  d->setChecked(is_logging);
}

QAction *DataRemote::execmenu(QWidget *parent, QMenu *menu, QPoint point) {
  QAction *z;

  z = menu->exec(point);

  // auto_refresh=b->isChecked();

  if (z == b) {
    SendPeriod(RefreshRate_ms(), b->isChecked());
  }

  if (z == c) {
    bool ok;
    // uint16_t time = QInputDialog::getInt(this, QString("Set refresh rate
    // (%1)").arg(title().text()),tr("Value (ms):"),
    // (uint16_t)(qRound(refresh_rate*1000)), 1, 65535, 10, &ok);
    uint16_t time = QInputDialog::getInt(
        parent, "Set refresh rate ", "Value (ms):",
        (uint16_t)(qRound(refresh_rate * 1000)), 1, 65535, 10, &ok);
    if (ok == true && time != qRound(refresh_rate * 1000)) {
      // refresh_rate=time/1000.;
      SendPeriod(time, b->isChecked());
    }
  }

  return z;
}

uint16_t DataRemote::RefreshRate_ms(void) {
  return (uint16_t)(qRound(refresh_rate * 1000.));
}

bool DataRemote::IsEnabled(void) { return auto_refresh; }

void DataRemote::SendPeriod(int period, bool auto_refresh) {
  RemoveAllAttributes();

  SetAttribute("period", period);
  SetAttribute("enabled", auto_refresh);

  connectionLayout()->XmlToSend(XmlDoc());

  RemoveAttribute("period");
  RemoveAttribute("enabled");
}

int DataRemote::ReceiveSize(void) { return receivesize; }

void DataRemote::XmlSetup(QDomElement dom) {
  refresh_rate = dom.attribute("period").toInt() / 1000.;
  if (dom.attribute("enabled") == "1")
    auto_refresh = true;
  else
    auto_refresh = false;
}
