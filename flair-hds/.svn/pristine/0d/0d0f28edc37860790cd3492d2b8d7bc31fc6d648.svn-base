//  created:    2015/10/07
//  filename:   Sobel.cpp
//
//  author:     Gildas Bayard
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Sobel
//
//
/*********************************************************************/

#include "Sobel.h"
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

Sobel::Sobel(const IODevice* parent,const LayoutPosition* position,string name) : IODevice(parent,name),output(0) {
    GroupBox* reglages_groupbox=new GroupBox(position,name);
    dx=new SpinBox(reglages_groupbox->NewRow(),"dx:",0,1,1,1);
    dy=new SpinBox(reglages_groupbox->NewRow(),"dy:",0,1,1,1);

    Printf("TODO: IODevice doit faire un check de GetInputDataType et GetOutputDataType\n");
    //cvimage devrait accepter un type dans son constructeur pour construire un type identique
    try{
        cvimage::Type const &imageType=dynamic_cast<cvimage::Type const &>(parent->GetOutputDataType());
        if(imageType.GetFormat()==cvimage::Type::Format::Gray) {
            output=new cvimage(this,imageType.GetWidth(),imageType.GetHeight(),imageType.GetFormat(),"sobel");
        } else {
            Err("input image is not gray\n");
        }

    } catch(std::bad_cast& bc) {
        Err("io type mismatch\n");
    }
}

Sobel::~Sobel(void) {
}

cvimage* Sobel::Output(void) {
    return output;
}

void Sobel::UpdateFrom(const io_data *data) {
    cvimage *cvImage=(cvimage*)data;
    IplImage *gimg=cvImage->img;

    data->GetMutex();
    output->GetMutex();
    dspSobel(gimg,output->img,dx->Value(),dy->Value());
    output->ReleaseMutex();
    data->ReleaseMutex();

    output->SetDataTime(data->DataTime());
    ProcessUpdate(output);
}

DataType const &Sobel::GetOutputDataType() const {
    if(output!=NULL) {
        return output->GetDataType();
    } else {
        return dummyType;
    }
}

} // end namespace filter
} // end namespace flair
