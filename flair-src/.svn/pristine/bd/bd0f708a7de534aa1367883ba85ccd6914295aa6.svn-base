// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file MetaVrpnObject.h
 * \brief Classe haut niveau intégrant un objet VRPN
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/08
 * \version 3.4
 */

#ifndef METAVRPNOBJECT_H
#define METAVRPNOBJECT_H

#include <VrpnObject.h>
#include "io_data.h"

namespace flair {
namespace core {
class Vector3D;
class FloatType;
}
namespace gui {
class DataPlot1D;
class DataPlot2D;
class Tab;
}
namespace filter {
class EulerDerivative;
class LowPassFilter;
}
namespace sensor {
class VrpnClient;
}
}

namespace flair {
namespace meta {

/*! \class MetaVrpnObject
*
* \brief Classe haut niveau intégrant un objet VRPN
*
* Contient un objet VRPN et une dérivée, d'euler.
*/
class MetaVrpnObject : public sensor::VrpnObject {
public:
  MetaVrpnObject(const sensor::VrpnClient *parent, std::string name);
  MetaVrpnObject(const sensor::VrpnClient *parent, std::string name,
                 uint8_t id);
  ~MetaVrpnObject();
  gui::DataPlot1D *VxPlot(void) const; // 1,0
  gui::DataPlot1D *VyPlot(void) const; // 1,1
  gui::DataPlot1D *VzPlot(void) const; // 1,2
  gui::DataPlot2D *XyPlot(void) const;
  void GetSpeed(core::Vector3D &speed) const;

private:
  void ConstructorCommon(const sensor::VrpnClient *parent, std::string name);
  filter::LowPassFilter *pbas;
  filter::EulerDerivative *euler;
  gui::DataPlot2D *xy_plot;
  gui::DataPlot1D *vx_opti_plot, *vy_opti_plot, *vz_opti_plot;
  gui::Tab *plot_tab;
  core::FloatType elementDataType;
};
} // end namespace meta
} // end namespace flair
#endif // METAVRPNOBJECT_H
