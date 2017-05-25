//  created:    2014/07/17
//  filename:   CvtColor.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Image color conversion
//
//
/*********************************************************************/

#include "CvtColor.h"
#include <cvimage.h>
#include <dspcv_gpp.h>
#include <typeinfo>

using std::string;
using namespace flair::core;

namespace flair { namespace filter {

CvtColor::CvtColor(const core::IODevice* parent,std::string name,Conversion_t conversion) : IODevice(parent,name),output(0) {
    this->conversion=conversion;

    switch(conversion) {
    case Conversion_t::ToGray:
        try{
            cvimage::Type const &imageType=dynamic_cast<cvimage::Type const &>(parent->GetOutputDataType());
            output=new cvimage(this,imageType.GetWidth(),imageType.GetHeight(),cvimage::Type::Format::Gray,"conversion",true,2);

        } catch(std::bad_cast& bc) {
            Err("io type mismatch\n");
        }
        break;
    default:
        Err("conversion not supported\n");
    }
}

CvtColor::~CvtColor(void) {}

cvimage* CvtColor::Output(void) {
    return output;

}

DataType const &CvtColor::GetOutputDataType() const {
    if(output!=NULL) {
        return output->GetDataType();
    } else {
        return dummyType;
    }
}

void CvtColor::UpdateFrom(const io_data *data) {
    IplImage *img=((cvimage*)data)->img;

    data->GetMutex();
    output->GetMutex();

    switch(conversion) {
    case Conversion_t::ToGray:
        switch(((cvimage*)data)->GetDataType().GetFormat()) {
        case cvimage::Type::Format::YUYV:
            dspCvtColor(img,output->img,DSP_YUYV2GRAY);
            break;
        case cvimage::Type::Format::UYVY:
            dspCvtColor(img,output->img,DSP_UYVY2GRAY);
            break;
        case cvimage::Type::Format::BGR:
            dspCvtColor(img,output->img,DSP_BGR2GRAY);
            break;
        default:
            Err("input format not supported\n");
        }
        break;
    default:
        Err("conversion not supported\n");
    }

    output->ReleaseMutex();
    data->ReleaseMutex();

    output->SetDataTime(data->DataTime());
    ProcessUpdate(output);
}

} // end namespace filter
} // end namespace flair
