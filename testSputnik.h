/***********************************************************************
* Header File:
*    Test Sputnik : Test the Sputnik class
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Sputnik
************************************************************************/

#pragma once

#include "sputnik.h"
#include "unitTest.h"

/*******************************
* TEST Sputnik
* A friend class for Sputnik which contains the Sputnik unit tests
********************************/
class TestSputnik : public UnitTest
{
public:
   void run()
   {
      // Constructor
      construct_default();

      // Accessors
      getName();

      // Orientation
      updateOrientation();

      // Draw
      draw();

      report("Sputnik");
   }

private:
   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   none
    * output:  name=="Sputnik"
    *********************************************/
   void construct_default();

   /*********************************************
    * name:    GET NAME
    * input:   none
    * output:  getName()=="Sputnik"
    *********************************************/
   void getName();

   /*********************************************
    * name:    UPDATE ORIENTATION
    * input:   position=(0,1000)
    * output:  angle==270°
    *********************************************/
   void updateOrientation();

   /*********************************************
    * name:    DRAW
    * input:   any state
    * output:  no crash, sprite rendered correctly
    *********************************************/
   void draw();
};