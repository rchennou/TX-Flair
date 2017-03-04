// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/03/07
//  filename:   SendData.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Abstract class for sending datas to ground station
//
//
/*********************************************************************/

#include "SendData.h"
#include "SendData_impl.h"
#include "Layout.h"
#include "LayoutPosition.h"
#include "FrameworkManager.h"
#include "FrameworkManager_impl.h"

using namespace std;
using namespace flair::core;

namespace flair {
namespace gui {

SendData::SendData(const LayoutPosition *position, string name, string type,
                   uint16_t default_periodms, bool default_enabled)
    : Widget(position->getLayout(), name, type) {
  pimpl_ = new SendData_impl();

  pimpl_->send_size = 0;

  // default refesh rate: (ms)
  pimpl_->send_period = default_periodms;
  pimpl_->is_enabled = default_enabled;

  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());
  GetPersistentXmlProp("period", pimpl_->send_period);
  SetPersistentXmlProp("period", pimpl_->send_period);
  GetPersistentXmlProp("enabled", pimpl_->is_enabled);
  SetPersistentXmlProp("enabled", pimpl_->is_enabled);

  delete position;

  if (getUiCom() != NULL) {
    // register SendData for sending to ground station
    getUiCom()->AddSendData(this);
    // resume if necessary
    getUiCom()->UpdateSendData(this);
  }
}

SendData::~SendData() {
  if (getUiCom() != NULL) {
    // unregister SendData for sending to ground station
    getUiCom()->RemoveSendData(this);
  }

  delete pimpl_;
}

void SendData::XmlEvent(void) {
  uint16_t send_period;
  bool is_enabled;
  bool something_changed = false;

  if (GetPersistentXmlProp("period", send_period) &&
      GetPersistentXmlProp("enabled", is_enabled)) {
    if (send_period != SendPeriod())
      something_changed = true;
    if (is_enabled != IsEnabled())
      something_changed = true;
  }

  if (something_changed) {
    getFrameworkManager()->BlockCom();

    SetSendPeriod(send_period);
    SetEnabled(is_enabled);

    getFrameworkManager()->UpdateSendData(this);

    // ack pour la station sol
    // period and enabled are already in persistent prop
    SetVolatileXmlProp("period", send_period);
    SetVolatileXmlProp("enabled", is_enabled);
    SendXml();

    getFrameworkManager()->UnBlockCom();
  }

  ExtraXmlEvent();
}

size_t SendData::SendSize(void) const { return pimpl_->send_size; }

uint16_t SendData::SendPeriod(void) const { return pimpl_->send_period; }

bool SendData::IsEnabled(void) const { return pimpl_->is_enabled; }

void SendData::SetEnabled(bool value) { pimpl_->is_enabled = value; }

void SendData::SetSendSize(size_t value) {
  pimpl_->send_size = value;

  if (getUiCom() != NULL)
    getUiCom()->UpdateDataToSendSize();
}

void SendData::SetSendPeriod(uint16_t value) { pimpl_->send_period = value; }

} // end namespace core
} // end namespace flair
