//  created:    2015/11/05
//  filename:   SimpleFleet.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    demo fleet
//
//
/*********************************************************************/

#ifndef SIMPLEFLEET_H
#define SIMPLEFLEET_H

#include <UavStateMachine.h>

namespace flair {
    namespace core {
        class FrameworkManager;
        class Socket;
        class AhrsData;
    }
    namespace filter {
        class TrajectoryGenerator2DSquare;
    }
    namespace gui {
        class DoubleSpinBox;
    }
}


class SimpleFleet : public flair::meta::UavStateMachine {
    public:
        SimpleFleet(flair::meta::Uav* uav,std::string broadcast,flair::sensor::TargetController *controller);
        ~SimpleFleet();

    private:
        enum class BehaviourMode_t {
            Default,
            PositionHold1,
            Square1,
            PositionHold2,
            PositionHold3,
            Square2,
            PositionHold4,
        };

//        BehaviourMode_t orientation_state;
        BehaviourMode_t behaviourMode;
        bool vrpnLost;

        void VrpnPositionHold(void);//flight mode
        void StartSquare(void);
        void StopSquare(void);
        void ExtraTakeOff(void);
        void ExtraSecurityCheck(void);
        void ExtraCheckJoystick(void);
        const flair::core::AhrsData *GetOrientation(void) const;
        void AltitudeValues(float &z,float &dz) const;
        void PositionValues(flair::core::Vector2D &pos_error,flair::core::Vector2D &vel_error,float &yaw_ref);
        const flair::core::AhrsData *GetReferenceOrientation(void);
        void SignalEvent(Event_t event);
        void CheckMessages(void);

        flair::filter::Pid *u_x, *u_y;

        flair::core::Vector2D pos_hold;
        float yaw_hold;
        flair::core::Socket *message;
        flair::core::Time posWait;

        flair::filter::TrajectoryGenerator2DSquare *square;
        flair::gui::DoubleSpinBox *xSquareCenter,*ySquareCenter,*yDisplacement;
        flair::core::AhrsData *customReferenceOrientation,*customOrientation;
};

#endif // SIMPLEFLEET_H
