/***********************************************************************
 * Source File:
 *    Body
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/
#include "body.h"
#include <cmath>

// Constants for Earth gravity
static constexpr double EARTH_RADIUS_M = 6378000.0;     // meters
static constexpr double EARTH_SURFACE_GRAVITY = 9.80665; // m/s^2

Body::Body(const Position& pos, const Velocity& vel, double radius)
   : mPos(pos)
   , mVel(vel)
   , mRadius(radius)
   , mExpired(false)
{
}

Body::~Body() = default;

void Body::update(double dt)
{
   // Burn up if we've hit the Earth
   double r = hypot(mPos.getMetersX(), mPos.getMetersY());
   if (r <= EARTH_RADIUS_M && canBurnUp()) {
      expire();
      return;
   }

   // Compute acceleration (default: gravity toward earth)
   Acceleration a = computeAcceleration();

   // Save old velocity
   double oldDx = mVel.getDx();
   double oldDy = mVel.getDy();

   // Integrate velocity: v = v + a*dt
   mVel.addDx(a.getDDX() * dt);
   mVel.addDy(a.getDDY() * dt);

   // Integrate position: p = p + v*dt + 0.5*a*dt^2
   double dxTerm = oldDx * dt;
   double dyTerm = oldDy * dt;
   double axTerm = 0.5 * a.getDDX() * dt * dt;
   double ayTerm = 0.5 * a.getDDY() * dt * dt;

   mPos.addMetersX(dxTerm + axTerm);
   mPos.addMetersY(dyTerm + ayTerm);
}

void Body::onCollision(Body* /*other*/) noexcept
{
   // Default behavior: expire the body
   expire();
}

std::vector<Body*> Body::breakUp()
{
   // Default: no breakup
   return {};
}

bool Body::intersects(const Body& other) const
{
   double dx = mPos.getMetersX() - other.mPos.getMetersX();
   double dy = mPos.getMetersY() - other.mPos.getMetersY();
   double dist2 = dx * dx + dy * dy;
   double radiusSum = getRadius() + other.mRadius;
   return dist2 <= (radiusSum * radiusSum);
}

Acceleration Body::computeAcceleration() const
{
   // Compute height above earth's surface
   double x = mPos.getMetersX();
   double y = mPos.getMetersY();
   double r = hypot(x, y);

   // If below or at surface, no acceleration
   if (r < EARTH_RADIUS_M) {                 // below surface?
      return Acceleration{ 0,0 };
   }

   // Compute gravity magnitude
   double h = r - EARTH_RADIUS_M;

   // Gravity magnitude at altitude h: gh = g0 * (R / (R + h))^2
   double gh = EARTH_SURFACE_GRAVITY * pow(EARTH_RADIUS_M / (EARTH_RADIUS_M + h), 2);

   // Direction of gravity: toward (0,0)
   // angle d such that 0 rad points "up" (positive y), so use atan2(xe-xs, ye-ys)
   double d = atan2(-x, -y);

   // Build and return the vector
   Acceleration a;
   a.setDDX(sin(d) * gh);
   a.setDDY(cos(d) * gh);
   return a;
}
