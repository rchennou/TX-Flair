//  created:    2013/06/27
//  filename:   MeanFilter.h
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

#ifndef MEANFILTER_H
#define MEANFILTER_H

// we fix the max number of elements to compute the mean
// this is a simple example, it should be dynamical
#define MAX_NUMBER_OF_ELEMENTS 200

// necessary include, as IODevice is a base of our class
#include <IODevice.h>

// forward declaration for other classes
namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class LayoutPosition;
class GroupBox;
class SpinBox;
}
}

// MeanFilter is a class computing a mean
// based on a parametrizable number of elements
// it derives on IODevice as it as an input and an output
// it is a filter, we extend the namespace
namespace flair {
namespace filter {
class MeanFilter : public core::IODevice {

public:
  /*!
  * \brief Constructor
  *
  * Builds a mean filter. \n
  * After calling this function, position will be deleted as it is no longer
  *usefull. \n
  *
  * \param parent IODevice to use as parent
  * \param position where to place settings
  * \param name name of the object
  */
  MeanFilter(const core::IODevice *parent, const gui::LayoutPosition *position,
             std::string name);

  /*!
  * \brief Destructor
  */
  ~MeanFilter();

  /*!
  * \brief Output matrix
  *
  * allows to access output matrix, to get signal value or to put it in a graph.
  *\n
  *
  * \return pointer to the output matrix
  */
  core::cvmatrix *GetMatrix(void) const;

  /*!
  * \brief Value
  *
  * this method is equivalent to GetMatrix()->Value(0,0)
  *
  * \return actual mean value
  */
  float GetValue(void) const;

private:
  // UpdateFrom method from base class IODevice
  void UpdateFrom(const core::io_data *data);
  gui::GroupBox *groupBox;
  gui::SpinBox *numberOfElements;
  core::cvmatrix *output;
  float previousValues[MAX_NUMBER_OF_ELEMENTS]; // previous values storage
};
} // end namespace filter
} // end namespace flair
#endif // MEANFILTER_H
