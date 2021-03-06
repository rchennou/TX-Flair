//  created:    2011/05/01
//  filename:   CircleFollower.h
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

#ifndef CIRCLEFOLLOWER_H
#define CIRCLEFOLLOWER_H

#include <UavStateMachine.h>

namespace flair {
    namespace gui {
        class PushButton;
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

class CircleFollower : public flair::meta::UavStateMachine {
    public:
        CircleFollower(flair::meta::Uav* uav,flair::sensor::TargetController *controller);
        ~CircleFollower();

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
};

#endif // CIRCLEFOLLOWER_H
