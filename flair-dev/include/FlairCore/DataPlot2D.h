// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file DataPlot2D.h
 * \brief Class displaying a 2D plot on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/10/07
 * \version 4.0
 */

#ifndef DATAPLOT2D_H
#define DATAPLOT2D_H

#include <DataPlot.h>
#include <stdint.h>

namespace flair {
namespace core {
class IODataElement;
}
}
namespace flair {
namespace gui {

class LayoutPosition;

/*! \class DataPlot2D
*
* \brief Class displaying a 2D plot on the ground station
*
*/
class DataPlot2D : private DataPlot {
public:
  /*!
  * \brief Constructor
  *
  * Construct a 2D plot at given place position.
  *
  * \param position position to display the plot
  * \param name name
  * \param x_name name of x axis
  * \param xmin default xmin of the plot
  * \param xmax default xmax of the plot
  * \param y_name name of y axis
  * \param ymin default ymin of the plot
  * \param ymax default ymax of the plot
  */
  DataPlot2D(const LayoutPosition *position, std::string name,
             std::string x_name, float xmin, float xmax, std::string y_name,
             float ymin, float ymax);

  /*!
  * \brief Destructor
  *
  */
  ~DataPlot2D();

  /*!
  * \brief Add a curve from elements to the plot.
  *
  * Curve's color can be selected by its name.
  *
  * \param x_element element to plot for x coordinate
  * \param y_element element to plot for y coordinate
  * \param color color of the curve
  * \param curve_name name of the curve ofr the legend
  */
  void AddCurve(const core::IODataElement *x_element,
                const core::IODataElement *y_element, Color_t color,
                std::string curve_name = "");

  /*!
  * \brief Add a curve from elements to the plot.
  *
  * Curve's color can be selected by its RGB components.
  *
  * \param x_element element to plot for x coordinate
  * \param y_element element to plot for y coordinate
  * \param r red component of the curve
  * \param g green component of the curve
  * \param b blue component of the curve
  * \param curve_name name of the curve ofr the legend
  */
  void AddCurve(const core::IODataElement *x_element,
                const core::IODataElement *y_element, uint8_t r = 255,
                uint8_t g = 0, uint8_t b = 0, std::string curve_name = "");
};

} // end namespace gui
} // end namespace flair

#endif // DATAPLOT2D_H
