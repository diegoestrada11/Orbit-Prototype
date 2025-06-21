/***********************************************************************
 * Source File:
 *    SATELLITE
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "satellite.h"
#include "acceleration.h"
#include <cmath>

static constexpr double EARTH_RADIUS = 6.378e6;  // meters
static constexpr double GRAVITY = 9.81;    // m/s²

Satellite::Satellite()
   : position(), velocity(), angle()
{
}

const Position& Satellite::getPosition() const
{
   return position;
}

const Velocity& Satellite::getVelocity() const
{
   return velocity;
}

const Angle& Satellite::getAngle() const
{
   return angle;
}

void Satellite::setPosition(const Position& pos)
{
   position = pos;
}

void Satellite::setVelocity(const Velocity& vel)
{
   velocity = vel;
}

void Satellite::update(double dt)
{
   // Compute distance from Earth's center
   double x = position.getMetersX();
   double y = position.getMetersY();
   double r = std::hypot(x, y);

   // If off-center, apply inverse-square gravity
   if (r > 0.0)
   {
      double ux = -x / r;
      double uy = -y / r;
      double a_mag = GRAVITY * (EARTH_RADIUS * EARTH_RADIUS) / (r * r);

      Acceleration a;
      a.setDDX(ux * a_mag);
      a.setDDY(uy * a_mag);

      velocity.add(a, dt);
   }

   position.addMetersX(velocity.getDx() * dt);
   position.addMetersY(velocity.getDy() * dt);

   // Recompute orientation so the same face points inward
   updateOrientation();
}

void Satellite::updateOrientation()
{
   double x = position.getMetersX();
   double y = position.getMetersY();

   // Don't change angle if at the exact center
   if (x == 0.0 && y == 0.0)
      return;

   // Angle so that “front” points toward (0,0)
   double rad = std::atan2(-y, -x);
   angle.setRadians(rad);
}

void Satellite::draw() const
{
   //
}
