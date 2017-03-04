// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file DataPlot.h
 * \brief Abstract class to display plots on ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/10
 * \version 4.0
 */

#ifndef DATAPLOT_H
#define DATAPLOT_H

#include <SendData.h>

class DataPlot_impl;

namespace flair {
namespace core {
class IODataElement;
}
}
namespace flair {
namespace gui {
class LayoutPosition;

/*! \class DataPlot
*
* \brief Abstract class to display plots on ground station
*
*/
class DataPlot : public SendData {
public:
  /*!
  \enum Color_t
  \brief Types of colors
  */
  typedef enum {
    Red /*! red  */,
    Blue /*! blue  */,
    Green /*! green  */,
    Yellow /*! yellow  */,
    Black /*! black  */,
    White /*! white  */,
  } Color_t;

  /*!
  * \brief Constructor
  *
  * Type must agree with predifined (hard coded) types
  * in ground station code. After calling this constructor,
  * position will be deleted as it is no longer usefull.
  * The DataPlot will automatically be child of position->getLayout() Layout.
  *
  * \param position position
  * \param name nom
  * \param type type
  */
  DataPlot(const LayoutPosition *position, std::string name, std::string type);

  /*!
  * \brief Destructor
  *
  */
  ~DataPlot();

protected:
  /*!
  * \brief Add an IODataElement to the plot.
  *
  * This method registers element for sending.
  *
  * \param element element to plot
  */
  void AddDataToSend(const core::IODataElement *element);

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

  class DataPlot_impl *pimpl_;
};

/*!
* \brief Get RGB components from color type
*
*
* \param color input color
* \param r output component
* \param g output component
* \param b output component
*/
void RGBFromColor(DataPlot::Color_t color, uint8_t &r, uint8_t &g, uint8_t &b);

} // end namespace gui
} // end namespace flair

#endif // DATAPLOT_H
