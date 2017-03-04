// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef LANDMARK_H
#define LANDMARK_H

#include <QGeoMapGroupObject>
#include <QGeoCoordinate>

namespace QtMobility {
class QGraphicsGeoMap;
class QGeoMapTextObject;
class QGeoMapPixmapObject;
}

class Landmark : public QtMobility::QGeoMapGroupObject {

public:
  Landmark(QtMobility::QGraphicsGeoMap *geoMap,
           const QtMobility::QGeoCoordinate &coordinate, QString name,
           QString type = "landmark");
  ~Landmark();

  QtMobility::QGeoCoordinate coordinate(void);
  void setCoordinate(const QtMobility::QGeoCoordinate &coordinate);
  void setText(QString string);
  void setColor(Qt::GlobalColor color);
  void RemoveLandmark(void);
  void AddLandmark(QtMobility::QGraphicsGeoMap *geoMap);
  bool IsUptodate(void);

private:
  QtMobility::QGeoMapTextObject *text;
  QtMobility::QGeoMapPixmapObject *pixmap;
  QtMobility::QGraphicsGeoMap *geoMap;
};

#endif
