/***********************************************************************
 * Header File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich
 * Summary:
 ************************************************************************/
#pragma once

#include "angle.h";

/*********************************************
 * Acceleration
*********************************************/
class Acceleration
{

public:
   // Constructors
   Acceleration() : ddx(0.00), ddy(0.00) {}
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) {}

   // Getters
   double getDDX() const { return ddx; }
   double getDDY() const { return ddy; }

   // Setters
   void set(const Angle& a, const double magnitude);
   void setDDX(double ddx) { this->ddx = ddx; }
   void setDDY(double ddy) { this->ddy = ddy; }
   void addDDX(double ddx) { this->ddx += ddx; }
   void addDDY(double ddy) { this->ddy += ddy; }
   void add(const Acceleration& rhs);

private:
   double ddx; // horizontal acceleration
   double ddy; // vertical acceleration
};

