/***********************************************************************
 * Header File:
 *    Fragment
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about fragment on the screen.
 ************************************************************************/
#pragma once
#include "body.h"

 /****************************************************************************
  * FRAGMENT CLASS
  * A small piece of debris that expires after a limited lifetime. 
  ****************************************************************************/
class Fragment : public Body {
public:
   Fragment(const Position& pos, const Velocity& vel, double radius, int lifetimeFrames);
   virtual ~Fragment() = default;

   // Integrate physics and decrement lifetime
   void update(double dt) override;

   void draw() const override;

   // Fragments do not break up further
   vector<Body*> breakUp() override { return {}; }

private:
   int mFramesLeft;
};