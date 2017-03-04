// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2014/04/03
//  filename:   X8.h
//
//  author:     Majd Saied, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe definissant un X8
//
/*********************************************************************/

#ifndef X8_H
#define X8_H

#include <Model.h>
#include <stdint.h>

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

class X8 : public Model {
public:
  X8(const Simulator *parent, std::string name, int dev_id);
  ~X8();
  virtual void Draw(void);
  virtual void ExtraDraw(void){};

protected:
#ifdef GL
  irr::scene::IMesh *red_arm, *black_arm, *motor;
  MeshSceneNode *fl_arm, *fr_arm, *rl_arm, *rr_arm;
  MeshSceneNode *tfl_motor, *tfr_motor, *trl_motor, *trr_motor;
  MeshSceneNode *bfl_motor, *bfr_motor, *brl_motor, *brr_motor;
  Blade *tfl_blade, *tfr_blade, *trl_blade, *trr_blade;
  Blade *bfl_blade, *bfr_blade, *brl_blade, *brr_blade;
#endif
private:
  void CalcModel(void);
#ifdef GL
  void AnimateModel(void);
  size_t dbtSize(void) const;
  void WritedbtBuf(char *dbtbuf);
  void ReaddbtBuf(char *dbtbuf);
  core::Mutex *motor_speed_mutex;
#endif

  actuator::SimuBldc *motors;
  float motor_speed[8];
  gui::DoubleSpinBox *m, *arm_length, *l_cg;
  gui::DoubleSpinBox *k_mot, *c_mot;
  gui::DoubleSpinBox *f_air_vert, *f_air_lat;
  gui::DoubleSpinBox *j_roll, *j_pitch, *j_yaw;
  gui::DoubleSpinBox *j_r, *sigma, *S;
};
} // end namespace simulator
} // end namespace flair
#endif // X8_H
