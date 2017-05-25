//  created:    2015/10/07
//  filename:   ImgThreshold.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    ImgThreshold
//
//
/*********************************************************************/

#include "ImgThreshold.h"
#include <cvimage.h>
#include <Layout.h>
#include <GroupBox.h>
#include <SpinBox.h>
#include <dspcv_gpp.h>
#include <typeinfo>

using std::string;
using namespace flair::core;
using namespace flair::gui;

namespace flair { namespace filter {

ImgThreshold::ImgThreshold(const IODevice* parent,const LayoutPosition* position,string name) : IODevice(parent,name),output(0) {
    GroupBox* reglages_groupbox=new GroupBox(position,name);
    threshold=new SpinBox(reglages_groupbox->NewRow(),"threshold:",0,255,1,127);

    Printf("todo: pouvoir reutiliser la meme image en sortie\n");
    try{
        cvimage::Type const &imageType=dynamic_cast<cvimage::Type const &>(parent->GetOutputDataType());
        if(imageType.GetFormat()==cvimage::Type::Format::Gray) {
            output=new cvimage(this,imageType.GetWidth(),imageType.GetHeight(),imageType.GetFormat(),"threshold");
        } else {
            Err("input image is not gray\n");
        }
    } catch(std::bad_cast& bc) {
        Err("io type mismatch\n");
    }
}

ImgThreshold::~ImgThreshold(void) {
}

cvimage* ImgThreshold::Output(void) {
    return output;
}

void ImgThreshold::UpdateFrom(const io_data *data) {
    cvimage *cvImage=(cvimage*)data;
    IplImage *gimg=cvImage->img;

    data->GetMutex();
    output->GetMutex();
    dspThreshold(gimg, output->img, threshold->Value(), 255, CV_THRESH_BINARY);
    output->ReleaseMutex();
    data->ReleaseMutex();

    output->SetDataTime(data->DataTime());
    ProcessUpdate(output);
}

DataType const &ImgThreshold::GetOutputDataType() const {
    if(output!=NULL) {
        return output->GetDataType();
    } else {
        return dummyType;
    }
}

} // end namespace filter
} // end namespace flair
