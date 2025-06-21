/***********************************************************************
* Header File:
*    Test Velocity : Test the Velocity class
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Velocity
************************************************************************/

#pragma once

#include "velocity.h"
#include "unitTest.h"

/*******************************
* TEST Velocity
* A friend class for Velocity which contains the Velocity unit tests
********************************/
class TestVelocity : public UnitTest
{
public:
   void run()
   {
      // Constructor
      construct_default();

      // Setters
      setDx();
      setDy();
      setFromAngleAndMagnitude();

      // Getters
      getDx();
      getDy();
      getSpeed();

      report("Velocity");
   }

private:
   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   none
    * output:  dx=0, dy=0
    *********************************************/
   void construct_default();

   /*********************************************
    * name:    SET DX
    * input:   dx=3.14
    * output:  getDx()==3.14
    *********************************************/
   void setDx();

   /*********************************************
    * name:    SET DY
    * input:   dy=-5.0
    * output:  getDy()==-5.0
    *********************************************/
   void setDy();

   /*********************************************
    * name:    SET FROM ANGLE AND MAGNITUDE
    * input:   magnitude=10, angle=45°
    * output:  dx=7.07, dy=7.07
    *********************************************/
   void setFromAngleAndMagnitude();

   /*********************************************
    * name:    GET DX
    * input:   dx set
    * output:  getDx() returns dx
    *********************************************/
   void getDx();

   /*********************************************
    * name:    GET DY
    * input:   dy set
    * output:  getDy() returns dy
    *********************************************/
   void getDy();

   /*********************************************
    * name:    GET SPEED
    * input:   dx=3, dy=4
    * output:  getSpeed()==5
    *********************************************/
   void getSpeed();
};