/***********************************************************************
* Header File:
*    Test Satellite
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Satellite
************************************************************************/

#pragma once

#include "satellite.h"
#include "unitTest.h"

 /***********************************************************************
 * TEST Satellite
 * A friend class for Satellite which contains the Satellite unit tests
 ************************************************************************/
class TestSatellite : public UnitTest {
public:
   void run();

private:
   void test_onCollision_setsExpired();
   void test_breakUp_customCount();
   void test_angleToward_cardinal();
   void test_draw_invokesDrawSatellite();
   void test_inheritsBodyIntersects();
};