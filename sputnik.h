/***********************************************************************
 * Header File:
 *    Sputnik
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a sputnik satellite on the screen.
 ************************************************************************/

#pragma once
#include "satellite.h"
#include <string>
#include <vector>

/****************************************************************************
* SPUTNIK
****************************************************************************/
class Sputnik : public Satellite {
public:
   Sputnik();

   // Draw Sputnik sprite (radius = 4px)
   void drawSatellite() const override;

   // When Sputnik collides, break into 4 fragments
   vector<Body*> breakUp() override;
};