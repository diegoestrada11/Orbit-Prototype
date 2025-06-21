/***********************************************************************
 * Source File:
 *    TEST ANGLE
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "TestAngle.h"
#include "angle.h"
#include "unitTest.h"
#include <cmath>

void TestAngle::construct_default()
{
   Angle a;
   assertEquals(a.getDegrees(), 0.0);
   assertUnit(fabs(a.getRadians()) < 0.0001);
}

void TestAngle::setDegrees()
{
   Angle a;
   a.setDegrees(180.0);
   assertUnit(fabs(a.getDegrees() - 180.0) < 0.001);
}

void TestAngle::setRadians()
{
   Angle a;
   a.setRadians(M_PI);
   assertUnit(fabs(a.getRadians() - M_PI) < 0.001);
}

void TestAngle::setFromRadians()
{
   Angle a;
   a.setRadians(atan2(-1.0, 0.0));
   assertUnit(fabs(a.getDegrees() - 270.0) < 0.01);
}

void TestAngle::getDegrees()
{
   Angle a(90.0);
   assertUnit(fabs(a.getDegrees() - 90.0) < 0.001);
}

void TestAngle::getRadians()
{
   Angle a;
   a.setRadians(M_PI_2);
   assertUnit(fabs(a.getRadians() - M_PI_2) < 0.001);
}

void TestAngle::normalizeAbove360()
{
   Angle a;
   a.setDegrees(450.0);
   assertUnit(fabs(a.getDegrees() - 90.0) < 0.001);
}

void TestAngle::normalizeNegative()
{
   Angle a;
   a.setDegrees(-90.0);
   assertUnit(fabs(a.getDegrees() - 270.0) < 0.001);
}