// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file LaserRangeFinder.h
 * \brief Classe generique des telemetres laser
 * \author César RICHARD, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/07/22
 * \version 1.0
 */

#ifndef LASERRANGEFINDER_H
#define LASERRANGEFINDER_H

#include <IODevice.h>

namespace flair {
namespace core {
class FrameworkManager;
class cvmatrix;
}
namespace gui {
class Tab;
class TabWidget;
class GroupBox;
class Layout;
class RangeFinderPlot;
}
}

namespace flair {
namespace sensor {
/*! \class LaserRangeFinder
*
* \brief Classe generique intégrant les telemetres laser
*/
class LaserRangeFinder : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Laser Range Finder.
  *
  * \param parent parent
  * \param name name
  */
  LaserRangeFinder(const core::FrameworkManager *parent, std::string name);
  /*!
  * \brief Constructor
  *
  * Construct a UsRangeFinder. Simulation part.
  *
  * \param parent parent
  * \param name name
  */
  LaserRangeFinder(const core::IODevice *parent, std::string name);
  /*!
  * \brief Destructor
  *
  */
  ~LaserRangeFinder();

  /*!
  * \brief Use default plot
  *
  */
  void UseDefaultPlot(void);

  /*!
  * \brief Plot
  *
  * \return DataPlot1D
  */
  gui::RangeFinderPlot *GetPlot(void) const;

  /*!
  * \brief Setup Layout
  *
  * \return a Layout available
  */
  gui::Layout *GetLayout(void) const;

  /*!
  * \brief Plot tab
  *
  * \return plot Tab
  */
  gui::Tab *GetPlotTab(void) const;

  /*!
  * \brief Value
  *
  * \return output value
  */
  float Value(void) const;

protected:
  /*!
      * \brief Output matrix
      *
      * \return output matrix
      */
  core::cvmatrix *output;

  /*!
  * \brief Setup GroupBox
  *
  * \return a GroupBox available
  */
  gui::GroupBox *GetGroupBox(void) const;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  gui::Tab *main_tab;
  gui::TabWidget *tab;
  gui::GroupBox *setup_groupbox;
  gui::Tab *sensor_tab;
  gui::RangeFinderPlot *plot;
  gui::Tab *plot_tab;
};
} // end namespace sensor
} // end namespace framewor
#endif // LASERRANGEFINDER_H
