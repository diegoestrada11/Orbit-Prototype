/***********************************************************************
* Source File:
*    Hubble
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
************************************************************************/

#include "hubble.h"
#include "fragment.h"
#include "uiDraw.h"
#include <cmath>
#include <random>

// GEO at 42,164 km from center, orbital velocity 3.1 km/s
static const Position HUBBLE_INITIAL_POS(0.0, -42164000.0);
static const Velocity HUBBLE_INITIAL_VEL(3100.0, 0.0);
static constexpr double HUBBLE_RADIUS_PX = 10.0;

// Breakup parameters
static constexpr double HELMET_PART_RADIUS = 10.0; // telescope body
static constexpr int    HELMET_FRAGMENT_CNT = 3;
static constexpr double COMPUTER_PART_RADIUS = 7.0;
static constexpr int    COMPUTER_FRAGMENT_CNT = 2;
static constexpr double ARRAY_PART_RADIUS = 8.0;
static constexpr int    ARRAY_FRAGMENT_CNT = 2;
static constexpr double FRAG_RADIUS_PX = 2.0;
static constexpr double SPAWN_OFFSET_PX = 4.0;

// random utilities
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

Hubble::Hubble()
   : Satellite(HUBBLE_INITIAL_POS,
      HUBBLE_INITIAL_VEL,
      HUBBLE_RADIUS_PX)
{
}

void Hubble::drawSatellite() const
{
   Position pos = getPosition();
   double   rot = angleToward(Position(0, 0)).toRadians();
   ogstream gout(pos);
   gout.drawHubble(pos, rot);
}

vector<Body*> Hubble::breakUp()
{
   vector<Body*> pieces;
   Position center = getPosition();
   Velocity vel = getVelocity();

   // Part: Telescope body
   // pieces.push_back(new HubbleTelescope(center, vel, HELMET_PART_RADIUS));
   for (int i = 0; i < HELMET_FRAGMENT_CNT; ++i) {
      double theta = randAngle();
      double kick = randSpeed(5000.0, 9000.0);
      Velocity nv(vel.getDx() + sin(theta) * kick,
         vel.getDy() + cos(theta) * kick);
      Position np = center;
      np.addPixelsX(sin(theta) * SPAWN_OFFSET_PX);
      np.addPixelsY(cos(theta) * SPAWN_OFFSET_PX);
      int lifetime = 50 + (rand() % 51);
      pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
   }

   // Part: Computer module
   // pieces.push_back(new HubbleComputer(center, vel, COMPUTER_PART_RADIUS));
   for (int i = 0; i < COMPUTER_FRAGMENT_CNT; ++i) {
      double theta = randAngle();
      double kick = randSpeed(5000.0, 9000.0);
      Velocity nv(vel.getDx() + sin(theta) * kick,
         vel.getDy() + cos(theta) * kick);
      Position np = center;
      np.addPixelsX(sin(theta) * SPAWN_OFFSET_PX);
      np.addPixelsY(cos(theta) * SPAWN_OFFSET_PX);
      int lifetime = 50 + (rand() % 51);
      pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
   }

   // Part: Left solar array
   // pieces.push_back(new HubbleLeft(center, vel, ARRAY_PART_RADIUS));
   for (int i = 0; i < ARRAY_FRAGMENT_CNT; ++i) {
      double theta = randAngle();
      double kick = randSpeed(5000.0, 9000.0);
      Velocity nv(vel.getDx() + sin(theta) * kick,
         vel.getDy() + cos(theta) * kick);
      Position np = center;
      np.addPixelsX(sin(theta) * SPAWN_OFFSET_PX);
      np.addPixelsY(cos(theta) * SPAWN_OFFSET_PX);
      int lifetime = 50 + (rand() % 51);
      pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
   }

   // Part: Right solar array
   // pieces.push_back(new HubbleRight(center, vel, ARRAY_PART_RADIUS));
   for (int i = 0; i < ARRAY_FRAGMENT_CNT; ++i) {
      double theta = randAngle();
      double kick = randSpeed(5000.0, 9000.0);
      Velocity nv(vel.getDx() + sin(theta) * kick,
         vel.getDy() + cos(theta) * kick);
      Position np = center;
      np.addPixelsX(sin(theta) * SPAWN_OFFSET_PX);
      np.addPixelsY(cos(theta) * SPAWN_OFFSET_PX);
      int lifetime = 50 + (rand() % 51);
      pieces.push_back(new Fragment(np, nv, FRAG_RADIUS_PX, lifetime));
   }

   return pieces;
}
