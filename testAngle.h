/***********************************************************************
* Header File:
*    Test Angle : Test the Angle class
* Author:
*    Natalia Navarrete, Diego Estrada
* Summary:
*    All the unit tests for Angle
************************************************************************/

#pragma once

#include "angle.h"
#include "unitTest.h"

/*******************************
* TEST Angle
* A friend class for Angle which contains the Angle unit tests
********************************/
class TestAngle : public UnitTest
{
public:
   void run()
   {
      // Constructor
      construct_default();

      // Setters
      setDegrees();
      setRadians();
      setFromRadians();

      // Getters
      getDegrees();
      getRadians();

      // Normalization
      normalizeAbove360();
      normalizeNegative();

      report("Angle");
   }

private:
   /*********************************************
   * name:    DEFAULT CONSTRUCTOR
   * input:   none
   * output:  degrees=0, radians=0
   *********************************************/
   void construct_default();

   /*********************************************
   * name:    SET DEGREES
   * input:   degrees=180
   * output:  getDegrees()==180
   *********************************************/
   void setDegrees();

   /*********************************************
   * name:    SET RADIANS
   * input:   radians=M_PI
   * output:  getRadians()==M_PI
   *********************************************/
   void setRadians();

   /*********************************************
   * name:    SET FROM RADIANS
   * input:   atan2(-1,0)
   * output:  getDegrees()==270
   *********************************************/
   void setFromRadians();

   /*********************************************
   * name:    GET DEGREES
   * input:   degrees set
   * output:  getDegrees() returns input
   *********************************************/
   void getDegrees();

   /*********************************************
   * name:    GET RADIANS
   * input:   radians set
   * output:  getRadians() returns input
   *********************************************/
   void getRadians();

   /*********************************************
   * name:    NORMALIZE ABOVE 360°
   * input:   degrees=450
   * output:  getDegrees()==90
   *********************************************/
   void normalizeAbove360();

   /*********************************************
   * name:    NORMALIZE NEGATIVE
   * input:   degrees=-90
   * output:  getDegrees()==270
   *********************************************/
   void normalizeNegative();
};
