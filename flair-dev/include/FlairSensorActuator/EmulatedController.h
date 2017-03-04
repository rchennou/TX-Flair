//  created:    2015/04/14
//  filename:   EmulatedController.h
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class that emulate a remote control.
//              Typical use case: run a demo without any reliable communication channel
//
//
/*********************************************************************/

#ifndef EMULATEDCONTROLLER_H
#define EMULATEDCONTROLLER_H

#include <TargetController.h>
#include <list>

namespace flair {
    namespace core {
        class FrameworkManager;
        class cvmatrix;
    }
    namespace gui {
        class Tab;
        class TabWidget;
        class DataPlot1D;
    }
}

namespace flair { namespace sensor {
    /*! \class EmulatedController
    *
    * \brief Emulated remote control
    *
    */
    class EmulatedController : public TargetController {
    public:
        EmulatedController(const core::FrameworkManager* parent,std::string name,uint8_t priority=0);
        ~EmulatedController();
        enum class ButtonType : uint16_t {
            start=0x0001,select=0x0002,square=0x0004,triangle=0x0008,
            circle=0x0010,cross=0x0020,left1=0x0040,left2=0x0080,
            left3=0x0100,right1=0x0200,right2=0x0400,right3=0x0800,
            up=0x1000,down=0x2000,left=0x4000,right=0x8000
        };
        void AddStep(unsigned int durationMs,std::string description,uint16_t buttonPressed, float leftAxisX, float leftAxisY, float rightAxisX, float rightAxisY);
    protected :
        bool IsConnected() const;
        //controller state stuff
        bool ProcessMessage(core::Message *msg);
        bool IsDataFrameReady();
        void AcquireAxisData(core::cvmatrix &axis); //responsible for getting the axis data from the hardware
        void AcquireButtonData(core::cvmatrix &button); //responsible for getting the button data from the hardware
        bool ControllerInitialization();

    private:
        enum class DataType { axis,button };
        void ComputeControllerData(DataType dataType, core::cvmatrix &data);
        template<typename T> void fillVectorNoMutex(core::cvmatrix &vector,T data[],unsigned int size);
        void fillVectorNoMutex(core::cvmatrix &destination,core::cvmatrix &source,unsigned int size);
        struct StepData {
            unsigned int durationMs; //milliseconds
            core::cvmatrix *axisData;
            core::cvmatrix *buttonData;
            std::string description;
            void Print();
        };
        std::list<StepData> steps;
    };

}}

#endif // EMULATEDCONTROLLER_H
