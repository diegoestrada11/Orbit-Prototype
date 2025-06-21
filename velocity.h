/***********************************************************************
 * Header File:
 *    Velocity
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a velocity on the screen.
 ************************************************************************/

#include <cmath>
#include "angle.h"
#include "acceleration.h"
#pragma once
class TestVelocity;


/*********************************************
 * Velocity
 *********************************************/
class Velocity
{
   friend class TestVelocity;

public:
   // Constructors
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy) : dx(dx), dy(dy) {}

   // Getters
   double getDx()    const { return dx; }
   double getDy()    const { return dy; }
   double getSpeed() const { return sqrt(dx * dx + dy * dy); }

   // Setters
   void set(double magnitude, const Angle& angle);

   void add(const Acceleration& acceleration, double time);

   void setDx(double dx) { this->dx = dx; }
   void setDy(double dy) { this->dy = dy; }
   void addDx(double dx) { this->dx += dx; }
   void addDy(double dy) { this->dy += dy; }

private:
   double dx;  // horizontal velocity
   double dy;  // vertical velocity
};