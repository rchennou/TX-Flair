// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2012/08/21
//  filename:   X4.h
//
//  author:     Osamah Saif, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un x4
//
/*********************************************************************/

#ifndef X4_H
#define X4_H

#include <Model.h>
#include <stdint.h>
#include <stdio.h>

namespace flair {
namespace core {
class Mutex;
}
namespace gui {
class DoubleSpinBox;
}
namespace actuator {
class SimuBldc;
}
}

#ifdef GL
namespace irr {
namespace scene {
class IMesh;
}
}
#endif

namespace flair {
namespace simulator {
class Simulator;
class Blade;
class MeshSceneNode;

class X4 : public Model {
public:
  X4(const Simulator *parent, std::string name, int dev_id);
  ~X4();
#ifdef GL
  virtual void Draw(void);
  virtual void ExtraDraw(void){};

protected:
  irr::scene::IMesh *red_arm, *black_arm, *motor;
  MeshSceneNode *fl_arm, *fr_arm, *rl_arm, *rr_arm;
  MeshSceneNode *fl_motor, *fr_motor, *rl_motor, *rr_motor;
  Blade *fl_blade, *fr_blade, *rl_blade, *rr_blade;
  core::Mutex *motor_speed_mutex;
#endif
private:
  void CalcModel(void);
#ifdef GL
  void AnimateModel(void);
  size_t dbtSize(void) const;
  void WritedbtBuf(char *dbtbuf);
  void ReaddbtBuf(char *dbtbuf);
#endif

  actuator::SimuBldc *motors;
  float motor_speed[4];
  gui::DoubleSpinBox *m, *arm_length, *l_cg;
  gui::DoubleSpinBox *k_mot, *c_mot;
  gui::DoubleSpinBox *f_air_vert, *f_air_lat;
  gui::DoubleSpinBox *j_roll, *j_pitch, *j_yaw;
};
} // end namespace simulator
} // end namespace flair
#endif // X4_H
