// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file cvimage.h
 * \brief Class defining an image of kind IplImage
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/03/20
 * \version 4.0
 */

#ifndef CVIMAGE_H
#define CVIMAGE_H

#include <cxcore.h>
#include <io_data.h>
#include <stdint.h>

namespace flair {
namespace core {
/*! \class cvimage
*
* \brief Class defining an image of kind IplImage
*
* IplImage is an image struct defined in OpenCV.
*
*/
class cvimage : public io_data {
public:
  class Type : public DataType {
  public:
    /*!
    \enum Format_t
    \brief Picture formats
    */
    enum class Format {
      YUYV, /*!< YUYV 16 bits */
      UYVY, /*!< UYVY 16 bits */
      BGR,  /*!< BGR 24 bits */
      GRAY, /*!< gray 8 bits */
    };
    Type(uint16_t _width, uint16_t _height, Format _format)
        : width(_width), height(_height), format(_format) {}

    size_t GetSize() const {
      size_t pixelSize;
      switch (format) {
      case Format::GRAY:
        pixelSize = 1;
        break;
      case Format::YUYV:
      case Format::UYVY:
        pixelSize = 2;
        break;
      case Format::BGR:
        pixelSize = 3;
        break;
      default:
        pixelSize = 0; // TODO should throw an exception instead
      }
      return pixelSize * width * height;
    }
    std::string GetDescription() const { return "cv image"; };

    Format GetFormat() const { return format; };
    uint16_t GetWidth() const { return width; };
    uint16_t GetHeight() const { return height; };

  private:
    uint16_t width;
    uint16_t height;
    Format format;
  };

  /*!
  * \brief Constructor
  *
  * Construct an io_data representing an IplImage.
  *
  * \param parent parent
  * \param width image width
  * \param height image height
  * \param name name
  * \param allocate_data if true, IplImage image data is allocated; otherwise
  *img->imagedata must be changed
  * \param n number of samples
  */
  cvimage(const Object *parent, uint16_t width, uint16_t height,
          Type::Format format, std::string name = "", bool allocate_data = true,
          int n = 1);

  /*!
  * \brief Destructor
  *
  */
  ~cvimage();

  /*!
  * \brief IplImage
  *
  * \return IplImage
  */
  IplImage *img;

  Type const &GetDataType() const { return dataType; };

private:
  /*!
  * \brief Copy datas
  *
  * Reimplemented from io_data. \n
  * See io_data::CopyDatas.
  *
  * \param dst destination buffer
  */
  void CopyDatas(char *dst) const;

  bool allocate_data;
  Type dataType;
};

} // end namespace core
} // end namespace flair

#endif // CVIMAGE_H
