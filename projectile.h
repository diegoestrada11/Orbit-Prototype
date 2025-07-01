/***********************************************************************
 * Header File:
 *    Projectile
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a projectile on the screen.
 ************************************************************************/

#pragma once
#include "body.h"
#include <vector>

 /***********************************************************************
  * Projectile Class
  * A projectile fired by the Ship; expires after a fixed lifetime
  ************************************************************************/
class Projectile : public Body {
public:
   Projectile(const Position& pos, const Velocity& vel, double radius, int lifetimeFrames);
   virtual ~Projectile() = default;

   // Integrate motion and decrement lifetime
   void update(double dt) override;

   void draw() const override;

   // Projectiles do not break up further
   vector<Body*> breakUp() override { return {}; }
private:
   int mFramesLeft;  // remaining frames before expiry
};
