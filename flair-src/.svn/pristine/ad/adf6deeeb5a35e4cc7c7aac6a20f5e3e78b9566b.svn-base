// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/25
//  filename:   Model.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un modele a simuler
//
/*********************************************************************/

#include "Model.h"
#include "Model_impl.h"
#include "Simulator.h"
#include "Simulator_impl.h"
#include <DoubleSpinBox.h>

#ifdef GL
#include "FollowMeCamera.h"
#include "Gui.h"
#include <ICameraSceneNode.h>
using namespace irr;
using namespace irr::scene;
using namespace irr::core;
#endif

using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace simulator {

Model::Model(const Simulator *parent, std::string name)
    : IODevice(parent, name) {
#ifdef GL
  pimpl_ =
      new Model_impl(this, name, getGui()->getSceneManager(), parent->pimpl_);
#else
  pimpl_ = new Model_impl(this, name, parent->pimpl_);
#endif
  parent->pimpl_->models.push_back(this);
}

Model::~Model() { delete pimpl_; }
#ifdef GL
ISceneNode *Model::getSceneNode() const { return pimpl_; }
/*
only used by dbt, to rewrite using conversion functions (irrlicht <-> simulator)
void Model::setPosition(Vector3D pos)
{
    //note that irrlicht frame is left handed
    pimpl_->setPosition(ToIrrlichtScale(1)*vector3df(pos.y,pos.z,-pos.x));
}
*/
void Model::setScale(float value) {
  pimpl_->setScale(vector3df(value, value, value));
}

aabbox3d<f32> *Model::Box() const { return &(pimpl_->box); }

FollowMeCamera *Model::getFollowMeCamera(void) const { return pimpl_->camera; }

void Model::setTriangleSelector(ITriangleSelector *selector) {

  pimpl_->selector = selector;
  pimpl_->setTriangleSelector(selector);
}

void Model::setCameraFarValue(float zf) { pimpl_->camera->getCameraSceneNode()->setFarValue(zf); }
#endif

TabWidget *Model::GetTabWidget(void) const { return pimpl_->tabwidget; }

float Model::dT(void) const { return pimpl_->dT->Value(); }

} // end namespace simulator
} // end namespace flair
