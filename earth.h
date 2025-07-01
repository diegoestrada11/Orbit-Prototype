/***********************************************************************
 * Header File:
 *    Earth
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about Earth planet on the screen.
 ************************************************************************/
#pragma once

#include "body.h"
#include "position.h"
#include <vector>

/*************************************************************************
* EARTH CLASS
* Represents the Earth at the center of the simulation.
**************************************************************************/
class Earth : public Body {
public:
   explicit Earth();
   virtual ~Earth() = default;

   /// Advance Earth's rotation
   void update(double dt) override;

   /// Draw the Earth at (0,0) with current rotation
   void draw() const override;

   /// Earth never breaks up
   vector<Body*> breakUp() override { return {}; }
};
