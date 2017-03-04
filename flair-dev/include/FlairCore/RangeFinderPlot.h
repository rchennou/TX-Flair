// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file RangeFinderPlot.h
 * \brief Class displaying a 2D plot on the ground station for laser range
 * finder like Hokuyo
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/07/23
 * \version 4.0
 */

#ifndef RANGEFINDERPLOT_H
#define RANGEFINDERPLOT_H

#include <SendData.h>
#include <stdint.h>

namespace flair {
namespace core {
class cvmatrix;
}
}

namespace flair {
namespace gui {

class LayoutPosition;

/*! \class RangeFinderPlot
*
* \brief Class displaying a 2D plot on the ground station for laser range finder
*like Hokuyo
*
*/
class RangeFinderPlot : public SendData {
public:
  /*!
  * \brief Constructor
  *
  * Construct a 2D plot at given position. \n
  * The RangeFinderPlot will automatically be child of position->getLayout()
  *Layout. After calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param position position to display the plot
  * \param name name
  * \param x_name name of x axis
  * \param xmin default xmin of the plot
  * \param xmax default xmax of the plot
  * \param y_name name of y axis
  * \param ymin default ymin of the plot
  * \param ymax default ymax of the plot
  * \param datas laser datas
  * \param start_angle start angle of the laser
  * \param end_angle end angle of the laser
  * \param nb_samples number of samples
  */
  RangeFinderPlot(const LayoutPosition *position, std::string name,
                  std::string x_name, float xmin, float xmax,
                  std::string y_name, float ymin, float ymax,
                  const core::cvmatrix *datas, float start_angle,
                  float end_angle, uint32_t nb_samples);

  /*!
  * \brief Destructor
  *
  */
  ~RangeFinderPlot();

private:
  /*!
  * \brief Copy datas to specified buffer
  *
  * Reimplemented from SendData.
  *
  * \param buf output buffer
  */
  void CopyDatas(char *buf) const;

  /*!
  * \brief Extra Xml event
  *
  * Reimplemented from SendData.
  */
  void ExtraXmlEvent(void){};

  const core::cvmatrix *datas;
};

} // end namespace gui
} // end namespace flair

#endif // RANGEFINDERPLOT_H
