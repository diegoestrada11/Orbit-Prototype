/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"
#include "velocity.h"

 /*********************************************
   * VELOCITY : ADD
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   dx += acceleration.getDDX() * time;
   dy += acceleration.getDDY() * time;
}

/*********************************************
 * VELOCITY : SET
 *********************************************/
void Velocity::set(double magnitude, const Angle& angle)
{
   double radians = angle.getRadians();
   dx = sin(radians) * magnitude;
   dy = cos(radians) * magnitude;
}
