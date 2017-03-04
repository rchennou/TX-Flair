// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/05/02
//  filename:   Euler.cpp
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class defining euler angles
//
//
/*********************************************************************/

#include "Euler.h"
#include "Quaternion.h"
#include <math.h>

#define PI ((float)3.14159265358979323846)
#define PI_D ((double)3.14159265358979323846)

namespace flair {
namespace core {

Euler::Euler(float inRoll, float inPitch, float inYaw)
    : roll(inRoll), pitch(inPitch), yaw(inYaw) {}

Euler::~Euler() {}

Euler &Euler::operator=(const Euler &euler) {
  roll = euler.roll;
  pitch = euler.pitch;
  yaw = euler.yaw;
  return (*this);
}
/*
void Euler::RotateX(float value) {
    float pitch_tmp;
    pitch_tmp=pitch*cosf(value)+yaw*sinf(value);
    yaw=-pitch*sinf(value)+yaw*cosf(value);
    pitch=pitch_tmp;
    roll+=value;
    if(roll<-PI) roll+=2*PI;
    if(roll>PI) roll-=2*PI;
}

void Euler::RotateXDeg(float value) {
    RotateX(ToRadian(value));
}

void Euler::RotateY(float value) {
    float roll_tmp;
    roll_tmp=roll*cosf(value)-yaw*sinf(value);
    yaw=roll*sinf(value)+yaw*cosf(value);
    roll=roll_tmp;
    pitch+=value;
    if(pitch<-PI) pitch+=2*PI;
    if(pitch>PI) pitch-=2*PI;
}

void Euler::RotateYDeg(float value) {
    RotateY(ToRadian(value));
}

void Euler::RotateZ(float value) {
    float roll_tmp;
    roll_tmp=roll*cosf(value)+pitch*sinf(value);
    pitch=-roll*sinf(value)+pitch*cosf(value);
    roll=roll_tmp;
    yaw+=value;
    if(yaw<-PI) yaw+=2*PI;
    if(yaw>PI) yaw-=2*PI;
}

void Euler::RotateZDeg(float value) {
    RotateZ(ToRadian(value));
}
*/
void Euler::ToQuaternion(Quaternion &quaternion) const {
  quaternion.q0 = cos(yaw / 2) * cos(pitch / 2) * cos(roll / 2) +
                  sin(yaw / 2) * sin(pitch / 2) * sin(roll / 2);

  quaternion.q1 = cos(yaw / 2) * cos(pitch / 2) * sin(roll / 2) -
                  sin(yaw / 2) * sin(pitch / 2) * cos(roll / 2);

  quaternion.q2 = cos(yaw / 2) * sin(pitch / 2) * cos(roll / 2) +
                  sin(yaw / 2) * cos(pitch / 2) * sin(roll / 2);

  quaternion.q3 = sin(yaw / 2) * cos(pitch / 2) * cos(roll / 2) -
                  cos(yaw / 2) * sin(pitch / 2) * sin(roll / 2);
}

Quaternion Euler::ToQuaternion(void) const {
  Quaternion quaternion;
  ToQuaternion(quaternion);
  return quaternion;
}

float Euler::ToDegree(float radianValue) { return radianValue * 180.0f / PI; }

float Euler::ToRadian(float degreeValue) { return degreeValue / 180.0f * PI; }

float Euler::YawDistanceFrom(float angle) const {
  float rot1, rot2;
  if (angle > yaw) {
    rot1 = angle - yaw;
    rot2 = 2 * PI - angle + yaw;
  } else {
    rot1 = 2 * PI + angle - yaw;
    rot2 = yaw - angle;
  }
  if (rot2 < rot1)
    rot1 = -rot2;
  rot1 = -rot1; // pour avoir rot1=yaw-angle

  return rot1;
}

} // end namespace core
} // end namespace flair
