/***********************************************************************
* Header File:
*    Test Velocity
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Velocity
************************************************************************/
#pragma once

#include "velocity.h"
#include "unitTest.h"

/************************************************************************
 * TEST Velocity
 * A friend class for Velocity which contains the Velocity unit tests
 ************************************************************************/
class TestVelocity : public UnitTest {
public:
   void run();

private:
   // Constructor tests
   void test_construct_default();    // default constructor
   void test_construct_params();     // non-default constructor

   // Getter tests
   void test_getDxDy();              // getDx()/getDy()
   void test_getSpeed();             // magnitude computation

   // Setter & modifier tests
   void test_setMagnitudeAngle();    // set(mag, angle)
   void test_addAcceleration();      // add(acceleration, dt)
   void test_setDxDy();              // setDx()/setDy()
   void test_addDxDy();              // addDx()/addDy()
};
