/***********************************************************************
* Source File:
*    GPS
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
************************************************************************/

#include "gps.h"
#include "fragment.h"
#include "uiDraw.h"
#include <cmath>
#include <random>

// GPS orbits at 20 180 km altitude, 3.9 km/s. 12px radius.
static const Position GPS_INITIAL_POS[] = {
    {   0.0, 26560000.0},
    {23001634.72, 13280000.0},
    {23001634.72,-13280000.0},
    {   0.0,-26560000.0},
    {-23001634.72,-13280000.0},
    {-23001634.72, 13280000.0}
};
static const Velocity GPS_INITIAL_VEL[] = {
    {-3880.00,    0.0},
    {-1940.00, 3360.18},
    { 1940.00, 3360.18},
    { 3880.00,    0.0},
    { 1940.00,-3360.18},
    {-1940.00,-3360.18}
};
static constexpr double GPS_RADIUS_PX = 12.0;
static constexpr int    NUM_CENTER_PART = 1;
static constexpr int    NUM_ARRAY_PART = 2;
static constexpr int    NUM_FRAGMENTS = 2;
static constexpr double PART_RADIUS_CENTER = 7.0;
static constexpr double PART_RADIUS_ARRAY = 8.0;
static constexpr double FRAG_RADIUS_PX = 2.0;
static constexpr double SPAWN_OFFSET_PX = 4.0;

// random helper
static double randAngle() {
   static mt19937 gen{ std::random_device{}() };
   uniform_real_distribution<> dist(0, 2 * M_PI);
   return dist(gen);
}
static double randSpeed(double min, double max) {
   static mt19937 gen{ std::random_device{}() };
   uniform_real_distribution<> dist(min, max);
   return dist(gen);
}

GPS::GPS()
   : Satellite(GPS_INITIAL_POS[0],
      GPS_INITIAL_VEL[0],
      GPS_RADIUS_PX)
{
   // If you want to place all six GPS satellites, do so in the simulator:
   // for (i=0..5) bodies.push_back(new GPS(i));
}

void GPS::drawSatellite() const
{
   // no rotation on a static GPS
   ogstream gout(getPosition());
   gout.drawGPS(getPosition(), getAngle().toRadians());
}

vector<Body*> GPS::breakUp()
{
   vector<Body*> pieces;

   Position center = getPosition();
   Velocity vel = getVelocity();

   // Create the 3 persistent parts
   // pieces.push_back(new GPSCenter(center, vel, PART_RADIUS_CENTER));
   // pieces.push_back(new GPSLeft  (center, vel, PART_RADIUS_ARRAY));
   // pieces.push_back(new GPSRight (center, vel, PART_RADIUS_ARRAY));

   // Create 2 small fragments
   for (int i = 0; i < NUM_FRAGMENTS; ++i) {
      double theta = randAngle();
      double kick = randSpeed(5000, 9000);

      // new velocity = parent vel + kick
      Velocity nv(vel.getDx() + sin(theta) * kick,
         vel.getDy() + cos(theta) * kick);

      // offset spawn so they don't immediately re-collide
      Position np = center;
      np.addPixelsX(sin(theta) * SPAWN_OFFSET_PX);
      np.addPixelsY(cos(theta) * SPAWN_OFFSET_PX);

      // random lifetime 50–100 frames
      int lifetime = 50 + (rand() % 51);
      pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
   }

   return pieces;
}
