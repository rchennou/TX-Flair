/*!
 * \file ArDrone2CamV.h
 * \brief Class for ardrone2 horizontal camera
 * \author Guillaume Sanahuja
 * \date 2014/07/16
 * \version 4.0
 */

#ifndef ARDRONE2CAMV_H
#define ARDRONE2CAMV_H

#define   CMATRIX_LEN 6

#include "V4LCamera.h"

namespace flair {
    namespace core {
        class I2cPort;
    }
}

namespace flair {
namespace sensor {
    /*! \class ArDrone2CamV
    *
    * \brief Class for ardrone2 vertical camera
    */
    class ArDrone2CamV : public V4LCamera
    {

        public:
            /*!
            * \brief Constructor
            *
            * Construct a ArDrone2CamV.
            * It will be child of the FrameworkManager.
						* 
            * \param name name
            * \param priority priority of the Thread
            */
            ArDrone2CamV(std::string name,uint8_t priority);

            /*!
            * \brief Destructor
            *
            */
            ~ArDrone2CamV();

        private:
            /*!
            * \brief Set Gain
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value between 0 and 1
            */
            void SetGain(float value);

            /*!
            * \brief Set Auto Gain
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value
            */
            void SetAutoGain(bool value);

            /*!
            * \brief Set Exposure
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value between 0 and 1
            */
            void SetExposure(float value);

            /*!
            * \brief Set Auto Exposure
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value
            */
            void SetAutoExposure(bool value);

            /*!
            * \brief Set Brightness
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value between 0 and 1
            */
            void SetBrightness(float value);

            /*!
            * \brief Set Saturation
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value between 0 and 1
            */
            void SetSaturation(float value);

            /*!
            * \brief Set Hue
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value between 0 and 1
            */
            void SetHue(float value);

            /*!
            * \brief Set Contrast
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value between 0 and 1
            */
            void SetContrast(float value);

            int ov7670_write(uint8_t reg,uint8_t value);
            int ov7670_read(uint8_t reg,uint8_t* value);
            unsigned char ov7670_abs_to_sm(uint8_t v);
            int ov7670_store_cmatrix(int matrix[CMATRIX_LEN]);
            void ov7670_calc_cmatrix(int matrix[CMATRIX_LEN]);
            float hue,sat;
            core::I2cPort* i2cport;
            //cmatrix for V4L2_MBUS_FMT_UYVY8_2X8
            int cmatrix[CMATRIX_LEN]= { 128, -128, 0, -34, -94, 128 };
    };
} // end namespace sensor
} // end namespace flair
#endif // ARDRONE2CAMV_H
