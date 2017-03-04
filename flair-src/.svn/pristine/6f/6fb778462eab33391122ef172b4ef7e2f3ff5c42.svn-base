// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2007/10/17, 2014/01/15
//  filename:   AhrsKalman_impl.cpp
//
//  author:     Tom Pycke (tom.pycke@gmail.com)
//		API changes by Guillaume Sanahuja to fit the Flair framework
//
//  version:    $Id: $
//
//  purpose:    Class defining an Ahrs Kalman filter
//
//
/*********************************************************************/

/***********************************************************************
 *                                                                     *
 * This file contains the code for the kalman filter that uses the     *
 * sensor data as inputs.                                              *
 *                                                                     *
 *                                                                     *
 ***********************************************************************
 *                                                                     *
 * Comments:                                                           *
 *   To help others to understand the kalman filter, I used one of     *
 *   the most accessible sources with information on it:               *
 *   http://en.wikipedia.org/wiki/Kalman_filter                        *
 *   The code is split into 2 parts: a Predict function and an         *
 *   Update function, just as the wikipedia page does.                 *
 *   The model I used in the kalman filter is the following:           *
 *   Our gyroscope measures the turnrate in degrees per second. This   *
 *   is the derivative of the angle, called dotAngle. The bias is the  *
 *   output of our gyro when the rotationrate is 0 degrees per second  *
 *   (not rotating). Because of drift it changes over time.            *
 *   So mathematically we just integrate the gyro (dt is timespan      *
 *   since last integration):                                          *
 *              angle = angle + (dotAngle - bias) * dt                 *
 *   When we include the bias in our model, the kalman filter will     *
 *   try to estimate the bias, thanks to our last input: the measured  *
 *   angle. This is just an estimate and comes from the accelerometer. *
 *   So the state used in our filter had 2 dimensions: [ angle, bias ] *
 *   Jump to the functions to read more about the actual               *
 *   implementation.                                                   *
 *                                                                     *
 ***********************************************************************/

#include "AhrsKalman.h"
#include "AhrsKalman_impl.h"
#include <Imu.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <Layout.h>
#include <LayoutPosition.h>
#include <ImuData.h>
#include <AhrsData.h>
#include <math.h>

#define PI ((float)3.14159265358979323846)

using std::string;
using namespace flair::core;
using namespace flair::gui;

AhrsKalman_impl::AhrsKalman_impl(const Layout* layout,AhrsData *inAhrsData): ahrsData(inAhrsData) {
    is_init=false;
    euler.yaw=0;

    Q_angle=new DoubleSpinBox(layout->NewRow(),"Q_angle:",0.,10000,0.0001,4);
    Q_gyro=new DoubleSpinBox(layout->NewRow(),"Q_gyro:",0.,10000,0.0001,4);
    R_angle=new DoubleSpinBox(layout->NewRow(),"R_angle:",0.,1000000,0.0001,4);


    //init ars
    //ars_Init(&ars_roll, 1/*Q_angle*/, 0.1/*Q_gyro*/, 10000/*R_angle*/);
    //ars_Init(&ars_pitch, 1/*Q_angle*/, 0.1/*Q_gyro*/, 10000/*R_angle*/);
    ars_Init(&ars_roll, Q_angle->Value(), Q_gyro->Value(), R_angle->Value());
    ars_Init(&ars_pitch, Q_angle->Value(), Q_gyro->Value(), R_angle->Value());
}

AhrsKalman_impl::~AhrsKalman_impl() {
}

