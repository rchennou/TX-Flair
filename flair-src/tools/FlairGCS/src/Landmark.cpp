// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "Landmark.h"
#include <QPen>
#include <QGeoMapTextObject>
#include <QGeoMapPixmapObject>
#include <QGraphicsGeoMap>

using namespace QtMobility;

Landmark::Landmark(QGraphicsGeoMap *geoMap, const QGeoCoordinate &coordinate,
                   QString name, QString type) {
  geoMap->addMapObject(this);
  this->geoMap = geoMap;
  pixmap = new QGeoMapPixmapObject();
  pixmap->setCoordinate(coordinate);

  if (type == "cross") {
    pixmap->setOffset(QPoint(-16, -16));
    pixmap->setPixmap(QPixmap(":cross.png"));
  } else {
    pixmap->setOffset(QPoint(-2, -30));
    pixmap->setPixmap(QPixmap(":landmark.png"));
  }
  addChildObject(pixmap);

  QFont font;
  font.setWeight(QFont::Bold);
  text = new QGeoMapTextObject(coordinate, name, font, QPoint(0, 10));
  text->setPen(QPen(Qt::NoPen));
  text->setBrush(QBrush(Qt::red));
  addChildObject(text);
}

Landmark::~Landmark() {
  geoMap->removeMapObject(this);
  clearChildObjects();
}

void Landmark::setText(QString string) { text->setText(string); }

void Landmark::setColor(Qt::GlobalColor color) {
  text->setBrush(QBrush(color));
}

bool Landmark::IsUptodate(void) {
  if(text->brush()==QBrush(Qt::white)) {
    return true;
  } else {
    return false;
  }
}

void Landmark::setCoordinate(const QGeoCoordinate &coordinate) {
  pixmap->setCoordinate(coordinate);
  text->setCoordinate(coordinate);
}

QGeoCoordinate Landmark::coordinate(void) { return pixmap->coordinate(); }

void Landmark::RemoveLandmark(void) { geoMap->removeMapObject(this); }

void Landmark::AddLandmark(QGraphicsGeoMap *geoMap) {
  geoMap->addMapObject(this);
  this->geoMap = geoMap;
}
