// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/02/05
//  filename:   UavFactory.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:   construct a Uav based on the type name
//
//
/*********************************************************************/

#ifndef UAVFACTORY
#define UAVFACTORY

#include <Uav.h>

flair::meta::Uav *CreateUav(flair::core::FrameworkManager *parent,
                            std::string uav_name, std::string uav_type,
                            flair::filter::UavMultiplex *multiplex = NULL);

void RegisterUavCreator(flair::meta::Uav*(*func)(flair::core::FrameworkManager *parent,
                                   std::string uav_name, std::string uav_type,
                                   flair::filter::UavMultiplex *multiplex));
#endif // UAVFACTORY
