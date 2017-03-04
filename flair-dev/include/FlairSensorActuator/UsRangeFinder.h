// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file UsRangeFinder.h
 * \brief Base class for UsRangeFinder
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/22
 * \version 4.0
 */

#ifndef USRANGEFINDER_H
#define USRANGEFINDER_H

#include <IODevice.h>

namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class Tab;
class TabWidget;
class GroupBox;
class Layout;
class DataPlot1D;
}
}

namespace flair {
namespace sensor {
/*! \class UsRangeFinder
*
* \brief Base class for UsRangeFinder
*
* Use this class to define a custom UsRangeFinder.
*
*/
class UsRangeFinder : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a UsRangeFinder. Control part.
  *
  * \param parent parent
  * \param name name
  */
  UsRangeFinder(const core::FrameworkManager *parent, std::string name);

  /*!
  * \brief Constructor
  *
  * Construct a UsRangeFinder. Simulation part.
  *
  * \param parent parent
  * \param name name
  */
  UsRangeFinder(const core::IODevice *parent, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~UsRangeFinder();

  /*!
  * \brief Lock user interface
  *
  */
  void LockUserInterface(void) const;

  /*!
  * \brief Unlock user interface
  *
  */
  void UnlockUserInterface(void) const;

  /*!
  * \brief Use default plot
  *
  * Should no be used for the simulation part.
  */
  void UseDefaultPlot(void);

  /*!
  * \brief Plot
  *
  * \return DataPlot1D
  */
  gui::DataPlot1D *GetPlot(void) const;

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
  gui::DataPlot1D *plot;
  gui::Tab *plot_tab;
};
} // end namespace sensor
} // end namespace flair
#endif // USRANGEFINDER_H