void AhrsKalman_impl::UpdateFrom(const io_data *data) {
    ImuData *input=(ImuData*)data;
    float delta_t;
    Vector3D rawAcc,rawMag,rawGyr;

    input->GetRawAccMagAndGyr(rawAcc,rawMag,rawGyr);

    delta_t=(float)(data->DataTime()-previous_time)/1000000000.;
    previous_time=data->DataTime();

    if(Q_angle->ValueChanged() || Q_gyro->ValueChanged() || R_angle->ValueChanged()) {
        ars_Init(&ars_roll, Q_angle->Value(), Q_gyro->Value(), R_angle->Value());
        ars_Init(&ars_pitch, Q_angle->Value(), Q_gyro->Value(), R_angle->Value());
    }

    if(is_init==true) {
        //execute kalman roll filter
        ars_predict(&ars_roll, rawGyr.x, delta_t);
        ars_update(&ars_roll, atan2(-rawAcc.y, -rawAcc.z));//1 ou -az
       
        //execute kalman pitch filter
        ars_predict(&ars_pitch, rawGyr.y, delta_t);
        ars_update(&ars_pitch, -atan2(-rawAcc.x, -rawAcc.z));//1 ou -az


        euler.roll=ars_roll.x_angle;
        euler.pitch=ars_pitch.x_angle;
        euler.yaw += rawGyr.z *delta_t;
        if(euler.yaw>PI) euler.yaw-=2*PI;
        if(euler.yaw<-PI) euler.yaw+=2*PI;

        ahrsData->SetQuaternionAndAngularRates(euler.ToQuaternion(),
                                               rawGyr-Vector3D(ars_roll.x_bias,ars_pitch.x_bias,0));
    } else {
        is_init=true;
    }

    ahrsData->SetDataTime(data->DataTime());
}


void AhrsKalman_impl::ars_Init(ars_Gyro1DKalman *ars, double Q_angle, double Q_gyro, double R_angle) {
    ars->Q_angle = Q_angle;
    ars->Q_gyro  = Q_gyro;
    ars->R_angle = R_angle;
    ars->x_bias=0;
    ars->x_angle=0;
    ars->P_00 =0;
    ars->P_01 =0;
    ars->P_10 =0;
    ars->P_11 =0;
}

/*
 * The predict function. Updates 2 variables:
 * our model-state x and the 2x2 matrix P
 *
 * x = [ angle, bias ]'
 *
 *   = F x + B u
 *
 *   = [ 1 -dt, 0 1 ] [ angle, bias ] + [ dt, 0 ] [ dotAngle 0 ]
 *
 *   => angle = angle + dt (dotAngle - bias)
 *      bias  = bias
 *
 *
 * P = F P transpose(F) + Q
 *
 *   = [ 1 -dt, 0 1 ] * P * [ 1 0, -dt 1 ] + Q
 *
 *  P(0,0) = P(0,0) - dt * ( P(1,0) + P(0,1) ) + dt * P(1,1) + Q(0,0)
 *  P(0,1) = P(0,1) - dt * P(1,1) + Q(0,1)
 *  P(1,0) = P(1,0) - dt * P(1,1) + Q(1,0)
 *  P(1,1) = P(1,1) + Q(1,1)
 *
 *
 */
void AhrsKalman_impl::ars_predict(ars_Gyro1DKalman *ars, const double dotAngle, const double dt) {
    ars->x_angle += dt * (dotAngle - ars->x_bias);

    ars->P_00 +=  - dt * (ars->P_10 + ars->P_01) + ars->Q_angle * dt;
    ars->P_01 +=  - dt * ars->P_11;
    ars->P_10 +=  - dt * ars->P_11;
    ars->P_11 +=  + ars->Q_gyro * dt;
}

/*
 *  The update function updates our model using
 *  the information from a 2nd measurement.
 *  Input angle_m is the angle measured by the accelerometer.
 *
 *  y = z - H x
 *
 *  S = H P transpose(H) + R
 *    = [ 1 0 ] P [ 1, 0 ] + R
 *    = P(0,0) + R
 *
 *  K = P transpose(H) S^-1
 *    = [ P(0,0), P(1,0) ] / S
 *
 *  x = x + K y
 *
 *  P = (I - K H) P
 *
 *    = ( [ 1 0,    [ K(0),
 *          0 1 ] -   K(1) ] * [ 1 0 ] ) P
 *
 *    = [ P(0,0)-P(0,0)*K(0)  P(0,1)-P(0,1)*K(0),
 *        P(1,0)-P(0,0)*K(1)  P(1,1)-P(0,1)*K(1) ]
 */
void AhrsKalman_impl::ars_update(ars_Gyro1DKalman *ars, const double angle_m) {
    const double y = angle_m - ars->x_angle;

    const double S = ars->P_00 + ars->R_angle;
    const double K_0 = ars->P_00 / S;
    const double K_1 = ars->P_10 / S;

    ars->x_angle +=  K_0 * y;
    ars->x_bias  +=  K_1 * y;

    ars->P_00 -= K_0 * ars->P_00;
    ars->P_01 -= K_0 * ars->P_01;
    ars->P_10 -= K_1 * ars->P_00;
    ars->P_11 -= K_1 * ars->P_01;
}
