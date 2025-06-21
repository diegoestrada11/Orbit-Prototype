/***********************************************************************
 * Source File:
 *    SPUTNIK
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "sputnik.h"
#include "uiDraw.h"

Sputnik::Sputnik()
   : Satellite(), name("Sputnik")
{
}

std::string Sputnik::getName() const
{
   return name;
}

void Sputnik::draw() const
{
   Position pos = getPosition();
   double   rot = getAngle().getRadians();

   ogstream gout(pos);
   gout.drawSputnik(pos, rot);
}