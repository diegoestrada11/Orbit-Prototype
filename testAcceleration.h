/***********************************************************************
 * Header File:
 *    TestAcceleration
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for Acceleration
 ************************************************************************/
#pragma once

#include "acceleration.h"
#include "unitTest.h"

 /************************************************************************
  * TEST Acceleration
  * A friend class for Acceleration which contains its unit tests
  ************************************************************************/
class TestAcceleration : public UnitTest 
{
public:
   void run();

private:
   void test_defaultConstructor();         // default constructor sets zero
   void test_paramConstructor();           // constructor with components
   void test_getDDXDDY();                  // getters
   void test_setDDXDDY();                  // direct setters
   void test_addDDXDDY();                  // addDDX/addDDY
   void test_addVector();                  // add(acceleration)
   void test_setMagnitudeAngle();          // set(angle, magnitude)
};
