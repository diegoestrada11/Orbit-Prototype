/***********************************************************************
 * Source File:
 *    SPUTNIK
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "sputnik.h"
#include "uiDraw.h"
#include "fragment.h"
#include <cmath>
#include <random>

// Constants from spec
static const Position SPUTNIK_INITIAL_POS(-36515095.13, 21082000.0);
static const Velocity SPUTNIK_INITIAL_VEL(2050.0, 2684.68);
static constexpr double SPUTNIK_RADIUS_PX = 4.0;
static constexpr int    NUM_FRAGMENTS = 4;
static constexpr double KICK_MIN = 5000.0;  // m/s
static constexpr double KICK_MAX = 9000.0;  // m/s
static constexpr double FRAG_RADIUS_PX = 2.0;
static constexpr double SPAWN_OFFSET_PX = 4.0;

// Utility to generate uniform random double in [min,max]
double randDouble(double min, double max) {
   static random_device rd;
   static mt19937       gen(rd());
   uniform_real_distribution<> dist(min, max);
   return dist(gen);
}

Sputnik::Sputnik()
   : Satellite(SPUTNIK_INITIAL_POS, SPUTNIK_INITIAL_VEL, SPUTNIK_RADIUS_PX)
{
}

void Sputnik::drawSatellite() const
{
   Position pos = getPosition();
   double rot = angleToward(Position(0, 0)).toRadians();
   ogstream gout(pos);
   gout.drawSputnik(pos, rot);
}

vector<Body*> Sputnik::breakUp()
{
   vector<Body*> pieces;
   // spawn NUM_FRAGMENTS small fragments
   for (int i = 0; i < NUM_FRAGMENTS; ++i) {
      // random kick direction
      double theta = randDouble(0.0, 2 * M_PI);
      double kickSpeed = randDouble(KICK_MIN, KICK_MAX);

      // compute new velocity = parent vel + kick
      double dvx = std::sin(theta) * kickSpeed;
      double dvy = std::cos(theta) * kickSpeed;
      Velocity newVel(mVel.getDx() + dvx,
         mVel.getDy() + dvy);

      // spawn position offset by SPAWN_OFFSET_PX in pixel-space;
      Position newPos = mPos;
      newPos.addPixelsX(std::sin(theta) * SPAWN_OFFSET_PX);
      newPos.addPixelsY(std::cos(theta) * SPAWN_OFFSET_PX);

      int frames = 50; // or some other fixed lifetime
      pieces.push_back(new Fragment(newPos, newVel, FRAG_RADIUS_PX, frames));
   }
   return pieces;
}
