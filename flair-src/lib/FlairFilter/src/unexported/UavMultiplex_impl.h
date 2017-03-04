// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file UavMultiplex_impl.h
 * \brief Class defining uav multiplexing
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/04/11
 * \version 4.0
 */

#ifndef UAVMULTIPLEX_IMPL_H
#define UAVMULTIPLEX_IMPL_H

#include <stdint.h>
#include <string>

namespace flair {
namespace core {
class FrameworkManager;
class cvmatrix;
class io_data;
}
namespace gui {
class Tab;
class ComboBox;
class GroupBox;
class TabWidget;
}
namespace filter {
class UavMultiplex;
}
}

/*! \class UavMultiplex_impl
*
* \brief Class defining uav multiplexing
*/
class UavMultiplex_impl {
public:
  /*!
  * \brief Constructor
  *
  * Construct a uav multiplexing
  *
  * \param parent parent
  * \param name name
  */
  UavMultiplex_impl(const flair::core::FrameworkManager *parent,
                    flair::filter::UavMultiplex *self, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~UavMultiplex_impl();

  flair::core::cvmatrix *input;
  void SetMultiplexComboBox(std::string name, int index);
  int MultiplexValue(int index) const;

  flair::gui::TabWidget *tabwidget;
  flair::gui::Tab *setup_tab;

private:
  flair::gui::Tab *main_tab;
  flair::gui::ComboBox **multiplexcombobox;
  flair::gui::GroupBox *groupbox;
  flair::filter::UavMultiplex *self;
};

#endif // UAVMULTIPLEX_IMPL_H
