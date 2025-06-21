/***********************************************************************
 * Header File:
 *    Body
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a body on the screen.
 ************************************************************************/

#include "position.h"
#include "velocity.h"
#pragma once

/****************************************************************************
 * BODY
 ****************************************************************************/
class Body
{
public:
   Body() : position(), velocity(), active(true) {}
   virtual ~Body() = default;

   // Getters
   const Position& getPosition() const { return position; }
   const Velocity& getVelocity() const { return velocity; }
   bool            isActive()   const { return active; }

   // Setters
   void setPosition(const Position& pos) { position = pos; }
   void setVelocity(const Velocity& vel) { velocity = vel; }
   void setActive(bool a) { active = a; }

   virtual void update(double dt);
   virtual void draw() const = 0;

private:
   Position position;
   Velocity velocity;
   bool     active;
};