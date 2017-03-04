// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file TrajectoryGenerator1D.h
 * \brief Class generating a trajectory in 1D
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef TRAJECTORYGENERATOR1D_H
#define TRAJECTORYGENERATOR1D_H

#include <IODevice.h>

namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class LayoutPosition;
}
}

class TrajectoryGenerator1D_impl;

namespace flair {
namespace filter {
/*! \class TrajectoryGenerator1D
*
* \brief Class generating a trajectory in 1D
*
* This class generates position and velocity references, given
* an absolute maximum velocity and an absolute acceleration. \n
* When trajectory is started (see StartTraj()), position and velocity will
*increase
* at the given acceleration. If the maximum velocity is reached,
* velocity will not increase anymore. Then, velocity will decrease according
* to the given acceleration until velocity is null and final position is
*reached. \n
* Manual inputs can be introduced using SetPositionOffset() and
*SetSpeedOffset().
*
*/
class TrajectoryGenerator1D : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a TrajectoryGenerator1D at given position. \n
  * The TrajectoryGenerator1D will automatically be child of
  *position->getLayout() Layout. After calling this function,
  * position will be deleted as it is no longer usefull. \n
  *
  * \param position position to display settings
  * \param name name
  * \param unit unit of the position (for exemple m, deg, etc). Its only used
  *for display on ground station.
  */
  TrajectoryGenerator1D(const gui::LayoutPosition *position, std::string name,
                        std::string unit = "");

  /*!
  * \brief Destructor
  *
  */
  ~TrajectoryGenerator1D();

  /*!
  * \brief Start trajectory
  *
  * \param start_pos start position
  * \param end_pos end position
  */
  void StartTraj(float start_pos, float end_pos);

  /*!
  * \brief Stop trajectory
  *
  */
  void StopTraj(void);

  /*!
  * \brief Reset
  *
  * Reset all outputs to 0. This can be done only when IsRunning()==false.
  *
  */
  void Reset(void);

  /*!
  * \brief Is trajectory running?
  *
  * \return true if trajectory is running
  */
  bool IsRunning(void) const;

  /*!
  * \brief Set position offset
  *
  * \param value position offset
  */
  void SetPositionOffset(float value);

  /*!
  * \brief Set speed offset
  *
  * \param value speed offset
  */
  void SetSpeedOffset(float value);

  /*!
  * \brief Update using provided datas
  *
  * Uses values specified by StartTraj(),
  * SetPositionOffset() and SetSpeedOffset().
  *
  * \param time time of the update
  */
  void Update(core::Time time);

  /*!
  * \brief Position
  *
  */
  float Position(void) const;

  /*!
  * \brief Speed
  *
  */
  float Speed(void) const;

  /*!
  * \brief Output matrix
  *
  * \return matrix
  */
  core::cvmatrix *Matrix(void) const;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice. Nothing to do in this IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  TrajectoryGenerator1D_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // TRAJECTORYGENERATOR1D_H
