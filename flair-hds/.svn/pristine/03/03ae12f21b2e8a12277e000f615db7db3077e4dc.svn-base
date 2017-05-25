//  created:    2015/10/07
//  filename:   HoughLines.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    HoughLines
//
//
/*********************************************************************/

#include "HoughLines.h"
#include <cvimage.h>
#include <OneAxisRotation.h>
#include <cvmatrix.h>
#include <Layout.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <DoubleSpinBox.h>
#include <dspcv_gpp.h>
#include <typeinfo>

#define MAX_LINES 100

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair { namespace filter {

HoughLines::HoughLines(const IODevice* parent,const LayoutPosition* position,string name,const Vector2Df *inPtRefGlobal,float inThetaRefGlobal) : IODevice(parent,name) {
  GroupBox* reglages_groupbox=new GroupBox(position,name);
  rotation=new OneAxisRotation(reglages_groupbox->NewRow(),"pre rotation");
  fullRhoStep=new SpinBox(reglages_groupbox->NewRow(),"full rho step:","pixels",0,255,1,1);
  fullThetaStep=new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),"full theta step:","degrees",0,90,1,1);
  trackingRhoStep=new SpinBox(reglages_groupbox->NewRow(),"tracking rho step:","pixels",0,255,1,1);
  trackingThetaStep=new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),"tracking theta step:","degrees",0,90,1,1);
  trackingDeltaTheta=new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),"tracking delta theta:","degrees",0,90,1,1);
  nbPoints=new SpinBox(reglages_groupbox->NewRow(),"nb points:",0,10000,10,100);

  isTracking=false;
  linesStorage = cvCreateMat(MAX_LINES, 1, CV_32FC2);

  //init output matrix of same size as init
  cvmatrix_descriptor* desc=new cvmatrix_descriptor(4,1);
  desc->SetElementName(0,0,"distance");
  desc->SetElementName(1,0,"orientation rad");
  desc->SetElementName(2,0,"orientation deg");
  desc->SetElementName(3,0,"line_detected");
  output=new cvmatrix(this,desc,floatType,name);
  delete desc;

  try{
    cvimage::Type const &imageType=dynamic_cast<cvimage::Type const &>(parent->GetOutputDataType());
    if(imageType.GetFormat()!=cvimage::Type::Format::Gray) {
        Err("input image is not gray\n");
    }
  } catch(std::bad_cast& bc) {
    Err("io type mismatch\n");
  }
  
  thetaRefGlobal=inThetaRefGlobal;
  if (inPtRefGlobal==NULL) {
    ptRefGlobal=NULL;
  } else { //rotation from global coordinates to hough space
    ptRefGlobal =new Vector2Df(inPtRefGlobal->x,inPtRefGlobal->y);
  }
}

HoughLines::~HoughLines(void) {
    cvReleaseMat(&linesStorage);
    if(ptRefGlobal!=NULL) delete ptRefGlobal;
}

//select best line. Returns false if no line found
bool HoughLines::SelectBestLine(CvMat* linesStorage, size_t nbLines, float &rho, float &theta) {
  if(nbLines==0) {
    return false;
  }
  //one line is found
  if (nbLines==1) {
    rho=linesStorage->data.fl[0];
    theta=linesStorage->data.fl[1];
    //printf("rho=%f,theta=%f (one line)\n",rho,theta);
    return true;
  }
  //lines are ordered by quality, the first one will be our reference
  float thetaRef=linesStorage->data.fl[1];
  float thetaRefErrorSum=0;
  float rhoSum=linesStorage->data.fl[0];
  //printf("rho=%f,theta=%f (first of multilines)\n",rhoSum,thetaRef);
  for(int i=1;i<nbLines;i++) {
    //printf("rho=%f,theta=%f (multilines)\n",linesStorage->data.fl[2*i],linesStorage->data.fl[2*i+1]);
    float thetaDiff=linesStorage->data.fl[2*i+1]-thetaRef;
    float rhoLine=linesStorage->data.fl[2*i];
    if (thetaDiff>CV_PI/2) {
      thetaDiff-=CV_PI;
      rhoLine=-rhoLine;
    } else if (thetaDiff<-CV_PI/2) {
      thetaDiff+=CV_PI;
      rhoLine=-rhoLine;
    }
    thetaRefErrorSum += thetaDiff;
    rhoSum+=rhoLine;
  }
  rho=rhoSum/nbLines;
  theta=thetaRef+thetaRefErrorSum/nbLines;
  if (theta<0) {
    theta+=CV_PI;
    rho=-rho;
  }
  if (theta>CV_PI) {
    theta-=CV_PI;
    rho=-rho;
  }
  return true;
}

