/*!
 * \file ArDrone2CamH.h
 * \brief Class for ardrone2 horizontal camera
 * \author Guillaume Sanahuja
 * \date 2014/07/16
 * \version 4.0
 */

#ifndef ARDRONE2CAMH_H
#define ARDRONE2CAMH_H

#include "V4LCamera.h"

struct regval_list {
  uint16_t reg_num;
  uint16_t size;
  uint32_t value;
};

namespace flair {
    namespace core {
        class I2cPort;
    }
}

namespace flair {
namespace sensor {
    /*! \class ArDrone2CamH
    *
    * \brief Class for ardrone2 horizontal camera
    */
    class ArDrone2CamH : public V4LCamera {
        public:
            /*!
            * \brief Constructor
            *
            * Construct a ArDrone2CamH.
						* It will be child of the FrameworkManager.
            *
            * \param name name
            * \param width width
            * \param height height
            * \param priority priority of the Thread
            */
            ArDrone2CamH(std::string name,uint16_t width,uint16_t height,uint8_t priority);

            /*!
            * \brief Destructor
            *
            */
            ~ArDrone2CamH();

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
            * \brief Set Contrast
            *
            * Reimplemented from V4LCamera class
            *
            * \param value value between 0 and 1
            */
            void SetContrast(float value);

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



            void mt9m114_detect(void);
            void mt9m114_init(void);
            int mt9m114_reset(void);
            int mt9m114_errata_1(void);
            int mt9m114_errata_2(void);
            int mt9m114_PLL_settings(void);
            int mt9m114_write_array(struct regval_list *vals);
            int mt9m114_sensor_optimization(void);
            int soc1040_read_reg(uint16_t reg, uint32_t *val,uint16_t data_length);
            int soc1040_write_reg(uint16_t reg,uint32_t val, uint16_t data_length);
            int check_uvc_status(const char* funcName);
            int mt9m114_refresh(void);
            int mt9m114_wait_num_frames(uint16_t numFrames);
            int poll_command_register_bit(uint16_t bit_mask);
            core::I2cPort* i2cport;
            struct regval_list *wh_regval_list;
    };
} // end namespace sensor
} // end namespace flair
#endif // ARDRONE2CAMH_H
