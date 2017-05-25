//  created:    2017/02/10
//  filename:   ApriltagFollower.h
//
//  author:     Thomas Fuhrmann
//              Osamah Saif
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Following an Apriltag
//              Based on the CircleFollower demo
//
//
/*********************************************************************/

#ifndef APRILTAGFOLLLOWER_H
#define APRILTAGFOLLLOWER_H

#include <UavStateMachine.h>

class Streaming;

namespace flair {
    namespace core {
        class cvmatrix;
    }
    namespace gui {
        class PushButton;
        class DoubleSpinBox;
    }
    namespace filter {
        class EulerDerivative;
        class LowPassFilter;
        class ButterworthLowPass;
    }
    namespace sensor {
        class TargetController;
    }
}

class ApriltagFollower : public flair::meta::UavStateMachine {
public:
    ApriltagFollower(flair::sensor::TargetController *controller, const std::string streaminIp);
    ~ApriltagFollower();

private:
    enum class BehaviourMode_t {
        Default,
        PositionHold,
        Tracking
    };

    BehaviourMode_t behaviourMode;

    void StartPositionHold(void);
    void StartTracking(void);
    void ExtraCheckPushButton(void);
    void ExtraCheckJoystick(void);
    void ExtraSecurityCheck(void);
    const flair::core::AhrsData *GetOrientation(void) const;
    void PositionValues(flair::core::Vector2Df &pos_error, flair::core::Vector2Df &vel_error, float &yaw_ref);
    flair::core::AhrsData *GetReferenceOrientation(void);
    void SignalEvent(Event_t event);
    void ComputePositionHoldReferenceOrientation(void);
    void ComputeTrackingReferenceOrientation(void);

    flair::filter::Pid *uX, *uY;

    flair::core::Vector2Df posHold;
    float yawHold;
    flair::gui::PushButton *startTracking, *startPositionHold;
    flair::core::AhrsData *customReferenceOrientation, *customOrientation;

    Streaming *stream;
    flair::gui::DoubleSpinBox *desiredDepthApriltag;
    flair::gui::DoubleSpinBox *desiredYApriltag;

    flair::filter::EulerDerivative *eulerVel;
    flair::filter::LowPassFilter *filterVel;
    flair::filter::ButterworthLowPass *filterVel2;
    //flair::filter::LowPassFilter *opticalFlowSpeed;
    //flair::core::cvmatrix *opticalFlowRealSpeed;
    
    flair::core::Vector3Df trackingPosition;
    flair::core::Euler trackingRotation;
    bool trackingDetection;
    bool trackingNewData;
    bool wasLost;
};

#endif // APRILTAGFOLLLOWER_H
