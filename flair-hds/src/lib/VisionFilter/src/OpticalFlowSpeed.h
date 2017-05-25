/*!
 * \file OpticalFlowSpeed.h
 * \brief Optical flow speed calculation
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/04/12
 * \version 4.0
 */


#ifndef OPTICALFLOWSPEED_H
#define OPTICALFLOWSPEED_H

#include <IODevice.h>

namespace flair
{
    namespace core
    {
        class cvmatrix;
    }
  namespace gui {
    class LayoutPosition;
    class SpinBox;
    class DoubleSpinBox;
    class CheckBox;
  }
}

namespace flair
{
namespace filter
{
    class OpticalFlow;
    class Ahrs;

    /*! \class OpticalFlowSpeed
    *
    * \brief Optical flow speed calculation
    *
    * Speed is the mean of all optical flow values.
    */
    class OpticalFlowSpeed : public core::IODevice
    {
        public:
            /*!
            * \brief Constructor
            *
            * Construct OpticalFlowSpeed.
            *
            * \param parent parent
            * \param name name
            */
            OpticalFlowSpeed(const core::IODevice* parent, const filter::Ahrs *ahrs, const gui::LayoutPosition* position,std::string name);

            /*!
            * \brief Destructor
            *
            */
            ~OpticalFlowSpeed();

            /*!
            * \brief Speed along x axis
            *
            */
            float Vx(void) const;

            /*!
            * \brief Speed along y axis
            *
            */
            float Vy(void) const;

            /*!
            * \brief Output matrix
            *
            * Matrix is of sze (2,1). \n
            * First line is speed along x axis. \n
            * Second line is speed along y axis. \n
            */
            core::cvmatrix *Output() const;

        private:
            /*!
            * \brief Update using provided datas
            *
            * Reimplemented from IODevice.
            *
            * \param data data from the parent to process
            */
            void UpdateFrom(const core::io_data *data);

            core::cvmatrix *output;
      gui::DoubleSpinBox *quality;
      gui::CheckBox *weightedAverage;
      gui::CheckBox *timeMultiplication;
};

} // end namespace filter
} // end namespace flair
#endif // OPTICALFLOWSPEED_H
