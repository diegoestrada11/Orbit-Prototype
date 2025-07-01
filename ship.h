/***********************************************************************
 * Header File:
 *    Ship
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a ship on the screen.
 ************************************************************************/

#pragma once
#include "body.h"
#include "projectile.h"
#include <vector>

 /****************************************************************************
  * Ship Class
  * User-controlled spaceplane (Dream Chaser)
  ****************************************************************************/
class Ship : public Body {
public:
   Ship();
   virtual ~Ship() = default;

   void rotateLeft() { rotateBy(-TURN_RAD); }
   void rotateRight() { rotateBy(TURN_RAD); }
   void startThrust() { mThrusting = true; }
   void stopThrust() { mThrusting = false; }
   Projectile* fireProjectile();

   // Physics update
   void update(double dt) override;

   void draw() const override;

protected:
   // Override to add thrust on top of gravity
   Acceleration computeAcceleration() const override;

private:
   bool mThrusting;
   bool mFire;

   // Ship constants
   static constexpr double INITIAL_X = -450.0;    // pixels
   static constexpr double INITIAL_Y = 450.0;
   static constexpr double INITIAL_VX = 0.0;
   static constexpr double INITIAL_VY = -2000.0;
   static constexpr double SHIP_RADIUS = 10.0;    // pixels
   static constexpr double TURN_RAD = 0.1;     // radians per input
   static constexpr double THRUST_ACC = 2.0;     // m/s^2
   static constexpr double PROJECTILE_KICK = 9000.0; // m/s
   static constexpr double PROJECTILE_OFFSET = 19.0; // pixels
};