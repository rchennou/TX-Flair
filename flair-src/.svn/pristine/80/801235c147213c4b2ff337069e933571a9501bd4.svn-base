//  created:    2016/06/01
//  filename:   PidUav.h
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Uav class showing the incidence of pid parameters choice
//
//
/*********************************************************************/

#ifndef PID_UAV_H
#define PID_UAV_H

#include <UavStateMachine.h>

namespace flair {
  namespace core {
    class cvmatrix;
  }
  namespace gui {
    class GroupBox;
    class DoubleSpinBox;
  }
  namespace filter {
    class Pid;
  }
  namespace sensor {
    class TargetController;
  }
}

class PidUav : public flair::meta::UavStateMachine {
public:
  PidUav(flair::meta::Uav *uav,
         flair::sensor::TargetController *controller);
  ~PidUav();

protected:
  void SignalEvent(Event_t event);
  void ExtraCheckJoystick(void);

private:
  void ComputeCustomTorques(flair::core::Euler &torques);
  bool StartCustomMode();
  void StartOscillatingMode();
  flair::filter::Pid *my_uPitch, *my_uRoll;
  enum class BehaviourMode_t { Default, Oscillating };
  BehaviourMode_t behaviourMode;
};

#endif // PID_UAV_H
