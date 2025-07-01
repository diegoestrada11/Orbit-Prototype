/***********************************************************************
 * Source File:
 *    TEST VELOCITY
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "testVelocity.h"
#include <cmath>

void TestVelocity::run() {
   test_construct_default();
   test_construct_params();
   test_getDxDy();
   test_getSpeed();
   test_setMagnitudeAngle();
   test_addAcceleration();
   test_setDxDy();
   test_addDxDy();
   report("Velocity");
}

/******************************************************
* TEST CONSTRUCT DEFAULT
* verify default velocity is zero
*******************************************************/
void TestVelocity::test_construct_default() {
   // Setup and Exercise
   Velocity v;
   // Verify
   assertEquals(v.getDx(), 0.0);
   assertEquals(v.getDy(), 0.0);
   // Teardown
}

/******************************************************
* TEST CONSTRUCT PARAM
* verify constructor initializes dx, dy
*******************************************************/
void TestVelocity::test_construct_params() {
   // Setup
   double dx = 3.5, dy = -2.25;
   // Exercise
   Velocity v(dx, dy);
   // Verify
   assertEquals(v.getDx(), 3.5);
   assertEquals(v.getDy(), -2.25);
   assertEquals(dx, 3.5);
   assertEquals(dy, -2.25);
   // Teardown
}

/******************************************************
* TEST GET DX DY
* verify getDx() and getDy() return correct values
*******************************************************/
void TestVelocity::test_getDxDy() {
   // Setup
   double dx = 7.0, dy = -4.0;
   double vDX, vDY;
   Velocity v(dx, dy);
   // Exercise
   vDX = v.getDx();
   vDY = v.getDy();
   // Verify
   assertEquals(vDX, 7.0);
   assertEquals(vDY, -4.0);
   assertEquals(dx, 7.0);
   assertEquals(dy, -4.0);
   // Teardown
}

/******************************************************
* TEST GET SPEED
* verify getSpeed() computes Pythagorean magnitude
*******************************************************/
void TestVelocity::test_getSpeed() {
   // Setup
   double dx = 3.0, dy = 4.0;
   double speed;
   Velocity v(dx, dy);
   // Exercise
   speed = v.getSpeed();
   // Verify
   assertEquals(speed, 5.0);
   assertEquals(dx, 3.0);
   assertEquals(dy, 4.0);
   // Teardown
}

/******************************************************
* TEST SET MAGNITUDE ANGLE
* verify set(mag, angle) sets dx, dy correctly
*******************************************************/
void TestVelocity::test_setMagnitudeAngle() {
   // Setup
   Velocity v;
   double mag = 5.0, angDegrees = 90.0;
   Angle angle = Angle::fromDegrees(angDegrees);
   // Exercise
   v.set(mag, angle);
   // Verify
   assertEquals(v.getDx(), mag * sin(angle.toRadians()));
   assertEquals(v.getDy(), mag * cos(angle.toRadians()));
   assertEquals(mag, 5.0);
   assertEquals(angDegrees, 90.0);
   assertEquals(v.getSpeed(), mag);
   assertEquals(angle.toDegrees(), angDegrees);
   // Teardown
}

/******************************************************
* TEST ADD ACCELERATION
* verify add(acceleration, dt) updates dx, dy
*******************************************************/
void TestVelocity::test_addAcceleration() {
   // Setup
   Velocity v(1.0, 2.0);
   Acceleration a;
   a.setDDX(0.5);
   a.setDDY(-1.5);
   double dt = 4.0;
   // Exercise
   v.add(a, dt);
   // Verify: dx += a.ax*dt, dy += a.ay*dt
   assertEquals(v.getDx(), 1.0 + 0.5 * dt);
   assertEquals(v.getDy(), 2.0 - 1.5 * dt);
   // Teardown
}

/******************************************************
* TEST SET DX DY
* verify setDx() and setDy() set values correctly
*******************************************************/
void TestVelocity::test_setDxDy() {
   // Setup
   Velocity v;
   double dx = 9.9, dy = -7.7;
   // Exercise
   v.setDx(dx);
   v.setDy(dy);
   // Verify
   assertEquals(v.getDx(), dx);
   assertEquals(v.getDy(), dy);
   // Teardown
}

/******************************************************
* TEST ADD DX DY
* verify addDx() and addDy() modify dx, dy correctly
*******************************************************/
void TestVelocity::test_addDxDy() {
   // Setup
   Velocity v(1.0, 1.0);
   // Exercise
   v.addDx(2.5);
   v.addDy(-3.5);
   // Verify: dx = 3.5, dy = -2.5
   assertEquals(v.getDx(), 3.5);
   assertEquals(v.getDy(), -2.5);
   // Teardown
}
