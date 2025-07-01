/***********************************************************************
* Header File:
*    Test Starlink
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Starlink
************************************************************************/

#pragma once

#include "starlink.h"
#include "unitTest.h"

/************************************************************************
 * TEST Starlink class
 ************************************************************************/
class TestStarlink : public UnitTest {
public:
   void run();

private:
   void test_constructor_initialValues();   // check starting pos, vel, radius
   void test_breakUp_count();               // should return 6 fragments
   void test_breakUp_fragmentType();        // each returned is a Fragment
   void test_breakUp_offsetDistance();      // each fragment offset by 4 px
   void test_draw_invokesDrawStarlink();    // draw() calls drawSatellite()
};