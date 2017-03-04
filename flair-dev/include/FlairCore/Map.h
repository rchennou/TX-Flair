// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Map.h
 * \brief Class displaying a GPS map on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2013/07/23
 * \version 4.0
 */

#ifndef MAP_H
#define MAP_H

#include <SendData.h>
#include <stdint.h>

namespace flair {
namespace core {
class GeoCoordinate;
}

namespace gui {

class LayoutPosition;

/*! \class Map
*
* \brief Class displaying a GPS map on the ground station
*
*/
class Map : public SendData {
public:
  /*!
  * \brief Constructor
  *
  * Construct a map at given position. \n
  * The Map will automatically be child of position->getLayout() Layout. After
  *calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param position position to draw map
  * \param name name
  */
  Map(const LayoutPosition *position, std::string name);

  /*!
  * \brief Destructor
  *
  */
  ~Map();

  /*!
  * \brief Add a point to the map
  *
  * \param point point to draw
  * \param name name
  */
  void AddPoint(const core::GeoCoordinate *point, std::string name = "");

  /*!
  * \brief Copy datas to specified buffer
  *
  * Reimplemented from SendData.
  *
  * \param buf output buffer
  */
  void CopyDatas(char *buf) const;

private:
  /*!
  * \brief Extra Xml event
  *
  * Reimplemented from SendData.
  */
  void ExtraXmlEvent(void);

  void removeCheckpoint(size_t index);

  std::vector<core::GeoCoordinate *> checkpoints;
  std::vector<const core::GeoCoordinate *> to_draw;
  // std::vector<xmlNodePtr> checkpoints_node;
  // bool init;
};

} // end namespace gui
} // end namespace flair

#endif // MAP_H
