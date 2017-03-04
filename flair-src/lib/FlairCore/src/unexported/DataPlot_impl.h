// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file DataPlot_impl.h
 * \brief Classe de base pour les gprahes
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/10
 * \version 4.0
 */

#ifndef DATAPLOT_IMPL_H
#define DATAPLOT_IMPL_H

#include <vector>

namespace flair {
namespace core {
class IODataElement;
}
}

/*! \class DataPlot_impl
* \brief Classe de base pour les graphes
*
*/
class DataPlot_impl {
public:
  DataPlot_impl();
  ~DataPlot_impl();

  std::vector<const flair::core::IODataElement *> tosend;
};

#endif // DATAPLOT_IMPL_H
