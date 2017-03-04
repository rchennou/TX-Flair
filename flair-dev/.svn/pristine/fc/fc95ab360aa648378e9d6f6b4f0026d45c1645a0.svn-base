// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file MetaUsRangeFinder.h
 * \brief Classe haut niveau pour capteur à ultra son
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/08
 * \version 3.4
 */

#ifndef METAUSRANGEFINDER_H
#define METAUSRANGEFINDER_H

#include <Object.h>

namespace flair {
namespace filter {
class ButterworthLowPass;
class EulerDerivative;
}
namespace sensor {
class UsRangeFinder;
}
namespace gui {
class DataPlot1D;
}
}

namespace flair {
namespace meta {
/*! \class MetaUsRangeFinder
*
* \brief Classe haut niveau pour capteur à ultra son
*
* Contient une dérivée d'euler et un passe bas.
* Cette classe est adaptée pour un capteur d'altitude.
*/
class MetaUsRangeFinder : public core::Object {
public:
  MetaUsRangeFinder(sensor::UsRangeFinder *us);
  ~MetaUsRangeFinder();
  void UseDefaultPlot(void);
  float z(void) const;
  float Vz(void) const;
  gui::DataPlot1D *GetZPlot();
  gui::DataPlot1D *GetVzPlot();

private:
  sensor::UsRangeFinder *us;
  filter::ButterworthLowPass *pbas_z, *pbas_vz;
  filter::EulerDerivative *vz_euler;
  gui::DataPlot1D *vz_plot;
};
} // end namespace meta
} // end namespace flair
#endif // METAUSRANGEFINDER_H
