/***********************************************************************
 * Header File:
 *    TestPosition : Test the Position class
 * Author:
 *    Natalia Navarrete and Diego Estrada
 * Summary:
 *    All the unit tests for Position
 ************************************************************************/
#pragma once

#include "position.h"
#include "unitTest.h"

 /*******************************
  * TEST Position
  * A friend class for Position which contains the Position unit tests
  ********************************/
class TestPosition : public UnitTest
{
public:
   void run();

private:
   void construct_default();
   void construct_nonDefault();
   void construct_copy();
   void assign();
   void getMetersX();
   void getMetersY();
   void setMetersX();
   void setMetersY();
};
