// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2017/03/04
//  filename:   X4WithTag.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un x4 avec april tag
//
/*********************************************************************/

#include "X4WithTag.h"
#include "Gui.h"
#include "MeshSceneNode.h"
#include <ISceneManager.h>

using namespace irr::scene;
using namespace irr::core;
using namespace irr::video;

namespace flair {
namespace simulator {
  
X4WithTag::X4WithTag(std::string name, uint32_t modelId) : X4(name,modelId){
  
}

X4WithTag::~X4WithTag() {
  
}

// create unite (1m=100cm) UAV; scale will be adapted according to arm_length
// parameter
// note that the frame used is irrlicht one:
// left handed, North East Up
void X4WithTag::ExtraDraw(void) {
  const IGeometryCreator *geo;
  geo = getGui()->getSceneManager()->getGeometryCreator();
  
  ITexture *texture = getGui()->getTexture("25h9_id0.png");
  IMesh* plane= geo->createPlaneMesh(irr::core::dimension2df(100,100));
  MeshSceneNode* tag= new MeshSceneNode(this, plane, vector3df(-150, 0, 0),vector3df(0, 0, 90),texture);
  //creation d'un fond sinon le tag est transparent lorsqu'il est vu de l'autre coté
  MeshSceneNode* fond= new MeshSceneNode(this, plane, vector3df(-150, 0, 0),vector3df(0, 0, -90));
  
  texture = getGui()->getTexture("carbone.jpg");
  IMesh *black_cyl = geo->createCylinderMesh(2.5, -150, 16, SColor(0, 128, 128, 128));
  MeshSceneNode *tag_arm = new MeshSceneNode(this, black_cyl, vector3df(0, 0, 0),vector3df(0, 0, -90),texture);
}

} // end namespace simulator
} // end namespace flair