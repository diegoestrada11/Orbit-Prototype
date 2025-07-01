/***********************************************************************
 * Source File:
 *    Starlink
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "starlink.h"
#include "fragment.h"
#include "uiDraw.h"
#include <cmath>
#include <random>

// LEO scaled up to (0, -13,020,000), velocity (5800,0)
static const Position STARLINK_INITIAL_POS(0.0, -13020000.0);
static const Velocity STARLINK_INITIAL_VEL(5800.0, 0.0);
static constexpr double STARLINK_RADIUS_PX = 6.0;
static constexpr double BODY_PART_RADIUS_PX = 2.0;
static constexpr double ARRAY_PART_RADIUS_PX = 4.0;
static constexpr int    FRAGMENTS_PER_PART = 3;
static constexpr double FRAG_RADIUS_PX = 2.0;
static constexpr double SPAWN_OFFSET_PX = 4.0;

// random helpers
static double randAngle() {
   static mt19937 gen{ std::random_device{}() };
   uniform_real_distribution<> dist(0.0, 2.0 * M_PI);
   return dist(gen);
}
static double randSpeed(double min, double max) {
   static mt19937 gen{ std::random_device{}() };
   uniform_real_distribution<> dist(min, max);
   return dist(gen);
}

Starlink::Starlink()
   : Satellite(STARLINK_INITIAL_POS,
      STARLINK_INITIAL_VEL,
      STARLINK_RADIUS_PX * Position().getZoom())
{
}

void Starlink::drawSatellite() const
{
   Position pos = getPosition();
   double   rot = angleToward(Position(0, 0)).toRadians();
   ogstream gout(pos);
   gout.drawStarlink(pos, rot);
}

vector<Body*> Starlink::breakUp()
{
   vector<Body*> pieces;
   Position center = getPosition();
   Velocity vel = getVelocity();

   // Create two persistent parts: body and array
   // pieces.push_back(new StarlinkBody(center, vel, BODY_PART_RADIUS_PX));
   // pieces.push_back(new StarlinkArray(center, vel, ARRAY_PART_RADIUS_PX));

   // Each part breaks into FRAGMENTS_PER_PART fragments
   for (int part = 0; part < 2; ++part) {
      for (int i = 0; i < FRAGMENTS_PER_PART; ++i) {
         double theta = randAngle();
         double kick = randSpeed(5000.0, 9000.0);

         // New velocity = parent vel + kick vector
         Velocity nv(vel.getDx() + sin(theta) * kick,
            vel.getDy() + cos(theta) * kick);

         // Offset spawn so they don't immediately re-collide
         Position np = center;
         np.addPixelsX(sin(theta) * SPAWN_OFFSET_PX);
         np.addPixelsY(cos(theta) * SPAWN_OFFSET_PX);

         // Random lifetime 50–100 frames
         int lifetime = 50 + (rand() % 51);
         pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
      }
   }

   return pieces;
}
