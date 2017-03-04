// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   Model.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un modele a simuler
//
/*********************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include <IODevice.h>
#include <Quaternion.h>
#include <Vector3D.h>
#include <DiscreteTimeVariable.h>

#ifdef GL
#include <aabbox3d.h>
#include <IEventReceiver.h>
namespace irr {
class SEvent;
namespace scene {
class ISceneManager;
class ISceneNode;
class ITriangleSelector;
}
}
#endif

namespace flair {
namespace gui {
class TabWidget;
}
namespace sensor {
class SensorGL;
}
}

class Gui_impl;
class Simulator_impl;
class Model_impl;

namespace flair {
namespace simulator {
class Simulator;
class FollowMeCamera;

class Model : public core::IODevice
#ifdef GL
, public irr::IEventReceiver
#endif
 {
  friend class ::Gui_impl;
  friend class ::Simulator_impl;
  friend class ::Model_impl;
  friend class sensor::SensorGL;

public:
  Model(const Simulator *parent, std::string name);
  virtual ~Model();

  typedef struct simu_state {
    core::Quaternion Quat;
    core::Vector3D W;
    core::Vector3D Pos;
    core::Vector3D Vel;
  } simu_state_t;

#ifdef GL
  irr::scene::ISceneNode *getSceneNode() const;
  irr::core::aabbox3d<irr::f32> *Box() const;

  virtual size_t dbtSize(void) const = 0;
  virtual void Draw(void){};
  virtual void ExtraDraw(void){};
  virtual void WritedbtBuf(char *dbtbuf) = 0;
  virtual void ReaddbtBuf(char *dbtbuf) = 0;

  //default event handling
  bool OnEvent(const irr::SEvent &event) { return false;};

  //! Sets the value of the camera's far clipping plane (default: 2000.0f)
  /** \param zf: New z far value. */
  void setCameraFarValue(float zf);
#endif
  gui::TabWidget *GetTabWidget(void) const;

protected:
  DiscreteTimeVariable<simu_state_t, 3> state;
  float dT(void) const;
  virtual void CalcModel(void) = 0;
#ifdef GL
  FollowMeCamera *getFollowMeCamera(void) const;
  virtual void AnimateModel(void) = 0;
  // void setPosition(core::Vector3D pos);
  void setScale(float value);
  void setTriangleSelector(irr::scene::ITriangleSelector *selector);
#endif

private:
  void UpdateFrom(const core::io_data *data){};
  class Model_impl *pimpl_;
};
} // end namespace simulator
} // end namespace flair
#endif // MODEL_H
