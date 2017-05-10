// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/08
//  filename:   TrajectoryGenerator2DSquare_impl.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    objet permettant la generation d'une trajectoire cercle
//
//
/*********************************************************************/

#include "TrajectoryGenerator2DSquare_impl.h"
#include "TrajectoryGenerator2DSquare.h"
#include <cvmatrix.h>
#include <Layout.h>
#include <GroupBox.h>
#include <DoubleSpinBox.h>
#include <cmath>
#include <iostream>

#define PI ((float)3.14159265358979323846)

using std::string;
using namespace flair::core;
using namespace flair::gui;
using namespace flair::filter;

TrajectoryGenerator2DSquare_impl::TrajectoryGenerator2DSquare_impl(
    TrajectoryGenerator2DSquare *self, const LayoutPosition *position,
    string name) {
  first_update = true;
  is_running = false;
  is_finishing = false;
  is_finishing_previous = false;

  nb = 0;

  // init UI
  GroupBox *reglages_groupbox = new GroupBox(position, name);
  T = new DoubleSpinBox(reglages_groupbox->NewRow(), "period, 0 for auto", " s",
                        0, 1, 0.01);
  rayon = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(), "R", " m", 0,
                            1000, .1);
  veloctity = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(), "velocity",
                                " m/s", -10, 10, 1);
  acceleration =
      new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),
                        "acceleration (absolute)", " m/s²", 0, 10, .1);

  // init matrix
  cvmatrix_descriptor *desc = new cvmatrix_descriptor(2, 2);
  desc->SetElementName(0, 0, "pos.x");
  desc->SetElementName(0, 1, "pos.y");
  desc->SetElementName(1, 0, "vel.x");
  desc->SetElementName(1, 1, "vel.y");
  output = new cvmatrix(self, desc, floatType, name);

  output->SetValue(0, 0, 0);
  output->SetValue(0, 1, 0);
  output->SetValue(1, 0, 0);
  output->SetValue(1, 1, 0);
}

TrajectoryGenerator2DSquare_impl::~TrajectoryGenerator2DSquare_impl() {
  delete output;
}

void TrajectoryGenerator2DSquare_impl::StartTraj(const Vector2D &start_pos,
                                                 float nb_lap) {
  is_running = true;
  first_update = true;
  is_finishing = false;
  this->nb_lap = nb_lap;

  // configure trajectory
  angle_off = atan2(start_pos.y - pos_off.y, start_pos.x - pos_off.x);				// pos_start.x - pos_off.x ==> position départ en x
  CurrentTime = 0;
}

void TrajectoryGenerator2DSquare_impl::FinishTraj(void) {
  if (!is_finishing) {
    is_finishing = true;
    FinishTime = CurrentTime;
  }
}

void TrajectoryGenerator2DSquare_impl::setNb(unsigned int n)
{
		nb = n;
}

