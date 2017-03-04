// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/27
//  filename:   Gui.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant une Gui
//
/*********************************************************************/
#ifdef GL

#include "Gui_impl.h"
#include "Gui.h"
#include "Simulator.h"
#include "GenericObject.h"
#include "Model.h"
#include "Model_impl.h"
#include <Object.h>
#include <Euler.h>
#include <irrlicht.h>
#include <unistd.h>
#include <sstream>

using namespace irr;
using namespace irr::video;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;
using namespace flair::core;
using namespace flair::simulator;

class MyEventReceiver : public IEventReceiver {
public:
  // This is the one method that we have to implement
  bool OnEvent(const SEvent &event) {
    // Remember whether each key is down or up
    if (event.EventType == EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    if (model)
      return model->OnEvent(event);

    return false;
  }

  // This is used to check whether a key is being held down
  bool IsKeyDown(EKEY_CODE keyCode) {
    if (KeyIsDown[keyCode] == true) {
      KeyIsDown[keyCode] = false;
      return true;
    } else {
      return false;
    }
  }

  MyEventReceiver(void) {
    model = NULL;
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  }
  void SetModel(Model *model) { this->model = model; }

private:
  // We use this array to store the current state of each key
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
  Model *model;
};

Gui_impl::Gui_impl(Gui *self, int app_width, int app_height, int scene_width,
                   int scene_height, std::string media_path,
                   E_DRIVER_TYPE driver_type) {
  this->self = self;
  dbtFile_w = NULL;
  dbtFile_r = NULL;
  this->media_path = media_path;
  this->scene_width = scene_width;
  this->scene_height = scene_height;

  device = createDevice(driver_type, dimension2d<u32>(app_width, app_height),
                        16, false, false, false);
  receiver = new MyEventReceiver();
  device->setEventReceiver(receiver);
  device->getLogger()->setLogLevel(ELL_NONE);

  device->getCursorControl()->setVisible(false);
  device->setResizable(false);

  // font = device->getGUIEnvironment()->getBuiltInFont();
  driver = device->getVideoDriver();
  smgr = device->getSceneManager();

  smgr->setAmbientLight(video::SColorf(1, 1, 1));

  /*
env = device->getGUIEnvironment();
IGUISkin* skin = env->getSkin();
  font = env->getFont("./fonthaettenschweiler.bmp");

  if (font)
          skin->setFont(font);

  // create menu

  IGUIContextMenu* menu = env->addMenu();
  menu->setMinSize(core::dimension2du(640,20));
  menu->addItem(L"File", -1, true, true);
  menu->addItem(L"View", -1, true, true);
  menu->addItem(L"Camera", -1, true, true);
  menu->addItem(L"Help", -1, true, true);

  // disable alpha

  for (s32 i=0; i<gui::EGDC_COUNT ; ++i)
  {
          video::SColor col =
env->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
          col.setAlpha(255);
          env->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
  }
   */
}

Gui_impl::~Gui_impl() {
  // printf("del Gui_impl\n");
  device->drop();

  delete receiver;
  // printf("del Gui_impl ok\n");
}

void Gui_impl::AddVisualizationCamera(VisualizationCamera* camera) {
  cameras.push_back(camera);
}

void Gui_impl::setMesh(std::string file, vector3df position, vector3df rotation,
                       vector3df scale) {
  IAnimatedMesh *mesh = smgr->getMesh(file.c_str());

  if (!mesh) {
    // model could not be loaded
    self->Err("Model %s could not be loaded\n", file.c_str());
    return;
  }

  node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
  node->setPosition(position);
  rotation +=
      irr::core::vector3df(90, 0, Euler::ToDegree(getSimulator()->Yaw()));
  node->setRotation(rotation);
  for (int i = 0; i < node->getMaterialCount(); i++) {
    node->getMaterial(i).TextureLayer->TextureWrapU = video::ETC_REPEAT;
    node->getMaterial(i).TextureLayer->TextureWrapV = video::ETC_REPEAT;
  }
  // Ceillig
  // node->getMaterial(0).getTextureMatrix(0).setTextureScale(scale.X/2.0,scale.Z/2.0);
  // Walls
  node->getMaterial(1).getTextureMatrix(0).setTextureScale(1 / (scale.Y / 2.5),
                                                           1 / (scale.Z / 2.5));
  // Floor
  node->getMaterial(2).getTextureMatrix(0).setTextureScale(
      1 / (scale.X / 20.0), 1 / (scale.Z / 20.0));

  node->setScale(scale);
  // selector
  selector = smgr->createOctreeTriangleSelector(node->getMesh(), node, 128);
  node->setTriangleSelector(selector);
}

void Gui_impl::RunGui(std::vector<Model *> models,
                      std::vector<GenericObject *> objects) {
  int lastFPS = -1;
  int cam_id = 0;

  receiver->SetModel(models.at(0));

  for (size_t i = 0; i < models.size(); i++) {
    models.at(i)->Draw();
  }

  for (size_t i = 0; i < models.size(); i++) {
    models.at(i)->pimpl_->MetaTriangleSelector()->addTriangleSelector(selector);
    for (size_t j = 0; j < objects.size(); j++) {
      models.at(i)->pimpl_->MetaTriangleSelector()->addTriangleSelector(
          objects.at(j)->TriangleSelector());
    }
    for (size_t j = 0; j < models.size(); j++) {
      if (i == j) continue;
      models.at(i)->pimpl_->MetaTriangleSelector()->addTriangleSelector(
          models.at(j)->pimpl_->TriangleSelector());
    }
  }

  selector->drop(); // As soon as we're done with the selector, drop it.*/

  // wait all models to be started
  for (size_t i = 0; i < models.size(); i++) {
    models.at(i)->pimpl_->SynchronizationPoint();
  }

  setWindowCaption(0, 0);

  while (device->run()) {
    if (dbtFile_r != NULL) // rejeu
    {
      takeScreenshot(); // on enregistre l'image precedente
      road_time_t time;
      road_timerange_t tr = 0;
      if (read_hdfile(dbtFile_r, (void *)dbtbuf, &time, &tr) != 0) {
        vector3df vect;
        char *buf = dbtbuf;
        for (size_t i = 0; i < models.size(); i++) {
          models.at(i)->ReaddbtBuf(buf);
          buf += models.at(i)->dbtSize();
        }
      } else {
        // Printf("fin play\n");
        close_hdfile(dbtFile_r);
        dbtFile_r = NULL;
        free(dbtbuf);
        for (size_t i = 0; i < models.size(); i++) {
          models.at(i)->pimpl_->Resume();
        }
      }
    } else // mode normal
    {
      for (size_t i = 0; i < models.size(); i++) {
        models.at(i)->pimpl_->UpdatePos();
      }
    }

    driver->beginScene(true, true, video::SColor(255, 200, 200, 200));

    // vue poursuite
    //smgr->setActiveCamera(models.at(cam_id)->getFollowMeCamera()->getCameraSceneNode());
    smgr->setActiveCamera(cameras.at(cam_id)->getCameraSceneNode());
    driver->setViewPort(core::rect<s32>(0, 0, scene_width, scene_height));
    smgr->drawAll(); // commente voir plus bas
                     /*
                 env->drawAll();
                 if (font)
                 {
                                     font->draw(L"This demo shows that Irrlicht is also capable
                 of drawing 2D graphics.",
                                             core::rect<s32>(130,10,300,50),
                                             video::SColor(255,255,255,255));
                 }
                 else
                 {
                 printf("err\n");
                 }
                 device->setWindowCaption(L"toto");*/

    if (dbtFile_r == NULL) // mode normal
    {
      for (size_t i = 0; i < models.size(); i++) {
        models.at(i)->pimpl_->CheckCollision();
      }
    }

    for (size_t i = 0; i < models.size(); i++) {
      models.at(i)->ProcessUpdate(NULL);
    }

    // on fait ca ici, devrait etre un peu plus haut
    // mais a priori souci avec models.at(i)->pimpl_->CheckCollision();
    // (setelipsoid?)
    //smgr->setActiveCamera(models.at(cam_id)->getFollowMeCamera()->getCameraSceneNode());
    smgr->setActiveCamera(cameras.at(cam_id)->getCameraSceneNode());
    driver->setViewPort(core::rect<s32>(0, 0, scene_width, scene_height));
    smgr->drawAll();

    driver->endScene();

    int fps = driver->getFPS();

    if (lastFPS != fps) {
      setWindowCaption(cam_id, fps);
      lastFPS = fps;
    }

    if (receiver->IsKeyDown(KEY_PRIOR)) {
      cam_id++;
      if (cam_id >= (int)cameras.size()) cam_id = 0;
      receiver->SetModel(getModelFromVisualizationCamera(models,cameras.at(cam_id)));
      setWindowCaption(cam_id, fps);
    }
    if (receiver->IsKeyDown(KEY_NEXT)) {
      cam_id--;
      if (cam_id < 0) cam_id = cameras.size() - 1;
      receiver->SetModel(getModelFromVisualizationCamera(models,cameras.at(cam_id)));
      setWindowCaption(cam_id, fps);
    }

    // enregistrement DBT
    if (receiver->IsKeyDown(KEY_KEY_R) && dbtFile_w == NULL) {
      dbtFile_w = inithdFile((char *)"./record.dbt", UAV, dbtSize(models));
      dbtbuf = (char *)malloc(dbtSize(models));
    }
    if (receiver->IsKeyDown(KEY_KEY_S) && dbtFile_w != NULL) {
      close_hdfile(dbtFile_w);
      dbtFile_w = NULL;
      free(dbtbuf);
      // rt_printf("stop rec\n");
    }
    if (dbtFile_w != NULL) {
      Time time = GetTime();
      vector3df vect;
      char *buf = dbtbuf;

      for (size_t i = 0; i < models.size(); i++) {
        models.at(i)->WritedbtBuf(buf);
        buf += models.at(i)->dbtSize();
      }

      write_hdfile(dbtFile_w, dbtbuf, (road_time_t)(time / 1000),
                   (road_timerange_t)(time % 1000), dbtSize(models));
    }

    // lecture dbt
    if (receiver->IsKeyDown(KEY_KEY_P) && dbtFile_r == NULL) {
      dbtFile_r = open_hdfile((char *)"./record.dbt", READ_MODE);
      dbtbuf = (char *)malloc(dbtSize(models));
      // on suspend les models pour ne pas interferer
      for (size_t i = 0; i < models.size(); i++) {
        models.at(i)->pimpl_->Suspend();
      }
    }
    if (receiver->IsKeyDown(KEY_KEY_S) && dbtFile_r != NULL) {
      // rt_printf("stop play\n");
      close_hdfile(dbtFile_r);
      dbtFile_r = NULL;
      free(dbtbuf);
      // on resume les models
      for (size_t i = 0; i < models.size(); i++) {
        models.at(i)->pimpl_->Resume();
      }
    }
  }

  receiver->SetModel(NULL);
}

Model *Gui_impl::getModelFromVisualizationCamera(std::vector<Model *> models,VisualizationCamera *camera) {
  for (size_t i = 0; i < models.size(); i++) {
      if(models.at(i)->getFollowMeCamera()==camera) return models.at(i);
  }
  return NULL;
}

void Gui_impl::setWindowCaption(int cam_id, int fps) {
  std::ostringstream text;

  text << "Cam: " << cameras.at(cam_id)->getName().c_str()
     << ", FPS: " << fps;

  device->setWindowCaption(stringw(text.str().c_str()).c_str());
}

void Gui_impl::takeScreenshot(void) {
  static int cpt = 0;
  // get image from the last rendered frame
  IImage *const image = driver->createScreenShot();
  if (image) // should always be true, but you never know. ;)
  {
    // construct a filename, consisting of local time and file extension
    c8 filename[64];
    // snprintf(filename, 64, "screenshot_%u.png",
    // device->getTimer()->getRealTime());
    snprintf(filename, 64, "screenshot_%u.png", cpt);
    cpt++;
    // write screenshot to file
    if (!driver->writeImageToFile(image, filename))
      device->getLogger()->log(L"Failed to take screenshot.", ELL_WARNING);

    // Don't forget to drop image since we don't need it anymore.
    image->drop();
  }
}

size_t Gui_impl::dbtSize(std::vector<Model *> models) {
  size_t size = 0;
  for (size_t i = 0; i < models.size(); i++) {
    size += models.at(i)->dbtSize();
  }

  return size;
}
#endif // GL
