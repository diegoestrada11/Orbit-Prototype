/***********************************************************************
 * Source File:
 *    Crew Dragon
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "crewDragon.h"
#include "fragment.h"
#include "uiDraw.h"
#include <cmath>
#include <random>

// LEO at (0, 8,000,000) m and velocity (-7900,0) m/s
static const Position DRAGON_INITIAL_POS(0.0, 8000000.0);
static const Velocity DRAGON_INITIAL_VEL(-7900.0, 0.0);
static constexpr double DRAGON_RADIUS_PX = 7.0;

// Parts & fragments parameters
static constexpr double CENTER_PART_RADIUS_PX = 6.0;
static constexpr double ARRAY_PART_RADIUS_PX = 6.0;
static constexpr int    CENTER_FRAGMENT_COUNT = 4;
static constexpr int    ARRAY_FRAGMENT_COUNT = 2;
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

CrewDragon::CrewDragon()
   : Satellite(DRAGON_INITIAL_POS,
      DRAGON_INITIAL_VEL,
      DRAGON_RADIUS_PX)
{
}

void CrewDragon::drawSatellite() const
{
   Position pos = getPosition();
   double   rot = angleToward(Position(0, 0)).toRadians();
   ogstream gout(pos);
   gout.drawCrewDragon(pos, rot);
}

vector<Body*> CrewDragon::breakUp()
{
   vector<Body*> pieces;
   Position center = getPosition();
   Velocity vel = getVelocity();

   // Part: center module
   // pieces.push_back(new CrewDragonCenter(center, vel, CENTER_PART_RADIUS_PX));
   for (int i = 0; i < CENTER_FRAGMENT_COUNT; ++i) {
      double theta = randAngle();
      double kick = randSpeed(5000.0, 9000.0);
      Velocity nv(vel.getDx() + std::sin(theta) * kick,
         vel.getDy() + std::cos(theta) * kick);
      Position np = center;
      np.addPixelsX(std::sin(theta) * SPAWN_OFFSET_PX);
      np.addPixelsY(std::cos(theta) * SPAWN_OFFSET_PX);
      int lifetime = 50 + (std::rand() % 51);
      pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
   }

   // Part: left solar array
   // pieces.push_back(new CrewDragonLeft(center, vel, ARRAY_PART_RADIUS_PX));
   for (int i = 0; i < ARRAY_FRAGMENT_COUNT; ++i) {
      double theta = randAngle();
      double kick = randSpeed(5000.0, 9000.0);
      Velocity nv(vel.getDx() + std::sin(theta) * kick,
         vel.getDy() + std::cos(theta) * kick);
      Position np = center;
      np.addPixelsX(std::sin(theta) * SPAWN_OFFSET_PX);
      np.addPixelsY(std::cos(theta) * SPAWN_OFFSET_PX);
      int lifetime = 50 + (std::rand() % 51);
      pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
   }

   // Part: right solar array
   // pieces.push_back(new CrewDragonRight(center, vel, ARRAY_PART_RADIUS_PX));
   for (int i = 0; i < ARRAY_FRAGMENT_COUNT; ++i) {
      double theta = randAngle();
      double kick = randSpeed(5000.0, 9000.0);
      Velocity nv(vel.getDx() + std::sin(theta) * kick,
         vel.getDy() + std::cos(theta) * kick);
      Position np = center;
      np.addPixelsX(std::sin(theta) * SPAWN_OFFSET_PX);
      np.addPixelsY(std::cos(theta) * SPAWN_OFFSET_PX);
      int lifetime = 50 + (std::rand() % 51);
      pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
   }

   return pieces;
}
