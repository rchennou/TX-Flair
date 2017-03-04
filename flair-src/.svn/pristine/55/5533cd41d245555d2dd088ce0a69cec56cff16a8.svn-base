// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/03/07
//  filename:   SimuCameraGL.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//              pbo code from Song Ho Ahn (song.ahn@gmail.com)
//
//  version:    $Id: $
//
//  purpose:    Class for a simulation camera
//
//
/*********************************************************************/
#ifdef GL

#include "SimuCameraGL.h"
#include "Model.h"
#include <SharedMem.h>
#include <TabWidget.h>
#include <Tab.h>
#include <DoubleSpinBox.h>
#include <Vector3DSpinBox.h>
#include <Gui.h>
#include <Euler.h>

#include <ISceneManager.h>
#include <ICameraSceneNode.h>
#include <IVideoDriver.h>

#define PBO_COUNT 2

using namespace irr;
using namespace irr::scene;
using namespace irr::core;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::simulator;

namespace flair {
namespace sensor {

SimuCameraGL::SimuCameraGL(const Model *parent, std::string name, int width,
                           int height, int x, int y, int dev_id)
    : SimuCamera(parent, name, width, height, 3, dev_id), SensorGL(parent) {
  smgr = getGui()->getSceneManager();
  camera = smgr->addCameraSceneNode();
  camera->addAnimator(this);
  camera->setAspectRatio(4.0f / 3.0f); // on force a cause du view port

  this->width = width;
  this->height = height;
  this->x = x;
  this->y = y;

  index = 0;

  buffer = (char *)malloc(width * height * 3);

  // user interface
  Tab *setup_tab = new Tab(parent->GetTabWidget(), name);
  position = new Vector3DSpinBox(setup_tab->NewRow(), "position", -2, 2, .01);
  direction = new Vector3DSpinBox(setup_tab->NewRow(), "direction", -2, 2, .01);
  up = new Vector3DSpinBox(setup_tab->NewRow(), "up", -2, 2, .01);
  fov = new DoubleSpinBox(setup_tab->NewRow(), "fov:", 0, 180, 5);

  if (strcmp((char *)glGetString(GL_VENDOR),
             "Intel Open Source Technology Center") == 0) {
    Thread::Warn("disabling cameras output for Intel card (bug with PBO)\n");
    disable_output = true;
  } else {
    disable_output = false;
  }

  if (isGlExtensionSupported("GL_ARB_pixel_buffer_object")) {
    use_pbo = true;
    // create 2 pixel buffer objects, you need to delete them when program
    // exits.
    // glBufferDataARB with NULL pointer reserves only memory space.
    pboIds = (GLuint *)malloc(PBO_COUNT * sizeof(GLuint));
    glGenBuffersARB(PBO_COUNT, pboIds);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[0]);
    glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, width * height * 3, 0,
                    GL_STREAM_READ_ARB);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[1]);
    glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, width * height * 3, 0,
                    GL_STREAM_READ_ARB);

    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
  } else {
    use_pbo = false;
    Thread::Warn("GL_ARB_pixel_buffer_object is not suppoorted\n");
  }
  if (isGlExtensionSupported("GL_PACK_INVERT_MESA")) {
    invert_pixel = false;
    Thread::Warn("GL_PACK_INVERT_MESA is suppoorted\n");
  } else {
    invert_pixel = true;
  }
}

SimuCameraGL::~SimuCameraGL() {
  free(buffer);

  if (use_pbo) {
    glDeleteBuffersARB(PBO_COUNT, pboIds);
    free(pboIds);
  }
}

void SimuCameraGL::setNearValue(float zn) { camera->setNearValue(zn); }

void SimuCameraGL::setFarValue(float zf) { camera->setFarValue(zf); }

void SimuCameraGL::UpdateFrom(const io_data *data) {
  if (noGui() == false && data == NULL) {
    smgr->setActiveCamera(camera);
    smgr->getVideoDriver()->setViewPort(rect<s32>(x, y, x + width, y + height));
    smgr->drawAll();
    // use_pbo=false;
    getImage();
  }
}

