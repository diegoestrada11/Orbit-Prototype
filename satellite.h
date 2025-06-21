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

 /****************************************************************************
  * SATELLITE
  ****************************************************************************/
class Satellite
{
public:
   Satellite();
   virtual ~Satellite() = default;

   // Getters
   const Position& getPosition() const;
   const Velocity& getVelocity() const;
   const Angle& getAngle()    const;

   // Setters
   void setPosition(const Position& pos);
   void setVelocity(const Velocity& vel);

   virtual void update(double dt);
   virtual void draw() const;
   void updateOrientation();

private:
   Position position;
   Velocity velocity;
   Angle    angle;
};
