/***********************************************************************
 * Header File:
 *    Test Body
 * Author:
 *    Natalia Navarrete Diego Estrada
 * Summary:
 *    All the unit tests for Body
 ************************************************************************/

#pragma once

#include "body.h"
#include "unitTest.h"

 /************************************************************************
  * TEST Body
  * A friend class for Body which contains the Body unit tests
  ************************************************************************/
class TestBody : public UnitTest
{
public:
   void run();

private:
   void test_expire_setsExpired();
   void test_onCollision_expires();
   void test_breakUp_defaultEmpty();
   void test_intersects_true();
   void test_intersects_false();
   void test_computeAcceleration_belowSurface();
   void test_computeAcceleration_atSurface();
   void test_update_burnUp();
   void test_update_physicsIntegration();
};