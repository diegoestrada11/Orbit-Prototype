/***********************************************************************
 * Source File:
 *    TEST ANGLE
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 ************************************************************************/

#include "TestAngle.h"
#include <cmath>

void TestAngle::run() {
   test_defaultConstructor();
   test_parameterConstructorNormalize();
   test_fromDegrees();
   test_toDegrees();
   test_setRadians();
   test_setDegrees();
   test_rotateBy();
   test_fromVector();
   test_sinCos();
   test_operators();
   report("Angle");
}

/******************************************************
* TEST DEFAULT CONSTRUCTOR
* verify that Angle() should be 0 radians
*******************************************************/
void TestAngle::test_defaultConstructor() {
   // Setup
   Angle a;
   double rad = -99.99;
   // Exercise
   rad = a.toRadians();
   // Verify
   assertEquals(rad, 0.0);
   // Teardown
}

/******************************************************
* TEST PARAMETER CONSTRUCTOR NORMALIZE
* verify that Angle(double radians) normalizes
*******************************************************/
void TestAngle::test_parameterConstructorNormalize() {
   // Setup & Exercise
   double rad1 = -M_PI / 2; // -90° radians
   double rad2 = 3 * M_PI;  // 540° radians
   // Exercise
   Angle a1(rad1);
   Angle a2(rad2);
   // Verify
   assertEquals(a1.toRadians(), 3 * M_PI / 2);
   assertEquals(a2.toRadians(), M_PI);
   // Teardown
}

/******************************************************
* TEST FROM DEGREES
* verify fromDegrees() converts degrees to radians
*******************************************************/
void TestAngle::test_fromDegrees() {
   // Setup & Exercise
   Angle zero = Angle::fromDegrees(0.0);
   Angle half = Angle::fromDegrees(180.0);
   Angle full = Angle::fromDegrees(360.0);
   // Verify
   assertEquals(zero.toRadians(), 0.0);
   assertEquals(half.toRadians(), M_PI);
   assertEquals(full.toRadians(), 0.0);
   // Teardown
}

/******************************************************
* TEST TO DEGREES
* verify toDegrees() converts radians to degrees
*******************************************************/
void TestAngle::test_toDegrees() {
   // Setup
   Angle a(M_PI / 2); // 90°
   // Exercise
   double deg = a.toDegrees();
   // Verify
   assertEquals(deg, 90.0);
   // Teardown
}

/******************************************************
* TEST SET RADIANS
* verify setRadians() normalizes to [0,2pi)
*******************************************************/
void TestAngle::test_setRadians() {
   // Setup
   Angle a;
   // Exercise
   a.setRadians(-M_PI / 2);
   // Verify
   assertEquals(a.toRadians(), 3 * M_PI / 2);
   // Teardown
}

/******************************************************
* TEST SET DEGREES
* verify setDegrees() normalizes to [0,360)
*******************************************************/
void TestAngle::test_setDegrees() {
   // Setup
   Angle a;
   // Exercise
   a.setDegrees(-90.0);
   // Verify
   assertEquals(a.toRadians(), 3 * M_PI / 2);
   // Teardown
}

/******************************************************
* TEST ROTATE BY
* verify rotateBy() normalizes results
*******************************************************/
void TestAngle::test_rotateBy() {
   // Setup
   Angle a(M_PI);
   // Exercise
   a.rotateBy(M_PI);
   // Verify
   assertEquals(a.toRadians(), 0.0);
   // Teardown
}

/******************************************************
* TEST FROM VECTOR
* verify fromVector() uses atan2 to create angles
*******************************************************/
void TestAngle::test_fromVector() {
   // Setup & Exercise
   Angle up = Angle::fromVector(0.0, 1.0); // dx=0,dy=1 ? atan2(0,1)=0 rad (0° up)
   Angle right = Angle::fromVector(1.0, 0.0); // dx=1,dy=0 ? atan2(1,0)=?/2 rad (90° right)
   // Verify
   assertEquals(up.toRadians(), 0.0);
   assertEquals(right.toRadians(), M_PI / 2);
   // Teardown
}

/******************************************************
* TEST SIN COS
* verify sin() and cos() return correct values
*******************************************************/
void TestAngle::test_sinCos() {
   // Setup
   Angle a(M_PI / 6); // 30°
   // Exercise & Verify
   assertEquals(a.sin(), sin(M_PI / 6));
   assertEquals(a.cos(), cos(M_PI / 6));
   // Teardown
}

/******************************************************
* TEST OPERATORS
* verify that +, -, +=, -= operators work correctly
*******************************************************/
void TestAngle::test_operators() {
   // Setup
   Angle a(M_PI / 2);      // 90°
   Angle b(M_PI);          // 180°
   // Exercise
   Angle sum = a + b;      // 270° ? 3?/2
   Angle diff = b - a;     // 90° ? ?/2
   a += b;                 // modifies a to 270°
   b -= Angle(M_PI / 2);   // modifies b to 180°-90°=90°
   // Verify
   assertEquals(sum.toRadians(), 3 * M_PI / 2);
   assertEquals(diff.toRadians(), M_PI / 2);
   assertEquals(a.toRadians(), 3 * M_PI / 2);
   assertEquals(b.toRadians(), M_PI / 2);
   // Teardown
}
