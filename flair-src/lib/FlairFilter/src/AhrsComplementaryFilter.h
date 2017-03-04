// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file AhrsComplementaryFilter.h
 * \brief Class defining an Ahrs Kalman filter
 * \author Augustin Manecy (RT-MaG Toolbox author, augustin.manecy@gmail.com), API changes by Guillaume Sanahuja to fit the Flair framework
 * \date 2014/01/15
 * \version 4.0
 */

#ifndef AHRSCOMPLEMENTARYFILTER_H
#define AHRSCOMPLEMENTARYFILTER_H

#include <Ahrs.h>
#include <Vector3D.h>
#include <Quaternion.h>

namespace flair {
    namespace sensor {
        class Imu;
    }
    namespace gui {
        class DoubleSpinBox;
    }
}

namespace flair { namespace filter {
    /*! \class AhrsComplementaryFilter
    *
    * \brief Class defining an Ahrs complementary filter
    *
    * Implementation from Augustin Manecy
    */
    class AhrsComplementaryFilter : public Ahrs {
        public:
            /*!
            * \brief Constructor
            *
            * Construct an AhrsComplementaryFilter.
            *
            * \param parent parent
            * \param name name
            */
            AhrsComplementaryFilter(const sensor::Imu* parent,std::string name);

            /*!
            * \brief Destructor
            *
            */
            ~AhrsComplementaryFilter();

        private:
            /*!
            * \brief Update using provided datas
            *
            * Reimplemented from IODevice.
            *
            * \param data data from the parent to process
            */
            void UpdateFrom(const core::io_data *data);

            core::Time previous_time;

            bool isInit;
            core::Quaternion QHat;
            core::Vector3D BHat;
            gui::DoubleSpinBox *ka[3];
            gui::DoubleSpinBox *kb[3];
    };
} // end namespace filter
} // end namespace flair
#endif // AHRSCOMPLEMENTARYFILTER_H
