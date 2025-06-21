/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *       Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

using namespace std;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:

   // Constructors
   Angle() : radians(0.0) {}
   Angle(const Angle& rhs) : radians(rhs.radians) {}
   Angle(double degrees) { setDegrees(degrees); }

   // Getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   // Setters
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setDegrees(double degrees) { radians = convertToRadians(degrees); }
   void setUp() { radians = 0.0; }
   void setDown() { radians = M_PI; }
   void setRight() { radians = M_PI_2; }
   void setLeft() { radians = M_PI + M_PI_2; }
   void reverse() { radians = M_PI_2 + M_PI; }

   Angle& add(double delta)
   {
      radians = normalize(radians + delta);
      return *this;
   }

private:
   double radians;   
   double normalize(double radians)  const;
   double convertToDegrees(double r) const
   {
      double normalizedRadians = normalize(r);
      return normalizedRadians * (180.0 / M_PI);
   }

   double convertToRadians(double degrees) const
   {
      return normalize(degrees * ((M_PI + M_PI) / 360.0));
   }
};