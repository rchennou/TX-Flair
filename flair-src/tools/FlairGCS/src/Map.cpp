// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "Map.h"
#include "Landmark.h"
#include "Layout.h"
#include "mapwidget.h"
#include <QNetworkProxy>
#include <QFormLayout>
#include <QInputDialog>
#include <QtGlobal>
#include <QMenu>
#include <QGeoMappingManager>
#include <QGeoServiceProvider>
#include <QComboBox>
#include <QToolButton>
#include <QCoreApplication>
#include <qendian.h>

//todo: merge Map and mapwidget

using namespace QtMobility;

Map::Map(Layout *parent, int row, int col, QString name,
         QList<QGeoCoordinate> coordinates, bool enabled, int period)
    : DataRemote(name, "Map", parent, enabled, period) {
  visible_widget = new QWidget();
  visible_widget->setObjectName(name);
  centeredpoint = 0;

  mapTypes[QGraphicsGeoMap::StreetMap] = tr("Street map");
  mapTypes[QGraphicsGeoMap::SatelliteMapDay] = tr("Satellite map (day)");
  mapTypes[QGraphicsGeoMap::SatelliteMapNight] = tr("Satellite map (night)");
  mapTypes[QGraphicsGeoMap::TerrainMap] = tr("Terrain map");

  mapWidget = new MapWidget(this, visible_widget);
  geoMap = 0;

  QVBoxLayout *map_layout = new QVBoxLayout();
  parent->getQGridLayout()->addLayout(map_layout, row, col);
  QHBoxLayout *tool_layout = new QHBoxLayout();
  map_layout->addLayout(tool_layout, 0);

  QFormLayout *servicelayout = new QFormLayout();
  serviceCombo = new QComboBox(visible_widget);
  servicelayout->addRow("service: ", serviceCombo);
  QFormLayout *maplayout = new QFormLayout();
  mapTypeCombo = new QComboBox(visible_widget);
  maplayout->addRow("map type: ", mapTypeCombo);
  QFormLayout *proxylayout = new QFormLayout();
  proxyCombo = new QComboBox(visible_widget);
  proxylayout->addRow("proxy: ", proxyCombo);

  if (findServices()) {
    tool_layout->addLayout(servicelayout, 0);
    tool_layout->addLayout(maplayout, 1);
    tool_layout->addLayout(proxylayout, 2);

    zoomin = new QToolButton(visible_widget);
    zoomout = new QToolButton(visible_widget);
    zoomInAction =
        new QAction(QIcon(QPixmap(":zoomin.png")), tr("Zoom &In"), zoomin);
    zoomOutAction =
        new QAction(QIcon(QPixmap(":zoomout.png")), tr("Zoom &Out"), zoomout);
    zoomin->setDefaultAction(zoomInAction);
    zoomout->setDefaultAction(zoomOutAction);
    tool_layout->addWidget(zoomin, 3);
    tool_layout->addWidget(zoomout, 4);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

    selectService(0);

    findproxy();

    connect(serviceCombo, SIGNAL(currentIndexChanged(int)), this,
            SLOT(selectService(int)));
    connect(mapTypeCombo, SIGNAL(currentIndexChanged(int)), this,
            SLOT(changeMapType(int)));
    connect(proxyCombo, SIGNAL(currentIndexChanged(int)), this,
            SLOT(changeproxy(int)));
  } else {
    printf("Error, no services!\n");
    mapWidget->setEnabled(false);
  }

  map_layout->addWidget(mapWidget, 1);
  for (int i = 0; i < coordinates.size(); i++) {
    mapWidget->AddLandmark((QGeoCoordinate &)coordinates.at(i));
  }
}

Map::~Map() {
  for (int i = 0; i < points.count(); i++) delete points.at(i);
  delete mapWidget;
}

bool Map::findServices(void) {
  QCoreApplication::addLibraryPath(qgetenv("OECORE_HOST_SYSROOT") +
                                   "/usr/lib/qt4/");

  QStringList services = QGeoServiceProvider::availableServiceProviders();

  if (services.isEmpty()) {
    QGraphicsTextItem *item = mapWidget->scene()->addText(
        tr("Failed to find any map services. Please ensure that "
           "the location services plugins for Qt Mobility are "
           "installed and, if necessary, set the IGEP_ROOT "
           "environment variable to the good location."));

    item->setTextWidth(300);

    return false;
  }

  QMap<QString, QVariant> parameters;

  foreach (QString name, services) {

    parameters["mapping.cache.directory"] = name;
    parameters["mapping.cache.size"] = QString("500000000");

    QGeoServiceProvider *service = new QGeoServiceProvider(name, parameters);

    if (service->error() != QGeoServiceProvider::NoError) {
      delete service;
      continue;
    }

    QGeoMappingManager *manager = service->mappingManager();

    if (manager) {
      serviceCombo->addItem(name);
      managers.append(manager);
    }
  }

  return true;
}

void Map::selectService(int item) {
  QString name = serviceCombo->currentText();

  QGeoCoordinate coordinate = QGeoCoordinate(0, 0);
  QGraphicsGeoMap::MapType mapType = QGraphicsGeoMap::StreetMap;
  int zoomLevel = 1;

  if (geoMap) {
    coordinate = geoMap->center();
    mapType = geoMap->mapType();
    zoomLevel = geoMap->zoomLevel();

    mapWidget->RemoveLandmarks();
    RemovePoints();
    geoMap->deleteLater();
  }

  manager = managers[item];
  geoMap = new QGraphicsGeoMap(manager);

  mapWidget->AddLandmarks(geoMap);
  AddPoints(geoMap);
  geoMap->setCenter(coordinate);
  geoMap->setMapType(mapType);

  populateMapTypeCombo();
  updateZoom(zoomLevel);

  mapWidget->setMap(geoMap);
  connect(geoMap, SIGNAL(zoomLevelChanged(qreal)), this,
          SLOT(updateZoom(qreal)));
}

