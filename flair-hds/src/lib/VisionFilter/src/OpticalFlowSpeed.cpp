//  created:    2012/04/12
//  filename:   OpticalFlowSpeed.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    calcul de la vitesse à partir du flux optique
//
//
/*********************************************************************/

#include "OpticalFlowSpeed.h"
#include "OpticalFlowData.h"
#include <cvmatrix.h>
#include <Object.h>
#include <Layout.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <CheckBox.h>
#include <DoubleSpinBox.h>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair { namespace filter {

OpticalFlowSpeed::OpticalFlowSpeed(const IODevice* parent, const Ahrs *ahrs, const LayoutPosition* position,string name) : IODevice(parent,name) {
  cvmatrix_descriptor* desc=new cvmatrix_descriptor(2,1);
  desc->SetElementName(0,0,"vx");
  desc->SetElementName(1,0,"vy");
  output=new cvmatrix(this,desc,floatType,name);
  delete desc;

  AddDataToLog(output);

  GroupBox* reglages_groupbox=new GroupBox(position,name);
  quality=new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),"optical flow quality:",0.,100.,1.,1,5.);
  weightedAverage=new CheckBox(reglages_groupbox->LastRowLastCol(),"Weighted average", true);
  timeMultiplication=new CheckBox(reglages_groupbox->LastRowLastCol(),"Time multiplication", true);
}

OpticalFlowSpeed::~OpticalFlowSpeed(void) { }

void OpticalFlowSpeed::UpdateFrom(const io_data *data) {
    OpticalFlowData *input=(OpticalFlowData*)data;
    float deplx,deply;
    float nb_depl=0;

    deplx=0;
    deply=0;

    //error is 0 if perfect match and 7x7x255x255 at worst
    float qualityThreshold=quality->Value()/100.*7*7*255*255;
    input->GetMutex();
    int nbUsedPoints=0;
    for(int i=0;i<input->NbFeatures();i++) {
        //if point is found in both images and quality is sufficient
        if((input->FoundFeature()[i]!=0)&&(input->FeatureError()[i]<qualityThreshold)) {
          nbUsedPoints++;
          float qualityFactor=1.0;
          if (weightedAverage->Value()) {
            //displacement is weigthed by quality
            qualityFactor/=(1+input->FeatureError()[i]);
          } 
            deplx+=(input->PointsB()[i].x-input->PointsA()[i].x)*qualityFactor;
            deply+=(input->PointsB()[i].y-input->PointsA()[i].y)*qualityFactor;
            nb_depl+=qualityFactor;
        }
    }
    input->ReleaseMutex();
    float deltaT;
    if (timeMultiplication->Value()) deltaT=(float)(data->DataTime()-output->DataTime())/(1000.*1000.*1000.);
    else deltaT=1.;
    output->SetDataTime(data->DataTime());

    if(nb_depl!=0) {
//Printf("Nombre de points=%d/%d (nb_depl=%f,pondération=%d), deltaT=%f\n",nbUsedPoints,input->NbFeatures(),nb_depl,weightedAverage->Value(),deltaT);
        output->SetValue(0,0,deplx/(nb_depl*deltaT));
        output->SetValue(1,0,deply/(nb_depl*deltaT));
    }
//    output->SetDataTime(data->DataTime());
    ProcessUpdate(output);
}

float OpticalFlowSpeed::Vx(void) const {
    return output->Value(0,0);
}

float OpticalFlowSpeed::Vy(void) const {
    return output->Value(1,0);
}

core::cvmatrix *OpticalFlowSpeed::Output() const {
    return output;
}
} // end namespace filter
} // end namespace flair