void HoughLines::UpdateFrom(const io_data *data) {
  cvimage *cvImage=(cvimage*)data;
  IplImage *gimg=cvImage->img;
  size_t nbLines;
  Vector2Df ptRef;
  float thetaRef;
  
  if (ptRefGlobal==NULL) {
      ptRef.x=cvImage->GetDataType().GetWidth()/2;
      ptRef.y=cvImage->GetDataType().GetHeight()/2;
  } else { //rotation from global coordinates to hough space
      Vector3Df ptRef3D(ptRefGlobal->x,ptRefGlobal->y,0);
      rotation->ComputeRotation(ptRef3D);
      ptRef.x=ptRef3D.x;
      ptRef.y=ptRef3D.y;
  }
  
  //orientation in global space is rotated by pi/2 compared to orientation in hough space
  //eg: vertical line has a 0 orientation in global space (north), but a pi/2 (or -pi/2) orientation in hough space (theta)
  thetaRef=thetaRefGlobal+CV_PI/2+rotation->GetAngle();
  if (thetaRef>CV_PI) thetaRef-=CV_PI;
  if (thetaRef<0) thetaRef+=CV_PI;
    
    data->GetMutex();
    if(!isTracking) {
        nbLines=dspHoughLines2(gimg,linesStorage,CV_HOUGH_STANDARD,
                                fullRhoStep->Value(),fullThetaStep->Value()*CV_PI/180,
                                nbPoints->Value());
    } else {
        nbLines=dspHoughLinesTracking(gimg,linesStorage,CV_HOUGH_STANDARD,
                                     trackingRhoStep->Value(),
                                     theta,trackingDeltaTheta->Value()*CV_PI/180,
                                     trackingThetaStep->Value()*CV_PI/180,
                                     nbPoints->Value());
/*        nbLines=dspHoughLines2_test(gimg,linesStorage,CV_HOUGH_STANDARD,
                                     trackingRhoStep->Value(),
                                     thetaPrev-trackingDeltaTheta->Value()*CV_PI/180,thetaPrev+trackingDeltaTheta->Value()*CV_PI/180,
                                     trackingThetaStep->Value()*CV_PI/180,
                                     nbPoints->Value());*/
    }
    data->ReleaseMutex();

    //saturation sur le nb max de ligne, au cas ou le DSP n'aurait pas la meme valeur
    if(nbLines>MAX_LINES) {
        Warn("erreur nb lines %u>%u\n",nbLines,MAX_LINES);
        nbLines=MAX_LINES;
    }
    float rho;
    bool noLine=!SelectBestLine(linesStorage,nbLines,rho,theta);

    if (noLine) {
        isTracking=false;
    } else {
        isTracking=true;
//        float thetaRef=0;

        //line equation is ax+by+c=0 with a=cos(theta), b=sin(theta) and c=-rho
        //distance from point xRef,yRef to the line is (a.xRef+b.yRef+c)/sqrt(a*a+b*b)
        distance=-(cos(theta)*ptRef.x+sin(theta)*ptRef.y-rho);

        orientation=theta-thetaRef;
        if (orientation<-CV_PI/2) {
          orientation+=CV_PI;
          distance=-distance;
        }
        if (orientation>CV_PI/2) {
          orientation-=CV_PI;
          distance=-distance;
        }

        //printf("=> pour theta=%f et rho=%f, distance au point(%f,%f)=%f\n",theta,rho,xRef,yRef,distance);
   }

    output->GetMutex();
    output->SetValueNoMutex(0,0,distance);
    output->SetValueNoMutex(1,0,orientation);
    output->SetValueNoMutex(2,0,orientation*180/CV_PI);
    if(noLine) {
        output->SetValueNoMutex(3,0,0);
    } else {
        output->SetValueNoMutex(3,0,1);
    }
    output->ReleaseMutex();

    output->SetDataTime(data->DataTime());
    ProcessUpdate(output);
}

bool HoughLines::isLineDetected() const {
    if(output->Value(3,0)==1) {
        return true;
    } else {
        return false;
    }
}

float HoughLines::GetOrientation(void) const {
    return output->Value(1,0);
}

float HoughLines::GetDistance(void) const {
    return output->Value(0,0);
}

cvmatrix *HoughLines::Output(void) const {
    return output;
}

} // end namespace filter
} // end namespace flair
