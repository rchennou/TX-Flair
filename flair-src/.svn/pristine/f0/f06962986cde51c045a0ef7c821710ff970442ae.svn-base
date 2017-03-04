//  created:    2015/10/29
//  filename:   MyApp.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    skeleton to use UavStateMachine with custom torques only
//
//
/*********************************************************************/

#ifndef MYAPP_H
#define MYAPP_H

#include <UavStateMachine.h>

namespace framework {
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
            CustomTorques
        };

        BehaviourMode_t behaviourMode;

        void ComputeCustomTorques(flair::core::Euler &torques);
        void StartCustomTorques(void);
        void StopCustomTorques(void);
        void ExtraCheckPushButton(void);
        void ExtraCheckJoystick(void);
        void SignalEvent(Event_t event);

        flair::gui::PushButton *start_CustomTorques,*stop_CustomTorques;
};

#endif // MYAPP_H