void TrajectoryGenerator2DSquare_impl::Update(Time time) {
  float delta_t;
  float theta;
  float V = veloctity->Value();
  float A = acceleration->Value();
  float R = rayon->Value();
  Vector2D v;

  if (V < 0)
    A = -A;

  if (T->Value() == 0) {
    if (first_update) {
      first_update = false;
      previous_time = time;

      return;
    } else {
      delta_t = (float)(time - previous_time) / 1000000000.;
    }
  } else {
    delta_t = T->Value();
  }

	is_finishing = false;

  previous_time = time;																																// algo "temps réel"
  CurrentTime += delta_t;


  if (is_running) {
    if (R == 0) {																																			// Rayon à 0 ==> position à 0 (centre du cercle)
      pos.x = 0;
      pos.y = 0;
      v.x = 0;
      v.y = 0;
    } else {

        if (nb < 6 && pos.x != 0 && pos.y != 0) {

          if(nb == 0)
          {
      				v.y = A * CurrentTime;

      				if (fabs(v.y) > fabs(V)) {
       		 		if (v.y > 0)
          				v.y = V;
        				else
          				v.y = -V;
      				}
      				pos.y = v.y * CurrentTime;

      				if (R - v.y * v.y / (2 * A) <= pos.y && v.y >= 0)
        				A = -A;
      				if (R - v.y * v.y / (2 * A) >= pos.y && v.y < 0)
        				A = -A;

      				if ( (pos.y >= R && v.y >= 0) || (pos.y <= R && v.y < 0) )
      				{
        				v.y = 0;
      					pos.y = R;
      					setNb(1);
      					FinishTime = CurrentTime;
        			}
        	}
        	else if(nb == 1)
        	{
        			v.x = A * (CurrentTime - FinishTime);
      				if (fabs(v.x) > fabs(V)) {
       		 		if (v.x > 0)
          				v.x = V;
        				else
          				v.x = -V;
      				}
      				pos.x = v.x * (CurrentTime - FinishTime);
      				if (R - v.x * v.x / (2 * A) <= pos.x && v.x >= 0)
        				A = -A;
      				if (R - v.x * v.x / (2 * A) >= pos.x && v.x < 0)
        				A = -A;

      				if ( (pos.x >= R && v.x >= 0) || (pos.x <= R && v.x < 0) )
      				{
        				v.x = 0;
      					pos.x = R;
      					setNb(2);
      					FinishTime = CurrentTime;
        			}
        	}
        	else if(nb == 2)
        	{
        			v.y = A * (CurrentTime - FinishTime);
      				if (fabs(v.y) > fabs(V)) {
       		 		if (v.y > 0)
          				v.y = V;
        				else
          				v.y = -V;
      				}
      				pos.y = -v.y * (CurrentTime - FinishTime) + R;
      				if (R - v.y * v.y / (2 * A) <= pos.y && v.y >= 0)
        				A = -A;
      				if (R - v.y * v.y / (2 * A) >= pos.y && v.y < 0)
        				A = -A;

        			if ( (pos.y <= -R && v.y >= 0) || (pos.y >= -R && v.y < 0) )
      				{
        				v.y = 0;
      					pos.y = -R;
      					setNb(3);
      					FinishTime = CurrentTime;
        			}

        	}
        	else if(nb == 3)
        	{
        			v.x = A * (CurrentTime - FinishTime);
      				if (fabs(v.x) > fabs(V)) {
       		 		if (v.x > 0)
          				v.x = V;
        				else
          				v.x = -V;
      				}
      				pos.x = -v.x * (CurrentTime - FinishTime) + R;
      				if (R - v.x * v.x / (2 * A) <= pos.x && v.x >= 0)
        				A = -A;
      				if (R - v.x * v.x / (2 * A) >= pos.x && v.x < 0)
        				A = -A;

        			if ( (pos.x <= -R && v.x >= 0) || (pos.x >= -R && v.x < 0) )
      				{
        				v.x = 0;
      					pos.x = -R;
      					setNb(4);
      					FinishTime = CurrentTime;
        			}

        	}
        	else if(nb == 4)
        	{
      				v.y = A * (CurrentTime - FinishTime);
      				if (fabs(v.y) > fabs(V)) {
       		 		if (v.y > 0)
          				v.y = V;
        				else
          				v.y = -V;
      				}
      				pos.y = v.y * (CurrentTime - FinishTime) - R;
      				if (R - v.y * v.y / (2 * A) <= pos.y && v.y >= 0)
        				A = -A;
      				if (R - v.y * v.y / (2 * A) >= pos.y && v.y < 0)
        				A = -A;
      				if ( (pos.y >= R && v.y >= 0) || (pos.y <= R && v.y < 0) )
      				{
        				v.y = 0;
      					pos.y = R;
      					setNb(5);
      					FinishTime = CurrentTime;
        			}

        	}
        	else if(nb == 5)
        	{
        			v.x = A * (CurrentTime - FinishTime);
      				if (fabs(v.x) > fabs(V)) {
       		 		if (v.x > 0)
          				v.x = V;
        				else
          				v.x = -V;
      				}
      				pos.x = v.x * (CurrentTime - FinishTime) - R;
      				if (R - v.x * v.x / (2 * A) <= pos.x && v.x >= 0)
        				A = -A;
      				if (R - v.x * v.x / (2 * A) >= pos.x && v.x < 0)
        				A = -A;

      				if ( (pos.x >= R && v.x >= 0) || (pos.x <= R && v.x < 0) )
      				{
        				v.x = 0;
      					pos.x = R;
      					setNb(6);
        			}

        	}

        } else {

          v.x = 0;
    			v.y = 0;
    			pos.x = R;
          pos.y = R;

    			nb = 2;
    			CurrentTime = 0;
    			FinishTime = 0;

        }
      }

  } else {
    v.x = 0;
    v.y = 0;
    CurrentTime = 0;
    FinishTime = 0;
  }



  // on prend une fois pour toute les mutex et on fait des accès directs
  output->GetMutex();
  output->SetValueNoMutex(0, 0, pos.x + pos_off.x);
  output->SetValueNoMutex(0, 1, pos.y + pos_off.y);
  output->SetValueNoMutex(1, 0, v.x + vel_off.x);
  output->SetValueNoMutex(1, 1, v.y + vel_off.y);
  output->ReleaseMutex();

  output->SetDataTime(time);
}
