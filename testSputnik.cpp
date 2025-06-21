/***********************************************************************
 * Source File:
 *    TEST SPUTNIK
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/


#include "TestSputnik.h"
#include "unitTest.h"
#include "sputnik.h"     // bring in the Sputnik definition
#include <cmath>

void TestSputnik::construct_default()
{
   Sputnik s;
   // assertEquals only handles doubles, so use assertUnit for string equality:
   assertUnit(s.getName() == "Sputnik");
}

void TestSputnik::getName()
{
   Sputnik s;
   assertUnit(s.getName() == "Sputnik");
}

void TestSputnik::updateOrientation()
{
   Sputnik s;
   Position p(0, 1000);
   s.setPosition(p);
   s.updateOrientation();
   // angle in degrees should be 270
   assertUnit(fabs(s.getAngle().getDegrees() - 270.0) < 0.01);
}

void TestSputnik::draw()
{
   Sputnik s;
   s.draw();  // should not crash
   assertUnit(true);
}
