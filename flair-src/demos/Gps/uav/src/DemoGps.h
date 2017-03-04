//  created:    2016/07/01
//  filename:   DemoGps.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    demo GPS
//
//
/*********************************************************************/

#ifndef DEMOGPS_H
#define DEMOGPS_H

#include <UavStateMachine.h>

namespace flair {
    namespace gui {
        class PushButton;
    }
    namespace filter {
        class TrajectoryGenerator2DCircle;
    }
    namespace sensor {
        class TargetController;
        class Mb800;
        class SimuGps;
    }
}

class DemoGps : public flair::meta::UavStateMachine {
    public:
        DemoGps(flair::meta::Uav* uav,flair::sensor::TargetController *controller);
        ~DemoGps();

    private:
        enum class BehaviourMode_t {
            Default,
            PositionHold,
            Circle
        };

        BehaviourMode_t behaviourMode;

        void GpsPositionHold(void);
        void StartCircle(void);
        void StopCircle(void);
        void ExtraSecurityCheck(void);
        void ExtraCheckPushButton(void);
        void ExtraCheckJoystick(void);
        void PositionValues(flair::core::Vector2D &pos_error,flair::core::Vector2D &vel_error,float &yaw_ref);
        flair::core::AhrsData *GetReferenceOrientation(void);
        void SignalEvent(Event_t event);

        flair::filter::Pid *uX, *uY;

        flair::core::Vector2D posHold;
        float yawHold;

        flair::gui::PushButton *startCircle,*stopCircle;
        flair::filter::TrajectoryGenerator2DCircle *circle;
        flair::core::AhrsData *customReferenceOrientation,*customOrientation;
        //flair::sensor::Mb800 *gps;
        flair::sensor::SimuGps *gps;
};

#endif // DEMOGPS_H
