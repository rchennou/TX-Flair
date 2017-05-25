/*!
 * \file CvtColor.h
 * \brief Image color conversion
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/07/17
 * \version 4.0
 */


#ifndef CVTCOLOR_H
#define CVTCOLOR_H

#include <IODevice.h>

namespace flair
{
    namespace core
    {
        class cvimage;
    }
}

namespace flair
{
namespace filter
{
    /*! \class CvtColor
    *
    * \brief Image color conversion
    *
    * The conversion is done using the DSP of the DM3730.
    */
    class CvtColor : public core::IODevice
    {
        public:
            /*!
            \enum Conversion_t
            \brief Conversion formats
            */
            enum class Conversion_t {
                ToBGR,/*!< BGR 24 bits */
                ToGray,/*!< gray 8 bits */
                } ;

            /*!
            * \brief Constructor
            *
            * Construct an Ahrs.
            *
            * \param parent parent
            * \param name name
            * \param conversion conversion format
            */
            CvtColor(const core::IODevice* parent,std::string name,Conversion_t conversion);

            /*!
            * \brief Destructor
            *
            */
            ~CvtColor();

            /*!
            * \brief Output image
            *
            * Output matrix is of the same size as declared in constructor. \n
            * Its type depends of the conversion type.
            *
            * \return the output image
            */
            core::cvimage* Output(void);

            core::DataType const &GetOutputDataType() const;

        private:
            /*!
            * \brief Update using provided datas
            *
            * Reimplemented from IODevice.
            *
            * \param data data from the parent to process
            */
            void UpdateFrom(const core::io_data *data);

            core::cvimage *output;
            Conversion_t conversion;
    };
} // end namespace filter
} // end namespace flair
#endif // CVTCOLOR_H
