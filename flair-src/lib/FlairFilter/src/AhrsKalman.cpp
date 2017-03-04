// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/01/15
//  filename:   AhrsKalman.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining an Ahrs Kalman filter
//
//
/*********************************************************************/

#include "AhrsKalman.h"
#include "AhrsKalman_impl.h"
#include <Imu.h>
#include <AhrsData.h>

using std::string;
using namespace flair::core;
using namespace flair::sensor;

namespace flair { namespace filter {

AhrsKalman::AhrsKalman(const Imu* parent,string name): Ahrs(parent,name) {
    AhrsData* ahrsData;
    GetDatas(&ahrsData);
    pimpl_=new AhrsKalman_impl(parent->GetLayout(),ahrsData);
}

AhrsKalman::~AhrsKalman() {
    delete pimpl_;
}

void AhrsKalman::UpdateFrom(const io_data *data) {
    pimpl_->UpdateFrom(data);
    AhrsData* ahrsData;
    GetDatas(&ahrsData);
    ProcessUpdate(ahrsData);
}

} // end namespace filter
} // end namespace flair
