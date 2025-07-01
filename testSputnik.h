/***********************************************************************
* Header File:
*    Test Sputnik
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Sputnik
************************************************************************/

#pragma once

#include "sputnik.h"
#include "unitTest.h"

/************************************************************************
* TEST Sputnik
* A friend class for Sputnik which contains the Sputnik unit tests
*************************************************************************/
class TestSputnik : public UnitTest
{
public:
   void run();

private:
   void test_constructor_initialValues();        // verify initial pos & vel
   void test_breakUp_count();                    // returns 4 fragments
   void test_breakUp_fragmentType();             // each piece is a Fragment
   void test_breakUp_offsetDistance();           // each fragment offset 4 px
   void test_draw_invokesDrawSputnik();          // draw() calls drawSatellite()
};