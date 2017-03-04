// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file X4X8Multiplex.h
 * \brief Class defining X4 and X8 multiplexing
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/04/10
 * \version 4.0
 */

#ifndef X4X8MULTIPLEX_H
#define X4X8MULTIPLEX_H

#include <UavMultiplex.h>

class X4X8Multiplex_impl;

namespace flair {
namespace filter {
/*! \class X4X8Multiplex
*
* \brief Class defining X4 and X8 multiplexing
*
* The output order of the motors can be changed through ground station.
*/
class X4X8Multiplex : public UavMultiplex {
  friend class ::X4X8Multiplex_impl;

public:
  /*!
 \enum UavType_t
 \brief type of UAV
 */
  typedef enum {
    X4, /*!< 4 motors: front left, front right, rear left, rear right */
    X8  /*!< 8 motors: top front left, top front right, top rear left, top rear
           right, bottom front left, bottom front right, bottom rear left, bottom
           rear right */
  } UavType_t;

  /*!
  \enum MotorNames_t
  \brief Motor names
  */
  typedef enum {
    TopFrontLeft = 0,     /*!< Top front left, X4 or X8 */
    TopFrontRight = 1,    /*!< Top front right, X4 or X8 */
    TopRearLeft = 2,      /*!< Top rear left, X4 or X8 */
    TopRearRight = 3,     /*!< Top rear right, X4 or X8 */
    BottomFrontLeft = 4,  /*!< Bottom front left, X8 */
    BottomFrontRight = 5, /*!< Bottom front right, X8 */
    BottomRearLeft = 6,   /*!< Bottom rear left, X8 */
    BottomRearRight = 7,  /*!< Bottom rear right, X8 */
  } MotorNames_t;

  /*!
  * \brief Constructor
  *
  * Construct a X4 and X8 multiplexing
  *
  * \param parent parent
  * \param name name
  * \param type type
  */
  X4X8Multiplex(const core::FrameworkManager *parent, std::string name,
                UavType_t type);

  /*!
  * \brief Destructor
  *
  */
  ~X4X8Multiplex();

  /*!
  * \brief Use default plot
  *
  * Plot the output values.
  *
  */
  void UseDefaultPlot(void);

  /*!
  * \brief Motors count
  *
  * Reimplemented from UavMultiplex.
  *
  * \return motors count
  */
  uint8_t MotorsCount(void) const;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data);

  X4X8Multiplex_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // X4X8MULTIPLEX_H
