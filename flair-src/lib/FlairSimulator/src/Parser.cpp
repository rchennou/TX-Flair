// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/08/02
//  filename:   Parser.cpp
//
//  author:     César Richard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe chargeant un XML decrivant une map
//
/*********************************************************************/
#ifdef GL

#include "Parser.h"
#include "Simulator.h"
#include "GenericObject.h"
#include "FixedCamera.h"
#include <vector3d.h>
#include <Vector3D.h>
#include <IrrlichtDevice.h>
#include <IFileSystem.h>
#include "GenericObject.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace flair::core;
using namespace flair::simulator;

// todo: getMeshVect doit plutot donner point3D et euler
// adaptr le xml et la dtd

namespace flair {
namespace simulator {
Parser::Parser(Simulator *parent, int app_width, int app_height,
               int scene_width, int scene_height, std::string media_path,
               std::string xmlFile)
    : Gui(parent, "Parser", app_width, app_height, scene_width, scene_height,
          media_path) {
  this->media_path = media_path;
  this->parent = parent;
  xmlNode *root_element = NULL;
  doc = xmlReadFile(xmlFile.c_str(), NULL, 0);
  xmlDtdPtr dtd = NULL;
  dtd = xmlParseDTD(NULL,
                    (const xmlChar *)(media_path.append("/scene.dtd").c_str()));

  if (dtd == NULL) {
    // xmlGenericError(xmlGenericErrorContext,
    Err("Could not parse DTD scene.dtd\n");
  } else {
    xmlValidCtxt cvp;
    cvp.userData = (void *)stderr;
    cvp.error = (xmlValidityErrorFunc)fprintf;
    cvp.warning = (xmlValidityWarningFunc)fprintf;
    if (!xmlValidateDtd(&cvp, doc, dtd)) {
      // xmlGenericError(xmlGenericErrorContext,
      Err("Document does not validate against scene.dtd\n");
    }
  }

  if (doc == NULL) {
    Err("error: could not parse file %s\n", xmlFile.c_str());
  } else {
    /*
     * Get the root element node
     */
    root_element = xmlDocGetRootElement(doc);
    processElements(root_element);
  }
}

Parser::~Parser() {
  if (doc != NULL) {
    /*
     * free the document
     */
    xmlFreeDoc(doc);
    ;
  }
  /*
   *Free the global variables that may
   *have been allocated by the parser.
   */
  xmlCleanupParser();
}

/* Recursive function that prints the XML structure */
void Parser::processElements(xmlNode *a_node) {
  xmlNode *cur_node = NULL;
  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrEqual(cur_node->name, (xmlChar *)"params")) {
        processParams(cur_node->children);
      } else if (xmlStrEqual(cur_node->name, (xmlChar *)"objects")) {
        processObjects(cur_node->children);
      } else {
        processElements(cur_node->children);
      }
    }
  }
}

void Parser::processObjects(xmlNode *a_node) {
  FILE *fp;
  std::string fileName;
  xmlNode *cur_node = NULL;

  const IGeometryCreator *geo;

  geo = getGui()->getSceneManager()->getGeometryCreator();

  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (xmlStrEqual(cur_node->name, (xmlChar *)"mesh")) {
      fileName = this->media_path;
      fp = NULL;
      fp = fopen(fileName.append((char *)xmlGetProp(
                                     cur_node, (xmlChar *)"model")).c_str(),
                 "rb");
      if (fp != NULL) {
        GenericObject *object =
            new GenericObject(parent, "Object", getSceneManager());
        object->setMesh(getGui()->getMesh(
            (char *)xmlGetProp(cur_node, (xmlChar *)"model")));
        object->setPosition(
            getMeshVect(cur_node->children, (xmlChar *)"position"));
        object->setRotation(
            getMeshVect(cur_node->children, (xmlChar *)"rotation"));
        object->setScale(getMeshVect(cur_node->children, (xmlChar *)"scale"));
        object->render();
      } else {
        Err("FATAL ERROR : File %s doesn't exist !\r\n",
            (char *)xmlGetProp(cur_node, (xmlChar *)"model"));
      }
    } else if (xmlStrEqual(cur_node->name, (xmlChar *)"cylinder")) {
      GenericObject *object =
          new GenericObject(parent, "Object", getSceneManager());
      object->setMesh(geo->createCylinderMesh(
          ToIrrlichtScale(
              atof((char *)xmlGetProp(cur_node, (xmlChar *)"radius"))),
          ToIrrlichtScale(
              atof((char *)xmlGetProp(cur_node, (xmlChar *)"length"))),
          atof((char *)xmlGetProp(cur_node, (xmlChar *)"tesselation")),
          SColor(100, 255, 100, 100)));
      object->setPosition(
          getMeshVect(cur_node->children, (xmlChar *)"position"));
      object->setRotation(
          getMeshVect(cur_node->children, (xmlChar *)"rotation"));
      object->setScale(getMeshVect(cur_node->children, (xmlChar *)"scale"));
      // object->setMaterialTexture(0,getTexture("/home/apeiron/igep/uav_dev_svn/trunk/media/nskinbl.jpg"));
      object->setMaterialType(video::EMT_SOLID);
      object->render();
    } else if (xmlStrEqual(cur_node->name, (xmlChar *)"eight")) {
      GenericObject *object =
          new GenericObject(parent, "Object", getSceneManager());
      object->setMesh(geo->createCubeMesh(
          vector3df(atof((char *)xmlGetProp(cur_node, (xmlChar *)"length")),
                    atof((char *)xmlGetProp(cur_node, (xmlChar *)"width")),
                    atof((char *)xmlGetProp(cur_node, (xmlChar *)"eight")))));
      object->setPosition(
          getMeshVect(cur_node->children, (xmlChar *)"position"));
      object->setRotation(
          getMeshVect(cur_node->children, (xmlChar *)"rotation"));
      object->setScale(getMeshVect(cur_node->children, (xmlChar *)"scale"));
      object->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
      // object->getMaterial(0).Textures[0] =
      // getTexture("/home/apeiron/igep/uav_dev_svn/trunk/media/nskinbl.jpg");
      object->setMaterialFlag(EMF_LIGHTING, false);
      object->render();
    }
  }
}

