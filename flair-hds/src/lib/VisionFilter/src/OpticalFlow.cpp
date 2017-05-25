//  created:    2012/04/12
//  filename:   OpticalFlow.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    calcul flux optique lk
//
//
/*********************************************************************/

#include "OpticalFlow.h"
#include "OpticalFlowData.h"
#include <cvimage.h>
#include <Layout.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <dspcv_gpp.h>
#include <algorithm>
#include <OneAxisRotation.h>
#include <Vector3D.h>
#include <typeinfo>

#define LEVEL_PYR 2

using std::string;
using std::swap;
using namespace flair::core;
using namespace flair::gui;

namespace flair
{
namespace filter
{

OpticalFlow::OpticalFlow(const IODevice* parent,const LayoutPosition* position,string name) : IODevice(parent,name)
{
    Printf("optical flow: voir pour faire du multiple output\n");//pour pts A et B, found et error

    try{
        cvimage::Type const &imageType=dynamic_cast<cvimage::Type const &>(parent->GetOutputDataType());
        pyr=cvCreateImage(cvSize(imageType.GetWidth(),imageType.GetHeight()),IPL_DEPTH_8U,1);
        pyr_old=cvCreateImage(cvSize(imageType.GetWidth(),imageType.GetHeight()),IPL_DEPTH_8U,1);

    } catch(std::bad_cast& bc) {
        Err("io type mismatch\n");
        pyr=NULL;
        pyr_old=NULL;
    }

    is_init=false;

    GroupBox* reglages_groupbox=new GroupBox(position,name);
    rotation=new OneAxisRotation(reglages_groupbox->NewRow(),"post rotation");
    max_features=new SpinBox(reglages_groupbox->NewRow(),"max features:",1,65535,1,1);

    output=new OpticalFlowData(parent,max_features->Value());

    pointsA=(CvPoint *)cvAlloc(max_features->Value()*sizeof(CvPoint));
    pointsB=(CvPoint *)cvAlloc(max_features->Value()*sizeof(CvPoint));

    found_feature=(char *)cvAlloc(max_features->Value()*sizeof(char));
    feature_error=(unsigned int *)cvAlloc(max_features->Value()*sizeof(unsigned int));
}

OpticalFlow::~OpticalFlow(void)
{
    cvReleaseImage(&pyr);
    cvReleaseImage(&pyr_old);
    cvFree(&pointsA);
    cvFree(&pointsB);
    cvFree(&found_feature);
    cvFree(&feature_error);
}

void OpticalFlow::UpdateFrom(const io_data *data) {
//Time tStart=GetTime();
    IplImage *gimg=((cvimage*)data)->img;
    IplImage *gimg_old=((cvimage*)data->Prev(1))->img;

    unsigned int count;
    CvSize window = cvSize(3,3);
    CvTermCriteria termination_criteria = cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3 );
    unsigned int i;

    if(max_features->ValueChanged()==true) {
        cvFree(&pointsA);
        cvFree(&pointsB);
        cvFree(&found_feature);
        cvFree(&feature_error);
        pointsA=(CvPoint *)cvAlloc(max_features->Value()*sizeof(CvPoint));
        pointsB=(CvPoint *)cvAlloc(max_features->Value()*sizeof(CvPoint));
        found_feature=(char *)cvAlloc(max_features->Value()*sizeof(char));
        feature_error=(unsigned int *)cvAlloc(max_features->Value()*sizeof(unsigned int));

        output->Resize(max_features->Value());
    }

    if(is_init==false) {
        data->GetMutex();
        //init image old
        dspPyrDown(gimg,pyr_old,LEVEL_PYR);
        data->ReleaseMutex();
        is_init=true;
        printf("ajouter mise a 0 des points\n");
        return;
    }

    data->GetMutex();
    data->Prev(1)->GetMutex();

    //select good features
    count=max_features->Value();
    dspGoodFeaturesToTrack(gimg_old,pointsA,&count,0.08,5);
    //pyramide
    dspPyrDown(gimg,pyr,LEVEL_PYR);
    //lk
    dspCalcOpticalFlowPyrLK(gimg_old,gimg,pyr_old,pyr,pointsA,pointsB,count,window,LEVEL_PYR,found_feature,feature_error,termination_criteria,0) ;

    data->Prev(1)->ReleaseMutex();
    data->ReleaseMutex();

    //apply rotation
    for(i=0;i<count;i++) {
        Vector3Df tmp;
        tmp.x=pointsA[i].x;
        tmp.y=pointsA[i].y;
        tmp.z=0;
        rotation->ComputeRotation(tmp);
        pointsA[i].x=tmp.x;
        pointsA[i].y=tmp.y;

        tmp.x=pointsB[i].x;
        tmp.y=pointsB[i].y;
        tmp.z=0;
        rotation->ComputeRotation(tmp);
        pointsB[i].x=tmp.x;
        pointsB[i].y=tmp.y;
    }

    output->GetMutex();
    CvPoint2D32f* pointsBf= output->PointsB();
    for(i=0;i<count;i++) {
        pointsBf[i].x=pointsA[i].x+((float)pointsB[i].x)/256;
        pointsBf[i].y=pointsA[i].y+((float)pointsB[i].y)/256;
    }
    output->ReleaseMutex();

    output->SetPointsA(pointsA);
    output->SetFoundFeature(found_feature);
    output->SetFeatureError(feature_error);
    output->SetNbFeatures(count);

    //rotation
    swap(pyr,pyr_old);

    output->SetDataTime(data->DataTime());
//Printf("Optical flow computation time=%f\n",(GetTime()-tStart)/(1000.*1000));
    ProcessUpdate(output);
}

} // end namespace filter
} // end namespace flair
