/***********************************************************************
 * Header File:
 *    TestAcceleration : Test the Acceleration class
 * Author:
 *    Natalia Navarrete, Diego Estrada
 * Summary:
 *    All the unit tests for Acceleration
 ************************************************************************/
#pragma once

#include "acceleration.h"
#include "unitTest.h"

 /*******************************
  * TEST Acceleration
  * A friend class for Acceleration which contains its unit tests
  ********************************/
class TestAcceleration : public UnitTest
{
public:
   void run();

private:
   void construct_default();
   void construct_param();
   void getDDX();
   void getDDY();
   void setDDX();
   void setDDY();
   void addDDX();
   void addDDY();
   void add_acceleration();
   void set_from_angle();
};
