/***********************************************************************
* Header File:
*    Test GPS
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for GPS
************************************************************************/

#pragma once

#include "gps.h"
#include "unitTest.h"

/***********************************************************
 * TEST GPS
 ***********************************************************/
class TestGPS : public UnitTest {
public:
   void run();

private:
   void test_constructor_initialValues();    // verify initial pos, vel, radius
   void test_breakUp_count();                // returns 2 fragments
   void test_breakUp_fragmentType();         // each piece is a Fragment
   void test_breakUp_offsetDistance();       // offset by SPAWN_OFFSET_PX
   void test_draw_invokesDrawGPS();          // draw() calls drawSatellite()
};