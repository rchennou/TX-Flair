// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file BebopImu.h
 * \brief Class for Bebop IMU
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2017/04/25
 * \version 4.0
 */

#ifndef BEBOPIMU_H
#define BEBOPIMU_H

#include <Thread.h>
#include <Imu.h>

class MPU6050;
namespace flair {
    namespace core {
        class I2cPort;
    }
}

namespace flair { namespace sensor {
    /*! \class BebopImu
    *
    * \brief Class for Bebop IMU
    */
    class BebopImu : public core::Thread, public sensor::Imu {
        public:
            /*!
            * \brief Constructor
            *
            * Construct a BebopImu.
						* It will be child of the FrameworkManager.
            *
            * \param name name
            * \param i2cPort i2c port
            * \param priority priority of the Thread
            */
            BebopImu(std::string name,core::I2cPort* i2cPort,uint8_t priority);

            /*!
            * \brief Destructor
            *
            */
            ~BebopImu();

            /*!
            * \brief Use default plot
            *
            */
            void UseDefaultPlot(void);

        private:
            /*!
            * \brief Run function
            *
            * Reimplemented from Thread.
            *
            */
            void Run(void);
            
            void UpdateFrom(const core::io_data *data){};
            
            MPU6050* mpu;
    };
} // end namespace sensor
} // end namespace flair

#endif // BEBOPIMU_H
