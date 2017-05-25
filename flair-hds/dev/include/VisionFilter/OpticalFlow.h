/*!
 * \file OpticalFlow.h
 * \brief Lucas and Kanade optical flow algorithm
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/04/12
 * \version 4.0
 */


#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H

#include <IODevice.h>
#include <cv.h>

namespace flair
{
    namespace core
    {
        class cvimage;
        class OneAxisRotation;
    }
    namespace gui
    {
        class LayoutPosition;
        class SpinBox;
    }
    namespace filter
    {
        class OpticalFlowData;
    }
}

namespace flair
{
namespace filter
{
    /*! \class OpticalFlow
    *
    * \brief Lucas and Kanade optical flow algorithm
    *
    * Optical flow is done using the DSP of the DM3730.
    */
    class OpticalFlow : public core::IODevice
    {

        public:
            /*!
            * \brief Constructor
            *
            * Construct an OpticalFlow filter at given position. \n
            * After calling this function, position will be deleted as it is no longer usefull. \n
            *
            * \param parent parent
            * \param position position
            * \param name name
            */
            OpticalFlow(const core::IODevice* parent,const gui::LayoutPosition* position,std::string name);

            /*!
            * \brief Destructor
            *
            */
            ~OpticalFlow();

        private:
            void UpdateFrom(const core::io_data *data);
            OpticalFlowData *output;
            gui::SpinBox *max_features;
            core::OneAxisRotation* rotation;

            CvPoint* pointsA;
            CvPoint* pointsB;
            char *found_feature;
            unsigned int *feature_error;
            IplImage *pyr,*pyr_old;

            bool is_init;
    };
} // end namespace filter
} // end namespace flair
#endif // OPTICALFLOW_H
