/***********************************************************************
 * Source File:
 *    Projectile
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a projectile on the screen.
 ************************************************************************/

#include "projectile.h"
#include "fragment.h"
#include "uiDraw.h"
#include <cmath>

Projectile::Projectile(const Position& pos, const Velocity& vel, double radius, int lifetimeFrames)
   : Body(pos, vel, radius), mFramesLeft(lifetimeFrames)
{
   // set initial lifetime in frames
   mExpired = false;
   mFramesLeft = lifetimeFrames;
   // initial orientation matches velocity vector
   setAngle(Angle::fromVector(vel.getDx(), vel.getDy()));
}

void Projectile::update(double dt)
{
   // Integrate motion via base class
   Body::update(dt);

   // Decrement lifetime and expire when done
   if (--mFramesLeft <= 0) {
      expire();
   }
}

void Projectile::draw() const
{
   Position pos = getPosition();
   ogstream gout(pos);
   gout.drawProjectile(pos);
}