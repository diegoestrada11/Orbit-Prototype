/***********************************************************************
* Header File:
*    Test Hubble
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Hubble
************************************************************************/

#pragma once

#include "hubble.h"
#include "unitTest.h"

/*************************************************************************
 * TEST Hubble
 * Unit tests for the Hubble class (subclass of Satellite).
 *************************************************************************/
class TestHubble : public UnitTest {
public:
   void run();

private:
   void test_constructor_initialValues();     // check initial pos, vel
   void test_breakUp_count();                 // total fragments = 3+2+2+2 = 9
   void test_breakUp_fragmentType();          // each returned is Fragment
   void test_breakUp_offsetDistance();        // offset by 4 px
   void test_draw_invokesDrawHubble();        // draw() calls drawSatellite()
};