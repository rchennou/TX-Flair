// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/15
//  filename:   Man.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe chargeant un personnage
//
/*********************************************************************/

#ifndef MAN_H
#define MAN_H

#include <Model.h>

namespace irr {
namespace scene {
class IAnimatedMeshSceneNode;
}
}

namespace flair {
namespace gui {
class DoubleSpinBox;
}
}

namespace flair {
namespace simulator {
class Simulator;

class Man : private Model {
public:
  Man(const Simulator *parent, std::string name);
  ~Man();

private:
  size_t dbtSize(void) const;
  void WritedbtBuf(char *dbtbuf);
  void ReaddbtBuf(char *dbtbuf);
  void CalcModel(void);
  void AnimateModel(void){};
  bool OnEvent(const irr::SEvent &event);

  irr::scene::IAnimatedMeshSceneNode *node;
  gui::DoubleSpinBox *t_speed, *r_speed;
};
} // end namespace simulator
} // end namespace flair
#endif // MAN_H
