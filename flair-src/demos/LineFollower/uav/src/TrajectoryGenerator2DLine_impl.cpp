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

#include "TrajectoryGenerator2DLine_impl.h"
#include "TrajectoryGenerator2DLine.h"
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
  is_finishing_previous = false;
  
  nb = 0;

  // init UI
  GroupBox *reglages_groupbox = new GroupBox(position, name);
  //GroupBox *reglages_groupbo = new GroupBox(position, "points");
  T = new DoubleSpinBox(reglages_groupbox->NewRow(), "period, 0 for auto", " s",
                        0, 1, 0.01);
  rayon = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(), "xPoint1", " m", 0,
                            1000, .1);
  veloctity = new DoubleSpinBox(reglages_groupbox->LastRowLastCol(), "velocity",
                                " m/s", -10, 10, 1);
acceleration =new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),
                        "acceleration (absolute)", " m/s²", 1, 10, .1);
     xPoint1=new DoubleSpinBox(reglages_groupbox->NewRow(),"xPoint1","", -100, 100, 1);
    yPoint1=new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),"yPoint1","", -100, 100, 1);
    xPoint2=new DoubleSpinBox(reglages_groupbox->NewRow(),"xPoint2","", -100, 100, 1);
    yPoint2=new DoubleSpinBox(reglages_groupbox->LastRowLastCol(),"yPoint2","", -100, 100, 1);	
  
      

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
  angle_off = atan2(start_pos.y - pos_off.y, start_pos.x - pos_off.x);				// pos_start.x - pos_off.x ==> position départ en x
  CurrentTime = 0;
  
  pos_start = start_pos;																											// position de départ
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

const Vector2D TrajectoryGenerator2DCircle_impl::move(float& A, float V, float R, float v, float pos, Time currentTime)
{
					Vector2D res;

	    		v = A * currentTime;
      		if (fabs(v) > fabs(V)) {
       		 if (v > 0)
          		v = V;
        		else
          		v = -V;
      		}
      		pos = v * currentTime;
      		if (R - v * v / (2 * A) <= pos && v >= 0)
        		A = -A;
      		if (R - v * v / (2 * A) >= pos && v < 0)
        		A = -A;
      		if (pos >= R && v >= 0)
        		is_finishing = true;
      		if (pos <= R && v < 0)
        		is_finishing = true; 
        		
        	res.x = pos;
        	res.y = v;
        	
        	return res;
}

void TrajectoryGenerator2DCircle_impl::Update(Time time) {
  float delta_t;
  float theta;
  float V = veloctity->Value();
  float A = acceleration->Value();
  float R = rayon->Value();
  float x1= xPoint1->Value();
  float y1= yPoint1->Value();
  float x2= xPoint2->Value();
  float y2= xPoint2->Value();
  float D = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  Vector2D v;

  if (V < 0)
    A = -A;

  if (T->Value() == 0) {
    if (first_update) {
      first_update = false;
      previous_time = time;
      
      /*output->GetMutex();
      output->SetValueNoMutex(0, 0, pos.x + pos_off.x);
  		output->SetValueNoMutex(0, 1, pos.y + pos_off.y);
  		output->SetValueNoMutex(1, 0, v.x + vel_off.x);
  		output->SetValueNoMutex(1, 1, v.y + vel_off.y);
      output->ReleaseMutex();

      output->SetDataTime(time);*/
      
      return;
    } else {
      delta_t = (float)(time - previous_time) / 1000000000.;
    }
  } else {
    delta_t = T->Value();
  }

	is_finishing_previous = is_finishing;
	is_finishing = false;

  previous_time = time;																																// algo "temps réel"
  CurrentTime += delta_t;

  /*if (is_finishing && CurrentTime > FinishTime + V / A)
    is_running = false;*/

  if (is_running) {
    if (D == 0) {																																			// Rayon à 0 ==> position à 0 (centre du cercle)
      pos.x = 0;
      pos.y = 0;
      v.x = 0;
      v.y = 0;
    } else {
    
        if (nb < 6) {
          
          if(nb == 0)
          {
      				v.y = A * CurrentTime;
				v.x = A * CurrentTime;
      				if (fabs(v.y) > fabs(V)) {
       		 		if (v.y > 0)
          				v.y = V;
        				else
          				v.y = -V;
      				}
				if (fabs(v.x) > fabs(V)) {
				if (v.x > 0)
          				v.x = V;
        				else
          				v.x = -V;
      				}
				pos.x= v.x * CurrentTime;
      				pos.y = v.y * CurrentTime;
      				if (y1/2 <= pos.y && v.y >= 0)
        				A = -A;
      				if (y1/2 >= pos.y && v.y < 0)
        				A = -A;
				if (x1/2 <= pos.x && v.x >= 0)
        				A = -A;
      				if (x1/2 >= pos.x && v.x < 0)
        				A = -A;
      				if ( (pos.y >= y1 && v.y >= 0) || (pos.y <= y1 && v.y < 0) )
      				{
        				v.y = 0;
				
      					pos.y = y1;
      					
        			}
				if ( (pos.x >= x1 && v.x >= 0) || (pos.x <= x1 && v.x < 0) )
      				{
        				v.x = 0;
				
      					pos.x = x1;
      					
      					
        			}
				if ( ((pos.y >= y1 && v.y >= 0) || (pos.y <= y1 && v.y < 0)) && ((pos.x >= x1 && v.x >= 0) || (pos.x <= x1 && v.x < 0)) )			{
					FinishTime = CurrentTime;
					setNb(1);
				}
        	} 
        	else if(nb == 1)
        	{
        			v.y = A * CurrentTime;
				v.x = A * CurrentTime;
      				if (fabs(v.y) > fabs(V)) {
       		 		if (v.y > 0)
          				v.y = V;
        				else
          				v.y = -V;
      				}
				if (fabs(v.x) > fabs(V)) {
				if (v.x > 0)
          				v.x = V;
        				else
          				v.x = -V;
      				}
				pos.x= v.x * CurrentTime;
      				pos.y = v.y * CurrentTime;
      				if (y2/2 <= pos.y && v.y >= 0)
        				A = -A;
      				if (y2/2 >= pos.y && v.y < 0)
        				A = -A;
				if (x2/2 <= pos.x && v.x >= 0)
        				A = -A;
      				if (x2/2 >= pos.x && v.x < 0)
        				A = -A;
      				if ( (pos.y >= y2 && v.y >= 0) || (pos.y <= y2 && v.y < 0) )
      				{
        				v.y = 0;
				
      					pos.y = y2;
      					setNb(8);
      					FinishTime = CurrentTime;
        			}
				if ( (pos.x >= x2 && v.x >= 0) || (pos.x <= x2 && v.x < 0) )
      				{
        				v.x = 0;
				
      					pos.x = x2;
      					setNb(8);
      					FinishTime = CurrentTime;
        			}

        	}
        	
        	
        } else {
          
          		v.x = 0;
    			v.y = 0;
    			pos.x = x2;
          		pos.y = y2;
    			
    			nb = 1;
    			CurrentTime = 0;
    			FinishTime = 0;
          
        }
      }

  } else {
    v.x = 0;
    v.y = 0;
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
