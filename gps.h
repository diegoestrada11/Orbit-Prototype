/***********************************************************************
 * Header File:
 *    GPS
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about GPS satellite on the screen.
 ************************************************************************/

#pragma once
#include "satellite.h"
#include <vector>

 /****************************************************************************
  * GPS CLASS
  ****************************************************************************/
class GPS : public Satellite {
public:
   GPS();

   void drawSatellite() const override;

   // Breaks into 3 persistent parts + 2 ephemeral fragments
   vector<Body*> breakUp() override;
};
