/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"
#include "velocity.h"

 /*********************************************
   * VELOCITY : ADD
   *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   dx += acceleration.getDDX() * time;
   dy += acceleration.getDDY() * time;
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *********************************************/
void Velocity::set(const Angle& angle, double magnitude)
{
   double radians = angle.getRadians();
   dx = sin(radians) * magnitude;
   dy = cos(radians) * magnitude;
}
