//  created:    2015/10/27
//  filename:   MyApp.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    skeleton to use UavStateMachine with custom reference angles only
//
//
/*********************************************************************/

#ifndef MYAPP_H
#define MYAPP_H

#include <UavStateMachine.h>

namespace flair {
    namespace core {
        class AhrsData;
    }
    namespace gui {
        class PushButton;
    }
    namespace sensor {
        class TargetController;
    }
}

class MyApp : public flair::meta::UavStateMachine {
    public:
        MyApp(flair::meta::Uav* uav,flair::sensor::TargetController *controller);
        ~MyApp();

    private:
        enum class BehaviourMode_t {
            Default,
            CustomReferenceAngles
        };

        BehaviourMode_t behaviourMode;

        void StartCustomAngles(void);
        void StopCustomAngles(void);
        void ExtraCheckPushButton(void);
        void ExtraCheckJoystick(void);
        flair::core::AhrsData *GetReferenceOrientation(void);
        void SignalEvent(Event_t event);

        flair::gui::PushButton *start_CustomAngles,*stop_CustomAngles;
        flair::core::AhrsData *customReferenceOrientation;
};

#endif // MYAPP_H
