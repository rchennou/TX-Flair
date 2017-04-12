// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file TrajectoryGenerator2DSquare.h
 * \brief Class generating a circle trajectory in 2D
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/04/08
 * \version 4.0
 */

#ifndef TRAJECTORYGENERATOR2DSQUARE_H
#define TRAJECTORYGENERATOR2DSQUARE_H

#include <IODevice.h>

namespace flair {
namespace core {
class cvmatrix;
class Vector2D;
}
namespace gui {
class LayoutPosition;
}
}

class TrajectoryGenerator2DSquare_impl;

namespace flair {
namespace filter {
/*! \class TrajectoryGenerator2DSquare
*
* \brief Class generating a circle trajectory in 2D
*
* This class generates position and velocity references, given
* a maximum velocity and an absolute acceleration, for a circle. \n
* When trajectory is started (StartTraj), position and velocity will increase
* at the given acceleration untill maximum velocity is reached. \n
* When trajectory is asked to be finished (see FinishTraj()), position
* and velocity will decrease at the given acceleration untill null velocity is
*reached. \n
* Position and velocity of the center of the circle can be manually changed
* through SetCenter() and SetCenterSpeed().
*/
class TrajectoryGenerator2DSquare : public core::IODevice {
public:
  /*!
  * \brief Constructor
  *
  * Construct a TrajectoryGenerator2DSquare at position. \n
  * The TrajectoryGenerator2DSquare will automatically be child of
  *position->getLayout() Layout. After calling this function,
  * position will be deleted as it is no longer usefull. \n
  *
  * \param position position to display settings
  * \param name name
  */
  TrajectoryGenerator2DSquare(const gui::LayoutPosition *position,
                              std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~TrajectoryGenerator2DSquare();

  /*!
  * \brief Start trajectory
  *
  * \param start_pos start position
  * \param nb_lap number of laps, -1 for infinite
  */
  void StartTraj(const core::Vector2D &start_pos, float nb_lap = -1);

  /*!
  * \brief Stop trajectory
  *
  * Stop abruptly the trajectory.
  */
  void StopTraj(void);

  /*!
  * \brief Finish trajectory
  *
  * Finish smoothly the trajectory.
  */
  void FinishTraj(void);

  /*!
  * \brief Set center position
  *
  * \param value center position
  */
  void SetCenter(const core::Vector2D &value);

  /*!
  * \brief Set center speed
  *
  * \param value center speed
  */
  void SetCenterSpeed(const core::Vector2D &value);

  /*!
  * \brief Update using provided datas
  *
  * Uses values specified by StartTraj(),
  * SetCenter() and SetCenterSpeed().
  *
  * \param time time of the update
  */
  void Update(core::Time time);

  /*!
  * \brief Position
  *
  * \param point returned position
  */
  void GetPosition(core::Vector2D &point) const;

  /*!
  * \brief Speed
  *
  * \param point returned speed
  */
  void GetSpeed(core::Vector2D &point) const;

  /*!
  * \brief Output matrix
  *
  * \return matrix
  */
  core::cvmatrix *Matrix(void) const;

  /*!
  * \brief Is trajectory running?
  *
  * \return true if trajectory is running
  */
  bool IsRunning(void) const;

private:
  /*!
  * \brief Update using provided datas
  *
  * Reimplemented from IODevice. Nothing to do in this IODevice.
  *
  * \param data data from the parent to process
  */
  void UpdateFrom(const core::io_data *data){};

  TrajectoryGenerator2DSquare_impl *pimpl_;
};
} // end namespace filter
} // end namespace flair
#endif // TrajectoryGenerator2DSquare_H
