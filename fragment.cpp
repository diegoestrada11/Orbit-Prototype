/***********************************************************************
* Source File:
*    ORBIT SIMULATOR
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
************************************************************************/

#include "fragment.h"
#include "uiDraw.h"    // for drawFragment()
#include <random>

static int randomInt(int min, int max) {
   static random_device rd;
   static mt19937 gen(rd());
   uniform_int_distribution<> dist(min, max);
   return dist(gen);
}

Fragment::Fragment(const Position& pos, const Velocity& vel, double radius, int lifetimeFrames)
   : Body(pos, vel, radius)
   , mFramesLeft(lifetimeFrames)
{
   // Optionally give fragments a random initial rotation
   double spin = randomInt(1, 5) * 0.1; // radians per update
   rotateBy(spin);
}

void Fragment::update(double dt)
{
   // Integrate motion
   Body::update(dt);

   // Decrement lifetime and expire if zero
   if (--mFramesLeft <= 0) {
      expire();
   }

   // Optionally rotate fragment each frame
   rotateBy(0.05); // adjust rotation speed as desired
}

void Fragment::draw() const
{
   Position pos = getPosition();
   double   rot = getAngle().toRadians();
   ogstream gout(pos);
   gout.drawFragment(pos, rot);
}