void Map::changeMapType(int index) {
  geoMap->setMapType(
      QGraphicsGeoMap::MapType(mapTypeCombo->itemData(index).toInt()));
}

void Map::populateMapTypeCombo(void) {
  mapTypeCombo->clear();

  foreach (QGraphicsGeoMap::MapType mapType, geoMap->supportedMapTypes()) {
    if (mapTypes.contains(mapType))
      mapTypeCombo->addItem(mapTypes[mapType], QVariant(mapType));
  }

  if (mapTypeCombo->count() > 0)
    geoMap->setMapType(
        QGraphicsGeoMap::MapType(mapTypeCombo->itemData(0).toInt()));
}

void Map::zoomIn(void) { updateZoom(geoMap->zoomLevel() + 1); }

void Map::zoomOut(void) { updateZoom(geoMap->zoomLevel() - 1); }

void Map::updateZoom(qreal value) {
  value =
      qBound(manager->minimumZoomLevel(), value, manager->maximumZoomLevel());

  geoMap->setZoomLevel(value);
  zoomin->setEnabled(geoMap->zoomLevel() < manager->maximumZoomLevel());
  zoomout->setEnabled(geoMap->zoomLevel() > manager->minimumZoomLevel());
}

void Map::findproxy(void) {
  proxyCombo->addItem("none");
  proxyCombo->addItem("new");
  proxyCombo->addItem("proxyweb.utc.fr:3128");
}

void Map::changeproxy(int index) {
  if (index == 0) {
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::NoProxy);
    QNetworkProxy::setApplicationProxy(proxy);
  } else if (index == 1) {
    bool ok;
    QString text =
        QInputDialog::getText(visible_widget, tr("New proxy:"), tr("proxy: "),
                              QLineEdit::Normal, "adress:port", &ok);
    if (ok == true) {
      proxyCombo->addItem(text);
      proxyCombo->setCurrentIndex(proxyCombo->count() - 1);
    }
  } else {
    QStringList string = proxyCombo->itemText(index).split(":");
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(string.at(0));
    proxy.setPort(string.at(1).toInt());
    QNetworkProxy::setApplicationProxy(proxy);
    updateZoom(geoMap->zoomLevel()); // refresh
  }
}

void Map::SetUptodate(void) {
  QList<Landmark *> *landmarks = mapWidget->Landmarks();
  for (int i = 0; i < landmarks->count(); i++) {
    RemoveAttribute("lat" + QString::number(i));
    RemoveAttribute("long" + QString::number(i));

    if (mapWidget->LandmarkToSend(i)) {
      SetAttribute("lat" + QString::number(i),
                   landmarks->at(i)->coordinate().latitude());
      SetAttribute("long" + QString::number(i),
                   landmarks->at(i)->coordinate().longitude());
    }
  }

  mapWidget->SetUptodate();
}

bool Map::IsUptodate(void) { return mapWidget->IsUptodate(); }

void Map::Reset(void) { mapWidget->Reset(); }

void Map::setCenteredPoint(int i) {
  centeredpoint = i;
  if (isCentered())
    geoMap->setCenter(points.at(i)->coordinate());
}

int Map::centeredPoint(void) { return centeredpoint; }

bool Map::isCentered(void) {
  if (centeredpoint != -1) {
    return true;
  } else {
    return false;
  }
}

void Map::XmlEvent(QDomElement dom) {
  if (dom.attribute("point") != "") {
    receivesize += 3 * sizeof(double);
    if (mapWidget->isEnabled()) {
      Landmark *landmark = new Landmark(geoMap, QGeoCoordinate(0, 0, 0),
                                        dom.attribute("point"), "cross");
      landmark->setColor(Qt::black);
      points.append(landmark);
      mapWidget->AddPoint(dom.attribute("point"));
    }
  } else {
    XmlSetup(dom);
  }
}

void Map::BufEvent(char **buf, int *buf_size, uint16_t period,
                   bool big_endian) {
  if (IsEnabled() == false || RefreshRate_ms() != period)
    return;

  for (int i = 0; i < points.count(); i++) {
    qint64 lat_raw;
    double *lat = (double *)&lat_raw;
    qint64 longitude_raw;
    double *longitude = (double *)&longitude_raw;
    qint64 alt_raw;
    double *alt = (double *)&alt_raw;

    memcpy(&lat_raw, *buf, sizeof(qint64));
    *buf += sizeof(qint64);
    memcpy(&longitude_raw, *buf, sizeof(qint64));
    *buf += sizeof(qint64);
    memcpy(&alt_raw, *buf, sizeof(qint64));
    *buf += sizeof(qint64);
    if (big_endian == true)
      lat_raw = qFromBigEndian(lat_raw);
    if (big_endian == true)
      longitude_raw = qFromBigEndian(longitude_raw);
    if (big_endian == true)
      alt_raw = qFromBigEndian(alt_raw);
    points.at(i)->setCoordinate(QGeoCoordinate(*lat, *longitude, *alt));

    if (i == centeredpoint)
      geoMap->setCenter(points.at(i)->coordinate());
  }
}

void Map::RemovePoints(void) {
  for (int i = 0; i < points.count(); i++) {
    points.at(i)->RemoveLandmark();
  }
}

void Map::AddPoints(QGraphicsGeoMap *geoMap) {
  for (int i = 0; i < points.count(); i++) {
    points.at(i)->AddLandmark(geoMap);
  }
}
