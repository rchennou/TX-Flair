// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Camera.h
 * \brief Base class for Camera
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/03/06
 * \version 4.0
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <IODevice.h>
#include <stdint.h>
#include <cvimage.h>

namespace flair {
namespace gui {
class GroupBox;
class Tab;
class TabWidget;
class Picture;
class GridLayout;
}
}

namespace flair {
namespace sensor {
/*! \class Camera
*
* \brief Base class for Camera
*
* Use this class to define a custom Camera.
*
*/
class Camera : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Camera.
  *
  * \param parent parent
  * \param name name
  * \param width width
  * \param height height
  * \param format image format
  */
  Camera(const core::FrameworkManager *parent, std::string name, uint16_t width,
         uint16_t height, core::cvimage::Type::Format format);

  /*!
  * \brief Constructor
  *
  * Construct a Camera. \n
  * This contructor must only be called for a simulated device.
  *
  * \param parent parent
  * \param name name
  */
  Camera(const core::IODevice *parent, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~Camera();

  /*!
  * \brief Use default plot
  *
  * \param image image to display
  */
  void UseDefaultPlot(const core::cvimage *image);

  /*!
  * \brief get Layout
  *
  * \return a Layout available
  */
  gui::GridLayout *GetLayout(void) const;

  /*!
  * \brief plot tab
  *
  * \return plot tab
  */
  gui::Tab *GetPlotTab(void) const;

  /*!
  * \brief Save picture to file
  *
  * \param filename filename
  */
  void SaveToFile(std::string filename) const;

  /*!
  * \brief Width
  *
  * \return width
  */
  uint16_t Width(void) const;

  /*!
  * \brief Height
  *
  * \return height
  */
  uint16_t Height(void) const;

  /*!
 * \brief Output matrix
 *
 * Output matrix is of the same size as declared in constructor. \n
 *
 * \return the output matrix
 */
  core::cvimage *Output(void);

  core::DataType const &GetOutputDataType() const;

protected:
  /*!
  * \brief get GroupBox
  *
  * \return a GroupBox available
  */
  gui::GroupBox *GetGroupBox(void) const;

  core::cvimage *output;

private:
  gui::Tab *main_tab, *sensor_tab, *plot_tab;
  gui::TabWidget *tab;
  gui::GroupBox *setup_groupbox;
  gui::GridLayout *setup_layout;
};
} // end namespace sensor
} // end namespace flair
#endif // CAMERA_H
