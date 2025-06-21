/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "body.h"

/***********************************************************************
 * update()
 * Moves the body by its velocity over time dt, but only if it's active.
 ************************************************************************/
void Body::update(double dt)
{
   if (!active)
      return;

   // compute new coordinates
   double x = position.getMetersX() + velocity.getDx() * dt;
   double y = position.getMetersY() + velocity.getDy() * dt;

   position.setMetersX(x);
   position.setMetersY(y);
}