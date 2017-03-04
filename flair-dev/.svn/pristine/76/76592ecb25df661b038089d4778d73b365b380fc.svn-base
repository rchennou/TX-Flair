// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file V4LCamera.h
 * \brief Base class for V4l camera
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/07/17
 * \version 4.0
 */

#ifndef V4LCamera_H
#define V4LCamera_H

#include <Thread.h>
#include "Camera.h"
#include <highgui.h>

namespace flair {
namespace core {
class cvimage;
class FrameworkManager;
}
namespace gui {
class GridLayout;
class DoubleSpinBox;
class CheckBox;
class Label;
}
}

namespace flair {
namespace sensor {
/*! \class V4LCamera
*
* \brief Base class for V4l camera
*/
class V4LCamera : public core::Thread, public Camera {
public:
  /*!
  * \brief Constructor
  *
  * Construct a Camera.
  *
  * \param parent parent
  * \param name name
  * \param camera_index camera index
  * \param width width
  * \param height height
  * \param format image format
  * \param priority priority of the Thread
  */
  V4LCamera(const core::FrameworkManager *parent, std::string name,
            uint8_t camera_index, uint16_t width, uint16_t height,
            core::cvimage::Type::Format format, uint8_t priority);

  /*!
  * \brief Destructor
  *
  */
  ~V4LCamera();

protected:
  /*!
  * \brief Set Gain
  *
  * \param value value between 0 and 1
  */
  virtual void SetGain(float value);

  /*!
  * \brief Set Auto Gain
  *
  * \param value value
  */
  virtual void SetAutoGain(bool value);

  /*!
  * \brief Set Exposure
  *
  * \param value value between 0 and 1
  */
  virtual void SetExposure(float value);

  /*!
  * \brief Set Auto Exposure
  *
  * \param value value
  */
  virtual void SetAutoExposure(bool value);

  /*!
  * \brief Set Brightness
  *
  * \param value value between 0 and 1
  */
  virtual void SetBrightness(float value);

  /*!
  * \brief Set Saturation
  *
  * \param value value between 0 and 1
  */
  virtual void SetSaturation(float value);

  /*!
  * \brief Set Hue
  *
  * \param value value between 0 and 1
  */
  virtual void SetHue(float value);

  /*!
  * \brief Set Contrast
  *
  * \param value value between 0 and 1
  */
  virtual void SetContrast(float value);

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);

  CvCapture *capture;

  gui::Tab *sensor_tab;
  gui::DoubleSpinBox *bright, *exposure, *gain, *contrast, *hue, *sharpness,
      *sat;
  gui::CheckBox *autogain, *awb, *autoexposure;
  gui::Label *fps;
};
} // end namespace sensor
} // end namespace flair
#endif // V4LCamera_H
