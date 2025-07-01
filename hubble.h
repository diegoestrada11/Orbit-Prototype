/***********************************************************************
 * Header File:
 *    Hubble
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about Hubble satellite on the screen.
 ************************************************************************/
#pragma once
#include "satellite.h"
#include <vector>

 /***********************************************************************
  * Hubble Class
  * Represents the Hubble Space Telescope satellite.
  * Inherits from Satellite and implements its specific behavior.
  ************************************************************************/
class Hubble : public Satellite {
public:
   Hubble();

   void drawSatellite() const override;

   // Breaks into 4 parts, each spawning fragments
   vector<Body*> breakUp() override;
};