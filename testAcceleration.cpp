/***********************************************************************
 * Source File:
 *    TEST ACCELERATION 
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for Acceleration
 ************************************************************************/
#include "TestAcceleration.h"
#include <cmath>

void TestAcceleration::run() {
   test_defaultConstructor();
   test_paramConstructor();
   test_getDDXDDY();
   test_setDDXDDY();
   test_addDDXDDY();
   test_addVector();
   test_setMagnitudeAngle();
   report("Acceleration");
}

/******************************************************
* TEST DEFAULT CONSTRUCTOR
* verify that Acceleration() initializes to zero
*******************************************************/
void TestAcceleration::test_defaultConstructor() {
   // Setup
   Acceleration a;
   // Exercise
   double dx = a.getDDX();
   double dy = a.getDDY();
   // Verify
   assertEquals(dx, 0.0);
   assertEquals(dy, 0.0);
   // Teardown
}

/******************************************************
* TEST PARAMETER CONSTRUCTOR
* verify that Acceleration(double ddx, double ddy) initializes
*******************************************************/
void TestAcceleration::test_paramConstructor() {
   // Setup & Exercise
   Acceleration a(1.5, -2.5);
   // Verify
   assertEquals(a.getDDX(), 1.5);
   assertEquals(a.getDDY(), -2.5);
   // Teardown
}

/******************************************************
* TEST GETDDXDDY
* verify that getDDX() and getDDY() return correct values
*******************************************************/
void TestAcceleration::test_getDDXDDY() {
   // Setup
   Acceleration a(3.0, 4.0);
   // Exercise & Verify
   assertEquals(a.getDDX(), 3.0);
   assertEquals(a.getDDY(), 4.0);
   // Teardown
}

/******************************************************
* TEST SET DDXDDY
* verify that setDDX() and setDDY() set values correctly
*******************************************************/
void TestAcceleration::test_setDDXDDY() {
   // Setup
   Acceleration a;
   // Exercise
   a.setDDX(-1.1);
   a.setDDY(2.2);
   // Verify
   assertEquals(a.getDDX(), -1.1);
   assertEquals(a.getDDY(), 2.2);
   // Teardown
}

/******************************************************
* TEST ADD DDXDDY
* verify that addDDX() and addDDY() increment values correctly
*******************************************************/
void TestAcceleration::test_addDDXDDY() {
   // Setup
   Acceleration a(0.5, -0.5);
   // Exercise
   a.addDDX(1.5);
   a.addDDY(2.0);
   // Verify
   assertEquals(a.getDDX(), 2.0);
   assertEquals(a.getDDY(), 1.5);
   // Teardown
}

/******************************************************
* TEST ADD VECTOR
* verify that add(Acceleration) adds components correctly
*******************************************************/
void TestAcceleration::test_addVector() {
   // Setup
   Acceleration a(1.0, 2.0);
   Acceleration b(0.5, -1.0);
   // Exercise
   a.add(b);
   // Verify
   assertEquals(a.getDDX(), 1.5);
   assertEquals(a.getDDY(), 1.0);
   // Teardown
}

/******************************************************
* TEST SET MAGNITUDE
* verify that set(angle, magnitude) sets components correctly
*******************************************************/
void TestAcceleration::test_setMagnitudeAngle() {
   // Setup
   Acceleration a;
   double magnitude = 10.0;
   // Exercise
   Angle angle = Angle::fromDegrees(180.0);
   a.set(angle, magnitude);
   // Verify
   assertEquals(a.getDDX(), magnitude * std::sin(angle.toRadians()));
   assertEquals(a.getDDY(), magnitude * std::cos(angle.toRadians()));
   // Teardown
}