void SimuCameraGL::getImage(void) {
  if (disable_output)
    return;
  // convert from irrlicht top left origin to gl bottom left origin
  int y = smgr->getVideoDriver()->getScreenSize().Height - height - this->y;

  // We want to read the front buffer to get the latest render finished.
  Time a = GetTime();
  glReadBuffer(GL_FRONT);
  if (use_pbo) // with PBO
  {
    // increment current index first then get the next index
    // "index" is used to read pixels from a framebuffer to a PBO
    // "nextIndex" is used to process pixels in the other PBO
    index = (index + 1) % PBO_COUNT;
    int nextIndex = (index + 1) % PBO_COUNT;

    // copy pixels from framebuffer to PBO
    // Use offset instead of pointer.
    // OpenGL should perform asynch DMA transfer, so glReadPixels() will return
    // immediately.
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[index]);
    glReadPixels(x, y, width, height, GL_BGR, GL_UNSIGNED_BYTE, 0);

    // map the PBO that contain framebuffer pixels before processing it
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pboIds[nextIndex]);
    GLubyte *src = (GLubyte *)glMapBufferARB(
        GL_PIXEL_PACK_BUFFER_ARB, GL_READ_WRITE_ARB); // GL_READ_ONLY_ARB);
    if (src) {
      putImage((char *)src);
      glUnmapBufferARB(
          GL_PIXEL_PACK_BUFFER_ARB); // release pointer to the mapped buffer
    }
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
  } else {
    glReadPixels(x, y, width, height, GL_BGR, GL_UNSIGNED_BYTE, buffer);
    putImage(buffer);
  }

  glReadBuffer(GL_BACK);
  Time b = GetTime();
  Time c = b - a;
  // printf("%s %f\n",Thread::ObjectName().c_str(),(float)(c/1000000.));
}

void SimuCameraGL::putImage(char *buf) {
  if (invert_pixel == true) {
    // opengl images are horizontally flipped, so we have to fix that here.
    const s32 pitch = width * 3;
    char *pixels = buf;
    char *p2 = pixels + (height - 1) * pitch;
    char *tmpBuffer = new char[pitch];
    for (int i = 0; i < height; i += 2) {
      memcpy(tmpBuffer, pixels, pitch);
      memcpy(pixels, p2, pitch);
      memcpy(p2, tmpBuffer, pitch);
      pixels += pitch;
      p2 -= pitch;
    }
    delete[] tmpBuffer;
  }

  shmem->Write(buf, width * height * 3);
}

void SimuCameraGL::animateNode(ISceneNode *node, u32 timeMs) {
  ICameraSceneNode *camera = static_cast<ICameraSceneNode *>(node);

  matrix4 m;
  m.setRotationDegrees(Node()->getRotation());

  // transform forward vector of camera
  vector3df frv = ToIrrlichtCoordinates(direction->Value());
  m.transformVect(frv);

  // transform upvector of camera
  vector3df upv = ToIrrlichtCoordinates(up->Value());
  m.transformVect(upv);

  // transform camera offset (thanks to Zeuss for finding it was missing)
  vector3df offset = ToIrrlichtCoordinates(position->Value());
  m.transformVect(offset);

  // set camera
  camera->setPosition(Node()->getPosition() +
                      offset); // position camera in front of the ship
  camera->setUpVector(upv);    // set up vector of camera >> Zeuss - tested with
  // +node->getPostion() and it didnt work, but this
  // works fine.
  camera->setTarget(Node()->getPosition() + offset + frv); // set target of
                                                           // camera (look at
                                                           // point) >> Zeuss -
                                                           // Dont forget to add
                                                           // the node positiob

  camera->setFOV(Euler::ToRadian(fov->Value()));
}

ISceneNodeAnimator *SimuCameraGL::createClone(ISceneNode *node,
                                              ISceneManager *newManager) {
  return NULL;
}

} // end namespace sensor
} // end namespace flair
#endif
