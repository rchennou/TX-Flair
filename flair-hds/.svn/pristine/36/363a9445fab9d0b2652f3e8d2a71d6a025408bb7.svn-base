//  created:    2012/04/12
//  filename:   OpticalFlowData.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe pour les données du flux optique
//
/*********************************************************************/

#include "OpticalFlowData.h"

using std::string;

namespace flair
{
namespace filter
{

OpticalFlowData::OpticalFlowData(const Object* parent,uint32_t max_features,string name,uint32_t n): io_data(parent,name,n)
{
    this->max_features=max_features;
    nb_features=0;

    pointsA=(CvPoint *)cvAlloc(max_features*sizeof(CvPoint));
    pointsB=(CvPoint2D32f *)cvAlloc(max_features*sizeof(CvPoint2D32f));

    found_features=(char *)cvAlloc(max_features*sizeof(char));
    features_error=(uint32_t*)cvAlloc(max_features*sizeof(uint32_t));
}

OpticalFlowData::~OpticalFlowData()
{
    cvFree(&pointsA);
    cvFree(&pointsB);

    cvFree(&found_features);
    cvFree(&features_error);
}

CvPoint* OpticalFlowData::PointsA(void) const
{
    return pointsA;
}

CvPoint2D32f* OpticalFlowData::PointsB(void) const
{
    return pointsB;
}

char *OpticalFlowData::FoundFeature(void) const
{
    return found_features;
}

uint32_t *OpticalFlowData::FeatureError(void) const
{
    return features_error;
}

// value is new max_features value
void OpticalFlowData::Resize(uint32_t value) {
    CvPoint *new_pointsA;
    CvPoint2D32f *new_pointsB;
    char *new_found_features;
    uint32_t *new_features_error;

    new_pointsA=(CvPoint *)cvAlloc(value*sizeof(CvPoint));
    new_pointsB=(CvPoint2D32f *)cvAlloc(value*sizeof(CvPoint2D32f));
    new_found_features=(char *)cvAlloc(value*sizeof(char));
    new_features_error=(uint32_t *)cvAlloc(value*sizeof(uint32_t));

    GetMutex();
    if(value>max_features)
    {
        memcpy(new_pointsA,pointsA,max_features*sizeof(CvPoint));
        memcpy(new_pointsB,pointsB,max_features*sizeof(CvPoint2D32f));
        memcpy(new_found_features,found_features,max_features*sizeof(char));
        memcpy(new_features_error,features_error,max_features*sizeof(uint32_t));
    }
    else
    {
        memcpy(new_pointsA,pointsA,value*sizeof(CvPoint));
        memcpy(new_pointsB,pointsB,value*sizeof(CvPoint2D32f));
        memcpy(new_found_features,found_features,value*sizeof(char));
        memcpy(new_features_error,features_error,value*sizeof(uint32_t));
        if(nb_features>value) nb_features=value; //si nb_features est le nombre de point qui ont effectivement une correspondande, ça me parait louche. Sauf si les points sont classés et que ceux qui ont une correpondance sont toujours au début
    }
    max_features=value;
    ReleaseMutex();

    cvFree(&pointsA);
    cvFree(&pointsB);
    cvFree(&found_features);
    cvFree(&features_error);

    pointsA=new_pointsA;
    pointsB=new_pointsB;
    found_features=new_found_features;
    features_error=new_features_error;
}

void OpticalFlowData::CopyDatas(char* dst) const
{
    Warn("non implementé\n");
}

void OpticalFlowData::SetPointsA(const CvPoint* points)
{
    GetMutex();
    memcpy(pointsA,points,max_features*sizeof(CvPoint));
    ReleaseMutex();
}

void OpticalFlowData::SetPointsB(const CvPoint2D32f* points)
{
    GetMutex();
    memcpy(pointsB,points,max_features*sizeof(CvPoint2D32f));
    ReleaseMutex();
}

void OpticalFlowData::SetFoundFeature(const char *found_features)
{
    GetMutex();
    memcpy(this->found_features,found_features,max_features*sizeof(char));
    ReleaseMutex();
}

void OpticalFlowData::SetFeatureError(const uint32_t *features_error)
{
    GetMutex();
    memcpy(this->features_error,features_error,max_features*sizeof(uint32_t));
    ReleaseMutex();
}

uint32_t OpticalFlowData::MaxFeatures(void) const
{
    return max_features;
}

uint32_t OpticalFlowData::NbFeatures(void) const
{
    return nb_features;
}

void OpticalFlowData::SetNbFeatures(uint32_t value)
{
    GetMutex();
    nb_features=value;
    ReleaseMutex();
}

} // end namespace filter
} // end namespace flair
