// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file SimuCameraGL.h
 * \brief Class for a simulation camera
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/03/07
 * \version 3.4
 */

#ifndef SIMUCAMERAGL_H
#define SIMUCAMERAGL_H

#include <SimuCamera.h>
#include <SensorGL.h>
#include <ISceneNodeAnimator.h>

// in order to get function prototypes from glext.h, define GL_GLEXT_PROTOTYPES
// before including glext.h
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

namespace irr {
namespace scene {
class ICameraSceneNode;
}
}

namespace flair {
namespace gui {
class DoubleSpinBox;
class Vector3DSpinBox;
}
namespace simulator {
class Model;
}
}

namespace flair {
namespace sensor {
/*! \class SimuCameraGL
* \brief Class for a simulation camera
*
*/
class SimuCameraGL : public SimuCamera,
                     public SensorGL,
                     public irr::scene::ISceneNodeAnimator {
public:
  // top left origin
  SimuCameraGL(const simulator::Model *parent, std::string name, int width,
               int height, int x, int y, int dev_id);
  ~SimuCameraGL();
  //! Sets the value of the near clipping plane. (default: 1.0f)
  /** \param zn: New z near value. */
  void setNearValue(float zn);

  //! Sets the value of the far clipping plane (default: 2000.0f)
  /** \param zf: New z far value. */
  void setFarValue(float zf);

private:
  void UpdateFrom(const core::io_data *data);
  void animateNode(irr::scene::ISceneNode *node, irr::u32 timeMs);
  ISceneNodeAnimator *createClone(irr::scene::ISceneNode *node,
                                  irr::scene::ISceneManager *newManager = 0);
  void getImage(void);
  void putImage(char *pixels);
  irr::scene::ICameraSceneNode *camera;
  irr::scene::ISceneManager *smgr;
  gui::Vector3DSpinBox *position, *direction, *up;
  gui::DoubleSpinBox *fov;
  int width, height, x, y;
  char *buffer;
  bool use_pbo, invert_pixel, disable_output;
  GLuint *pboIds;
  int index;
};
} // end namespace simulator
} // end namespace flair
#endif // SIMUCAMERAGL_H
