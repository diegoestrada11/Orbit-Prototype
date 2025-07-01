/***********************************************************************
* Header File:
*    Test Angle
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Angle
************************************************************************/

#pragma once

#include "angle.h"
#include "unitTest.h"

/************************************************************************
* TEST Angle
* A friend class for Angle which contains the Angle unit tests
*************************************************************************/
class TestAngle : public UnitTest {
public:
   void run();

private:
   void test_defaultConstructor();        // default radians = 0
   void test_parameterConstructorNormalize(); // normalization to [0,2pi)
   void test_fromDegrees();               // conversion from degrees
   void test_toDegrees();                 // conversion to degrees
   void test_setRadians();                // setter normalization
   void test_setDegrees();                // setter in degrees
   void test_rotateBy();                  // rotate within and beyond 2pi
   void test_fromVector();                // build from vector using atan2
   void test_sinCos();                    // sin() and cos() reflect internal radians
   void test_operators();                 // +, -, +=, -= operators
};
