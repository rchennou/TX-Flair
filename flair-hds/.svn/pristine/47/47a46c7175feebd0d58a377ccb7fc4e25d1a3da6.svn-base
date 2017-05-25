//  created:    2017/02/02
//  filename:   Streaming.h
//
//  author:     Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    streams data and receives computed information
//
//
/*********************************************************************/

#ifndef STREAMING_H
#define STREAMING_H

#define STREAMING
// Temporary define for the HIL
#define SIMU
#define REAL

#include <Thread.h>
#include <Quaternion.h>
#include <Vector3D.h>
#include <IODevice.h>

#include <chrono>
#include <sys/time.h>

struct tagData {
    uint8_t nbDetect;
    float distance;
    float x;
    float y;
    float z;
    float q0;
    float q1;
    float q2;
    float q3;
    flair::core::Time time;
}__attribute__ ((packed));

namespace flair {
    namespace core {
        class TcpSocket;
        class Mutex;
        class cvmatrix;
        class OneAxisRotation;
    }
    namespace gui {
        class Label;
        class GroupBox;
    }
    namespace filter {
        class CvtColor;
        class StreamingFilter;
    }
}

class Streaming : public flair::core::Thread, public flair::core::IODevice {

public:
    Streaming(const std::string streamIp);
    ~Streaming();

    /**
     * Copy the values of received data in the parameters.
     * If there is no new reception, copy the last value and returns false.
     * @param position [OUT] The received position
     * @param rotation [OUT] The received rotation
     * @return true if new values since previous call, false otherwise
     */
    bool GetComputedData(flair::core::Vector3Df &position, flair::core::Euler &rotation, bool &detection);
    
    flair::gui::GroupBox *graphGroupBox;
    flair::core::cvmatrix *graphCvMatrix;
    
protected:

private:
    // reimplement the run of the Thread class
    void Run();
    void UpdateFrom(const flair::core::io_data *data);
    void ComputeRotations(flair::core::Vector3Df &point);
    void ComputeRotations(flair::core::Quaternion &quat);

    flair::gui::Label *fps;
    flair::core::cvmatrix *savingMatrix;
    flair::core::cvmatrix *outputCvMatrix;
    flair::filter::CvtColor *greyCameraImage;
    flair::filter::StreamingFilter *streamingCameraImage;
    flair::core::TcpSocket *receivingSocket;
    std::chrono::time_point <std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsedSeconds;

    bool recvDataFlag;
    bool isTagDetected;
    flair::core::Mutex *recvDataMutex;
    flair::core::Quaternion recvQuaternion;
    flair::core::Vector3Df recvPosition;
    flair::core::OneAxisRotation *rotation_1, *rotation_2;
};

#endif // STREAMING_H
