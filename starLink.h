/***********************************************************************
 * Header File:
 *    Starlink
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a starlink satellite on the screen.
 ************************************************************************/

#pragma once

#include "satellite.h"
#include <vector>

 /****************************************************************************
  * Starlink Satellite Class
  ****************************************************************************/
class Starlink : public Satellite {
public:
   Starlink();

   void drawSatellite() const override;

   // Breaks into 2 parts each spawning 3 fragments
   vector<Body*> breakUp() override;
};