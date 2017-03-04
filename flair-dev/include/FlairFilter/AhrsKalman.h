// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file AhrsKalman.h
 * \brief Class defining an Ahrs Kalman filter
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/01/15
 * \version 4.0
 */

#ifndef AHRSKALMAN_H
#define AHRSKALMAN_H

#include <Ahrs.h>

namespace flair
{
    namespace sensor
    {
        class Imu;
    }
}

class AhrsKalman_impl;

namespace flair
{
namespace filter
{
    /*! \class AhrsKalman
    *
    * \brief Class defining an Ahrs Kalman filter
    */
    class AhrsKalman : public Ahrs
    {
        public:
            /*!
            * \brief Constructor
            *
            * Construct an AhrsKalman.
            *
            * \param parent parent
            * \param name name
            */
            AhrsKalman(const sensor::Imu* parent,std::string name);

            /*!
            * \brief Destructor
            *
            */
            ~AhrsKalman();

        private:
            /*!
            * \brief Update using provided datas
            *
            * Reimplemented from IODevice.
            *
            * \param data data from the parent to process
            */
            void UpdateFrom(const core::io_data *data);
            AhrsKalman_impl* pimpl_;
    };
} // end namespace filter
} // end namespace flair
#endif // AHRSKALMAN_H
