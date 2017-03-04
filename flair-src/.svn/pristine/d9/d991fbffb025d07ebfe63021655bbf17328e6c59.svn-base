// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2011/05/01
//  filename:   IODevice.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Abstract class for input/ouput system
//
//
/*********************************************************************/

#include "IODevice.h"
#include "IODevice_impl.h"
#include "io_data.h"
#include "io_data_impl.h"
#include "FrameworkManager.h"

using std::string;

namespace flair {
namespace core {

IODevice::IODevice(const Object* parent,string name): Object(parent,name,"IODevice") {
    pimpl_=new IODevice_impl(this);
    lastUpdate=GetTime();
}

IODevice::~IODevice() { delete pimpl_; }

void IODevice::AddDeviceToLog(const IODevice *device) {
  pimpl_->AddDeviceToLog(device);
}

void IODevice::OutputToShMem(bool enabled) { pimpl_->OutputToShMem(enabled); }

void IODevice::ProcessUpdate(io_data *data) {
  if (data != NULL)
    data->pimpl_->SetConsistent(true);

  for (size_t i = 0; i < TypeChilds()->size(); i++) {
    ((IODevice *)TypeChilds()->at(i))->UpdateFrom(data);
  }

    if(data!=NULL) {
        lastUpdate=data->DataTime();
        if(getFrameworkManager()->IsLogging()==true) pimpl_->WriteLog(data->DataTime());

    data->pimpl_->Circle();
  }

  pimpl_->WriteToShMem();

  pimpl_->ResumeThread();
}

void IODevice::AddDataToLog(const io_data *data) { pimpl_->AddDataToLog(data); }

DataType const &IODevice::GetInputDataType() const { return dummyType; }

DataType const &IODevice::GetOutputDataType() const { return dummyType; }

} // end namespace core
} // end namespace flair
