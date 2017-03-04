// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ControlLaw.h
 * \brief Base class for control law
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/04/30
 * \version 4.0
 */

#ifndef CONTROLLAW_H
#define CONTROLLAW_H

#include <IODevice.h>

namespace flair {
namespace gui {
class LayoutPosition;
}
namespace core {
class cvmatrix;
}
}

namespace flair {
namespace filter {
/*! \class ControlLaw
*
* \brief Base class for control law
* input must be created by reimplemented class.\n
* output is created by this class, it is of size (nb_out,1) and type float.\n
* see constructor for nb_out
*/
class ControlLaw : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a ControlLaw
  *
  * \param parent parent
  * \param name name
  * \param nb_out number of output
  */
  ControlLaw(const core::Object *parent, std::string name, uint32_t nb_out = 1);

  /*!
  * \brief Destructor
  *
  */
  ~ControlLaw();

  /*!
  * \brief Output value
  *
  * \param index output index, between 0 and nb_out-1
  *
  * \return output value
  */
  float Output(uint32_t index = 0) const;

  /*!
  * \brief Use default plot
  *
  * Plot the output value at given position. \n
  * Only Output(1,1) is plotted. \n
  * In case of a mutliple output ControlLaw, this function should be
  *reimplemented. \n
  * After calling this function, position will be deleted as it is no longer
  *usefull. \n
  *
  * \param position position to display plot
  */
  virtual void UseDefaultPlot(const gui::LayoutPosition *position);

  /*!
  * \brief Update using provided datas
  *
  * Reimplemented class must fill input matrix before calling this.
  *
  * \param time time of the update
  */
  void Update(core::Time time);

  /*!
  * \brief Reset the internal state of the control law
  *
  * Doesn't do anything by default
  *
  */
  virtual void Reset(){};

protected:
  /*!
  * \brief input matrix
  *
  * This matrix must be created by the reimplemented class.
  *
  */
  core::cvmatrix *input;

  /*!
  * \brief output matrix
  *
  * This matrix is created by this class. Its size is (nb_out,1) and its type
  * is io_data::Float.
  *
  */
  core::cvmatrix *output;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  virtual void UpdateFrom(const core::io_data *data) = 0;
};
} // end namespace filter
} // end namespace flair
#endif // CONTROLLAW_H
