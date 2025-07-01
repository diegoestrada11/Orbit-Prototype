/***********************************************************************
  * Header File:
  *    Acceleration : The representation of a acceleration on the screen
  * Author:
  *    Natalia Navarrete, Diego Estrada
  * Summary:
  *    Everything we need to know about an angle on the screen.
  ************************************************************************/

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

using namespace std;

/****************************************************************
 * ANGLE
 ****************************************************************/
class Angle
{
public:
   // Constructors
   Angle() : radians(0.0) {}
   explicit Angle(double rad) : radians(normalize(rad)) {}
   static Angle fromDegrees(double deg) {
      return Angle(normalize(deg * (M_PI / 180.0)));
   }

   static Angle fromVector(double dx, double dy) {
      return Angle(atan2(dx, dy));
   }

   // Get in radians or degrees
   double  toRadians() const { return radians; }
   double  toDegrees() const { return radians * (180.0 / M_PI); }

   // Set via radians or degrees
   void    setRadians(double r) { radians = normalize(r); }
   void    setDegrees(double d) { radians = normalize(d * (M_PI / 180.0)); }

   // Rotate by an offset (in radians)
   Angle& rotateBy(double deltaRad) { radians = normalize(radians + deltaRad); return *this; }
   Angle   rotated(double deltaRad) const { return Angle(radians + deltaRad); }

   // Unit vector for thrust/projectile direction
   double  sin() const { return std::sin(radians); }
   double  cos() const { return std::cos(radians); }

   // Operators for convenience
   Angle   operator+(const Angle& rhs) const { return Angle(radians + rhs.radians); }
   Angle& operator+=(const Angle& rhs) { return rotateBy(rhs.radians); }
   Angle   operator-(const Angle& rhs) const { return Angle(radians - rhs.radians); }
   Angle& operator-=(const Angle& rhs) { return rotateBy(-rhs.radians); }

private:
   double radians;

   // Keep everything in [0, 2)
   static double normalize(double r) {
      r = fmod(r, 2 * M_PI);
      return (r < 0 ? r + 2 * M_PI : r);
   }
};