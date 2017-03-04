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

#include <QApplication>
#include <QGeoCoordinate>
#include <QGraphicsScene>

#include <QTimer>
#include <QMenu>
#include "mapwidget.h"
#include "Landmark.h"
#include "Map.h"
#include "ConnectionLayout.h"

using namespace QtMobility;

MapWidget::MapWidget(Map *map, QWidget *parent) : QGraphicsView(parent) {
  setCursor(Qt::ArrowCursor);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  geoMap = 0;
  dragging = false;
  pressed = false;
  landmark_match = NULL;
  this->map = map;

  m_scene = new QGraphicsScene(this);
  setScene(m_scene);
  setMouseTracking(true);

  landmarks = new QList<Landmark *>;
  landmarks_old = new QList<Landmark *>;
}

MapWidget::~MapWidget() {
  m_scene->removeItem(geoMap);
  delete m_scene;
}

QGraphicsScene *MapWidget::scene(void) const { return m_scene; }

void MapWidget::setMap(QGraphicsGeoMap *geoMap) {
  m_scene->clear();
  m_scene->addItem(geoMap);
  this->geoMap = geoMap;
  geoMap->resize(m_scene->sceneRect().width(), m_scene->sceneRect().height());
}

void MapWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    pressed = true;
    dragStartPosition = event->pos();
    QTimer::singleShot(qApp->startDragTime(), this, SLOT(initDrag()));
    event->accept();
  }

  if (event->button() == Qt::RightButton) {
    QMenu *menu = new QMenu("nom", this);

    if (cursor().shape() != Qt::PointingHandCursor) {
      QAction *b, *z; //*a,
      QList<QAction *> go_to_actions;
      QList<QAction *> centered_actions;

      //add centered for every point
      QMenu *centered_menu = menu->addMenu("centered");
      for (int i = 0; i < points.count(); i++) {
        QAction *action = centered_menu->addAction(points.at(i));
        centered_actions.append(action);
        action->setCheckable(true);
        if (map->centeredPoint() == i) {
          action->setChecked(true);
        } else {
          action->setChecked(false);
        }
      }

      menu->addSeparator();

      b = menu->addAction("place checkpoint");

      //add go to for every landmark
      QMenu *go_to_menu = menu->addMenu("go to");
      for (int i = 0; i < landmarks->count(); i++) {
        QAction *action =
            go_to_menu->addAction(QString("checkpoint %1").arg(i + 1));
        go_to_actions.append(action);
      }
      if (landmarks->count() == 0)
        go_to_menu->setEnabled(false);

      map->appendmenu(menu);
      z = map->execmenu(this, menu, event->globalPos());

      //center to the desired point
      for (int i = 0; i < centered_actions.count(); i++) {
        if (z == centered_actions.at(i)) {
          if (centered_actions.at(i)->isChecked()) {
            map->setCenteredPoint(i);
          } else {
            map->setCenteredPoint(-1);
          }

          break;
        }
      }

      //add a landmark
      if (z == b) {
        Landmark *landmark = new Landmark(
            geoMap, geoMap->screenPositionToCoordinate(event->pos()),
            QString("%1").arg(landmarks->count() + 1));
        landmarks->append(landmark);
      }
      for (int i = 0; i < go_to_actions.count(); i++) {
        if (z == go_to_actions.at(i)) {
          map->setCenteredPoint(-1);
          geoMap->setCenter(landmarks->at(i)->coordinate());
          break;
        }
      }

    //delete landmark
    } else {
      QAction *a, *z;
      a = menu->addAction("delete");
      //get selected landmark id
      int landmark_index;
      for (landmark_index = 0; landmark_index < landmarks->count(); landmark_index++) {
          if (landmarks->at(landmark_index)->contains(
                  geoMap->screenPositionToCoordinate(event->pos()))) {
            a->setEnabled(landmarks->at(landmark_index)->IsUptodate());
            break;
          }
      }
      z = menu->exec(event->globalPos());

      if (z == a) {
        //remove from landmarks_old
        for (int i = 0; i < landmarks_old->count(); i++) {
          if (landmarks_old->at(i)->contains(
                  geoMap->screenPositionToCoordinate(event->pos()))) {
            landmarks_old->removeAt(i);
            break;
          }
        }

        //remove from landmarks
        delete landmarks->at(landmark_index);
        landmarks->removeAt(landmark_index);

        //reorder the remaining ones
        for (int j = landmark_index; j < landmarks->count(); j++) {
          landmarks->at(j)->setText(QString("%1").arg(j + 1));
        }

        //send delete
        map->RemoveAllAttributes();
        map->SetAttribute("lat" + QString::number(landmark_index),"delete");
        map->SetAttribute("long" + QString::number(landmark_index),"delete");
        map->connectionLayout()->XmlToSend(map->XmlDoc());
        map->RemoveAttribute("lat" + QString::number(landmark_index));
        map->RemoveAttribute("long" + QString::number(landmark_index));
      }
    }

    delete menu;
  }
}

void MapWidget::initDrag(void) {
  if (pressed && map->isCentered() && landmark_match == NULL) {
    dragging = true;
  }
}

