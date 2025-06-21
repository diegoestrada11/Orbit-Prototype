/***********************************************************************
 * Source File:
 *    TEST ACCELERATION 
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for Acceleration
 ************************************************************************/
 // TestAcceleration.cpp
#include "TestAcceleration.h"
#include <cmath>

/*****************************************
 * run()
 *****************************************/
void TestAcceleration::run()
{
   construct_default();
   construct_param();
   getDDX();
   getDDY();
   setDDX();
   setDDY();
   addDDX();
   addDDY();
   add_acceleration();
   set_from_angle();

   report("Acceleration");
}

/*****************************************
 * Test DEFAULT CONSTRUCTOR
 *   input:  none
 *   output: ddx = 0.0, ddy = 0.0
 *****************************************/
void TestAcceleration::construct_default()
{
   Acceleration a;
   assertEquals(a.getDDX(), 0.0);
   assertEquals(a.getDDY(), 0.0);
}

/*****************************************
 * Test PARAMETERIZED CONSTRUCTOR
 *****************************************/
void TestAcceleration::construct_param()
{
   Acceleration a(3.5, -2.2);
   assertEquals(a.getDDX(), 3.5);
   assertEquals(a.getDDY(), -2.2);
}

/*****************************************
 * Test GET DDX
 *****************************************/
void TestAcceleration::getDDX()
{
   Acceleration a;
   a.setDDX(4.4);
   assertEquals(a.getDDX(), 4.4);
}

/*****************************************
 * Test GET DDY
 *****************************************/
void TestAcceleration::getDDY()
{
   Acceleration a;
   a.setDDY(-1.1);
   assertEquals(a.getDDY(), -1.1);
}

/*****************************************
 * Test SET DDX
 *****************************************/
void TestAcceleration::setDDX()
{
   Acceleration a;
   a.setDDX(5.5);
   assertEquals(a.getDDX(), 5.5);
   assertEquals(a.getDDY(), 0.0);
}

/*****************************************
 * Test SET DDY
 *****************************************/
void TestAcceleration::setDDY()
{
   Acceleration a;
   a.setDDY(-3.3);
   assertEquals(a.getDDY(), -3.3);
   assertEquals(a.getDDX(), 0.0);
}

/*****************************************
 * Test ADD DDX
 *****************************************/
void TestAcceleration::addDDX()
{
   Acceleration a(1.0, 2.0);
   a.addDDX(2.5);
   assertEquals(a.getDDX(), 3.5);
   assertEquals(a.getDDY(), 2.0);
}

/*****************************************
 * Test ADD DDY
 *****************************************/
void TestAcceleration::addDDY()
{
   Acceleration a(1.0, 2.0);
   a.addDDY(-1.5);
   assertEquals(a.getDDX(), 1.0);
   assertEquals(a.getDDY(), 0.5);
}

/*****************************************
 * Test ADD Acceleration (vector addition)
 *****************************************/
void TestAcceleration::add_acceleration()
{
   Acceleration a1(2.0, 3.0);
   Acceleration a2(-1.0, 4.0);
   a1.add(a2);
   assertEquals(a1.getDDX(), 1.0);
   assertEquals(a1.getDDY(), 7.0);
}

/*****************************************
 * Test SET from angle & magnitude
 *****************************************/
void TestAcceleration::set_from_angle()
{
   Acceleration a;

   // 0° ? ddx = 0, ddy = magnitude
   Angle angle0(0.0);
   a.set(angle0, 10.0);
   assertEqualsTolerance(a.getDDX(), 0.0, 1e-4);
   assertEqualsTolerance(a.getDDY(), 10.0, 1e-4);

   // 90° ? ddx = magnitude, ddy = 0
   Angle angle90(90.0);
   a.set(angle90, 5.0);
   assertEqualsTolerance(a.getDDX(), 5.0, 1e-4);
   assertEqualsTolerance(a.getDDY(), 0.0, 1e-4);
}
