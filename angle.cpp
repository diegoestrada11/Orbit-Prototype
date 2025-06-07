/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "angle.h"
#include <math.h>

using namespace std;

/***************************************************************
 * ANGLE : NORMALIZE
 * Convert remainder radians to their real value between 0 and 2
 ***************************************************************/
double Angle::normalize(double radians) const
{
   radians = fmod(radians, 2 * M_PI); // remainder
   return (radians < 0.0) ? (radians + 2 * M_PI) : radians;
}
