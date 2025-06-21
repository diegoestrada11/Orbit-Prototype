/***********************************************************************
* Header File:
*    Test Satellite : Test the Satellite class
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Satellite
************************************************************************/

#pragma once

#include "satellite.h"
#include "unitTest.h"

 /*******************************
 * TEST Satellite
 * A friend class for Satellite which contains the Satellite unit tests
 ********************************/
class TestSatellite : public UnitTest
{
public:
   void run()
   {
      // Constructor
      construct_default();

      // Methods
      updateMovementOnly();
      updateOrientation();

      // Draw
      draw();

      report("Satellite");
   }

private:
   /*********************************************
   * name:    DEFAULT CONSTRUCTOR
   * input:   none
   * output:  position=(0,0), velocity=(0,0), angle=0
   *********************************************/
   void construct_default();

   /*********************************************
    * name:    UPDATE MOVEMENT ONLY
    * input:   velocity=(10,0), dt=1.0
    * output:  position.x==10
    *********************************************/
   void updateMovementOnly();

   /*********************************************
   * name:    UPDATE ORIENTATION
   * input:   position=(1000,0)
   * output:  angle==M_PI
   *********************************************/
   void updateOrientation();

   /*********************************************
    * name:    DRAW
    * input:   any state
    * output:  no crash, render called with angle
    *********************************************/
   void draw();
};
