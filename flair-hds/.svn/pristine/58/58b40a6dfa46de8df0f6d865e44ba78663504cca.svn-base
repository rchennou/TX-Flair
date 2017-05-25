/*!
 * \file ImgThreshold.h
 * \brief ImgThreshold algorithm
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2015/10/07
 * \version 4.0
 */


#ifndef IMGTHRESHOLD_H
#define IMGTHRESHOLD_H

#include <IODevice.h>
#include <cv.h>

namespace flair {
    namespace core {
        class cvimage;
    }
    namespace gui {
        class LayoutPosition;
        class SpinBox;
    }
}

namespace flair { namespace filter {
    /*! \class ImgThreshold
    *
    * \brief ImgThreshold algorithm
    *
    * ImgThreshold is done using the DSP of the DM3730.
    */
    class ImgThreshold : public core::IODevice {
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
            ImgThreshold(const core::IODevice* parent,const gui::LayoutPosition* position,std::string name);

            /*!
            * \brief Destructor
            *
            */
            ~ImgThreshold();

            /*!
            * \brief Output image
            *
            * Output matrix is of the same size as the input image. \n
            *
            * \return the output image
            */
            core::cvimage* Output(void);

            core::DataType const &GetOutputDataType() const;

        private:
            void UpdateFrom(const core::io_data *data);
            core::cvimage *output;
            gui::SpinBox *threshold;
    };
} // end namespace filter
} // end namespace flair
#endif // IMGTHRESHOLD_H
