// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/27
//  filename:   Gui.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant une Gui
//
/*********************************************************************/

#ifndef GUI_H
#define GUI_H

#include <Object.h>
#include <EDriverTypes.h>
#include <vector3d.h>

namespace irr {
class IrrlichtDevice;
namespace video {
class ITexture;
}
namespace scene {
class IAnimatedMesh;
class ISceneManager;
}
}

namespace flair {
namespace core {
class Object;
class Vector3D;
class Euler;
class Quaternion;
}
}

class Gui_impl;
class Simulator_impl;
class Model_impl;

namespace flair {
namespace simulator {
class Simulator;

class Gui : public core::Object {
  friend class ::Simulator_impl;
  friend class VisualizationCamera;

public:
  Gui(const Simulator *parent, std::string name, int app_width, int app_height,
      int scene_width, int scene_height, std::string media_path,
      irr::video::E_DRIVER_TYPE driver_type = irr::video::EDT_OPENGL);
  ~Gui();
  irr::core::vector3df getRotation(void) const;
  irr::video::ITexture *getTexture(std::string filename) const;
  irr::scene::IAnimatedMesh *getMesh(std::string filename) const;
  irr::scene::ISceneManager *getSceneManager(void) const;
  irr::IrrlichtDevice *getDevice(void) const;
  float getAspectRatio(void) const;

protected:
  void setMesh(std::string file,
               irr::core::vector3df position = irr::core::vector3df(0, 0, 0),
               irr::core::vector3df rotation = irr::core::vector3df(0, 0, 0),
               irr::core::vector3df scale = irr::core::vector3df(1, 1, 1));

private:
  Gui_impl *pimpl_;
};

/*!
* \brief get Gui
*
* \return the Gui
*/
Gui *getGui(void);

bool noGui(void);

bool isGlExtensionSupported(
    const std::string &ext); // check if a extension is supported

/*!
* \brief Convert to irrlicht scale
*
* \param value value in simulator scale
*
* \return value in irrlicht scale
*/
float ToIrrlichtScale(float value);

/*!
* \brief Convert to simulator scale
*
* \param value value in irrlicht scale
*
* \return value in simulator scale
*/
float ToSimulatorScale(float value);

/*!
* \brief Convert to irrlicht coordinates
*
* irrlicht is left handed and as a different scale
*
* \param vect vector in simulator coordinates
*
* \return vector in irrlicht coordinates
*/
irr::core::vector3df ToIrrlichtCoordinates(irr::core::vector3df vect);

/*!
* \brief Convert to irrlicht coordinates
*
* irrlicht is left handed and as a different scale
*
* \param vect vector in simulator coordinates
*
* \return vector in irrlicht coordinates
*/
irr::core::vector3df ToIrrlichtCoordinates(core::Vector3D vect);

/*!
* \brief Convert to simulator coordinates
*
* irrlicht is left handed and as a different scale
*
* \param vect vector in irrlicht coordinates
*
* \return vector in simulator coordinates
*/
core::Vector3D ToSimulatorCoordinates(irr::core::vector3df vect);

/*!
* \brief Convert to irrlicht orientation
*
* irrlicht is left handed
*
* \param quat quaternion in simulator frame
*
* \return quaternion in irrlicht frame
*/
core::Quaternion ToIrrlichtOrientation(core::Quaternion quat);

} // end namespace simulator
} // end namespace flair
#endif // GUI_H
