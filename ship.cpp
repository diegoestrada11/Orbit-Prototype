/***********************************************************************
* Source File:
*    ORBIT SIMULATOR
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
************************************************************************/

#include "ship.h"
#include "projectile.h"
#include "uiDraw.h"
#include <cmath>

Ship::Ship(): Body(
   [] {
      Position pos;
      // Now set its pixel coords:
      pos.setPixelsX(INITIAL_X);   // –450 px
      pos.setPixelsY(INITIAL_Y);   //  450 px
      return pos;
   }(),                           // temporary lambda builds the Position

      // Velocity stays in m/s, so unchanged:
      Velocity(INITIAL_VX, INITIAL_VY),

      // For the collision radius, set in pixels, then convert:
      SHIP_RADIUS* getZoom()  // getZoom() returns same scale as you set
      )
{
   setAngle(Angle::fromDegrees(270.0));
}

Projectile* Ship::fireProjectile() {
   Position center = getPosition();
   double theta = getAngle().toRadians();
   Velocity parentVel = getVelocity();

   double dvx = sin(theta) * PROJECTILE_KICK;
   double dvy = cos(theta) * PROJECTILE_KICK;
   Velocity pVel(parentVel.getDx() + dvx,
      parentVel.getDy() + dvy);

   Position pPos = center;
   pPos.addPixelsX(sin(theta) * PROJECTILE_OFFSET);
   pPos.addPixelsY(cos(theta) * PROJECTILE_OFFSET);

   return new Projectile(pPos, pVel, 1.0, 70);
}

void Ship::update(double dt)
{
   // integrate like any other Body (gravity + thrust)
   Body::update(dt);
}

Acceleration Ship::computeAcceleration() const
{
   Acceleration a = Body::computeAcceleration();
   if (mThrusting) {
      double theta = getAngle().toRadians();
      a.addDDX(sin(theta) * THRUST_ACC);
      a.addDDY(cos(theta) * THRUST_ACC);
   }
   return a;
}

void Ship::draw() const
{
   Position pos = getPosition();
   double   rot = getAngle().toRadians();
   ogstream gout(pos);
   // Pass thrust flag to show thrust animation
   gout.drawShip(pos, rot, mThrusting);
}
