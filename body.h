/***********************************************************************
 * Header File:
 *    Body
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a body on the screen.
 ************************************************************************/
#pragma once
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include <vector>

/****************************************************************************
 * BODY
 ****************************************************************************/
class Body
{
protected:
   Position    mPos;        // current x,y in meters (or world units)
   Velocity    mVel;        // current dx,dy in m/s
   Angle       mAngle;
   double      mRadius;     // collision/draw radius in pixels
   bool        mExpired;    // for fragments/projectiles that time out

public:
   Body(const Position& pos, const Velocity& vel, double radius);
   virtual ~Body();

   // main integration step: advance by dt seconds of sim time
   virtual void update(double dt);
   virtual void draw() const = 0;

   // called when you detect a collision with another Body
   // default: mark expired or do nothing.  Satellites override to breakUp().
   virtual void onCollision(Body* other) noexcept;

   // for Satellites: spawn zero-or-more new Bodies (Fragments, Parts)
   // default implementation returns an empty vector.
   virtual vector<Body*> breakUp();

   // getters
   const Position& getPosition() const { return mPos; }
   const Velocity& getVelocity() const { return mVel; }
   const Angle& getAngle()       const { return mAngle; }
   double           getRadius() const { return mRadius; }
   bool             isExpired() const { return mExpired; }

   // setters
   void          setAngle(const Angle& a) { mAngle = a; }
   void          rotateBy(double dr) { mAngle.rotateBy(dr); }
   
   // utility: circle based intersection test
   bool intersects(const Body& other) const;

   virtual bool canBurnUp() const { return true; }
   static double getZoom() {
      Position tmp;         // zoom was set once at position class
      return tmp.getZoom();
   }

protected:
   // default = gravity toward earth
   virtual Acceleration computeAcceleration() const;

   // mark this Body so the simulator will remove it at end of frame
   void expire() { mExpired = true; }
};
