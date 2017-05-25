// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/12/19
//  filename:   ArDrone2NavBoard.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet integrant les capteurs ardrone2
//
//
/*********************************************************************/

#include "ArDrone2NavBoard.h"
#include <FrameworkManager.h>
#include <cvmatrix.h>
#include <Imu.h>
#include <ImuData.h>
#include <UsRangeFinder.h>
#include <SerialPort.h>

#define G 9.81

using std::string;
using namespace flair::core;
using namespace flair::sensor;

namespace {

//from /data/config.ini
const float gyros_gains[3] = { 1.0679195e-03 ,-1.0669589e-03 ,-1.0683396e-03 };
const float acc_gains[3] = { 2.0327346e+00 ,-1.9626701e+00 ,-1.9494846e+00 };

class ArDrone2Imu : public Imu {
public:
    ArDrone2Imu(string name) :Imu(name) {
        //AddDataToLog(imudata);
    }

    ~ArDrone2Imu() {}

    void SetDatas(const Vector3Df &rawAcc,const Vector3Df &rawMag,const Vector3Df &rawGyr,Time time) {
        ImuData* imuData;
        GetDatas(&imuData);
        Vector3Df rawAccTmp=rawAcc;
        Vector3Df rawMagTmp=rawMag;
        Vector3Df rawGyrTmp=rawGyr;
        ApplyRotation(rawAccTmp);
        ApplyRotation(rawMagTmp);
        ApplyRotation(rawGyrTmp);
        imuData->SetRawAccMagAndGyr(rawAccTmp,rawMagTmp,rawGyrTmp);
        imuData->SetDataTime(time);
        ProcessUpdate(imuData);
    }
    void SetIsReady(bool status) {
      Imu::SetIsReady(status);
    }

private:
    void UpdateFrom(const io_data *data){};
};

class ArDrone2Us : public UsRangeFinder {
public:
    ArDrone2Us(string name) :UsRangeFinder(name) {}

    ~ArDrone2Us() {}

    void SetData(float value,Time time) {
        output->SetValue(0,0,value);
        output->SetDataTime(time);
        ProcessUpdate(output);
    }

private:
    void UpdateFrom(const io_data *data){};
};

}

