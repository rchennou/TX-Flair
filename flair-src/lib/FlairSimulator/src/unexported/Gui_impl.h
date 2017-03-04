// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/27
//  filename:   Gui_impl.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant une Gui
//
/*********************************************************************/

#ifndef GUI_IMPL_H
#define GUI_IMPL_H

#include <string>
#include <vector>
#include <io_hdfile.h>
#include <EDriverTypes.h>
#include <vector3d.h>

namespace irr {
class IrrlichtDevice;
namespace scene {
class ISceneManager;
class IMeshSceneNode;
class ITriangleSelector;
}
namespace video {
class IVideoDriver;
}
namespace gui {
class IGUIFont;
class IGUIEnvironment;
}
}

namespace flair {
namespace core {
class Object;
}
namespace simulator {
class Model;
class GenericObject;
class Gui;
class VisualizationCamera;
}
}

class MyEventReceiver;

class Gui_impl {
public:
  Gui_impl(flair::simulator::Gui *self, int app_width, int app_height,
           int scene_width, int scene_height, std::string media_path,
           irr::video::E_DRIVER_TYPE driver_type = irr::video::EDT_OPENGL);
  ~Gui_impl();
  void RunGui(std::vector<flair::simulator::Model *> models,
              std::vector<flair::simulator::GenericObject *> objects);
  void setMesh(std::string file,
               irr::core::vector3df position = irr::core::vector3df(0, 0, 0),
               irr::core::vector3df rotation = irr::core::vector3df(0, 0, 0),
               irr::core::vector3df scale = irr::core::vector3df(1, 1, 1));

  irr::scene::IMeshSceneNode *node;
  irr::IrrlichtDevice *device;
  std::string media_path;
  irr::video::IVideoDriver *driver;
  irr::scene::ISceneManager *smgr;
  int scene_width, scene_height;
  void AddVisualizationCamera(flair::simulator::VisualizationCamera* camera);

private:
  MyEventReceiver *receiver;
  irr::scene::ITriangleSelector *selector;
  irr::gui::IGUIFont *font;
  irr::gui::IGUIEnvironment *env;
  void setWindowCaption(int cam_id, int fps);
  void takeScreenshot(void);
  hdfile_t *dbtFile_r, *dbtFile_w;
  size_t dbtSize(std::vector<flair::simulator::Model *> modeles);
  char *dbtbuf;
  flair::simulator::Gui *self;
  std::vector<flair::simulator::VisualizationCamera *> cameras;
  flair::simulator::Model *getModelFromVisualizationCamera(std::vector<flair::simulator::Model *> models,flair::simulator::VisualizationCamera *camera);
};

#endif // GUI_IMPL_H
