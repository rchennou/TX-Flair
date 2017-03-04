// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file DataPlot1D.h
 * \brief Class displaying a 1D plot on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef DATAPLOT1D_H
#define DATAPLOT1D_H

#include <DataPlot.h>
#include <stdint.h>

namespace flair {
namespace core {
class IODataElement;
}

namespace gui {

class LayoutPosition;

/*! \class DataPlot1D
*
* \brief Class displaying a 1D plot on the ground station
*
*/
class DataPlot1D : private DataPlot {
public:
  /*!
  * \brief Constructor
  *
  * Construct a 1D plot at given position.
  *
  * \param position position to display the plot
  * \param name name
  * \param ymin default ymin of the plot
  * \param ymax default ymax of the plot
  */
  DataPlot1D(const LayoutPosition *position, std::string name, float ymin,
             float ymax);

  /*!
  * \brief Destructor
  *
  */
  ~DataPlot1D();

  /*!
  * \brief Add a curve from an IODataElement to the plot.
  *
  * Curve's color can be selected by its name.
  *
  * \param element element to plot
  * \param color color of the curve
  * \param curve_name name of the curve for the legend, if unspecified,
  *element->ObjectName() will be used
  */
  void AddCurve(const core::IODataElement *element, Color_t color,
                std::string curve_name = "");

  /*!
  * \brief Add a curve from an IODataElement to the plot.
  *
  * Curve's color can be selected by its RGB components.
  *
  * \param element element to plot
  * \param r red component of the curve
  * \param g green component of the curve
  * \param b blue component of the curve
  * \param curve_name name of the curve for the legend, if unspecified,
  *element->ObjectName() will be used
  */
  void AddCurve(const core::IODataElement *element, uint8_t r = 255,
                uint8_t g = 0, uint8_t b = 0, std::string curve_name = "");
};

} // end namespace gui
} // end namespace flair

#endif // DATAPLOT1D_H
