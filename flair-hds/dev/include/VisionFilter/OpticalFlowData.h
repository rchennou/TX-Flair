/*!
 * \file OpticalFlowData.h
 * \brief Class defining pptical flow datas
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/04/12
 * \version 4.0
 */

#ifndef OPTICALFLOWDATA_H
#define OPTICALFLOWDATA_H

#include <cxcore.h>
#include <io_data.h>

namespace flair { namespace filter {
    /*! \class OpticalFlowData
    *
    * \brief Class defining optical flow datas
    *
    * Optical flow datas are composed of the following: \n
    * PointsA: tracked points on first image
    * PointsB: tracked points on second image
    * FoundFeature: array representing if a point on first image is found on second image
    * FeatureError: array representing correlation error for each point (confidence)
    */
    class OpticalFlowData: public core::io_data {
    public:
        class Type: public core::DataType {
            size_t GetSize() const {return 0;} //TODO
            std::string GetDescription() const {return "optical flow";}
        };

        /*!
        * \brief Constructor
        *
        * Construct OpticalFlowData.
        *
        * \param parent parent
        * \param max_features maximum number of features to track
        * \param name name
        * \param n number of samples for the io_data
        */
        OpticalFlowData(const core::Object* parent,uint32_t max_features,std::string name="",uint32_t n=1);

        /*!
        * \brief Destructor
        *
        */
        ~OpticalFlowData();

        /*!
        * \brief Points on first image
        *
    */
        CvPoint* PointsA(void) const;

        /*!
        * \brief Points on second image
        *
        */
        CvPoint2D32f* PointsB(void) const;

        /*!
        * \brief Features found
        *
        * value of the array is one if feature is found
        */
        char *FoundFeature(void) const;

        /*!
        * \brief Correlation error
        *
        */
        uint32_t *FeatureError(void) const;

        /*!
        * \brief Set points of interest of frst image
        *
        * \param points points
        */
        void SetPointsA(const CvPoint *points);

        /*!
        * \brief Set points of interest of second image
        *
        * \param points points
        */
        void SetPointsB(const CvPoint2D32f *points);

        /*!
        * \brief Set found features
        *
        * \param found_features found features
        */
        void SetFoundFeature(const char *found_features);

        /*!
        * \brief Set features error
        *
        * \param features_error features error
        */
        void SetFeatureError(const unsigned int *features_error);

        /*!
        * \brief Number of maximum features
        *
        */
        uint32_t MaxFeatures(void) const;

        /*!
        * \brief Number of tracked features
        *
        */
        uint32_t NbFeatures(void) const;

        /*!
        * \brief Set number of tracked features
        *
        * \param value number of tracked features
        */
        void SetNbFeatures(uint32_t value);

        /*!
        * \brief Change number of maximum features
        *
        * \param value new number of maximum tracked features
        */
        void Resize(uint32_t value);

        OpticalFlowData::Type const &GetDataType() const {return dataType;}

    private:
        uint32_t max_features;
        uint32_t nb_features;
        CvPoint* pointsA;
        CvPoint2D32f* pointsB;
        char *found_features;
        uint32_t *features_error;
        void CopyDatas(char* dst) const;
        Type dataType;
    };
} // end namespace filter
} // end namespace flair
#endif // OPTICALFLOWDATA_H
