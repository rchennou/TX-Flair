// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}

//  created:    2014/04/28
//  filename:   AhrsComplementaryFilter.cpp
//
//  authors:    Augustin Manecy (RT-MaG Toolbox author, augustin.manecy@gmail.com)
//              API changes by Guillaume Sanahuja to fit the Flair framework
//
//  version:    $Id: $
//
//  purpose:    Class defining an Ahrs complementary filter
//
//
/*********************************************************************/

#include "AhrsComplementaryFilter.h"
#include <Imu.h>
#include <DoubleSpinBox.h>
#include <GridLayout.h>
#include <ImuData.h>
#include <AhrsData.h>
#include <math.h>

#define G 9.81

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::sensor;

namespace flair { namespace filter {

AhrsComplementaryFilter::AhrsComplementaryFilter(const Imu* parent,string name): isInit(false), Ahrs(parent,name) {

    QHat.q0=1;
    QHat.q1=0;
    QHat.q2=0;
    QHat.q3=0;
    BHat.x=0;
    BHat.y=0;
    BHat.z=0;

    ka[0]=new DoubleSpinBox(parent->GetLayout()->NewRow(),"ka[0]:",0.,10,0.1,2,0.5);
    ka[1]=new DoubleSpinBox(parent->GetLayout()->LastRowLastCol(),"ka[1]:",0.,10,0.1,2,0.5);
    ka[2]=new DoubleSpinBox(parent->GetLayout()->LastRowLastCol(),"ka[2]:",0.,10.,0.1,2,0.);

    kb[0]=new DoubleSpinBox(parent->GetLayout()->NewRow(),"kb[0]:",0.,10,0.1,2,0.01);
    kb[1]=new DoubleSpinBox(parent->GetLayout()->LastRowLastCol(),"kb[1]:",0.,10,0.1,2,0.01);
    kb[2]=new DoubleSpinBox(parent->GetLayout()->LastRowLastCol(),"kb[2]:",0.,10,0.1,2,0.01);

}

AhrsComplementaryFilter::~AhrsComplementaryFilter() {

}

void AhrsComplementaryFilter::UpdateFrom(const io_data *data) {
    ImuData *input=(ImuData*)data;
    float delta_t;
    AhrsData* ahrsData;
    GetDatas(&ahrsData);
    Vector3D rawAcc,rawMag,rawGyr;
    input->GetRawAccMagAndGyr(rawAcc,rawMag,rawGyr);

    delta_t=(float)(data->DataTime()-previous_time)/1000000000.;
    previous_time=data->DataTime();

    Vector3D aBar,aHat,aTilde;
    Vector3D mBar,mHat,mTilde;
    Vector3D alpha,dBHat,omegaHat;
    Quaternion dQHat;

    //float ka[3]={0.5,0.5,0};
    //float kb[3]={0.01,0.01,0.01};
    float k_m[3]= {0,0,0};

    if(isInit==true) {
        // CORRECTION FORM ACCELEROMETER
        aBar = rawAcc;

        // estimation of IMU vector using QHat (estimated quaternion): aHat = Inv(QHat) * g
        /*
          Inv(QHat) = [q0 -q1 -q2 -q3]'
          Inv(QHat)*g = [1-2(q2^2+q3^2)     2(q1q2+q0q3)     2(q1q3-q0q2)]     [0]
                         [  2(q1q2-q0q3)   1-2(q1^2+q3^2))    2(q2q3+q0q1)]  *  [0]
                         [  2(q1q3+q0q2)     2(q2q3-q0q1)   1-2(q1^2+q2^2)]     [g]
        */
        aHat.x = -2*G*(QHat.q1*QHat.q3 - QHat.q0*QHat.q2);
        aHat.y = -2*G*(QHat.q2*QHat.q3 + QHat.q0*QHat.q1);
        aHat.z = -G*(1-2.0*(QHat.q1*QHat.q1 + QHat.q2*QHat.q2));

        // cross(aHat, aBar)
        aTilde=CrossProduct(aHat, aBar);

        // CORRECTION FROM FICTIOUS MAGNETOMETER (to avoid drift of yaw)
        // estimation of IMU vector using QHat (estimated quaternion): mHat = Inv(QHat) * m_ref = Inv(QHat) * [1.0, 0.0, 0.0]'
        /*
          Inv(QHat) = [q0 -q1 -q2 -q3]'
          Inv(QHat)*g = [1-2(q2^2+q3^2)     2(q1q2+q0q3)     2(q1q3-q0q2)]     [1]
                         [  2(q1q2-q0q3)   1-2(q1^2+q3^2))    2(q2q3+q0q1)]  *  [0]
                         [  2(q1q3+q0q2)     2(q2q3-q0q1)   1-2(q1^2+q2^2)]     [0]
        */
        mBar.x=1;
        mBar.y=0;
        mBar.z=0;

        mHat.x = (1-2.0*(QHat.q2*QHat.q2 + QHat.q3*QHat.q3));
        mHat.y = 2.0*(QHat.q1*QHat.q2 - QHat.q0*QHat.q3);
        mHat.z = 2.0*(QHat.q1*QHat.q3 + QHat.q0*QHat.q2);

        // compute the error between mHat and mTilde
        mTilde=CrossProduct(mHat, mBar);

        // Compute the debiased rotation speed
        omegaHat = rawGyr - BHat;

        // calculate the correction to apply to the quaternion
        alpha.x = (ka[0]->Value()*aTilde.x)/(G*G) + (k_m[0]*mTilde.x);
        alpha.y = (ka[1]->Value()*aTilde.y)/(G*G) + (k_m[1]*mTilde.y);
        alpha.z = (ka[2]->Value()*aTilde.z)/(G*G) + (k_m[2]*mTilde.z);

        // Bias derivative
        dBHat.x = kb[0]->Value() * alpha.x;
        dBHat.y = kb[1]->Value() * alpha.y;
        dBHat.z = kb[2]->Value() * alpha.z;

        // Bias integration
        BHat = BHat+dBHat*delta_t;

        // Quaternion derivative: dQHat = 0.5*(QHat*Q_corr)
        // Q_corr: Corrected pure rotation quaternion for integration
        dQHat=QHat.GetDerivative(omegaHat - alpha);

        // Quaternion integration
        QHat = QHat +dQHat*delta_t;	// delta_t: sampling period [s]

        QHat.Normalize();

        ahrsData->SetQuaternionAndAngularRates(QHat,rawGyr - BHat);

    } else {
        isInit=true;
    }

    ahrsData->SetDataTime(data->DataTime());
    ProcessUpdate(ahrsData);
}

} // end namespace filter
} // end namespace flair
