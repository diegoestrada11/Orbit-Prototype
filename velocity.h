/***********************************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    
 ************************************************************************/
#pragma once

#include <math.h>

// for add()
class Acceleration;
class Angle;

/*********************************************
* Velocity
*********************************************/
class Velocity
{

public:
   // constructors
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy) : dx(dx), dy(dy) {}

   // getters
   double getDX()    const { return dx; }
   double getDY()    const { return dy; }
   double getSpeed() const { return sqrt((dx * dx) + (dy * dy)); }

   // setters
   void set(const Angle& angle, double magnitude);
   void add(const Acceleration& acceleration, double time);
   void setDX(double dx) { this->dx = dx; }
   void setDY(double dy) { this->dy = dy; }
   void addDX(double dx) { this->dx += dx; }
   void addDY(double dy) { this->dy += dy; }

private:
   double dx;           // horizontal velocity
   double dy;           // vertical velocity
};

