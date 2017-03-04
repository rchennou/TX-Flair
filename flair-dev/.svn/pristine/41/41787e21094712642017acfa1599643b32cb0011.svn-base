// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/08/02
//  filename:   Parser.h
//
//  author:     César Richard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe chargeant un XML decrivant une map
//
/*********************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include <Gui.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

namespace flair {
  namespace core {
    class Vector3D;
  }
}

namespace flair {
namespace simulator {
class Parser : public Gui {

  /*can create:
  - cylinders: in y axis
  - fixed cameras

  */
public:
  Parser(Simulator *parent, int app_width, int app_height, int scene_width,
         int scene_height, std::string media_path, std::string xmlFile);
  ~Parser();

private:
  xmlDoc *doc;
  std::string media_path;
  Simulator *parent;
  void processElements(xmlNode *a_node);
  void processObjects(xmlNode *a_node);
  void processParams(xmlNode *a_node);
  irr::core::vector3df getMeshVect(xmlNode *mesh_node, xmlChar *param);
  irr::core::vector3df getSceneVect(xmlNode *mesh_node, xmlChar *param,
                                    bool isScale = false);
  core::Vector3D getMeshVector3D(xmlNode *mesh_node, xmlChar *param);
};
}
}
#endif // PARSER_H
