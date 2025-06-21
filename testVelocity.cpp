/***********************************************************************
 * Source File:
 *    TEST VELOCITY
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/


#include "TestVelocity.h"
#include "unitTest.h"
#include "angle.h"
#include <cmath>

void TestVelocity::construct_default()
{
   Velocity v;
   assertEquals(v.getDx(), 0.0);
   assertEquals(v.getDy(), 0.0);
}

void TestVelocity::setDx()
{
   Velocity v;
   v.setDx(3.14);
   assertEquals(v.getDx(), 3.14);
}

void TestVelocity::setDy()
{
   Velocity v;
   v.setDy(-5.0);
   assertEquals(v.getDy(), -5.0);
}

void TestVelocity::setFromAngleAndMagnitude()
{
   Velocity v;
   Angle a(45.0);
   v.set(10.0, a);
   assertUnit(fabs(v.getDx() - 7.07) < 0.1);
   assertUnit(fabs(v.getDy() - 7.07) < 0.1);
}

void TestVelocity::getDx()
{
   Velocity v;
   v.setDx(2.5);
   assertEquals(v.getDx(), 2.5);
}

void TestVelocity::getDy()
{
   Velocity v;
   v.setDy(4.5);
   assertEquals(v.getDy(), 4.5);
}

void TestVelocity::getSpeed()
{
   Velocity v;
   v.setDx(3.0);
   v.setDy(4.0);
   assertUnit(fabs(v.getSpeed() - 5.0) < 0.0001);
}