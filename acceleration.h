/***********************************************************************
 * Header File:
 *    Acceleration : The representation of a acceleration on the screen
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about an acceleration on the screen.
 ************************************************************************/
#include "angle.h"
#pragma once
class testAcceleration;

/*********************************************
* ACCELERATION
*********************************************/
class Acceleration
{
   friend class TestAcceleration;
public:
   // Constructors
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) {}

   // Getters
   double getDDX() const { return ddx; }
   double getDDY() const { return ddy; }

   // Set via magnitude and Angle
   void set(const Angle& angle, double magnitude);

   // Direct setters
   void setDDX(double ddx) { this->ddx = ddx; }
   void setDDY(double ddy) { this->ddy = ddy; }
   void addDDX(double ddx) { this->ddx += ddx; }
   void addDDY(double ddy) { this->ddy += ddy; }

   void add(const Acceleration& rhs);

private:
   double ddx;   // horizontal component
   double ddy;   // vertical component
};
