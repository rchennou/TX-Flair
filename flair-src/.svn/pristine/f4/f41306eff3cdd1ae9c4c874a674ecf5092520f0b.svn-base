//  created:    2013/06/27
//  filename:   MeanFilter.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    object computing a mean filter
//
//
/*********************************************************************/

#include "MeanFilter.h"
#include <cvmatrix.h>
#include <LayoutPosition.h>
#include <GroupBox.h>
#include <SpinBox.h>

using namespace std;
using namespace flair::core;
using namespace flair::gui;

namespace flair {
namespace filter {

MeanFilter::MeanFilter(const IODevice *parent, const LayoutPosition *position,
                       string name)
    : IODevice(parent, name) {
  // interface initialisation
  groupBox = new GroupBox(position, name);
  numberOfElements = new SpinBox(groupBox->NewRow(), "numberOfElements:", 1,
                                 MAX_NUMBER_OF_ELEMENTS,
                                 1); // saturated to MAX_NUMBER_OF_ELEMENTS

  // init storage
  for (int i = 0; i < MAX_NUMBER_OF_ELEMENTS; i++)
    previousValues[i] = 0;

  // 1*1 output matrix
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(1, 1);
  desc->SetElementName(0, 0,
                       "mean filter"); // name will be used for graphs and logs
  output = new cvmatrix(this, desc, floatType, name);

  AddDataToLog(output);
}

MeanFilter::~MeanFilter() {}

cvmatrix *MeanFilter::GetMatrix() const { return output; }

float MeanFilter::GetValue(void) const { return output->Value(0, 0); }

// UpdateFrom, where we implement the filter
// this method is automatically called when the parent IODevice calls
// ProcessUpdate
// in our case it is the sinus or the 1st orde law pass filter
//(see in Sinus::Run the call to ProcessUpdate)
void MeanFilter::UpdateFrom(const io_data *data) {

  float result = 0;
  // get input argument in a cvmatrix
  cvmatrix *input = (cvmatrix *)data;

  // simple (and not efficent!) implementation of the filter
  previousValues[numberOfElements->Value() - 1] = input->Value(0, 0);
  for (int i = 0; i < numberOfElements->Value(); i++)
    result += previousValues[i];
  for (int i = 1; i < numberOfElements->Value(); i++)
    previousValues[i - 1] = previousValues[i];

  // put the result in output matrix
  output->SetValue(0, 0, result / numberOfElements->Value());
  // put corresponding time
  output->SetDataTime(data->DataTime());

  // ProcessUpdate is very important
  // we must call it after updating the output matrix
  // it allows:
  // -to save value in the logs
  // -to automatically call the next filter UpdateFrom method
  ProcessUpdate(output);
}
} // end namespace filter
} // end namespace flair
