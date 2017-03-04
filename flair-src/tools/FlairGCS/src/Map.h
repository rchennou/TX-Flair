// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include "DataRemote.h"
#include <QGeoCoordinate>
#include <QGraphicsGeoMap>

class Layout;
class MapWidget;
class QComboBox;
class Landmark;
class QToolButton;

namespace QtMobility {
class QGeoMappingManager;
class QGraphicsGeoMap;
class QGeoServiceProvider;
}

class Map : public DataRemote {
  Q_OBJECT

  friend class MapWidget;

public:
  Map(Layout *parent, int row, int col, QString name,
      QList<QtMobility::QGeoCoordinate> coordinates, bool enabled, int period);
  ~Map();
  void setCenteredPoint(int i);
  int centeredPoint(void);
  bool isCentered(void);

private:
  MapWidget *mapWidget;
  QtMobility::QGeoMappingManager *manager;
  QList<QtMobility::QGeoMappingManager *> managers;
  QtMobility::QGraphicsGeoMap *geoMap;
  QtMobility::QGeoServiceProvider *service;
  QComboBox *mapTypeCombo, *serviceCombo, *proxyCombo;
  QHash<QtMobility::QGraphicsGeoMap::MapType, QString> mapTypes;
  QToolButton *zoomin, *zoomout;
  QAction *zoomInAction;
  QAction *zoomOutAction;
  QList<Landmark *> points;
  int centeredpoint;

  bool findServices(void);
  void findproxy(void);
  void populateMapTypeCombo();
  bool IsUptodate(void);
  void SetUptodate(void);
  void Reset(void);
  void XmlEvent(QDomElement dom);
  void BufEvent(char **buf, int *buf_size, uint16_t period, bool big_endian);

  void RemovePoints(void);
  void AddPoints(QtMobility::QGraphicsGeoMap *geoMap);

private slots:
  void changeMapType(int index);
  void selectService(int index);
  void changeproxy(int index);
  void updateZoom(qreal value);
  void zoomIn(void);
  void zoomOut(void);
};

#endif // MAP_H
