// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file XAir.h
 * \brief Class defining a xair uav
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/02/08
 * \version 4.0
 */

#ifndef XAIR_H
#define XAIR_H

#include "Uav.h"

namespace flair {
namespace meta {
/*! \class XAir
*
* \brief Class defining a xair uav
*/
class XAir : public Uav {
public:
  XAir(core::FrameworkManager *parent, std::string uav_name,
       filter::UavMultiplex *multiplex = NULL);
  ~XAir();
  void StartSensors(void);

private:
};
} // end namespace meta
} // end namespace flair
#endif // XAIR_H
