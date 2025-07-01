/***********************************************************************
 * Header File:
 *    Orbit Simulator
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about the orbit simulator bodies on the screen.
 ************************************************************************/
#pragma once

#include "body.h"
#include "sputnik.h"
#include "gps.h"
#include "hubble.h"
#include "starlink.h"
#include "crewDragon.h"
#include "ship.h"
#include "earth.h"
#include "uiInteract.h"
#include "uiDraw.h"

#include <vector>

 /***********************************************************************
  * OrbitSimulator Class
  ************************************************************************/
class OrbitSimulator
{
public:
   OrbitSimulator(const Position& bounds);
   ~OrbitSimulator();

   void input(const Interface* pUI);
   void display();

private:
   Position               viewBounds;
   vector<Body*>     bodies;

   // Helpers
   void    advanceAll(double dt);
   void    handleCollisions();
   void    removeExpired();
};


