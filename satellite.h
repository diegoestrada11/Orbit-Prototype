/***********************************************************************
 * Header File:
 *    Satellite
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a satellite on the screen.
 ************************************************************************/

#pragma once
#include "position.h"
#include "velocity.h"
#include "angle.h"
#include <cmath>
#include "body.h"
#include <vector>

 /****************************************************************************
  * SATELLITE
  ****************************************************************************/
class Satellite : public Body
{
public:
   Satellite(const Position& pos, const Velocity& vel, double radius);
   virtual ~Satellite() = default;

   // Marks the satellite expired so simulator removes it
   void onCollision(Body* other) noexcept override;

   // Spawn parts/fragments after collision
   virtual vector<Body*> breakUp() = 0;

   // Each Satellite provides its own draw routine
   void draw() const override { drawSatellite(); }

   Angle angleToward(const Position& target) const {
      double vx = target.getMetersX() - mPos.getMetersX();
      double vy = target.getMetersY() - mPos.getMetersY();
      return Angle::fromVector(vx, vy);
   }

protected:
   // Draw the satellite sprite
   virtual void drawSatellite() const = 0;
};