void MapWidget::mouseMoveEvent(QMouseEvent *event) {
  if (!geoMap)
    return;

  Qt::CursorShape new_cursor;
  if (dragging == true) {
    new_cursor = Qt::ClosedHandCursor;
  } else {
    if (map->isCentered()) {
      if (pressed == true) {
        new_cursor = Qt::ForbiddenCursor;
      } else {
        new_cursor = Qt::ArrowCursor;
      }
    } else {
      new_cursor = Qt::OpenHandCursor;
    }
    if (landmark_match != NULL)
      new_cursor = Qt::PointingHandCursor;
  }

  for (int i = 0; i < landmarks->count(); i++) {
    if (landmarks->at(i)
            ->contains(geoMap->screenPositionToCoordinate(event->pos()))) {
      if (pressed && landmark_match == NULL) {
        landmark_match = landmarks->at(i);
        landmark_match->setColor(Qt::red);
      }
      new_cursor = Qt::PointingHandCursor;
      break;
    }
  }

  if (new_cursor != cursor().shape())
    setCursor(new_cursor);

  QPoint v = event->pos() - dragStartPosition;

  if (dragging) {
    geoMap->pan(-v.x(), -v.y());
    dragStartPosition = event->pos();

  } else if (landmark_match != NULL) {
    landmark_match->setCoordinate(
        geoMap->screenPositionToCoordinate(event->pos()));

  } else if (pressed && !map->isCentered() &&
             v.manhattanLength() >= qApp->startDragDistance()) {
    dragging = true;

  } else {
    dragStartPosition = event->pos();
    emit positionChanged(geoMap->screenPositionToCoordinate(event->pos()));
  }

  event->accept();
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event) {
  pressed = false;
  landmark_match = NULL;

  if (dragging) {
    QPoint v = event->pos() - dragStartPosition;
    geoMap->pan(-v.x(), -v.y());
    dragging = false;
  }

  event->accept();
}

void MapWidget::resizeEvent(QResizeEvent *event) {
  if (geoMap) {
    m_scene->setSceneRect(
        QRectF(0, 0, event->size().width(), event->size().height()));
    geoMap->resize(event->size().width(), event->size().height());
  }

  QGraphicsView::resizeEvent(event);
}

void MapWidget::wheelEvent(QWheelEvent *event) {
  int steps = event->delta() / 120;
  int zoom = qBound(geoMap->minimumZoomLevel(), geoMap->zoomLevel() + steps,
                    geoMap->maximumZoomLevel());

  if (zoom != geoMap->zoomLevel())
    geoMap->setZoomLevel(zoom);
  // if(!centered)
  // geoMap->setCenter(geoMap->screenPositionToCoordinate(event->pos()));
}

void MapWidget::mouseDoubleClickEvent(QMouseEvent *event) {
  if (!map->isCentered())
    geoMap->setCenter(geoMap->screenPositionToCoordinate(event->pos()));
}

bool MapWidget::IsUptodate(void) {
  for (int i = 0; i < landmarks->count(); i++) {
    if(!landmarks->at(i)->IsUptodate()) return false;
  }
  return true;
}

void MapWidget::SetUptodate(void) {
  for (int i = 0; i < landmarks_old->count(); i++) {
    delete landmarks_old->at(i);
  }
  landmarks_old->clear();

  for (int i = 0; i < landmarks->count(); i++) {
    landmarks->at(i)->setColor(Qt::white);
    Landmark *landmark =
        new Landmark(geoMap, landmarks->at(i)->coordinate(),
                     QString("%1").arg(landmarks->count() + 1));
    landmarks_old->append(landmark);
    landmarks_old->at(i)->setVisible(false);
  }
}

void MapWidget::Reset(void) {
  for (int i = 0; i < landmarks->count(); i++) {
    delete landmarks->at(i);
  }
  landmarks->clear();

  for (int i = 0; i < landmarks_old->count(); i++) {
    Landmark *landmark =
        new Landmark(geoMap, landmarks_old->at(i)->coordinate(),
                     QString("%1").arg(landmarks->count() + 1));
    landmarks->append(landmark);
    landmarks->at(i)->setColor(Qt::white);
  }
}

QList<Landmark *> *MapWidget::Landmarks(void) { return landmarks; }

bool MapWidget::LandmarkToSend(int index) {
  if (index >= landmarks_old->count())
    return true;

  if (landmarks->at(index)->coordinate() !=
      landmarks_old->at(index)->coordinate())
    return true;
  else
    return false;
}
void MapWidget::RemoveLandmarks(void) {
  for (int i = 0; i < landmarks->count(); i++) {
    landmarks->at(i)->RemoveLandmark();
  }
  for (int i = 0; i < landmarks_old->count(); i++) {
    landmarks_old->at(i)->RemoveLandmark();
  }
}

void MapWidget::AddLandmarks(QGraphicsGeoMap *geoMap) {
  for (int i = 0; i < landmarks->count(); i++) {
    landmarks->at(i)->AddLandmark(geoMap);
  }
  for (int i = 0; i < landmarks_old->count(); i++) {
    landmarks_old->at(i)->AddLandmark(geoMap);
  }
}

void MapWidget::AddLandmark(const QGeoCoordinate &coordinate) {
  Landmark *landmark = new Landmark(geoMap, coordinate,
                                    QString("%1").arg(landmarks->count() + 1));
  landmarks->append(landmark);
  landmark->setColor(Qt::white);
  landmark = new Landmark(geoMap, coordinate,
                          QString("%1").arg(landmarks_old->count() + 1));
  landmarks_old->append(landmark);
  landmark->setColor(Qt::white);
  landmark->setVisible(false);
}

void MapWidget::AddPoint(QString name) { points.append(name); }
