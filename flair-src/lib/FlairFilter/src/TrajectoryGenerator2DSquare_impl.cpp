// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/08
//  filename:   TrajectoryGenerator2DCircle_impl.cpp
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

TrajectoryGenerator2DCircle_impl::TrajectoryGenerator2DCircle_impl(
    TrajectoryGenerator2DCircle *self, const LayoutPosition *position,
    string name) {
  first_update = true;
  is_running = false;
  is_finishing = false;
  
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

TrajectoryGenerator2DCircle_impl::~TrajectoryGenerator2DCircle_impl() {
  delete output;
}

void TrajectoryGenerator2DCircle_impl::StartTraj(const Vector2D &start_pos,
                                                 float nb_lap) {
  is_running = true;
  first_update = true;
  is_finishing = false;
  this->nb_lap = nb_lap;

  // configure trajectory
  angle_off = atan2(start_pos.y - pos_off.y, start_pos.x - pos_off.x);				// pos_start.x - pos_off.x ==> position départ
  CurrentTime = 0;
  
  pos_start = start_pos;
}

void TrajectoryGenerator2DCircle_impl::FinishTraj(void) {
  if (!is_finishing) {
    is_finishing = true;
    FinishTime = CurrentTime;
  }
}

void TrajectoryGenerator2DCircle_impl::setNb(unsigned int n)
{
		nb = n;
}

void TrajectoryGenerator2DCircle_impl::Update(Time time) {
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

  previous_time = time;																																// algo "temps réel"
  CurrentTime += delta_t;

  if (is_finishing && CurrentTime > FinishTime + V / A)
    is_running = false;

  if (is_running) {
    if (R == 0) {																																			// Rayon à 0 ==> position à 0 (centre du cercle)
      pos.x = 0;
      pos.y = 0;
      v.x = 0;
      v.y = 0;
    } else {
    
      if (CurrentTime < V / A) {
        theta = angle_off + A / 2 * CurrentTime * CurrentTime / R;			// teta(t) = teta_zero + (1/2)*alpha*t^2 (alpha = w(point) avec w =  V / R)
        pos.x = R * cos(theta);
        pos.y = R * sin(theta);
        v.x = -A * CurrentTime * sin(theta);
        v.y = A * CurrentTime * cos(theta);
      } else {
        if (!is_finishing) {
          theta = angle_off + V * V / (2 * A * R) + (CurrentTime - V / A) * V / R; 		// teta(t) = teta_V/A + w*(t - V/A)
          pos.x = R * cos(theta);
          pos.y = R * sin(theta);
          v.x = -V * sin(theta);
          v.y = V * cos(theta);
        } else {
          theta = angle_off + V * V / (2 * A * R) +								// teta(t) = teta_FinishTime + w*(FinishTime - V/A) - (1/2)*alpha*(FinishTime - t)
                  (FinishTime - V / A) * V / R -
                  A / 2 * (FinishTime - CurrentTime) *
                      (FinishTime - CurrentTime) / R +
                  V * (CurrentTime - FinishTime) / R;
          pos.x = R * cos(theta);
          pos.y = R * sin(theta);
          v.x = -(V + A * (FinishTime - CurrentTime)) * sin(theta);
          v.y = (V + A * (FinishTime - CurrentTime)) * cos(theta);
          
        }
    
      /*if (nb == 0) { //CurrentTime < ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A)) { //((-V + sqrt(V*V-2*A*(R + pos_start.x - pos_off.x))) / A)

				v.x = 0;
        pos.y = ((1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime + (pos_start.y - pos_off.y));
      
        if( pos.y >= R && CurrentTime >= ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A) )
        {
        		setNb(1);
       	}
       	else if( pos.y < R && CurrentTime < ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
       	{
       	    v.y = (A * CurrentTime + V);
       	}

      } else {
     
      	//if (CurrentTime >= ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A) && CurrentTime < ((-V + sqrt(V*V-2*A*(-R + pos_start.x - pos_off.x))) / A))
      	if (nb == 1)
      	{
      			v.y = 0;
      			pos.x = ((1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime + pos_off.x);
      			
        		if( pos.x >= R && CurrentTime >= ((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A) )
       			{
        				setNb(2);
      		 	}
       			else if( pos.x < R && CurrentTime < ((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
       			{
       			    v.x = (A * CurrentTime + V);
       			}
      	}
      	else if (nb == 2)
      	{
      			v.x = 0;
      			pos.y = -((1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime - R + pos_off.y);
      			
      			if(pos.y <= -R && CurrentTime >= ((V - sqrt(V*V+2*A*(R))) / -A) + ((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
        		{
        				setNb(3);
       			}
       			else if ( pos.y > -R && CurrentTime < ((V - sqrt(V*V+2*A*(R))) / -A) + ((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
       			{
       	    		v.y = -(A * CurrentTime + V);
       			}
       			
      	}
      	else if (nb == 3)
      	{
      			v.y = 0;
      			pos.x = -((1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime - R + pos_off.x);
      			
        		if(pos.x <= -R && CurrentTime >= 2*((V - sqrt(V*V+2*A*(R))) / -A) + ((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A)) 
       			{
        				setNb(4);
      		 	}
       			else if( pos.x > -R && CurrentTime < 2*((V - sqrt(V*V+2*A*(R))) / -A) + ((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
       			{
       			    v.x = -(A * CurrentTime + V);
       			}
      	}
      	else if (nb == 4)
      	{
      			v.x = 0;
      			pos.y = ((1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime - R - pos_off.y);
      			
      			if(pos.y >= R && CurrentTime >= 2*((V - sqrt(V*V+2*A*(R))) / -A) + 2*((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
        		{
        				setNb(5);
       			}
       			else if( pos.y < R && CurrentTime < 2*((V - sqrt(V*V+2*A*(R))) / -A) + 2*((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
       			{
       	    		v.y = (A * CurrentTime + V);
       			}
      	}
      	else if (nb == 5)
      	{
      			v.y = 0;
      			pos.x = ((1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime - R - pos_off.x);
      			
        		if(pos.x >= R && CurrentTime >= 2*((V - sqrt(V*V+2*A*(R))) / -A) + 3*((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
       			{
        				setNb(6);
      		 	}
       			else if( pos.x < R && CurrentTime < 2*((V - sqrt(V*V+2*A*(R))) / -A) + 3*((-V + sqrt(V*V-2*A*(-R))) / A) + ((-V + sqrt(V*V-2*A*(-R + pos_start.y - pos_off.y))) / A))
       			{
       			    v.x = (A * CurrentTime + V);
       			}
      	}*/
      	
       /* else if (!is_finishing && CurrentTime < ((-V + sqrt(V*V-2*A*(-R + pos.y + pos_off.y))) / A) )
        {
        
          pos.y = (1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime + pos.y + pos_off.y;
          v.y = A * CurrentTime + V;

        }*/
        /*else if (!is_finishing && CurrentTime >= (((-V + sqrt(V*V-2*A*(- 2*R))) / A) + V / A)  && CurrentTime < (((-V + sqrt(V*V-2*A*(- 2*R))) / A) ))
        {

        	pos.x = pos_off.x + (1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime - R;
          v.x = A * CurrentTime + V;

        }*/
        /*else if (!is_finishing && pos.x >= R && pos.y >= R)
        {

        	pos.y = -((1 / 2) * A * CurrentTime * CurrentTime + V * CurrentTime - R) ;
          v.y =  -(A * CurrentTime + V);

        }*/
       /* else if( nb == 6 )
        {
    			v.x = 0;
    			v.y = 0;
        }*/
      }
    }


    if (theta - angle_off >= nb_lap * 2 * PI - (-A / 2 * (V / A) * (V / A) / R +
                                                V * (V / A) / R) &&
        nb_lap > 0) {
      FinishTraj();
    }

  } else {
    v.x = 0;
    v.y = 0;
  }

	   /*if(pos.y + pos_off.y >= R)
        	nb == 1;*/
        

  // on prend une fois pour toute les mutex et on fait des accès directs
  output->GetMutex();
  output->SetValueNoMutex(0, 0, pos.x + pos_off.x);
  output->SetValueNoMutex(0, 1, pos.y + pos_off.y);
  output->SetValueNoMutex(1, 0, v.x + vel_off.x);
  output->SetValueNoMutex(1, 1, v.y + vel_off.y);
  output->ReleaseMutex();

  output->SetDataTime(time);
}
