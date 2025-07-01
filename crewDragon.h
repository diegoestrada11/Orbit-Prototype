/***********************************************************************
 * Header File:
 *    CrewDragon
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    Everything we need to know about a crewDragon satellite on the screen.
 ************************************************************************/

#pragma once

#include "satellite.h"
#include <vector>
/*************************************************************************
* CrewDragon Class
**************************************************************************/
class CrewDragon : public Satellite {
public:
   CrewDragon();

   void drawSatellite() const override;
   vector<Body*> breakUp() override;
};
