/***********************************************************************
 * Header File:
 *    Test Earth
 * Author:
 *    Natalia Navarrete Diego Estrada
 * Summary:
 *    All the unit tests for Earth
 ************************************************************************/

#pragma once

#include "earth.h"
#include "unitTest.h"

/***************************************************************
 * TEST Earth Class
 ***************************************************************/
class TestEarth: public UnitTest
{
public:
   void run();
private:
   void test_constructor_initialValues();
   void test_update_rotation();
   void test_breakUp_empty();
   void test_draw_invokesDraw();
};