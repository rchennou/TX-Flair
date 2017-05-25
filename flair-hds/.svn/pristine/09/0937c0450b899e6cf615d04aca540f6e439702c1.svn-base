/*!
 * \file Sobel.h
 * \brief Sobel algorithm
 * \author Gildas Bayard, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2015/10/07
 * \version 4.0
 */


#ifndef SOBEL_H
#define SOBEL_H

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
    /*! \class Sobel
    *
    * \brief Sobel algorithm
    *
    * Sobel is done using the DSP of the DM3730.
    */
    class Sobel : public core::IODevice {
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
            Sobel(const core::IODevice* parent,const gui::LayoutPosition* position,std::string name);

            /*!
            * \brief Destructor
            *
            */
            ~Sobel();

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
            gui::SpinBox *dx;
            gui::SpinBox *dy;
    };
} // end namespace filter
} // end namespace flair
#endif // SOBEL_H
