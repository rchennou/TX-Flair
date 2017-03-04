// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Picture.h
 * \brief Class displaying a Picture on the ground station
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/01/30
 * \version 4.0
 */

#ifndef PICTURE_H
#define PICTURE_H

#include <SendData.h>
#include <cxtypes.h>

namespace flair {
namespace core {
class cvimage;
}

namespace gui {

class LayoutPosition;

/*! \class Picture
*
* \brief Class displaying a Picture on the ground station
*
*/
class Picture : public SendData {
public:
  /*!
  * \brief Constructor
  *
  * Construct a picture at given position. \n
  * The Picture will automatically be child of position->getLayout() Layout.
  *After calling this constructor,
  * position will be deleted as it is no longer usefull.
  *
  * \param position position to draw plot
  * \param name name
  * \param image image to draw
  */
  Picture(const LayoutPosition *position, std::string name,
          const core::cvimage *image);

  /*!
  * \brief Destructor
  *
  */
  ~Picture();

private:
  /*!
  * \brief Copy datas to specified buffer
  *
  * Reimplemented from SendData.
  *
  * \param buf output buffer
  */
  void CopyDatas(char *buf) const;

  /*!
  * \brief Extra Xml event
  *
  * Reimplemented from SendData.
  */
  void ExtraXmlEvent(void){};

  const core::cvimage *image;
};

} // end namespace gui
} // end namespace flair

#endif // PICTURE_H
