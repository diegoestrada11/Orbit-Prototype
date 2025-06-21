/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "acceleration.h"
#include <cmath>
using namespace std;

/*********************************************
 * add()
 *   Add another acceleration vector to this one.
 *********************************************/
void Acceleration::add(const Acceleration& rhs)
{
   ddx += rhs.ddx;
   ddy += rhs.ddy;
}

/*********************************************
 * set()
 *   Set via magnitude and angle (angle in radians).
 *********************************************/
void Acceleration::set(const Angle& angle, double magnitude)
{
   double r = angle.getRadians();
   ddx = sin(r) * magnitude;
   ddy = cos(r) * magnitude;
}
