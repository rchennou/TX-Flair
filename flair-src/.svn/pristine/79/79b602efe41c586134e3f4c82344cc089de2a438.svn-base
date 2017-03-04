// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of Qt. It was originally
** published as part of Qt Quarterly.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsView>
#include <QGraphicsGeoMap>

class QGraphicsScene;
class Map;
class Landmark;

using namespace QtMobility;

class MapWidget : public QGraphicsView {
  Q_OBJECT

public:
  MapWidget(Map *map, QWidget *parent = 0);
  ~MapWidget();
  void setMap(QtMobility::QGraphicsGeoMap *geoMap);
  QGraphicsScene *scene() const;
  bool IsUptodate(void);
  void SetUptodate(void);
  void Reset(void);
  QList<Landmark *> *Landmarks(void);
  bool LandmarkToSend(int index);
  void AddLandmark(const QGeoCoordinate &coordinate);
  void RemoveLandmarks(void);
  void AddLandmarks(QGraphicsGeoMap *geoMap);
  void AddPoint(QString name);

signals:
  void positionChanged(const QGeoCoordinate &coordinate);

protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void resizeEvent(QResizeEvent *event);
  void wheelEvent(QWheelEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
  void initDrag();

private:
  QGraphicsGeoMap *geoMap;
  bool dragging;
  QPoint dragStartPosition;
  bool pressed;

  QGraphicsScene *m_scene;
  QList<Landmark *> *landmarks;
  QList<Landmark *> *landmarks_old;
  QList<QString> points;
  Landmark *landmark_match;
  Map *map;
};

#endif
