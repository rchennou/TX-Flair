//  created:    2015/10/19
//  filename:   DemoFollowLine.h
//
//  author:     Gildas Bayard, Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    demo follow line
//
//
/*********************************************************************/

#ifndef DEMOFOLLOWLINE_H
#define DEMOFOLLOWLINE_H

#include <DemoOpticalFlow.h>

namespace flair {
    namespace core {
        class AhrsData;
    }
    namespace gui {
        class DoubleSpinBox;
    }
    namespace filter {
        class HoughLines;
    }
}

class DemoFollowLine : public DemoOpticalFlow {

    public:
        DemoFollowLine(flair::sensor::TargetController *controller);
        ~DemoFollowLine();

    protected:
        flair::gui::DoubleSpinBox *speedStep;
        void SignalEvent(Event_t event);
        void ExtraCheckJoystick(void);
        void ExtraSecurityCheck(void);
        const flair::core::AhrsData *GetReferenceOrientation(void);
        flair::filter::HoughLines *houghLines;

    private:
        const flair::core::AhrsData *GetOrientation(void) const;
        flair::core::AhrsData *customOrientation;
        float speedAlongLine;
        bool flagCameraLost;
};

#endif // DEMOFOLLOWLINE_H
