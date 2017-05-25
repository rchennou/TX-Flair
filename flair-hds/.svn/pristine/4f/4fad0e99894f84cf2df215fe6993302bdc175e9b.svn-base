/*!
 * \file HoughLines.h
 * \brief HoughLines algorithm
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2015/10/07
 * \version 4.0
 */


#ifndef HOUGHLINES_H
#define HOUGHLINES_H

#include <IODevice.h>
#include <Vector2D.h>
#include <cv.h>

namespace flair {
    namespace core {
        class cvimage;
        class cvmatrix;
        class OneAxisRotation;
    }
    namespace gui {
        class LayoutPosition;
        class SpinBox;
        class DoubleSpinBox;
    }
}

namespace flair { namespace filter {
    /*! \class HoughLines
    *
    * \brief HoughLines algorithm
    *
    * HoughLines is done using the DSP of the DM3730.
    */
    class HoughLines : public core::IODevice {
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
            * \param ptRefGlobal reference point used to compute distance to the line
            * \param thetaRefGlobal reference angle used to compute orientation in range [-pi/2,pi/2]. Default value is 0 which defines a vertical line
            */
            HoughLines(const core::IODevice* parent,const gui::LayoutPosition* position,std::string name,const core::Vector2Df *ptRefGlobal=NULL,float thetaRefGlobal=0);

            /*!
            * \brief Destructor
            *
            */
            ~HoughLines();

            bool isLineDetected(void) const;
            float GetOrientation(void) const;
            float GetDistance(void) const;
            core::cvmatrix *Output(void) const;

        private:
            core::OneAxisRotation* rotation;
            bool SelectBestLine(CvMat* linesStorage, size_t nbLines, float &rho, float &theta);
            void UpdateFrom(const core::io_data *data);
            gui::SpinBox *fullRhoStep,*trackingRhoStep,*nbPoints;
            gui::DoubleSpinBox *fullThetaStep,*trackingThetaStep,*trackingDeltaTheta;
            bool isTracking;
            float theta;
            float distance,orientation;
            core::Vector2Df* ptRefGlobal;
            float thetaRefGlobal;
            CvMat* linesStorage;
            core::cvmatrix *output;
    };
} // end namespace filter
} // end namespace flair
#endif // HOUGHLINES_H
