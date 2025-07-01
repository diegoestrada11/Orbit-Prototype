/***********************************************************************
 * Header File:
 *    Test CrewDragon
 * Author:
 *    Natalia Navarrete Diego Estrada
 * Summary:
 *    All the unit tests for CrewDragon
 ************************************************************************/

#pragma once

#include "crewDragon.h"
#include "unitTest.h"

/***************************************************************
 * TEST CrewDragon Class
 ***************************************************************/
class TestCrewDragon : public UnitTest {
public:
   void run();

private:
   void test_constructor_initialValues();   // verify initial pos & vel
   void test_breakUp_count();               // total fragments = 4+2+2 = 8
   void test_breakUp_fragmentType();        // each returned is Fragment
   void test_breakUp_offsetDistance();      // offset by 4 px
   void test_draw_invokesDrawCrewDragon();  // draw() calls drawSatellite()
};