//  created:    2011/05/01
//  filename:   SquareFollower.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    demo cercle avec optitrack
//
//
/*********************************************************************/

#ifndef SQUAREFOLLOWER_H
#define SQUAREFOLLOWER_H

#include <UavStateMachine.h>

namespace flair {
    namespace gui {
        class PushButton;
	class DoubleSpinBox;
    }
    namespace filter {
        class TrajectoryGenerator2DCircle;
    }
    namespace meta {
        class MetaVrpnObject;
    }
    namespace sensor {
        class TargetController;
    }
}

class SquareFollower : public flair::meta::UavStateMachine {
    public:
        SquareFollower(flair::meta::Uav* uav,flair::sensor::TargetController *controller);
        ~SquareFollower();

    private:
        enum class BehaviourMode_t {
            Default,
            PositionHold,
            Circle
        };

        BehaviourMode_t behaviourMode;
        bool vrpnLost;

        void VrpnPositionHold(void);//flight mode
        void StartCircle(void);
        void StopCircle(void);
        void ExtraSecurityCheck(void);
        void ExtraCheckPushButton(void);
        void ExtraCheckJoystick(void);
        const flair::core::AhrsData *GetOrientation(void) const;
        void AltitudeValues(float &z,float &dz);
        void PositionValues(flair::core::Vector2D &pos_error,flair::core::Vector2D &vel_error,float &yaw_ref);
        flair::core::AhrsData *GetReferenceOrientation(void);
        void SignalEvent(Event_t event);

        flair::filter::Pid *uX, *uY;

        flair::core::Vector2D posHold;
        float yawHold;

        flair::gui::PushButton *startCircle,*stopCircle;
        flair::meta::MetaVrpnObject *targetVrpn;
        flair::filter::TrajectoryGenerator2DCircle *circle;
        flair::core::AhrsData *customReferenceOrientation,*customOrientation;
	flair::gui::DoubleSpinBox *xPoint1, *yPoint1, *xPoint2, *yPoint2;
};

#endif // SquareFollower_H