void Parser::processParams(xmlNode *a_node) {

  xmlNode *cur_node = NULL;
  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (xmlStrEqual(cur_node->name, (xmlChar *)"archive")) {
      std::string file =
          media_path + "/" + (char *)xmlGetProp(cur_node, (xmlChar *)"path");
      getDevice()->getFileSystem()->addFileArchive(file.c_str());
    } else if (xmlStrEqual(cur_node->name, (xmlChar *)"mesh")) {
      setMesh((char *)xmlGetProp(cur_node, (xmlChar *)"model"),
              getSceneVect(cur_node->children, (xmlChar *)"position"),
              getSceneVect(cur_node->children, (xmlChar *)"rotation"),
              getSceneVect(cur_node->children, (xmlChar *)"scale", true));
    } else if (xmlStrEqual(cur_node->name, (xmlChar *)"camera")) {
      FixedCamera* fixedCamera=new FixedCamera(std::string((char *)xmlGetProp(cur_node, (xmlChar *)"name")),
                                               getMeshVector3D(cur_node->children, (xmlChar *)"position"),
                                               getMeshVector3D(cur_node->children, (xmlChar *)"lookat"));
    }
  }
}
// todo rendre un vector3D framework
// retirer irr::core::vector3df ToIrrlichtCoordinates(irr::core::vector3df
// vect);
vector3df Parser::getMeshVect(xmlNode *mesh_node, xmlChar *param) {
  xmlNode *cur_node = NULL;
  for (cur_node = mesh_node; cur_node; cur_node = cur_node->next) {
    if (xmlStrEqual(cur_node->name, param)) {
      return vector3df(atof((char *)xmlGetProp(cur_node, (xmlChar *)"x")),
                       atof((char *)xmlGetProp(cur_node, (xmlChar *)"y")),
                       atof((char *)xmlGetProp(cur_node, (xmlChar *)"z")));
    }
  }
  return vector3df(0, 0, 0);
}

Vector3D Parser::getMeshVector3D(xmlNode *mesh_node, xmlChar *param) {
  xmlNode *cur_node = NULL;
  for (cur_node = mesh_node; cur_node; cur_node = cur_node->next) {
    if (xmlStrEqual(cur_node->name, param)) {
      return Vector3D(atof((char *)xmlGetProp(cur_node, (xmlChar *)"x")),
                       atof((char *)xmlGetProp(cur_node, (xmlChar *)"y")),
                       atof((char *)xmlGetProp(cur_node, (xmlChar *)"z")));
    }
  }
  return Vector3D(0, 0, 0);
}

vector3df Parser::getSceneVect(xmlNode *mesh_node, xmlChar *param,
                               bool isScale) {
  xmlNode *cur_node = NULL;
  for (cur_node = mesh_node; cur_node; cur_node = cur_node->next) {
    if (xmlStrEqual(cur_node->name, param)) {
      if (isScale) {
        return vector3df(atof((char *)xmlGetProp(cur_node, (xmlChar *)"x")),
                         atof((char *)xmlGetProp(cur_node, (xmlChar *)"z")),
                         atof((char *)xmlGetProp(cur_node, (xmlChar *)"y")));
      }
      return vector3df(atof((char *)xmlGetProp(cur_node, (xmlChar *)"x")),
                       -atof((char *)xmlGetProp(cur_node, (xmlChar *)"z")),
                       atof((char *)xmlGetProp(cur_node, (xmlChar *)"y")));
    }
  }
  return vector3df(0, 0, 0);
}

} // end namespace simulator
} // end namespace flair
#endif // GL