namespace flair { namespace sensor {

ArDrone2NavBoard::ArDrone2NavBoard(string name,SerialPort* serialport,uint8_t priority) : Thread(getFrameworkManager(),name,priority) {
    this->serialport=serialport;

    us=new ArDrone2Us("parrot-us");
    imu=new ArDrone2Imu("parrot-imu");

    serialport->SetBaudrate(460800);
}

ArDrone2NavBoard::~ArDrone2NavBoard() {
    SafeStop();
    Join();

    delete imu;
    delete us;
}

Imu* ArDrone2NavBoard::GetImu(void) const {
    return imu;
}

UsRangeFinder* ArDrone2NavBoard::GetUsRangeFinder(void) const {
    return us;
}

void ArDrone2NavBoard::UseDefaultPlot(void) {
    us->UseDefaultPlot();
    imu->UseDefaultPlot();
}

void ArDrone2NavBoard::Run(void) {
    uint8_t data[60];
    nav_struct* nav=(nav_struct*)data;
    ssize_t lu=0;

    // stop acquisition
    uint8_t cmd=0x02;
    serialport->Write(&cmd, 1);

    SleepMS(20);
    serialport->FlushInput();

    // start acquisition
    cmd=0x01;
    serialport->Write(&cmd, 1);

    while(!ToBeStopped()) {
        lu+=serialport->Read(data+lu,sizeof(data)-lu);
        if (lu < 0) {
            Warn("error reading navboard %i %i\n",errno,lu);
        }
        
        if(lu!=sizeof(data)) continue;

        if(nav->size==0x3a) {
            Time time=GetTime();

            if(nav->checksum == Checksum(data)) {
                computeDatas(nav,time);
                lu=0;
            } else {
                Warn("Wrong checksum: got %x, expected %x, time %lld\n",nav->checksum,Checksum(data),time);
                for(int i=0;i<lu;i++) Printf("%x ",data[i]);
                Printf("\n");
                int i;
                for(i=1;i<lu;i++) {//skeep first
                    if(data[i]==0x3a) break;
                }
                printf("ok en %i\n",i);
                int k=0;
                for(int j=i;j<lu;j++) {
                        data[k]=data[j];
                        k++;
                }
                lu=k;
                for(int i=0;i<lu;i++) Printf("%x ",data[i]);
                Printf("\n");
            }
        } else {
            Warn("Wrong header: got %x, expected 0x3a, time %lld\n",data[0],GetTime());
            for(int i=0;i<lu;i++) Printf("%x ",data[i]);
            Printf("\n");
            int i;
            for(i=1;i<lu;i++) {//skeep first
                if(data[i]==0x3a) break;
            }
            printf("ok en %i\n",i);
            int k=0;
            for(int j=i;j<lu;j++) {
                    data[k]=data[j];
                    k++;
            }
            lu=k;
            for(int i=0;i<lu;i++) Printf("%x ",data[i]);
            Printf("\n");
        }
    }
}

void ArDrone2NavBoard::computeDatas(nav_struct* nav,Time time) {
    static float accs_offset[3]={0,0,0};
    static float gyrs_offset[3]={0,0,0};
    static int cpt=0;
    static uint16_t prev_seq;

    float ax,ay,az;
    float gx,gy,gz;
    float mx,my,mz;

    if(cpt!=0 && (uint16_t)(nav->seq-prev_seq)!=1) Warn("lost %i sample(s)\n",nav->seq-prev_seq-1);
    prev_seq=nav->seq;
    
    if(cpt==0) Printf("ArDrone2NavBoard::calibrating offsets, do not move imu\n");
    
    if(cpt<2000) { //init offsets
        for(int i=0;i<3;i++) accs_offset[i]+=nav->acc[i];
        for(int i=0;i<3;i++) gyrs_offset[i]+=nav->gyro[i];
        
        if(cpt==1999) {
          ((ArDrone2Imu*)imu)->SetIsReady(true);
          Printf("ArDrone2NavBoard::calibration done\n");
        }
        cpt++;
        ax=0;
        ay=0;
        az=-G;//todo: should be done after applying rotation to the imu!!
        gx=0;
        gy=0;
        gz=0;
        mx=0;
        my=0;
        mz=0;
    } else {
        ax=acc_gains[0]*(nav->acc[0]-accs_offset[0]/cpt)/100.;//gains from parrot are in cm.s-2
        ay=acc_gains[1]*(nav->acc[1]-accs_offset[1]/cpt)/100.;
        az=acc_gains[2]*((nav->acc[2]-accs_offset[2]/cpt)/100.)-G;//todo: should be done after applying rotation to the imu!!

        gx=gyros_gains[0]*(nav->gyro[0]-gyrs_offset[0]/cpt);
        gy=gyros_gains[1]*(nav->gyro[1]-gyrs_offset[1]/cpt);
        gz=gyros_gains[2]*(nav->gyro[2]-gyrs_offset[2]/cpt);

        mx=nav->mag[0];
        my=nav->mag[1];
        mz=nav->mag[2];
    }

    ((ArDrone2Imu*)imu)->SetDatas(Vector3Df(ax,ay,az),
                                Vector3Df(mx,my,mz),
                                Vector3Df(gx,gy,gz),
                                time
                                );


     if(((nav->us_echo)&0x8000)==0x8000) {

       // printf("%i %i %i %i %i %i %i %i %i %i %i %i %i\n",nav->us_echo,nav->us_echo-0x8000,nav->us_echo_start,nav->us_echo_end,nav->us_association_echo,nav->us_distance_echo,
        //       nav->us_courbe_temps,nav->us_courbe_valeur,nav->us_courbe_ref,nav->nb_echo,nav->sum_echo,nav->gradient,nav->flag_echo_ini);
      if(nav->us_association_echo!=0) {
        Warn("us assoc echo=%i(!=0)\n",nav->us_association_echo);//TODO: on perd un sample, voir si on fait une prédiction?
        Warn("%i %i %i\n",nav->us_echo,nav->us_echo_start,nav->us_echo_end);//TODO: on perd un sample, voir is on fait une prédiction?
        Warn("%i %i\n",nav->nb_echo,nav->sum_echo);
        Warn("%f\n",(float)(((nav->us_echo)&0x7fff)) * 0.0340/100.);
      }else{
        float h  = (float)(((nav->us_echo)&0x7fff)) * 0.0340/100.;
        ((ArDrone2Us*)us)->SetData(h,time);
      }
    }
}

uint16_t ArDrone2NavBoard::Checksum(const uint8_t *data) const{
    uint16_t checksum = 0;
    for(int i = 2; i < 60-2; i += 2) {
        checksum += data[i] + (data[i+1] << 8);
    }
    return checksum;
}

} // end namespace sensor
} // end namespace flair

