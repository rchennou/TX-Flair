// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file AhrsKalman_impl.h
 * \brief Class defining an Ahrs Kalman filter
 * \author Tom Pycke, API changes by Guillaume Sanahuja to fit the Flair framework
 * \date 2007/10/17, 2014/01/15
 * \version
 */

#ifndef AHRSKALMAN_IMPL_H
#define AHRSKALMAN_IMPL_H

#include <Ahrs.h>
#include <Euler.h>

namespace flair {
    namespace core {
        class AhrsData;
    }
    namespace gui {
        class Layout;
        class DoubleSpinBox;
    }
}

/*! \class AhrsKalman_impl
* \brief Class defining an Ahrs Kalman filter
*/

class AhrsKalman_impl {
    public:
        AhrsKalman_impl(const flair::gui::Layout *layout,flair::core::AhrsData *ahrsData);
        ~AhrsKalman_impl();
        void UpdateFrom(const flair::core::io_data *data);

    private:
        flair::core::AhrsData *ahrsData;
        typedef struct ars_Gyro1DKalman
        {
            /* These variables represent our state matrix x */
            double x_angle,
                  x_bias;

            /* Our error covariance matrix */
            double P_00,
                  P_01,
                  P_10,
                  P_11;

            /*
             * Q is a 2x2 matrix of the covariance. Because we
             * assume the gyro and accelero noise to be independend
             * of eachother, the covariances on the / diagonal are 0.
             *
             * Covariance Q, the process noise, from the assumption
             *    x = F x + B u + w
             * with w having a normal distribution with covariance Q.
             * (covariance = E[ (X - E[X])*(X - E[X])' ]
             * We assume is linair with dt
             */
            double Q_angle, Q_gyro;
            /*
             * Covariance R, our observation noise (from the accelerometer)
             * Also assumed to be linair with dt
             */
            double R_angle;
        } ars_Gyro1DKalman;

        // Initializing the struct
        void ars_Init(ars_Gyro1DKalman *filterdata, double Q_angle, double Q_gyro, double R_angle);
        // Kalman predict
        void ars_predict(ars_Gyro1DKalman *filterdata, const double gyro, const double dt);
        // Kalman update
        void ars_update(ars_Gyro1DKalman *filterdata, const double angle_m);

        ars_Gyro1DKalman ars_roll;
        ars_Gyro1DKalman ars_pitch;
        flair::core::Time previous_time;
        bool is_init;
        flair::gui::DoubleSpinBox *Q_angle,*Q_gyro,*R_angle;
        flair::core::Euler euler;
};

#endif // AHRSKALMAN_IMPL_H
