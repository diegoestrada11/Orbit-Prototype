/***********************************************************************
 * Source File:
 *    TEST SATELLITE
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/


#include "TestSatellite.h"
#include "satellite.h"
#include <cmath>

void TestSatellite::construct_default()
{
   Satellite s;
   assertUnit(s.getPosition().getMetersX() == 0.0);
   assertUnit(s.getPosition().getMetersY() == 0.0);
   assertUnit(s.getVelocity().getDx() == 0.0);
   assertUnit(s.getVelocity().getDy() == 0.0);
   assertUnit(fabs(s.getAngle().getRadians()) < 0.0001);
}

void TestSatellite::updateMovementOnly()
{
   Satellite s;
   Velocity v;
   v.setDx(10.0);
   s.setVelocity(v);
   s.update(1.0);
   assertUnit(s.getPosition().getMetersX() == 10.0);
}

void TestSatellite::updateOrientation()
{
   Satellite s;
   Position p(1000.0, 0.0);
   s.setPosition(p);
   s.updateOrientation();
   assertUnit(fabs(s.getAngle().getRadians() - M_PI) < 0.01);
}

void TestSatellite::draw()
{
   Satellite s;
   s.draw();  // no crash
   assertUnit(true);
}